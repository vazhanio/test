#include "facedetector.h"
#include <iostream>
#include <thread>
std::mutex mute_net;
const std::string caffeConfigFile = "./weights/deploy.prototxt";
const std::string caffeWeightFile = "./weights/res10_300x300_ssd_iter_140000_fp16.caffemodel";
const cv::Scalar meanVal(104.0, 177.0, 123.0);
auto net_caffe = cv::dnn::readNetFromCaffe(caffeConfigFile, caffeWeightFile);

std::vector<cv::Rect> findFace_dnn_caffee(const cv::Mat& im, int resize_size){

    int frameHeight = im.rows;
    int frameWidth = im.cols;
    cv::Mat inputBlob = cv::dnn::blobFromImage(im, 1.0, cv::Size(resize_size, resize_size), meanVal, false, false);
    mute_net.lock();
    net_caffe.setInput(inputBlob, "data");
    cv::Mat detection = net_caffe.forward("detection_out");
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
