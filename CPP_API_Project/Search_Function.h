#include <stdlib.h>
#include <iostream>
#include <string>
#include <curl/curl.h>
#include <rapidjson/writer.h>
#include <rapidjson/document.h>
#include <vector>
using namespace std;


typedef struct {
    bool ALL_CNT;
    bool REGION_CD;
    bool REGION_NM;
    bool DEAL_OBJ;
    bool RESEARCH_DATE;
} boolType;

typedef struct {
    int ALL_CNT; // 전체 거래 수
    string REGION_CD; // 지역 번호
    string REGION_NM; // 지역 이름
    string DEAL_OBJ; // 거래 유형 ( 번호에 맞게 문자열 출력 )
    string RESEARCH_DATE; // 조사 날짜
    boolType booltype; // 출력 T/F 구조체
} Element;


// MySQL Connection

void FindAndPrintAllCnt(const rapidjson::Value& value, Element element); // 전체 거래량 출력
void FindAndPrintRegion_NM(const rapidjson::Value& value); // 지역별 거래량 출력
void FindAndPrintRESEARCH_DATA(const rapidjson::Value& value); // 기간별 거래량 출력
size_t write_callback(char* ptr, size_t size, size_t nmemb, void* userdata); // http 통신 정보 받아오기

// URL 정보 만들기
string MakeURL_DATA(int API_NUM, int DATE, int END_DATE, int REGION_CD, string DEAL_OBJ); // 기간별 거래량 URL
// API 지정
string API_select(int select);

// 구조체 데이터 입력
Element Insert_Value(const rapidjson::Value& value, Element element);

// T/F 설정에 따른 정보 출력
Element select_info(Element element);
