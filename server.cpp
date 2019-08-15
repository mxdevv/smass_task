#include <thread>

#include <opencv/cv.hpp>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>

#include "socket_server.cpp"
#include "socket_client.cpp"
#include "cv_video_info.h"

int size;
int distributor = 0;

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

  while(1) {
    cv::Mat frame;
    cap >> frame;

    unsigned char* data = frame.data;
    size = frame.total() * frame.elemSize();

    if (distributor ^= 1) {
      std::thread([&] {
        while(!socket_server.write(data, size));
      }).join();
    } else {
      std::thread([&] {
        while(!socket_server.write(data, size));
      }).join();
    }
  }
}
