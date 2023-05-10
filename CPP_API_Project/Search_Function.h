//
//  Search_Function.h
//  CPP_API_Project
//
//  Created by MacPeel on 2023/05/10.
//

#ifndef Search_Function_h
#define Search_Function_h
#include <iostream>
#include <string>
#include <curl/curl.h>
#include "rapidjson/document.h"
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

void FindAndPrintAllCnt(const rapidjson::Value& value);
void FindAndPrintREGION_NM(const rapidjson::Value& value);
void FindAndPrintRESEARCH_DATA(const rapidjson::Value& value);
size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata);

#endif /* Search_Function_h */
