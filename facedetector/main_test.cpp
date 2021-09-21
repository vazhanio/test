#include <opencv2/imgproc/imgproc.hpp>
#include <gtest/gtest.h>
#include "facedetector.h"

TEST(test_facedetector_one_face, face)
{
    auto im=cv::imread("./test_image/one_face.jpg");
    auto result=findFace_dnn_caffee(im);

    ASSERT_EQ(result.size(), 1);
}
TEST(test_facedetector_two_face, face)
{
    auto im=cv::imread("./test_image/two_face.jpg");
    auto result=findFace_dnn_caffee(im);

    ASSERT_EQ(result.size(), 2) ;
}

TEST(test_facedetector_no_face, no_face)
{
    auto im=cv::imread("./test_image/no_face.jpg");
    auto result=findFace_dnn_caffee(im);

    ASSERT_EQ(result.size(), 0) ;
}
int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
