#include <thread>

#include <opencv/cv.hpp>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>

#include "socket_server.cpp"
#include "socket_client.cpp"

int type, rows, cols;
size_t size;

int main(int argc, char** argv)
{
  cv::VideoCapture cap;

  Socket_client socket_client("/tmp/socket.video.smass");

  cv::namedWindow("ClientVideo", 1);
  while(1) {
    unsigned char* data2;
    while(!socket_client.read(data2));

    cv::Mat frame2(720, 1280, CV_8UC3, data2);
    imshow("ClientVideo", frame2);

    delete[] data2;

    if (cv::waitKey(30) >= 0) break;
  }
}
