#include "facesaver.h"


FaceSaver::FaceSaver(const std::string &json_path):json_path_m(json_path){
    if(!boost::filesystem::exists((json_path_m))){
        std::ofstream file(json_path_m);
    }
}

void FaceSaver::writeBatch(const std::vector<std::pair<std::string, std::vector<cv::Rect> > > &faces)
{
    std::ofstream json(json_path_m,std::ios::app);
    for(const auto & f:faces){
        std::vector<std::string> rect_as_string;
        std::transform(f.second.begin(),f.second.end(),std::back_inserter(rect_as_string),[this](const cv::Rect &r){return this->convertRectToString(r);});
        std::string joined_bboxes=boost::algorithm::join(rect_as_string,", ");
        json<<"{\n";
        json<<"\"image_id\": \""<<f.first<<"\",\n";
        json<<"\"faces\": [ ";
        json<<joined_bboxes;
        json<<" ]\n}\n\n";
    }
}

std::string FaceSaver::convertRectToString(const cv::Rect &rect){
    std::stringstream ss;
    ss<<"["<<rect.x<<", "<<rect.y<<", "<<rect.x+rect.width<<", "<<rect.y+rect.height<<"]";
    return ss.str();
}
