//#include "curl/curl.h" // has to go before opencv headers
//#include "opencv2/objdetect/objdetect.hpp"
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//#include <opencv2/video.hpp>
//#include "opencv2/imgcodecs.hpp"
//#include "opencv2/imgproc.hpp"
//#include "opencv2/videoio.hpp"
//
//#include <iostream>
//#include <stdio.h>
//
//using namespace std;
//using namespace cv;
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
////double min_face_size = 150;
////double max_face_size = 200;
//Mat detectFace(Mat src);
//Ptr<BackgroundSubtractor> pMOG2 = createBackgroundSubtractorMOG2(); //MOG2 approach
//
//
//int main()
//{
//	//VideoCapture cap(0);
//	//VideoCapture cap("E:/BachKhoaUni/DoAn/ThesisProject_2018/FallDetection_BK/Private/Office/sample3.mp4");
//	//cv::VideoCapture cap = cv::VideoCapture("http://192.168.0.103:9999/videostream.cgi?user=admin&pwd=admin");
//	namedWindow("window1", 1);
//	//if (cap.isOpened()){
//		while (1)
//		{
//			Mat frame=curlImg("http://192.168.0.222:8888/snapshot.cgi?loginuse=admin&loginpas=admin");
//			//cap >> frame;
//			if (frame.empty()){
//				break;
//			}
//			frame = detectFace(frame);
//
//			imshow("window1", frame);
//			// Press 'c' to escape
//			if (waitKey(1) == 'c') break;
//		}
//	//}
//	/*else
//	{
//		cout << "FAlLD TO CONNECT!!!" << endl;
//	}*/
//
//	waitKey(0);
//	return 0;
//}
//
//Mat detectFace(Mat image)
//{
//	// Name of the downloaded my cascades.. 
//	//string cascadeHead = "cascadeH5.xml";
//	string cascadeName = "cascadG.xml";
//
//
//	// Load the cascade
//	CascadeClassifier detectorBody;
//	bool loaded1 = detectorBody.load(cascadeName);
//	// save original make img gray
//	// draw rectangle back to the original colored sample
//	Mat img;
//	image.copyTo(img);
//	// Prepare vector for results 
//	vector<Rect> human;
//	// Prepare gray image
//	cvtColor(img, img, COLOR_BGR2GRAY);
//	cvtColor(image, image, COLOR_BGR2GRAY);
//	// equalize Histogram  
//	equalizeHist(img, img);
//	equalizeHist(image, image);
//	// detect body and head in the img 
//	// Set the proper min and max size for your case
//	detectorBody.detectMultiScale(img, human, 1.04, 4, 0 | 1, Size(45, 120), Size(80, 200));
//	cvtColor(image, image, COLOR_GRAY2BGR);
//	for (int gg = 0; gg < human.size(); gg++) {
//
//		rectangle(image, human[gg].tl(), human[gg].br(), Scalar(0, 0, 255), 2, 8, 0);
//
//	}
//	return image;
//}