#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <iomanip>
#include <memory>
#include <sstream>
#include <fstream>

using namespace std;


class InterM
{
public:
	InterM() = default;
	InterM (const int& count)
	{
		col = vector<shared_ptr<void>> (count, nullptr);
	}
	void push_back(const shared_ptr<void>& i);
	string read(const string& type, const int& i);
	void write(const string& type, const string& s);
	void write(const int& i, const string& type, const string& s);
	shared_ptr<void> operator [] (const unsigned int& i)
	{
		return col[i];
	}
	unsigned int size()
	{
		return col.size();
	}
private:
	vector<shared_ptr<void>> col;

};


