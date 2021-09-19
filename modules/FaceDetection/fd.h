#pragma once
#include <string>
#include <opencv2/opencv.hpp>
#include<iostream>
#include <vector>

//#if defined(_WIN32) || defined(_WIN64)

//  #define MYLIB_EXPORT __declspec(dllexport)
//  #define MYLIB_IMPORT __declspec(dllimport)

//#else
//  #define MYLIB_EXPORT __attribute__((visibility("default")))
//  #define MYLIB_IMPORT __attribute__((visibility("default")))
//  #define MYLIB_HIDDEN __attribute__((visibility("hidden")))
//#endif

//void MYLIB_EXPORT foo_fd();

std::vector<cv::Rect> findFace(std::string path, int resize_size=0);
std::vector<cv::Rect> findFace_dnn_caffee(std::string path, int resize_size=0);
std::vector<cv::Rect> findFace_dnn_tensor(std::string path, int resize_size=0);
std::vector<cv::Rect> convert_to_rect(const cv::Mat &pred,int frameWidth,int frameHeight, float threshold=0.5 );


//#ifndef _LIBRARY_H_
//#define _LIBRARY_H_

//#if defined(_WIN32) || defined(_WIN64)

//  #define MYLIB_EXPORT __declspec(dllexport)
//  #define MYLIB_IMPORT __declspec(dllimport)

//#else
//  #define MYLIB_EXPORT __attribute__((visibility("default")))
//  #define MYLIB_IMPORT __attribute__((visibility("default")))
//  #define MYLIB_HIDDEN __attribute__((visibility("hidden")))
//#endif

//struct /*MYLIB_EXPORT*/ sLibrary

//{
//  void print_info();
//};


//#endif /* _LIBRARY_H_ */
