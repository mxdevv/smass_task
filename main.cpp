#include <opencv/cv.hpp>
#include <opencv/highgui.h>

void test3()
{
  cv::VideoCapture cap("sample_raw.avi"); 
  if(!cap.isOpened()) {
    printf("Open fail!\n");
  }

  cv::namedWindow("Video", 1);
  for(;;)
  {
    cv::Mat frame;
    cap >> frame;
    imshow("Video", frame);
    if (cv::waitKey(30) >= 0) break;
  }
  return;
}

void test2(int argc, char** argv)
{
  const char* filename = "sample.mp4";

  printf("[i] file: %s\n", filename);

  cvNamedWindow("original", CV_WINDOW_AUTOSIZE);

  CvCapture* capture = cvCreateFileCapture(filename);
  if (!capture) printf("cvCreateFileCapture() failed!\n");

  IplImage* frame = 0;

  while(1) {
    frame = cvQueryFrame(capture); 
    if (!frame) {
      break;
    }

    cvShowImage("original", frame);

    char c = cvWaitKey(33);
    if (c == 27) { // еESC
      break;
    }
  }

  cvReleaseCapture(&capture);
  cvDestroyWindow("original");
}

void test1()
{
  IplImage* image = 0;
  char filename[] = "sample.jpg";
  image = cvLoadImage(filename, 1);
  printf("[i] image: %s\n", filename);
  assert( image != 0 );
  cvNamedWindow( "image");
  cvShowImage( "image", image );
  cvWaitKey(0);
  cvReleaseImage(&image);
  cvDestroyAllWindows();
}

int main(int argc, char** argv)
{
  test1();
  test2(argc, argv);
  test3();
}
