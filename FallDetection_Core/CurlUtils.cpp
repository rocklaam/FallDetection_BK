#include "CurlUtils.h"

bool CurlUtils::curlImg(char* imgURL, Mat& dst, int timeOut){
	vector<uchar> stream;
	CURL *curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, imgURL);				//the img url
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, _writeData);	// pass the writefunction
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &stream);			// pass the stream ptr to the writefunction
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeOut);			// timeout if curl_easy hangs, 
	struct curl_slist *hs = NULL;								// create header for request
	hs = curl_slist_append(hs, "Content-Type: image/jpeg");
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, hs);

	CURLcode res = curl_easy_perform(curl);						// start curl
	curl_easy_cleanup(curl);									// cleanup
	try{
		dst = imdecode(stream, -1);								// 'keep-as-is'
		return true;
	}
	catch (Exception e){
		return false;
	}
}
size_t CurlUtils::_writeData(char *ptr, size_t size, size_t nmemb, void *userData)
{
	vector<uchar> *stream = (vector<uchar>*)userData;
	size_t count = size * nmemb;
	stream->insert(stream->end(), ptr, ptr + count);
	return count;
}