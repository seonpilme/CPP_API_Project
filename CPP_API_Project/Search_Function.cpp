#include "Search_Function.h"

using namespace std;
string serviceKey = "Y7vOpcmZVqbyz7bUW4lvvkENbLBlu1kZDEoYBqLLjL9HgvguMaugkJZKxFXuJRcjjFSKEq7bMce9pAzQoUKJrQ%3D%3D";
// 서비스 키 정의


string API_select(int select) {
    string API;

    if (select == 1) {
        API = "getRealEstateTradingCount?"; // 단순 부동산 거래 건수 조회
    }
    else if (select == 2) {
        API = "getRealEstateTradingCountBuildType?"; // 건물유형별 부동산 거래 건수
    }
    else if (select == 3) {
        API = "getRealEstateTradingCountForeigner?"; // 외국인 부동산 거래 건수
    }

    return API;
}

// 통신 URL 만들기

// URL : 요청 API + 조사 시작 일자 + 조사 끝 일자 + 지역코드 + 거래 유형
string MakeURL_DATA(int API_NUM, int DATE, int END_DATE, int REGION_CD, string DEAL_OBJ) {
    string URL;
    URL += "https://api.odcloud.kr/api/RealEstateTradingSvc/v1/";
    // API Select 함수 만들어 넣기
    URL += API_select(API_NUM);
    URL += "page=1&perPage=1&cond%5BRESEARCH_DATE%3A%3ALTE%5D=";
    URL += to_string(DATE);
    URL += "&cond%5BRESEARCH_DATE%3A%3AGTE%5D=";
    URL += to_string(END_DATE);
    URL += "&cond%5BREGION_CD%3A%3AEQ%5D=";
    URL += to_string(REGION_CD);
    URL += "&cond%5BDEAL_OBJ%3A%3AEQ%5D=";
    URL += DEAL_OBJ;
    URL += "&serviceKey=";
    URL += serviceKey;


    // 완성된 URL 출력
    //    cout << URL << endl;
    return URL;
}



// 사용자가 원하는 정보만 True
// 삽입 함수 정의( 파라미터 Json value )
Element Insert_Value(const rapidjson::Value& value, Element element) {
    if (value.IsObject()) {
        if (value.HasMember("ALL_CNT")) {
            element.ALL_CNT = value["ALL_CNT"].GetInt();
            element.booltype.ALL_CNT = true;
        }
        if (value.HasMember("DEAL_OBJ")) {
            element.DEAL_OBJ = value["DEAL_OBJ"].GetString();
            element.booltype.DEAL_OBJ = true;
        }
        if (value.HasMember("REGION_CD")) {
            element.REGION_CD = value["REGION_CD"].GetString();
            element.booltype.REGION_CD = true;
        }
        if (value.HasMember("REGION_NM")) {
            element.REGION_NM = value["REGION_NM"].GetString();
            element.booltype.REGION_NM = true;
        }
        if (value.HasMember("RESEARCH_DATE")) {
            element.RESEARCH_DATE = value["RESEARCH_DATE"].GetString();
            element.booltype.RESEARCH_DATE = true;
        }
    }
    else if (value.IsArray()) {
        for (rapidjson::SizeType i = 0; i < value.Size(); ++i) {
            FindAndPrintAllCnt(value[i], element);

        }
    }

    return element;
}

// 사용자가 원하는 정보를 출력하기 위해 True / False를 정의하는 함수
Element select_info(Element element) {
    vector<Element> elements;

    // 컨테이너에 전달받은 요소 전달
    elements.push_back(Element(element));

    for (const auto& element : elements) {
  /*      cout << element.ALL_CNT << endl;
        cout << element.DEAL_OBJ << endl;
        cout << element.REGION_CD << endl;
        cout << element.REGION_NM << endl;
        cout << element.RESEARCH_DATE << endl;*/

        if (element.booltype.ALL_CNT != 0) {
            cout << "ALL_CNT: " << element.ALL_CNT << endl;
        }
        if (element.booltype.DEAL_OBJ != 0) {
            cout << "DEAL_OBJ: " << element.DEAL_OBJ << endl;
        }
        if (element.booltype.REGION_CD != 0) {
            cout << "REGION_CD: " << element.REGION_CD << endl;
        }
        if (element.booltype.REGION_NM != 0) {
            cout << "REGION_NM: " << element.REGION_NM << endl;
        }
        if (element.booltype.RESEARCH_DATE != 0) {
            cout << "RESEARCH_DATE: " << element.RESEARCH_DATE << endl;
        }
    }

    return element;
}

// 삽입함수 -> return element -> 출력함수에서 조건(사용자가 무엇을 원하는가)에 따른 출력 정보 제공
// 출력 함수 정의 ( 파라미터 element )
void FindAndPrintAllCnt(const rapidjson::Value& value, Element element) {
    if (value.IsObject()) {
        for (rapidjson::Value::ConstMemberIterator itr = value.MemberBegin(); itr != value.MemberEnd(); ++itr) {
            if (itr->name == "ALL_CNT") {
                element.ALL_CNT = itr->value.GetInt();
                cout << "ALL_CNT : " << element.ALL_CNT << endl;
            }
            if (itr->name == "REGION_CD") {
                element.REGION_CD = itr->value.GetString();
                cout << "REGION_CD : " << element.REGION_CD << endl;
            }
            if (itr->name == "RESEARCH_DATE") {
                element.RESEARCH_DATE = itr->value.GetString();
                cout << "RESEARCH: " << element.RESEARCH_DATE << endl;
            }
            FindAndPrintAllCnt(itr->value, element);

            // Json Key확인
            /*cout << "itr->name:" << itr->name.GetString() << endl*/;

        }
    }
    else if (value.IsArray()) {
        for (rapidjson::SizeType i = 0; i < value.Size(); ++i) {
            FindAndPrintAllCnt(value[i], element);
        }
    }

}


// curl write callback function
size_t write_callback(char* ptr, size_t size, size_t nmemb, void* userdata) {
    size_t realsize = size * nmemb;
    std::string* str = (std::string*)userdata;
    str->append(ptr, realsize);
    return realsize;
}
