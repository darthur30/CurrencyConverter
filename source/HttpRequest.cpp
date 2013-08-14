#include "programutilities.h"



/********************************************/
/***         STATIC INITIALIZATION        ***/
/********************************************/
std::string ProgUtilities::HttpRequest::htmlResponse("");


/********************************************/
/***             CONSTRUCTORS             ***/
/********************************************/
ProgUtilities::HttpRequest::HttpRequest(std::string url_string) :
    url(url_string)
{
}


/********************************************/
/***       GENERAL MEMBER FUNCTIONS       ***/
/********************************************/
void ProgUtilities::HttpRequest::execute()
{
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if (curl)
    {
        setopt();
        perform();
        validate();
    }

    cleanUp();
}


std::string ProgUtilities::HttpRequest::getResult()
{
    return htmlResponse;
}


/********************************************/
/***       PRIVATE UTILITY FUNCTIONS      ***/
/********************************************/
inline void ProgUtilities::HttpRequest::setopt()
{
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &ProgUtilities::HttpRequest::writeCallback);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
}


inline void ProgUtilities::HttpRequest::perform()
{
    res = curl_easy_perform(curl);
}


inline void ProgUtilities::HttpRequest::validate()
{
    if(res != CURLE_OK) qDebug() << "There was an error with the HTTP request";
}


inline void ProgUtilities::HttpRequest::cleanUp()
{
    curl_easy_cleanup(curl);
    curl_global_cleanup();
}


std::size_t ProgUtilities::HttpRequest::writeCallback(char * buf, size_t size, size_t nmemb, void* up)
{
    for( int i = 0; i < size * nmemb; i++  )
    {
       htmlResponse.push_back(buf[i]);
    }

    return size * nmemb;
}


