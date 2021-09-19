#include "fd.h"
#include <iostream>
#include <thread>
std::mutex mute_net;
//void sLibrary::print_info()
//{
//  std::cout << "Hello from library" << std::endl;
//}


auto finder=cv::CascadeClassifier("D:\\temp\\haarcascade_frontalface_default.xml");
const std::string caffeConfigFile = "D:/temp/deploy.prototxt";
const std::string caffeWeightFile = "D:/temp/res10_300x300_ssd_iter_140000_fp16.caffemodel";

const std::string tensorflowConfigFile = "D:/temp/opencv_face_detector.pbtxt";
const std::string tensorflowWeightFile = "D:/temp/opencv_face_detector_uint8.pb";
const cv::Scalar meanVal(104.0, 177.0, 123.0);
auto net_caffe = cv::dnn::readNetFromCaffe(caffeConfigFile, caffeWeightFile);
cv::dnn::Net net_tensor = cv::dnn::readNetFromTensorflow(tensorflowWeightFile, tensorflowConfigFile);
int size=300;
std::vector<cv::Rect> findFace(std::string path, int resize_size){
    auto im=cv::imread(path);

    if(resize_size){
        cv::resize(im,im,cv::Size(resize_size,resize_size));
    }
    cv::cvtColor(im,im,cv::COLOR_BGR2GRAY);

    std::vector<cv::Rect>faces;
    finder.detectMultiScale(im,faces);
    return faces;
}

std::vector<cv::Rect> findFace_dnn_caffee(std::string path, int resize_size){
//    auto net_caffe = cv::dnn::readNetFromCaffe(caffeConfigFile, caffeWeightFile);
    auto im=cv::imread(path);
    int frameHeight = im.rows;
    int frameWidth = im.cols;
    cv::Mat inputBlob = cv::dnn::blobFromImage(im, 1.0, cv::Size(300, 300), meanVal, false, false);
   mute_net.lock();
    net_caffe.setInput(inputBlob, "data");
    cv::Mat detection = net_caffe.forward("detection_out");
    mute_net.unlock();
    cv::Mat detectionMat(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());
    return convert_to_rect(detectionMat,frameWidth,frameHeight);
}

std::vector<cv::Rect> findFace_dnn_tensor(std::string path, int resize_size){

    auto im=cv::imread(path);
    int frameHeight = im.rows;
    int frameWidth = im.cols;

    cv::Mat inputBlob = cv::dnn::blobFromImage(im, 1.0, cv::Size(300, 300), meanVal, true, false);
    mute_net.lock();
    net_tensor.setInput(inputBlob, "data");
    cv::Mat detection = net_tensor.forward("detection_out");
    mute_net.unlock();
    cv::Mat detectionMat(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());
    return convert_to_rect(detectionMat,frameWidth,frameHeight);
}

std::vector<cv::Rect> convert_to_rect(const cv::Mat &pred, int frameWidth, int frameHeight, float threshold)
{
    std::vector<cv::Rect> bboxes;
    for(int i = 0; i < pred.rows; i++)
    {
        float confidence = pred.at<float>(i, 2);

        if(confidence > threshold)
        {
            int x1 = static_cast<int>(pred.at<float>(i, 3) * frameWidth);
            int y1 = static_cast<int>(pred.at<float>(i, 4) * frameHeight);
            int x2 = static_cast<int>(pred.at<float>(i, 5) * frameWidth);
            int y2 = static_cast<int>(pred.at<float>(i, 6) * frameHeight);
            bboxes.push_back(cv::Rect(cv::Point(x1,y1),cv::Point(x2,y2)));

        }
    }
    return bboxes;
}

