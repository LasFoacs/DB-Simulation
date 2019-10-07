#include "InterM.h"


void InterM::push_back(const shared_ptr<void>& i)
{
	col.push_back(i);
}
string InterM::read(const string& type, const int& i)
{
	if (col[i] == nullptr)
		return "NULL";
	if (type == "int")
		return to_string(*(static_pointer_cast<int> (col[i])));
	return (*(static_pointer_cast<string> (col[i])));
}
void InterM::write(const string& type, const string& s)
{
	if (s == "nullptr")
		col.push_back(nullptr);
	else if (type == "int")
		col.push_back(make_shared<int>(stoi(s)));
	else
		col.push_back(make_shared<string>(s));
}
void InterM::write(const int& i, const string& type, const string& s)
{
	if (s == "nullptr")
		col[i] = nullptr;
	else if (type == "int")
		col[i] = make_shared<int>(stoi(s));
	else
		col[i] = make_shared<string>(s);
}



