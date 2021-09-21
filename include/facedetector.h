#pragma once
#include <string>
#include <opencv2/opencv.hpp>
#include<iostream>
#include <vector>

std::vector<cv::Rect> findFace_dnn_caffee(const cv::Mat &im, int resize_size=300);
std::vector<cv::Rect> convert_to_rect(const cv::Mat &pred,int frameWidth,int frameHeight, float threshold=0.5 );
