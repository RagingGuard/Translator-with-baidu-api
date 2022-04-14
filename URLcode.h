#include<iostream>
#include<string>
#include<stdio.h>
#include<assert.h>
#include<fstream>

using namespace std;

class URLcode{
public:
	string UrlEncode(const string&);
	string UrlDecode(const string&);
private:
	unsigned char ToHex(unsigned char);
	unsigned char FromHex(unsigned char);
};