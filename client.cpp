#include <thread>

#include <opencv/cv.hpp>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>

#include "socket_server.cpp"
#include "socket_client.cpp"
#include "frame_info.cpp"

int main()
{
  Socket_client socket_client("/tmp/socket.video.smass");

  cv::namedWindow("ClientVideo", 1);

  Frame_info* info;
  unsigned char* data, * raw;
  while(1) {
    while(!socket_client.read(raw));
    info = (Frame_info*)raw;
    if (!info->checking()) {
      delete[] raw;
      continue;
    }
    while(!socket_client.read(data));

    cv::Mat frame(info->cols, info->rows, info->type, data);
    imshow("ClientVideo", frame);

    delete[] data;
    delete[] raw;

    if (cv::waitKey(30) >= 0) break;
  }
}
