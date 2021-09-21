#include <iostream>
#include <functional>
#include <exception>
#include "helpers/threadpoolwraper.h"
#include "helpers/facesaver.h"
#include "helpers/help_functions.h"
#include "include/facedetector.h"
using namespace std;
int main(int argc, char *argv[])
{
    std::string root_path;

    if(argc==1){
        std::cout<<"Please add root directory\n";
        return 0;
    }
    else{
        root_path=argv[1];
    }
    if(!boost::filesystem::exists(root_path)){
        std::cout<<"Root directory: "<<root_path<<" not exists\n";
        return 0;
    }

    FaceSaver face_writer(root_path+"/JSON.json");
    std::mutex mute_all_faces;
    std::vector<std::pair<std::string,std::vector<cv::Rect>>> all_facec;
    const int batch_size=20;
    all_facec.reserve(batch_size);
    ThreadPoolWraper pool(batch_size);
    for( auto &path: boost::filesystem::recursive_directory_iterator(root_path))
    {
        std::string extention=boost::filesystem::extension(path);
        std::for_each(std::begin(extention),
                      std::end(extention),
                      [](char &c){c=std::tolower(c);});
        if (extention==".jpg" || extention==".jpeg"){
            if(!pool.isFull()){
                pool.addFunction([&all_facec,path,&mute_all_faces]()
                {
                    try
                    {
                        std::string image_path=path.path().string();
                        cv::Mat image=cv::imread(image_path);
                        auto faces=findFace_dnn_caffee(image);
                        mute_all_faces.lock();
                        all_facec.push_back({path.path().string(),faces});
                        mute_all_faces.unlock();
                        blur_face(image,faces);
                        cv::resize(image,image,cv::Size(),0.5,0.5);
                        cv::imwrite(image_path+"_blured.png",image);
                        std::cout<<"For image: "<<image_path<<" find "<<faces.size()<<" faces\n";

                    }  catch (const std::exception &e)
                    {
                        // do nothing
                    }

                });
            }
            else
            {
                pool.process();
                face_writer.writeBatch(all_facec);
                all_facec.clear();
            }
        }
    }
    pool.process();
    std::cerr<<"Complite!\n";
    return 0;
}
