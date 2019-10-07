#pragma once
#include "SetOperator.h"
#include "RelOperator.h"
#include <stack>
#include <cctype>
#include <sstream>

Table Compute(const string& exp);
//根据输入的表名，读入对应的文件
/*def:	@ is Selection
		# is Projection
		* is Product
		- is Difference
*/
void AnalyExp(const string& exp, stack<pair<char, string>>& oper, stack<Table>& st);
Table DoSel(Table& t, const string& exp);
void DoSelByLog(stack<Table>& keys, stack<string>& logics);
vector<string> SplitCol(const string& s, const char &punct);
vector<string> SplitForSel(const string& s);




