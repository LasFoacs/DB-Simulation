#include "Table.h"


Table::Table(const string& s, const map<string, string>& tl)
{
	name = s;
	typelist = tl;
	for (auto i = tl.begin(); i != tl.end(); ++i)
		this->AddCol(i->second, i->first);
}

string Table::ConvertName(const string& rn)
{
	if (rn.find(".") == string::npos)
		return this->name + "." + rn;
	return rn;
}
void Table::AddCol(const string& type, const string& name)
{
	if (table.find(name) == table.end())
	{
		string colName = ConvertName(name);
		table[colName] = InterM(count);
		typelist[colName] = type;
	}
}
void Table::AddRow(const vector<string>& col, const vector<string>& data)
{
	for (unsigned int i = 0; i < col.size(); ++i)
	{
		string colName = ConvertName(col[i]);
		string type = typelist[colName];
		if (type == "int")
			table[colName].push_back(make_shared<int>(stoi(data[i])));
		else
			table[colName].push_back(make_shared<string>(data[i]));
	}
	++count;
	for (auto i = table.begin(); i != table.end(); ++i)
		if ((i->second).size() != count)
			i->second.push_back(nullptr);
}
void Table::RenameT(const string& name)
{
	if (this->name == name)
		return;
	this->name = name;
	auto temp = table;
	for (auto i = temp.begin(); i != temp.end(); ++i)
	{
		string NewName = i->first.substr(i->first.find(".") + 1);
		NewName = name == "" ? NewName : ConvertName(NewName);
		RenameC(i->first, NewName);
	}
}
void Table::RenameC(const string& rawName, const string& name)
{
	table[name] = table[rawName];
	typelist[name] = typelist[rawName];
	table.erase(rawName);
	typelist.erase(rawName);
}

string Table::ReadM(const string& col, const int& row)
{
	return table[col].read(typelist[col], row);
}
void Table::Change(const string& col, const int& row, const string& NewVal)
{
	table[col].write(row, typelist[col], NewVal);
}
void Table::WriteToFile(const string& fname)
{
	if (name == "")
	{
		cout << "template table can't write in file. Please get this table a name" << endl;
		return;
	}
	RenameT("");
	ofstream os(fname);
	for (auto i = table.begin(); i != table.end(); ++i)
		os << setw(10) << typelist[i->first];
	os << endl;
	os << *this;
}
void Table::ReadFromFile(const string& fname)
{
	ifstream is(fname);
	string line;
	getline(is, line);
	istringstream iss(line);
	string temp;
	while (iss >> temp)
	{
		string colName;
		is >> colName;
		colName = ConvertName(colName);
		AddCol(temp, colName);
	}
	while (getline(is, line))
	{
		if (!line.empty())
		{
			iss = istringstream(line);
			for (auto i = table.begin(); i != table.end() && iss >> temp; ++i)
				i->second.write(typelist[i->first], temp);
			++count;
		}
	}

}
void Table::AddRowFromOther(Table& t, const vector<int>& index)
{
	for (int j : index)
		for (auto i = t.begin(); i != t.end(); ++i)
			table[i->first].push_back(i->second[j]);
	count += index.size();
}
bool Table::FindKN(const string& KeyName)
{
	return table.find(KeyName) != table.end();
}
map<string, InterM>::iterator Table::begin()
{
	return table.begin();
}
map<string, InterM>::iterator Table::end()
{
	return table.end();
}
string Table::GetRow(const int& index)
{
	string res = "";
	for (auto i = table.begin(); i != table.end(); ++i)
		res += (i->second).read(typelist[i->first], index) + "\t";
	return res;
}
pair<string, InterM> Table::at(const string& KeyName)
{
	return pair<string, InterM>(typelist.at(KeyName), table.at(KeyName));
}
string Table::GetType(const string& s)
{
	return typelist[s];
}
void Table::ClearTable()
{
	table.clear();
	count = 0;
}
ostream& operator <<(ostream& os, Table& t)
{
	for (auto i = t.table.begin(); i != t.table.end(); ++i)
		os << setw(10) << i->first;
	os << endl;
	for (unsigned int j = 0; j < t.count; ++j)
	{
		for (auto i = t.table.begin(); i != t.table.end(); ++i)
			os << setw(10) << t.ReadM(i->first, j);
		os << endl;
	}
	return os;
}
