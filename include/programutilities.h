#ifndef PROGRAMUTILITIES_H
#define PROGRAMUTILITIES_H

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//            (programutilities.h)             //
//                                             //
//    Header contains declarations for:        //
//    ->  A HTTP Wrapper Class                 //
//    ->  2 Helper Functions                   //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

#include <stdlib.h>
#include <string>
#include <vector>
#include <QtGui>
#include <QDebug>

#include "curl/curl.h"


namespace ProgUtilities
{


    class HttpRequest
    {

    public:
        HttpRequest(std::string url_string);
        void execute();
        std::string getResult();

    private:
        CURL *curl;
        CURLcode res;
        std::string url;

        void setopt();
        void perform();
        void cleanUp();
        void validate();

        static std::string htmlResponse;
        static std::size_t writeCallback(char * buf, size_t size, size_t nmemb, void* up);
    };


    QStandardItemModel* generateModel(const std::vector<std::string> &values, QObject* parent = 0);


    std::vector<std::string> generateVector();



}

#endif // PROGRAMUTILITIES_H
