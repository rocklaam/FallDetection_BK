#include "MHIProcess.h"

//Properties
vector<Mat> MHIProcess::_buf = vector<Mat>(2);
int MHIProcess::_last = 0;
Mat MHIProcess::_mhi = Mat();

//Methods
void MHIProcess::updateMHI(const Mat& img, Mat& dst, int diff_threshold, float& sumHist){
	double timestamp = (double)clock() / CLOCKS_PER_SEC; // get current time in seconds
	Size size = img.size();
	int idx1 = _last;
	Rect comp_rect;
	// allocate images at the beginning or reallocate them if the frame size is changed
	if (_mhi.size() != size)
	{
		_mhi = Mat::zeros(size, CV_32F);
		_buf[0] = Mat::zeros(size, CV_8U);
		_buf[1] = Mat::zeros(size, CV_8U);
	}

	cvtColor(img, _buf[_last], COLOR_BGR2GRAY); // convert frame to grayscale

	int idx2 = (_last + 1) % 2; // index of (_last - (N-1))th frame
	_last = idx2;

	Mat silh = _buf[idx2];
	absdiff(_buf[idx1], _buf[idx2], silh); // get difference between frames

	threshold(silh, silh, diff_threshold, 1, THRESH_BINARY); // and threshold it
	updateMotionHistory(silh, _mhi, timestamp, MHI_DURATION); // update MHI
	_mhi.convertTo(dst, CV_8U, 255. / MHI_DURATION, (MHI_DURATION - timestamp)*255. / MHI_DURATION);// convert MHI to 8u image
	Mat1f bufVect;
	reduce(dst, bufVect, 0, CV_REDUCE_SUM);
	reduce(bufVect, bufVect, 1, CV_REDUCE_SUM);
	bufVect /= 255;
	sumHist = bufVect.at<float>(0, 0);
}