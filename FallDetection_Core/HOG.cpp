//// This file is part of OpenCV project.
//// It is subject to the license terms in the LICENSE file found in the top-level directory
//// of this distribution and at http://opencv.org/license.html
//
//#include "curl/curl.h" // has to go before opencv headers
//
//#include <opencv2/objdetect.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/imgproc.hpp>
//#include <opencv2/videoio.hpp>
//#include <iostream>
//#include <iomanip>
//
//using namespace cv;
//using namespace std;
//
//size_t write_data(char *ptr, size_t size, size_t nmemb, void *userdata)
//{
//	vector<uchar> *stream = (vector<uchar>*)userdata;
//	size_t count = size * nmemb;
//	stream->insert(stream->end(), ptr, ptr + count);
//	return count;
//}
//
////function to retrieve the image as cv::Mat data type
//Mat curlImg(const char *img_url, int timeout = 10)
//{
//	vector<uchar> stream;
//	CURL *curl = curl_easy_init();
//	curl_easy_setopt(curl, CURLOPT_URL, img_url); //the img url
//	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data); // pass the writefunction
//	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &stream); // pass the stream ptr to the writefunction
//	curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout); // timeout if curl_easy hangs, 
//	struct curl_slist *hs = NULL;
//	hs = curl_slist_append(hs, "Content-Type: image/jpeg");
//	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, hs);
//	CURLcode res = curl_easy_perform(curl); // start curl
//	curl_easy_cleanup(curl); // cleanup
//	return imdecode(stream, -1); // 'keep-as-is'
//}
//
//class Detector
//{
//	enum Mode { Default, Daimler } m;
//	HOGDescriptor hog, hog_d;
//public:
//	Detector() : m(Default), hog(), hog_d(Size(48, 96), Size(16, 16), Size(8, 8), Size(8, 8), 9)
//	{
//		hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
//		hog_d.setSVMDetector(HOGDescriptor::getDaimlerPeopleDetector());
//	}
//	void toggleMode() { m = (m == Default ? Daimler : Default); }
//	string modeName() const { return (m == Default ? "Default" : "Daimler"); }
//	vector<Rect> detect(InputArray img)
//	{
//		// Run the detector with default parameters. to get a higher hit-rate
//		// (and more false alarms, respectively), decrease the hitThreshold and
//		// groupThreshold (set groupThreshold to 0 to turn off the grouping completely).
//		vector<Rect> found;
//		if (m == Default)
//			hog.detectMultiScale(img, found, 0, Size(8, 8), Size(32, 32), 1.05, 2, false);
//			//hog.detectMultiScale(img, found, 0, Size(640, 480), Size(32, 32));
//		else if (m == Daimler)
//			hog_d.detectMultiScale(img, found, 0.5, Size(8, 8), Size(32, 32), 1.05, 2, true);
//		return found;
//	}
//	void adjustRect(Rect & r) const
//	{
//		// The HOG detector returns slightly larger rectangles than the real objects,
//		// so we slightly shrink the rectangles to get a nicer output.
//		r.x += cvRound(r.width*0.1);
//		r.width = cvRound(r.width*0.8);
//		r.y += cvRound(r.height*0.07);
//		r.height = cvRound(r.height*0.8);
//	}
//};
//
//static const string keys = "{ help h   |   | print help message }"
//"{ camera c | 0 | capture video from camera (device index starting from 0) }"
//"{ video v  |   | use video as input }";
//
//int main(int argc, char** argv)
//{
//	CommandLineParser parser(argc, argv, keys);
//	parser.about("This sample demonstrates the use ot the HoG descriptor.");
//	if (parser.has("help"))
//	{
//		parser.printMessage();
//		return 0;
//	}
//	int camera = 0;
//	string file = parser.get<string>("video");
//	if (!parser.check())
//	{
//		parser.printErrors();
//		return 1;
//	}
//
//	cout << "Press 'q' or <ESC> to quit." << endl;
//	cout << "Press <space> to toggle between Default and Daimler detector" << endl;
//	Detector detector;
//	VideoCapture cap(0);
//	Mat frame;
//	for (;;)
//	{
//		double timestamp = (double)clock() / CLOCKS_PER_SEC; // get current time in seconds
//		cap >> frame;
//		//frame = curlImg("http://192.168.0.222:8888/snapshot.cgi?loginuse=admin&loginpas=admin");
//		if (frame.empty())
//		{
//			cout << "Finished reading: empty frame" << endl;
//			break;
//		}
//		int64 t = getTickCount();
//		//resize(frame, frame, Size(frame.size().width / 2, frame.size().height / 2));
//		blur(frame, frame, Size(4, 4));
//		vector<Rect> found = detector.detect(frame);
//		t = getTickCount() - t;
//
//		// show the window
//		{
//			ostringstream buf;
//			buf << "Mode: " << detector.modeName() << " ||| "
//				<< "FPS: " << fixed << setprecision(1) << (getTickFrequency() / (double)t);
//			putText(frame, buf.str(), Point(10, 30), FONT_HERSHEY_PLAIN, 1.0, Scalar(0, 0, 255), 1);
//		}
//		if (found.size() > 0){
//			int theLargestArea = found[0].area();
//			int theLargestIndx = 0;
//			for (int i = 1; i < found.size(); i++)
//			{
//				if (found[i].area() > theLargestArea){
//					theLargestArea = found[i].area();
//					theLargestIndx = i;
//				}
//			}
//			detector.adjustRect(found[theLargestIndx]);
//			rectangle(frame, found[theLargestIndx].tl(), found[theLargestIndx].br(), cv::Scalar(0, 255, 0), 4);
//			cout << theLargestArea << endl;
//		}
//		imshow("People detector", frame);
//
//		// interact with user
//		const char key = (char)waitKey(30);
//		if (key == 27 || key == 'q') // ESC
//		{
//			cout << "Exit requested" << endl;
//			break;
//		}
//		else if (key == ' ')
//		{
//			detector.toggleMode();
//		}
//	}
//	return 0;
//}