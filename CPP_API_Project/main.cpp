#include <iostream>
#include <string>
#include <curl/curl.h>
#include "rapidjson/document.h"
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include "variable.h"
#include "Search_Function.h"
using namespace std;


int main() {
    CURL *curl;
    CURLcode res;
    std::string read_buffer;
    rapidjson::Document document;
    
    curl_global_init(CURL_GLOBAL_ALL);
    
    curl = curl_easy_init();
    if (curl) {
        string url = "https://api.odcloud.kr/api/RealEstateTradingSvc/v1/getRealEstateTradingCount?page=1&perPage=1&cond%5BRESEARCH_DATE%3A%3ALTE%5D=202201&cond%5BRESEARCH_DATE%3A%3AGTE%5D=202101&cond%5BREGION_CD%3A%3AEQ%5D=30000&cond%5BDEAL_OBJ%3A%3AEQ%5D=01&serviceKey=Y7vOpcmZVqbyz7bUW4lvvkENbLBlu1kZDEoYBqLLjL9HgvguMaugkJZKxFXuJRcjjFSKEq7bMce9pAzQoUKJrQ%3D%3D";
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);
        
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cout << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
        else {
            document.Parse(read_buffer.c_str());
            if (!document.HasParseError()) {
                rapidjson::StringBuffer buffer;
                rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
                document.Accept(writer);
                FindAndPrintAllCnt(document);
            } else {
                std::cout << "Parse Error: " << document.GetParseError() << std::endl;
            }
        }
        
    }
    curl_easy_cleanup(curl);
    curl_global_cleanup();
    return 0;
}

