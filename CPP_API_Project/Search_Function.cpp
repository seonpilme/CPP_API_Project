#include "Search_Function.h"

using namespace std;
string serviceKey = "Y7vOpcmZVqbyz7bUW4lvvkENbLBlu1kZDEoYBqLLjL9HgvguMaugkJZKxFXuJRcjjFSKEq7bMce9pAzQoUKJrQ%3D%3D";
// ���� Ű ����


string API_select(int select) {
    string API;

    if (select == 1) {
        API = "getRealEstateTradingCount?"; // �ܼ� �ε��� �ŷ� �Ǽ� ��ȸ
    }
    else if (select == 2) {
        API = "getRealEstateTradingCountBuildType?"; // �ǹ������� �ε��� �ŷ� �Ǽ�
    }
    else if (select == 3) {
        API = "getRealEstateTradingCountForeigner?"; // �ܱ��� �ε��� �ŷ� �Ǽ�
    }

    return API;
}

// ��� URL �����

// URL : ��û API + ���� ���� ���� + ���� �� ���� + �����ڵ� + �ŷ� ����
string MakeURL_DATA(int API_NUM, int DATE, int END_DATE, int REGION_CD, string DEAL_OBJ) {
    string URL;
    URL += "https://api.odcloud.kr/api/RealEstateTradingSvc/v1/";
    // API Select �Լ� ����� �ֱ�
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


    // �ϼ��� URL ���
    //    cout << URL << endl;
    return URL;
}



// ����ڰ� ���ϴ� ������ True
// ���� �Լ� ����( �Ķ���� Json value )
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

// ����ڰ� ���ϴ� ������ ����ϱ� ���� True / False�� �����ϴ� �Լ�
Element select_info(Element element) {
    vector<Element> elements;

    // �����̳ʿ� ���޹��� ��� ����
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

// �����Լ� -> return element -> ����Լ����� ����(����ڰ� ������ ���ϴ°�)�� ���� ��� ���� ����
// ��� �Լ� ���� ( �Ķ���� element )
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

            // Json KeyȮ��
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
