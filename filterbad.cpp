#include <opencv2/opencv.hpp>
#include <fstream>
#include <iostream>
#include <vector>

using namespace cv;

bool imgsMatch(Mat &img1, Mat &img2) {
    if (img1.rows != img2.rows || img1.cols != img2.cols) {
        return false;
    }

    Scalar sumScl = sum(img1 - img2);

    for (int channel=0; channel < img1.channels(); channel++) {
        if (sumScl[channel] != 0) {
            return false;
        }
    }

    return true;
}

int main(int argc, char const *argv[])
{
    std::vector<String> fileNames;
    std::vector<String> badImgNames;
    std::vector<Mat> badImgs;

    glob("bad/*.png", badImgNames, false);
    glob("plantneg/*.png", fileNames, false);

    for(auto badImgName : badImgNames) {
        badImgs.push_back(imread(badImgName, IMREAD_GRAYSCALE));
    }

    std::cout<<std::to_string(fileNames.size())<<" good imgs found.\n";
    std::cout<<std::to_string(badImgNames.size())<<" bad imgs found.\n";

    for(auto fileName : fileNames) {
        Mat img = imread(fileName, IMREAD_GRAYSCALE);

        for(auto badImg : badImgs) {
            if (imgsMatch(img, badImg)) {
                int status = remove(fileName.c_str());
                
                if (status == 0) {
                    std::cout<<"deleted: "<<fileName<<"\n";
                } else {
                    std::cout<<"failed to delete "<<fileName<<" with: "<<std::to_string(status)<<"\n";
                }

                break;
            }

        }
    }

    glob("plantneg/*.png", fileNames);

    std::cout<<std::to_string(fileNames.size())<<" imgs remaining.\n";

    std::ofstream bgOut("bg_plant.lst");
    for(auto fileName : fileNames) {
        bgOut<<fileName<<"\n";
    }

    bgOut.close();

    std::cout<<"done!\n";

    return 0;
}
