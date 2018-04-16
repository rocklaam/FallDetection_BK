//#include "curl/curl.h" // has to go before opencv headers
//
//#include <iostream>
//#include <time.h>
//#include <stdio.h>
//#include <vector>
//using namespace std;
//
//#include <opencv2/opencv.hpp>
//using namespace cv;
//
//void delay(unsigned int mseconds)
//{
//	clock_t goal = mseconds + clock();
//	while (goal > clock());
//}
//
////curl writefunction to be passed as a parameter
//// we can't ever expect to get the whole image in one piece,
//// every router / hub is entitled to fragment it into parts
//// (like 1-8k at a time),
//// so insert the part at the end of our stream.
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
//	cout << "curling" << endl;
//	curl_easy_cleanup(curl); // cleanup
//	return imdecode(stream, -1); // 'keep-as-is'
//}
//
//int main()
//{
//	namedWindow("Image in", CV_WINDOW_AUTOSIZE);
//	cout << "OpenCV version : " << CV_VERSION << endl;
//	cout << "Major version : " << CV_MAJOR_VERSION << endl;
//	cout << "Minor version : " << CV_MINOR_VERSION << endl;
//	cout << "Subminor version : " << CV_SUBMINOR_VERSION << endl;
//	while (true)
//	{
//		Mat image = curlImg("http://192.168.0.103:9999/snapshot.cgi?loginuse=admin&loginpas=admin");
//		if (image.empty()){
//			cout << "Load failed!" << endl;
//			break;
//		}
//		cout << image.cols << endl;
//		//imshow("Image output", image); // here's your car ;)
//		delay(30);
//	}
//	return 0; // infinite
//}
//
////#define _CRT_SECURE_NO_DEPRECATE
////#include <stdio.h>
////#include <curl/curl.h>
////
////size_t callbackfunction(void *ptr, size_t size, size_t nmemb, void* userdata)
////{
////	FILE* stream = (FILE*)userdata;
////	if (!stream)
////	{
////		printf("!!! No stream\n");
////		return 0;
////	}
////
////	size_t written = fwrite((FILE*)ptr, size, nmemb, stream);
////	return written;
////}
////
////bool download_jpeg(char* url)
////{
////	FILE* fp = fopen("out.jpg", "wb");
////	if (!fp)
////	{
////		printf("!!! Failed to create file on the disk\n");
////		return false;
////	}
////
////	CURL* curlCtx = curl_easy_init();
////	curl_easy_setopt(curlCtx, CURLOPT_URL, url);
////	curl_easy_setopt(curlCtx, CURLOPT_WRITEDATA, fp);
////	curl_easy_setopt(curlCtx, CURLOPT_WRITEFUNCTION, callbackfunction);
////	curl_easy_setopt(curlCtx, CURLOPT_FOLLOWLOCATION, 1);
////
////	CURLcode rc = curl_easy_perform(curlCtx);
////	if (rc)
////	{
////		printf("!!! Failed to download: %s\n", url);
////		return false;
////	}
////
////	long res_code = 0;
////	curl_easy_getinfo(curlCtx, CURLINFO_RESPONSE_CODE, &res_code);
////	if (!(rc != CURLE_ABORTED_BY_CALLBACK))
////	{
////		printf("!!! Response code: %d\n", res_code);
////		return false;
////	}
////
////	curl_easy_cleanup(curlCtx);
////
////	fclose(fp);
////
////	return true;
////}
////
////int main(int argc, char** argv)
////{
////	if (!download_jpeg("http://localhost:8088/a.jpg"))
////	{
////		printf("!! Failed to download file: %s\n", argv[1]);
////		return -1;
////	}
////
////	return 0;
////}