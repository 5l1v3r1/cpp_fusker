#include <iostream>
#include <random>
#include <string>
#include <curl/curl.h>
#include <fstream>

size_t write_data(void* buffer, size_t size, size_t nmemb, void* userp)
{
	return size * nmemb;
}

const int MAX = 62;

// Returns a string of random alphabets of 
// length n. 
using namespace std;
string printRandomString(int n)
{
	char alphabet[MAX] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g',
						  'h', 'i', 'j', 'k', 'l', 'm', 'n',
						  'o', 'p', 'q', 'r', 's', 't', 'u',
						  'v', 'w', 'x', 'y', 'z', 'A', 'B',
						  'C', 'D', 'E', 'F', 'G', 'H', 'I',
						  'J', 'K', 'L', 'M', 'N', 'O', 'P',
						  'Q', 'R', 'S', 'T', 'U', 'V', 'W',
						  'X', 'Y', 'Z', '0', '9', '8', '7',
						  '6', '5', '4', '3', '2', '1' };

	string res = "";
	for (int i = 0; i < n; i++)
		res = res + alphabet[rand() % MAX];

	return res;
}

int main(int argc, char* argv[])
{
	while (true)
	{
		CURL* curl = curl_easy_init();
		if (curl)
		{
			CURLcode res;
			string extension = argv[4];
			int n = atoi(argv[2]);
			string url_set = argv[1] + printRandomString(n) + extension;
			string filename = argv[3] + string(".txt");
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
			curl_easy_setopt(curl, CURLOPT_URL, url_set);
			curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
			res = curl_easy_perform(curl);
			cout << url_set << endl;
			if (res == CURLE_OK)
			{
				long response_code;
				curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
				ofstream myfile;
				myfile.open(filename);
				myfile << url_set << "\n";
				myfile.close();
				cout << url_set << "- 200\n";

				system("pause");
			}
			else if (res == CURLE_UNKNOWN_OPTION)
			{
				cout << "Response code (after redirect) is not 200\n";
			}
			else
			{
				cout << "Response code is not 200\n";
			}
			curl_easy_cleanup(curl);
		}
	}
}