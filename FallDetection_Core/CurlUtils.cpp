#include "CurlUtils.h"

const string CurlUtils::GOOGLE_KEY_SERVER = "AIzaSyAMBEmcJ-TMH0vhyDgd0yeG-hbeW6xYCeY";

bool CurlUtils::curlImg(char* imgURL, Mat& dst, int timeOut)
{
	vector<uchar> stream;
	CURL *curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, imgURL);				//the img url
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, _writeImgData);	// pass the writefunction
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &stream);			// pass the stream ptr to the writefunction
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeOut);			// timeout if curl_easy hangs, 
	struct curl_slist *hs = NULL;								// create header for request
	hs = curl_slist_append(hs, "Content-Type: image/jpeg");
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, hs);

	CURLcode res = curl_easy_perform(curl);						// start curl
	curl_easy_cleanup(curl);									// cleanup
	if (res)
	{
		return false;
	}
	try{
		dst = imdecode(stream, -1);								// 'keep-as-is'
		return true;
	}
	catch (Exception e){
		return false;
	}
}
bool CurlUtils::curlURLWithData(char* uRL, curl_slist* header, char* stringData, int timeOut)
{
	// init struct to read string (char*) data
	struct WriteThis wt;
	wt.readptr = stringData;
	wt.sizeleft = strlen(stringData);

	CURL *curl = curl_easy_init();
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, uRL);
		curl_easy_setopt(curl, CURLOPT_POST, 1L);							// spectify POST Method
		curl_easy_setopt(curl, CURLOPT_READFUNCTION, _readData);			// spectify read data function
		curl_easy_setopt(curl, CURLOPT_READDATA, &wt);						// spectify pointer to read function
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)wt.sizeleft);	// spectify size of string data
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);
		CURLcode res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		if (res)
		{
			return false;
		}
		return true;
	}
	return false;
}
size_t CurlUtils::_readData(void *dest, size_t size, size_t nmemb, void *userData)
{
	struct WriteThis *wt = (struct WriteThis *)userData;
	size_t buffer_size = size*nmemb;

	if (wt->sizeleft) {
		/* copy as much as possible from the source to the destination */
		size_t copy_this_much = wt->sizeleft;
		if (copy_this_much > buffer_size)
			copy_this_much = buffer_size;
		memcpy(dest, wt->readptr, copy_this_much);

		wt->readptr += copy_this_much;
		wt->sizeleft -= copy_this_much;
		return copy_this_much; /* we copied this many bytes */
	}

	return 0; /* no more data left to deliver */
}
size_t CurlUtils::_writeImgData(char *ptr, size_t size, size_t nmemb, void *userData)
{
	vector<uchar> *stream = (vector<uchar>*)userData;
	size_t count = size * nmemb;
	stream->insert(stream->end(), ptr, ptr + count);
	return count;
}