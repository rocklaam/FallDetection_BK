#include "Detector.h"

vector<Rect> Detector::detect(InputArray bluredImg)
{
	// Run the detector with default parameters. to get a higher hit-rate
	// (and more false alarms, respectively), decrease the hitThreshold and
	// groupThreshold (set groupThreshold to 0 to turn off the grouping completely).
	vector<Rect> found;
	if (m == Default)
		hog.detectMultiScale(bluredImg, found, 0, Size(4, 4), Size(32, 32), 1.05, 2, false);
	//hog.detectMultiScale(img, found, 0, Size(640, 480), Size(32, 32));
	else if (m == Daimler)
		hog_d.detectMultiScale(bluredImg, found, 0.5, Size(8, 8), Size(32, 32), 1.05, 2, true);
	return found;
}

void Detector::adjustRect(Rect & r) const
{
	// The HOG detector returns slightly larger rectangles than the real objects,
	// so we slightly shrink the rectangles to get a nicer output.
	r.x += cvRound(r.width*0.1);
	r.width = cvRound(r.width*0.8);
	r.y += cvRound(r.height*0.07);
	r.height = cvRound(r.height*0.8);
}

void Detector::calculateHuman(Mat & bluredImg, int & area)
{
	area = 0;
	vector<Rect> found = detect(bluredImg);
	if (found.size() > 0){
		adjustRect(found[0]);
		int theLargestIndx = 0;
		area = found[0].area();
		for (int i = 1; i < found.size(); i++)
		{
			adjustRect(found[i]);
			int a = found[i].area();
			if (a > area){
				area = found[i].area();
				theLargestIndx = i;
			}
		}
		rectangle(bluredImg, found[theLargestIndx].tl(), found[theLargestIndx].br(), cv::Scalar(0, 255, 0), 4);
	}
}