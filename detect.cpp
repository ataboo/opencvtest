#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;

int main(int argc, char const *argv[])
{
    CascadeClassifier blobCascade;
    if (!blobCascade.load("data/cascade.xml")) {
        printf("Failed to load blob cascade!");
    }

    Mat img = imread("pond_water_gray.png", IMREAD_GRAYSCALE);

    std::vector<Rect> matches;
    Mat frame_gray;   

    // cvtColor(img, frame_gray, COLOR_BGR2GRAY);
    
    blobCascade.detectMultiScale(img, matches, 1.1, 6, 0 | CASCADE_SCALE_IMAGE, Size(24, 24), Size(96, 96));

    for(size_t i=0; i < matches.size(); i++) {
        Rect match = matches[i];

        Point center(match.x + match.width/2, match.y + match.height/2);
        ellipse(img, center, Size(match.width / 2, match.height / 2), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);
    }

    imshow("Showing", img);

    waitKey();

    return 0;
}