The project is tested on Windows and Linux (with all necessary libraries pre-installed manually) 

Project structure:
 - dataset      -> the directory with test images 
 - dll          -> the directory with dianmic libraries 
 - facedetector -> the source directory for the face search function
 - helpers      -> the source directory for the helper classes
 - include      -> the directory with include files
 - test_image   -> the directory with test images for Gtest
 - weights      -> the directory with weights of neural network 


List of required libraries:
 - OpenCV
 - Boost
 - Gtest

For windows, the download of the necessary libraries can be done in Vcpkg (https://github.com/microsoft/vcpkg). Below is the script for automatic installation of all dependencies.   

        > git clone https://github.com/microsoft/vcpkg
        > cd vcpkg
        > .\vcpkg\bootstrap-vcpkg.bat
        > vcpkg install opencv:x64-windows
        > vcpkg install boost:x64-windows
        > vcpkg install gtest:x64-windows

There is no script for installing all dependencies for Linux. Unfortunately, I don't know Linux that well. 


