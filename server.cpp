#include <array>
#include <thread>
#include <mutex>
#include <condition_variable>

#include <unistd.h>

#include <opencv/cv.hpp>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>

#include "socket_server.cpp"
#include "socket_client.cpp"
#include "cv_video_info.h"

int size;
unsigned char* data;
std::mutex m;
std::condition_variable cond;
bool readed = false;
bool writed = false;
int writer_i = 0;

void write_frame(Socket_server& socket_server, int id)
{
  while(1) {
    std::unique_lock<std::mutex> lock(m);
    cond.wait(lock, [&id]{return readed && writer_i == id;});
    while(!socket_server.write(data, size));
    writed = true;
    readed = false;
    cond.notify_all();
  }
}

void get_frame(cv::VideoCapture& capture)
{
  while(1) {
    std::unique_lock<std::mutex> lock(m);
    writed = false;

    cv::Mat frame;
    capture >> frame;

    data = frame.data;
    size = frame.total() * frame.elemSize();

    readed = true;
    writer_i ^= 1;
    cond.notify_all();
    cond.wait(lock, []{return writed;});
  }
}

int main(int argc, char** argv)
{
  if (argc < 2) {
    std::cout << "Please, specify the path to the file." << std::endl;
    exit(-1);
  }
  cv::VideoCapture capture(argv[1]);

  Socket_server socket_server("/tmp/socket.video.smass");

  cv_video_info info = { CV_8UC3, (int)capture.get(CV_CAP_PROP_FRAME_WIDTH),
      (int)capture.get(CV_CAP_PROP_FRAME_HEIGHT) };

  while(!socket_server.write((unsigned char*)&info, sizeof(info)));

  std::array<std::thread, 3> threads {
      std::thread { write_frame, std::ref(socket_server), 0}, 
      std::thread { write_frame, std::ref(socket_server), 1},
      std::thread { get_frame, std::ref(capture) } };

  for(std::thread& thr : threads) {
    thr.join();
  }
}
