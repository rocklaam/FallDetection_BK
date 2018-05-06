#include <opencv2/optflow.hpp>

#include <ctime>

#include "Config.h"

using namespace cv;
using namespace std;
using namespace cv::motempl;

#ifndef MHIPROCESS
#define MHIPROCESS

class MHIProcess
{
public:
	static void updateMHI(const Mat& grayimg, Mat& dst, int diff_threshold, float& sumHist);
private:
	static vector < Mat > _buf;
	static int _last;
	static Mat _mhi;
};

#endif