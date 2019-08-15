#include <thread>

#include <opencv/cv.hpp>
#include <opencv/highgui.h>

#include "socket_server.cpp"
#include "socket_client.cpp"

int type, rows, cols;
size_t size;

int main(int argc, char** argv)
{
  cv::VideoCapture cap;
  if (argc >= 2) {
    cap.open(argv[1]);
  } else {
    cap.open("sample.mp4");
  }

  Socket_server socket_server("/tmp/socket.video.smass");
  Socket_client socket_client("/tmp/socket.video.smass");

  cv::namedWindow("Video", 1);
  while(1) {
    cv::Mat frame;
    cap >> frame;

    unsigned char* data = frame.data;
    type = frame.type();
    rows = frame.rows;
    cols = frame.cols;
    size = frame.total() * frame.elemSize();

    std::thread([&] {
      socket_server.write(data, size);
    }).detach();

    unsigned char* data2;
    while(!socket_client.read(data2));

    cv::Mat frame2(rows, cols, type, data2);
    imshow("Video", frame2);

    delete[] data2;

    if (cv::waitKey(30) >= 0) break;
  }
}
