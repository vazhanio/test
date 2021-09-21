#ifndef HELP_FUNCTIONS_H
#define HELP_FUNCTIONS_H
#include<opencv2/opencv.hpp>
#include <vector>
void blur_face(cv::Mat& image, std::vector<cv::Rect>& bboxes)
{
    for ( const auto &bbox: bboxes){
        int kerne_size=std::min(bbox.height,bbox.width);
        kerne_size=(kerne_size/8)+5;
        cv::blur(image(bbox),image(bbox),cv::Size(kerne_size,kerne_size));
    }
}
#endif // HELP_FUNCTIONS_H
