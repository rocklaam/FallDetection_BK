#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>

#include <iostream>
#include <sstream>

using namespace cv;
using namespace std;

#ifndef I_MOVINGOBJSEGMENT
#define I_MOVINGOBJSEGMENT

class I_MovingObjSegment
{
public:
	virtual void processVideo(char* videoFilename, char* windowName) = 0;
	virtual void processImage(char* fistFrameFilename) = 0;
private:
};

#endif