#include <iostream>
#include <string>
#include <curl/curl.h>
#include "rapidjson/document.h"
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

using namespace std;

void FindAndPrintAllCnt(const rapidjson::Value& value) {
    if (value.IsObject()) {
        for (rapidjson::Value::ConstMemberIterator itr = value.MemberBegin(); itr != value.MemberEnd(); ++itr) {
            if (itr->name == "ALL_CNT") {
                std::cout << "ALL_CNT: " << itr->value.GetInt() << std::endl;
                return; // 원하는 값이 출력되면 함수 종료
            }
            FindAndPrintAllCnt(itr->value);
        }
    } else if (value.IsArray()) {
        for (rapidjson::SizeType i = 0; i < value.Size(); ++i) {
            FindAndPrintAllCnt(value[i]);
        }
    }
}

void FindAndPrintREGION_NM(const rapidjson::Value& value) {
    if (value.IsObject()) {
        for (rapidjson::Value::ConstMemberIterator itr = value.MemberBegin(); itr != value.MemberEnd(); ++itr) {
            if (itr->name == "REGION_NM") {
                std::cout << "REGION_NM: " << itr->value.GetInt() << std::endl;
                return; // 원하는 값이 출력되면 함수 종료
            }
            FindAndPrintAllCnt(itr->value);
        }
    } else if (value.IsArray()) {
        for (rapidjson::SizeType i = 0; i < value.Size(); ++i) {
            FindAndPrintAllCnt(value[i]);
        }
    }
}

void FindAndPrintRESEARCH_DATA(const rapidjson::Value& value) {
    if (value.IsObject()) {
        for (rapidjson::Value::ConstMemberIterator itr = value.MemberBegin(); itr != value.MemberEnd(); ++itr) {
            if (itr->name == "RESEARCH_DATA") {
                std::cout << "RESEARCH_DATA: " << itr->value.GetInt() << std::endl;
                return; // 원하는 값이 출력되면 함수 종료
            }
            FindAndPrintAllCnt(itr->value);
        }
    } else if (value.IsArray()) {
        for (rapidjson::SizeType i = 0; i < value.Size(); ++i) {
            FindAndPrintAllCnt(value[i]);
        }
    }
}

// curl write callback function
size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
    size_t realsize = size * nmemb;
    std::string *str = (std::string *)userdata;
    str->append(ptr, realsize);
    return realsize;
}



