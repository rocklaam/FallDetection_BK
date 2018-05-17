#include <curl/curl.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>

#include "Config.h"

using namespace cv;
using namespace std;

#pragma once 
#ifndef UTILS
#define UTILS

class Utils
{
public:
	static void displayCVImage(Mat img, char* windowName, HWND dialog, int pictureControlID);
private:
};

#endif