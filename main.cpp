#include <iostream>
#include "./modules/FaceDetection/fd.h"
#include <opencv2/opencv.hpp>
#include <boost/filesystem.hpp>
#include <set>
#include <algorithm>
#include "watcher.h"
using namespace std;
//#include "./dll/simpledll/fd.h"
//#include "./dll/fd/fd.h"

//int main()
//{
//    foo_dll(5);
//    bar("fack");
//    std::cout<<"From main int->"<<foo_int();
//    return 0;
//}

std::set<std::string> convinient_extentions{".jpg",".png"};
std::string root_path="D:\\temp\\dataset_f";
void save_image(std::vector<cv::Rect> bboxes, cv::Mat& image, std::string path="D:\\temp\\results\\", std::string title=""){
    static int counter=0;
    for (auto &r:bboxes)
    {
        cv::rectangle(image,r,cv::Scalar(255,0,0),5);
    }
    cv::imwrite(path+std::to_string(counter++)+title+"_"+ ".jpg",image);
}



int main_(int argc, char *argv[])
{



    Watcher w1("Haar");
    Watcher w2("Caffe");
    Watcher w3("Tensor");
    std::set<std::string> convinient_extentions{".jpg",".png"};
    std::string root_path="D:\\temp\\dataset";
    std::cout<<"Path is excistt->"<<boost::filesystem::exists(root_path)<<"\n";
    for( auto &path: boost::filesystem::recursive_directory_iterator(root_path)){
        std::string extention=boost::filesystem::extension(path);
        std::for_each(std::begin(extention),
                      std::end(extention),
                      [](char &c){c=std::tolower(c);});
        if (convinient_extentions.find(extention)!=convinient_extentions.end()){
            std::cout<<"Path is ->"<<path<<"\n";

            w1.start();
            auto bboxes=findFace(path.path().string(),300);
            w1.stop();
//            std::cerr<<"Haar face size->"<<bboxes.size()<<" _ ";

//            w2.start();
//            auto bboxes_dnn=findFace_dnn_caffee(path.path().string());
//            w2.stop();
//            std::cerr<<"Caffe dnn face size->"<<bboxes_dnn.size()<<" _ ";

//            w3.start();
//            auto bboxes_dnn_tensor=findFace_dnn_tensor(path.path().string());
//            w3.stop();
//            std::cerr<<"Caffe dnn face size->"<<bboxes_dnn_tensor.size()<<"\n";



//            auto im = cv::imread(path.path().string());
//            save_image(bboxes,im.clone(),"D:\\temp\\results\\","haar");
//            save_image(bboxes_dnn,im.clone(),"D:\\temp\\results\\","caffe");
//            save_image(bboxes_dnn_tensor,im.clone(),"D:\\temp\\results\\","tensor");
        }
//        break;
    }
    auto r=w1.release();
    std::cout<<"Ellapsed time->_"<<w1.release()<<"_ms\n";
    std::cout<<"Ellapsed time->_"<<w2.release()<<"_ms\n";
    std::cout<<"Ellapsed time->_"<<w3.release()<<"_ms\n";

//    std::cerr<<"All time is ->"<<std::chrono::duration_cast<std::chrono::seconds>( w.release()).count()<<'\n';


//    auto s=FaceDetection::getString();
//    std::cout<<"First lint->"<<s<<std::endl;
//    FaceDetection::findFace("D:\\temp\\face1.jpg");
//    boost::filesystem::path p("D:\\temp");
//    std::cerr<<"Path is excistt->"<<boost::filesystem::exists(p)<<"\n";

    cout << "Hello World!" << endl;
    return 0;
}

#include <thread>
#include <boost/asio/thread_pool.hpp>
#include <boost/asio/post.hpp>
#include <functional>
#include <exception>
void foo2()
{

}

class myThreadPool{
public:
    explicit myThreadPool(int batch_size=20):pool_size_m(0), batch_size_m(batch_size)
    {
        pool_m=new boost::asio::thread_pool(8);
    }
    bool isFull()
    {
        return pool_size_m == batch_size_m;
    }
    void addFunction(std::function<void()> f)
    {
        boost::asio::post(*pool_m,f);
        pool_size_m++;
    }
    void process()
    {
        pool_m->join();
        pool_size_m=0;
        delete  pool_m;
        pool_m=new boost::asio::thread_pool(8);
    }
    boost::asio::thread_pool *pool_m;
private:
    int pool_size_m;
    const int batch_size_m;
};

void foo()
{
    for(int i=0;i<10;++i){
        auto f=[i](){
            std::cerr<<"Fth->"<<std::to_string(i)<<" stert->\n";
            std::this_thread::sleep_for(2000ms);
        };
    };

}


void blur_face(cv::Mat& image, std::vector<cv::Rect>& bboxes)
{
    for ( const auto &bbox: bboxes){
        cv::blur(image(bbox),image(bbox),cv::Size(5,5));
    }
}




#include <tuple>
int main(int argc, char *argv[])
{

    std::mutex mute_all_faces;

    std::vector<std::pair<std::string,std::vector<cv::Rect>>> all_facec;


    Watcher w1("Haar");
    const int batch_size=10;
    myThreadPool pool(batch_size);

    for( auto &path: boost::filesystem::recursive_directory_iterator(root_path)){
        w1.start();
        std::string extention=boost::filesystem::extension(path);
        std::for_each(std::begin(extention),
                      std::end(extention),
                      [](char &c){c=std::tolower(c);});
        if (convinient_extentions.find(extention)!=convinient_extentions.end()){
//            auto bboxes=findFace(path.path().string(),300);
//            std::cerr<<"bboxes size->"<<bboxes.size()<<"\n";
            if(!pool.isFull()){
                pool.addFunction([&all_facec,path,&mute_all_faces](){
//                    std::cerr<<"Path->"<<path.path().string() <<" ";
                    auto faces=findFace_dnn_tensor(path.path().string());
                    mute_all_faces.lock();
                    all_facec.push_back({path.path().string(),faces});
                    mute_all_faces.unlock();

                    std::cerr<<"Path->"<<path.path().string() <<" "<<"find faces->"<<faces.size()<<"\n";
                });
            }
            else{
                std::cerr<<"---------From else\n";
                pool.process();
            }
        }
        w1.stop();
    }
    pool.process();
//    auto r=w1.release();
    std::cout<<"Ellapsed time->_"<<w1.release()<<"_ms\n";
    std::cerr<<"All faces->"<<all_facec.size()<<"\n";
    std::cerr<<"hellooooooooo!!!!\n";
    return 0;
}
