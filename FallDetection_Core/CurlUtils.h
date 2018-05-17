#include <curl/curl.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>

#include "Config.h"

using namespace cv;
using namespace std;

#ifndef CURLUTILS
#define CURLUTILS

class CurlUtils
{
public:
	static bool curlImg(char* imgURL, Mat& dst, int timeOut = 10);
	static bool curlURLWithData(char* uRL, curl_slist* header, char* stringData, bool isPOSTCurl, int timeOut = 100);

private:
	static size_t _readData(void *dest, size_t size, size_t nmemb, void *userData);
	static size_t _writeImgData(char *ptr, size_t size, size_t nmemb, void *userData);

	struct WriteThis
	{
		const char *readptr;
		size_t sizeleft;
	};
};

#endif