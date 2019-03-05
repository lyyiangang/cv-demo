#include <opencv2/videoio/videoio.hpp> // Video write
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <easylogging++.h>

INITIALIZE_EASYLOGGINGPP

int main(int argc, char **argv)
{
    START_EASYLOGGINGPP(argc, argv);
    el::Loggers::addFlag(el::LoggingFlag::ColoredTerminalOutput);

    const int WIDTH = 1920, HEIGHT = 1080;
    //ok
    //cv::VideoCapture irVCap("nvcamerasrc sensor-id=0 ! video/x-raw(memory:NVMM), width=(int)640, height=(int)480, format=(string)I420, framerate=(fraction)30/1 ! nvvidconv flip-method=2 ! video/x-raw, format=(string)I420 ! videoconvert ! video/x-raw, format=(string)BGR ! appsink", cv::CAP_GSTREAMER);
    //cv::VideoCapture irVCap("nvcamerasrc sensor-id=0 ! 'video/x-raw(memory:NVMM),width=1920, height=1080, framerate=30/1, format=NV12' ! nvoverlaysink -ev");
    //cv::VideoCapture irVCap("nvcamerasrc sensor-id=0 ! video/x-raw(memory:NVMM), width=(int)1280, height=(int)720, format=(string)I420, framerate=(fraction)30/1 ! nvvidconv flip-method=0  ! video/x-raw, format=(string)I420 ! videoconvert ! video/x-raw, format=(string)BGR ! appsink", cv::CAP_GSTREAMER);
    cv::VideoCapture irVCap;
    //open with nvidia video api
    irVCap.open("nvcamerasrc sensor-id=0 ! video/x-raw(memory:NVMM), width=(int)1280, height=(int)720, format=(string)I420, framerate=(fraction)30/1 ! nvvidconv flip-method=0  ! video/x-raw, format=(string)I420 ! videoconvert ! video/x-raw, format=(string)BGR ! appsink");
    if(!irVCap.isOpened())
        LOG(FATAL)<<"can not open camera";
    // irVCap.set(cv::CAP_PROP_SETTINGS, -1);
    // irVCap.set(cv::CAP_PROP_FRAME_WIDTH, WIDTH);
    // irVCap.set(cv::CAP_PROP_FRAME_HEIGHT, HEIGHT);
    cv::Mat irFrame;
    while (true)
    {
        {
            TIMED_SCOPE(obj, "grap frame");
            irVCap >> irFrame;
        }
        if(irFrame.empty())
            break;
        cv::imshow("test", irFrame);
        int keycode = cv::waitKey(10) % 256;
        if (keycode == 'q')
            break;
    }
}