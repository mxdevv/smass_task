#include <thread>

#include <opencv/cv.hpp>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>

#include "socket_server.cpp"
#include "socket_client.cpp"
#include "cv_video_info.h"

int main()
{
  Socket_client socket_client("/tmp/socket.video.smass");

  cv_video_info* info;
  unsigned char* raw;
  while(!socket_client.read(raw));
  info = (cv_video_info*)raw;
  if (info->type != CV_8UC3) {
    std::cerr << "Server is not broadcasting from the beginning of stream."
                 " Restart the server." << std::endl;
    exit(-1);
  }

  cv::namedWindow("ClientVideo", 1);

  unsigned char* data;
  while(1) {
    while(!socket_client.read(data));

    cv::Mat frame(info->cols, info->rows, info->type, data);
    imshow("ClientVideo", frame);

    delete[] data;

    if (cv::waitKey(30) >= 0) break;
  }
}
