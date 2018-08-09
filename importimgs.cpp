#include <curl/curl.h>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

size_t write_data(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    vector<uchar> *stream = (vector<uchar>*)userdata;

    size_t count = size * nmemb;
    stream->insert(stream->end(), ptr, ptr + count);

    return count;
}

Mat curlImg (const char *url, int timeout=10)
{
    Mat img;
    vector<uchar> stream;
    CURL *curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &stream);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (res == 0 && !stream.empty()) {
        cout<<"Got image "<<url<<"\n";
        img = imdecode(stream, IMREAD_GRAYSCALE);
    } else {
        cout<<"CURL res: "+to_string(res)+"\n";
    }

    return img; 
}


int main(int argc, char const *argv[])
{
    ifstream fileStream;
    fileStream.open("plantneg/plant-urls.txt");
    
    int count = 0;
    vector<Mat> images;

    ofstream infoOut("bg_plant.lst");

    while(!fileStream.eof())
    {
        string line;

        count++;
        getline(fileStream, line);

        line.erase(line.find_last_not_of("\n\r") + 1);
        line.erase(0, line.find_first_not_of("\n\r"));

        Mat image = curlImg(line.c_str(), 10);

        if (image.empty()) {
            cout<<"Failed to get: "<<line<<"\n";
            continue;
        }

        const int MAX_DIM = 128;
        Size size;

        float ratio = (float)image.rows / (float)image.cols;
        if (image.rows > image.cols) {
            size = Size(MAX_DIM, (int)(MAX_DIM / ratio));
        } else {
            size = Size((int)(MAX_DIM * ratio), MAX_DIM);
        }

        resize(image, image, size);
        string fileName = "plantneg/p_"+to_string(count)+".png";

        imwrite(fileName, image);
        infoOut<<fileName<<"\n";
    }

    infoOut.close();

    cout<<"Done!\n";

    return 0;
}
