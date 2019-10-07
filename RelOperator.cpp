#include "RelOperator.h"
#include <functional>

const map<string, function<bool (string, string)>> Operator =
{
	{"==", equal_to<string>()},
	{"=", equal_to<string>()},
	{"!=", not_equal_to<string>()},
	{">", greater<string>()},
	{">=", greater_equal<string>()},
	{"<", less<string>()},
	{"<=", less_equal<string>()},

};
Table Projection(Table& t, const vector<string>& KeyNames)
{
	map<string, InterM> res;
	map<string, string> tl;
	for (auto s : KeyNames)
	{
		auto temp = t.at(s);
		tl[s] = temp.first;
		res[s] = temp.second;
	}
	return Table(tl, res, t.GetCount());
}
Table Product(Table& t1, Table& t2)
{
	map<string, string> tl;
	map<string, InterM> res;
	for (unsigned int k = 0; k < t1.GetCount(); ++k)
	{//把t1中每一行重复t2.count遍，放入res
		for (auto i = t1.begin(); i != t1.end(); ++i)
		{
			string colName = i->first;
			tl[colName] = t1.GetType(colName);
			for (unsigned int j = 0; j < t2.GetCount(); ++j)
				res[colName].push_back(i->second[k]);
		}
		//把t2中每一行放入res, 重复t2.count遍
		for (auto i = t2.begin(); i != t2.end(); ++i)
		{
			string colName = i->first;
			tl[colName] = t2.GetType(colName);
			for (unsigned int j = 0; j < t2.GetCount(); ++j)
				res[colName].push_back(i->second[j]);
		}
	}
	return Table(tl, res, t1.GetCount() * t2.GetCount());
}

Table Selection(Table& t, const string& KeyName1, const string& oper, const string& KeyName2)
{
	Table res = t;
	res.ClearTable();
	vector<int> index;
	if (t.FindKN(KeyName2))
	{//if kn2 is a colnum
		for (unsigned int i = 0; i < t.GetCount(); ++i)
			if (Operator.at(oper)(t.ReadM(KeyName1, i), t.ReadM(KeyName2, i)))
				index.push_back(i);
	}
	else//if kn2 is a value
		for (unsigned int i = 0; i < t.GetCount(); ++i)
			if (Operator.at(oper)(t.ReadM(KeyName1, i), KeyName2))
				index.push_back(i);	//找下标并放入index中
	res.AddRowFromOther(t, index);
	return res;
}

