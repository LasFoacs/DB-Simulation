#pragma once
#include "InterM.h"

class Table
{
public:
	Table() = default;
	Table(const map<string, string>& tl, map<string, InterM> msm, const int& c):typelist(tl), table(msm), count(c)
	{}
	Table(const string& s):name(s)
	{}
	Table(const string& s, const map<string, string>& tl);

	pair<string, InterM> at(const string& KeyName);
	void ClearTable();
	void AddCol(const string &type, const string& name);
	void AddRow(const vector<string>& col, const vector<string>& data);
	void AddRowFromOther(Table& t, const vector<int>& index);
	string ReadM(const string& col, const int& row);
	void Change(const string& col, const int& row, const string &NewVal);
	void WriteToFile(const string& fname);
	void ReadFromFile(const string& fname);
	string ConvertName(const string& rn);
	unsigned int GetCount()
	{
		return count;
	}
	map<string, InterM>::iterator begin();
	map<string, InterM>::iterator end();
//	string GetName();
	string GetType(const string& s);
	void RenameT(const string& name);
	void RenameC(const string &rawName, const string& name);
	bool FindKN(const string& KeyName);
	string GetRow(const int& index);
	friend ostream& operator <<(ostream& os, Table& t);
private:
	string name;
	map<string, string> typelist;	//only string or int
	map<string, InterM> table;
	unsigned int count;	//count == vector.size()
};
ostream& operator <<(ostream& os, Table& t);




