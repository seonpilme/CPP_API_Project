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
        // URL : ��û API + ���� ���� ���� + ���� �� ���� + �����ڵ� + �ŷ� ����
        string url = MakeURL_DATA(1, 202201, 202101, 30000, "01");

        // curl_easy_setopt : curl�� �۵� ��� ����
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); // URL ����
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback); // callback Ÿ�� ����
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer); // �ش� URL�� json �о����

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            cout << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
        } // ��� ����
        else {
            document.Parse(read_buffer.c_str()); // �о�� json�� ������ ������ ���� �Ľ�

            // �Ľ̿� ������ �߻����� ������ ���� ���
            if (!document.HasParseError()) {
                
                rapidjson::Value& data = document["data"];
                if (data.IsArray() && data.Size() > 0) {
                    element = Insert_Value(data[0], element);
                    // T/F�� ���� ���
                    select_info(element);
                    // ��ü Json ��� 
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
