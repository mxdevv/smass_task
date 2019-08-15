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

int main(int argc, char** argv)
{
  if (argc < 2) {
    std::cerr << "Please, specify the path to the file." << std::endl;
    exit(-1);
  }
  cv::VideoCapture cap(argv[1]);

  Socket_server socket_server("/tmp/socket.video.smass");

  cv_video_info info = { CV_8UC3, (int)cap.get(CV_CAP_PROP_FRAME_WIDTH),
      (int)cap.get(CV_CAP_PROP_FRAME_HEIGHT) };

  while(!socket_server.write((unsigned char*)&info, sizeof(info)));

  std::thread([&] {
    while(1) {
      std::unique_lock<std::mutex> lock(m);
      cond.wait(lock, []{return readed && writer_i == 0;});
      while(!socket_server.write(data, size));
      writed = true;
      readed = false;
      cond.notify_all();
    }
  }).detach();

  //  дублирующий код, исправить !
  std::thread([&] {
    while(1) {
      std::unique_lock<std::mutex> lock(m);
      cond.wait(lock, []{return readed && writer_i == 1;});
      while(!socket_server.write(data, size));
      writed = true;
      readed = false;
      cond.notify_all();
    }
  }).detach();

  std::thread([&] {
    while(1) {
      std::unique_lock<std::mutex> lock(m);
      writed = false;

      cv::Mat frame;
      cap >> frame;

      data = frame.data;
      size = frame.total() * frame.elemSize();

      readed = true;
      writer_i ^= 1;
      cond.notify_all();
      cond.wait(lock, []{return writed;});
    }
  }).join();
}
