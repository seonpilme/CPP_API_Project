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
    int ALL_CNT; // ��ü �ŷ� ��
    string REGION_CD; // ���� ��ȣ
    string REGION_NM; // ���� �̸�
    string DEAL_OBJ; // �ŷ� ���� ( ��ȣ�� �°� ���ڿ� ��� )
    string RESEARCH_DATE; // ���� ��¥
    boolType booltype; // ��� T/F ����ü
} Element;


// MySQL Connection

void FindAndPrintAllCnt(const rapidjson::Value& value, Element element); // ��ü �ŷ��� ���
void FindAndPrintRegion_NM(const rapidjson::Value& value); // ������ �ŷ��� ���
void FindAndPrintRESEARCH_DATA(const rapidjson::Value& value); // �Ⱓ�� �ŷ��� ���
size_t write_callback(char* ptr, size_t size, size_t nmemb, void* userdata); // http ��� ���� �޾ƿ���

// URL ���� �����
string MakeURL_DATA(int API_NUM, int DATE, int END_DATE, int REGION_CD, string DEAL_OBJ); // �Ⱓ�� �ŷ��� URL
// API ����
string API_select(int select);

// ����ü ������ �Է�
Element Insert_Value(const rapidjson::Value& value, Element element);

// T/F ������ ���� ���� ���
Element select_info(Element element);
