#ifndef FACESAVER_H
#define FACESAVER_H

#include <boost/filesystem.hpp>
#include <opencv2/opencv.hpp>
#include<boost/algorithm/string/join.hpp>
#include<string>
#include<vector>
#include<algorithm>
class FaceSaver
{
public:
    explicit FaceSaver(const std::string &json_path);
    void writeBatch(const  std::vector<std::pair<std::string,std::vector<cv::Rect>>> &faces);
private:
    std::string convertRectToString(const cv::Rect& rect);
private:
    std::string json_path_m;
};

#endif // FACESAVER_H
