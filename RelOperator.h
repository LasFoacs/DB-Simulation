#pragma once
#include "Table.h"


Table Projection(Table& t, const vector<string>& KeyNames);
Table Product(Table& t1, Table& t2);
Table Selection(Table& t, const string& KeyName1, const string& oper, const string& KeyName2);


