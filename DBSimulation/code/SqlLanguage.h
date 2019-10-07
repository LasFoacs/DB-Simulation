#pragma once
#include "Expression.h"


Table DoSql(const string& sql);
string SToLow(const string& s);
string SqlSelToExp(const map<string, string>& KeyPar);
Table SqlSel(const map<string, string>& KeyPar);
Table SqlDel(const map<string, string>& KeyPar);
Table SqlUpd(const map<string, string>& KeyPar);
Table SqlIns(const map<string, string>& KeyPar);
Table GetTable(const string& s);
map<string, string> SplitKeyPar(const string& sql, const vector<string>& Keys);

