// #include <opencv2/core/core.hpp>
// #include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.hpp>
#include <iostream>

int main(int argc, char** argv) {
    cv::Mat image;
    image = cv::imread("pond_water_gray.png", cv::IMREAD_COLOR);

    if (!image.data) {
        std::cout << "Could not open or find the image" << std::endl;
        return -1;
    }

    cv::namedWindow("Open CV display window", cv::WINDOW_AUTOSIZE);
    cv::imshow("Display window", image);

    cv::waitKey(0);
    return 0;
}