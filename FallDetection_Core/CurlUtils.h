#include <curl/curl.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>

using namespace cv;
using namespace std;

#ifndef CURLUTILS
#define CURLUTILS

class CurlUtils
{
public:
	static bool curlImg(char* imgURL, Mat& dst, int timeOut = 10);
private:
	static size_t _writeImgData(char *ptr, size_t size, size_t nmemb, void *userData);
};

#endif