#include "SqlLanguage.h"
#include <algorithm>



Table DoSql(const string& sql)
{
	string oper(sql.begin(), sql.begin() + 6);
	map<string, string> KeyPar;//关键字 : 参数表
	oper = SToLow(oper);
	if (oper == "select")
	{
		KeyPar = SplitKeyPar(sql, { "from", "where" });
		return SqlSel(KeyPar);
	}
	if (oper == "delete")
	{
		KeyPar = SplitKeyPar(sql, { "from", "where" });
		return SqlDel(KeyPar);
	}
	if (oper == "updata")
	{
		KeyPar = SplitKeyPar(sql, { "set", "where" });
		return SqlUpd(KeyPar);
	}
	if (oper == "insert")
	{
		KeyPar = SplitKeyPar(sql, { "into", "values" });
		return SqlIns(KeyPar);
	}
}
Table GetTable(const string& s)
{
	return DoSql("select * from " + s);
}
string SToLow(const string& s)
{
	string res = s;
	for_each(res.begin(), res.end(), [] (char& c) {c = tolower(c); });
	return res;
}
string SqlSelToExp(const map<string, string>& KeyPar)
{
	string exp = "";
	if (KeyPar.at("select") != "* ")
		exp += "#[" + KeyPar.at("select") + "]";
	if (KeyPar.find("where") != KeyPar.end())
		exp += "@[" + KeyPar.at("where") + "]";
	exp += KeyPar.at("from");
	return exp;

}
Table SqlSel(const map<string, string>& KeyPar)
{
	string exp;
	if (KeyPar.at("select") != "* ")
		exp += "#[" + KeyPar.at("select") + "]";
	if (KeyPar.find("where") != KeyPar.end())
		exp += "@[" + KeyPar.at("where") + "]";
	exp += KeyPar.at("from");

	return Compute(exp);
}
Table SqlDel(const map<string, string>& KeyPar)
{
	Table res = GetTable(KeyPar.at("from"));
	Table t = DoSel(res, KeyPar.at("where"));
	return Difference(res, t);
}
Table SqlIns(const map<string, string>& KeyPar)
{
	string line = KeyPar.at("into");
	Table res = GetTable(line.substr(0, line.find("(")));
	line = line.substr(line.find("(") + 1, line.find(")") - line.find("(") - 1);
	vector<string> col = SplitCol(line, ',');
	line = KeyPar.at("values");
	line = line.substr(line.find("(") + 1, line.find(")") - line.find("(") - 1);
	vector<string> val = SplitCol(line, ',');
	res.AddRow(col, val);
	return res;

}
Table SqlUpd(const map<string, string>& KeyPar)
{
	Table res = GetTable(KeyPar.at("updata"));
	auto NewVal = SplitCol(KeyPar.at("set"), ',');
	Table oldt = DoSel(res, KeyPar.at("where"));
	Table newt = oldt;
	for (string s : NewVal)
	{
		vector<string> Val = SplitCol(s, '=');
		for (unsigned int i = 0; i < newt.GetCount(); ++i)
			newt.Change(Val[0], i, Val[1]);
	}
	res = Difference(res, oldt);
	for (int i = 0; i < newt.GetCount(); ++i)
		res.AddRowFromOther(newt, { i });
	return res;
}
map<string, string> SplitKeyPar(const string& sql, const vector<string>& Keys)
{
	istringstream iss(sql);
	string oper;
	map<string, string> KeyPar;//关键字 : 参数表
	iss >> oper;
	string line;
	for (string temp; iss >> temp; )
		if (find(Keys.begin(), Keys.end(), SToLow(temp)) != Keys.end())
		{
			KeyPar[SToLow(oper)] = line;
			oper = temp;
			line = "";
		}
		else
			line += temp + ' ';
	KeyPar[SToLow(oper)] = line;
	return KeyPar;
}





