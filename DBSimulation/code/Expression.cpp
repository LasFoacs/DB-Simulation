#include "Expression.h"


const map<string, int> LogicOper =
{
	{"(", -1},
	{")", 0},
	{"or", 1},
	{"and", 2}

};


Table Compute(const string& exp)
{
	stack<pair<char, string>> oper;	//符号栈，存符号及符号所带表达式
	stack<Table> st;				//表栈
	AnalyExp(exp, oper, st);
	while (!oper.empty())
	{
		auto op = oper.top();
		if (op.first == '*')
		{
			auto t1 = st.top();
			st.pop();
			auto t2 = st.top();
			st.pop();
			st.push(Product(t1, t2));
		}
		if (op.first == '#')
		{
			vector<string> col = SplitCol(op.second, ',');
			auto t = st.top();
			st.pop();
			st.push(Projection(t, col));
		}
		if (op.first == '@')
		{
			//此处应当分析string中的逻辑
			auto t = st.top();
			st.pop();
			st.push(DoSel(t, op.second));
		}
		oper.pop();
	}
	return st.top();
}
void AnalyExp(const string& exp, stack<pair<char, string>>& oper, stack<Table>& st)
{//暂不处理and or not

	for (unsigned int i = 0; i < exp.size(); ++i)
	{
		if (exp[i] == '#' || exp[i] == '@')
		{
			pair<char, string> pss = { exp[i], "" };
			i += 2;	//跳过 ( 到后面的表达式中
			while (exp[i] != ']')
				pss.second += exp[i++];
			oper.push(pss);
		}
		if (isalpha(exp[i]))
		{
			string temp = "";
			while (isalpha(exp[i]))
				temp += exp[i++];
			Table ttable(temp);
			ttable.ReadFromFile(temp + ".txt");
			st.push(ttable);
		}
		if (exp[i] == '*')
			oper.push({ '*', "" });
		if (exp[i] == '(')
		{
			string temp = "";
			for (unsigned int flag = 1; flag; )
			{
				++i;
				if (exp[i] == ')')
				{
					--flag;
					if (!flag)
						break;
				}
				if (exp[i] == '(')
					++flag;
				temp += exp[i];
			}
			st.push(Compute(temp));
		}

	}
}
void DoSelByLog(stack<Table>& keys, stack<string>& logics)
{
	string log = logics.top();
	Table a = keys.top();
	keys.pop();
	Table b = keys.top();
	keys.pop();
	if (log == "and")
		keys.push(Intersection(a, b));
	else if (log == "or")
		keys.push(Union(a, b));
	logics.pop();
}
Table DoSel(Table& t, const string& exp)
{//应用计算法，定 and > or > ) 进行计算
	stack<Table> keys;
	stack<string> logics;
	istringstream iss(exp);
	string temp, line;
	while (iss >> temp)
	{
		if (temp.find(")") != string::npos)			//have )
		{
			line += temp.substr(0, temp.size() - 1);;
			temp = ")";
		}
		else if (temp.find("(") != string::npos)	//have (
		{
			line += temp.substr(1, temp.size() - 1);
			temp = "(";
		}
		if (temp == "(")
			logics.push(temp);
		else if (temp == "or" || temp == "and" || temp == ")")
		{
			if (line != "")
			{
				auto k1 = SplitForSel(line);
				keys.push(Selection(t, k1[0], k1[1], k1[2]));
				line = "";
			}
			while (!logics.empty() && LogicOper.at(temp) <= LogicOper.at(logics.top()))
				DoSelByLog(keys, logics);
			if (temp == ")" && logics.top() == "(")
				logics.pop();
			else
				logics.push(temp);
		}
		else
			line += temp;
	}
	if (line != "")
	{
		auto k1 = SplitForSel(line);
		keys.push(Selection(t, k1[0], k1[1], k1[2]));
		line = "";
	}
	while (!logics.empty())
		DoSelByLog(keys, logics);
	return keys.top();
}
vector<string> SplitCol(const string& s, const char& punct)
{
	string temp = "";
	vector<string> res;
	for (char c : s)
	{
		if (c == punct)
		{
			res.push_back(temp);
			temp = "";
		}
		else if (c == ' ' || c == '\'')
			continue;
		else
			temp += c;
	}
	res.push_back(temp);
	return res;
}
vector<string> SplitForSel(const string& s)
{
	string temp = "";
	vector<string> res;
	string ope;
	for (char c : s)
	{
		if (ispunct(c) && c != '.' && c != '\'')
		{
			if (temp != "")
				res.push_back(temp);
			temp = "";
			ope += c;
		}
		else if (c == ' ' || c == '\'')
			continue;
		else
			temp += c;
	}
	res.push_back(ope);
	res.push_back(temp);
	return res;
}
//"#(s.Sno)@(c.Cname = math)@(sc.Cno = c.Cno)@(s.Sno = sc.Sno)s*sc*c"
//"#(s.Sno)@(sc.Cno = c.Cno and c.Cname = math)@(s.Sno = sc.Sno)s*sc*c"
//#以及@的条件用[]写，对()进行顺序的分析


