#include "Search_Function.h"
using namespace std;



int main() {
    Element element;
    CURL* curl;
    CURLcode res;
    string read_buffer;
    rapidjson::Document document;
    //string API = API_select();
    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();
    if (curl) {
        // URL : 요청 API + 조사 시작 일자 + 조사 끝 일자 + 지역코드 + 거래 유형
        string url = MakeURL_DATA(1, 202201, 202101, 30000, "01");

        // curl_easy_setopt : curl의 작동 방식 선언
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); // URL 지정
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback); // callback 타입 선언
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer); // 해당 URL의 json 읽어오기

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            cout << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
        } // 통신 실패
        else {
            document.Parse(read_buffer.c_str()); // 읽어온 json을 데이터 가공을 위해 파싱

            // 파싱에 에러가 발생하지 않으면 정보 출력
            if (!document.HasParseError()) {
                
                rapidjson::Value& data = document["data"];
                if (data.IsArray() && data.Size() > 0) {
                    element = Insert_Value(data[0], element);
                    // T/F에 따라 출력
                    select_info(element);
                    // 전체 Json 출력 
                    /*std::cout << read_buffer;*/
                    
                }
            }
            else {
                std::cout << "Parse Error: " << document.GetParseError() << std::endl;
            }
        }
    }
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return 0;
}
