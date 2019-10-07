#include "SetOperator.h"




Table Difference(Table& t1, Table& t2)
{//默认t1与t2同型
	Table res = t1;
	res.ClearTable();
	vector<int> index;
	for (unsigned int i = 0; i < t1.GetCount(); ++i)
	{
		bool flag = false;
		for (unsigned int j = 0; j < t2.GetCount() && !flag; ++j)
			flag = (t1.GetRow(i) == t2.GetRow(j));
		if (!flag)
			index.push_back(i);
	}
	res.AddRowFromOther(t1, index);
	return res;
}
Table Intersection(Table& t1, Table& t2)
{
	Table res = t1;
	res.ClearTable();
	vector<int> index;
	for (unsigned int i = 0; i < t1.GetCount(); ++i)
		for (unsigned int j = 0; j < t2.GetCount(); ++j)
			if (t1.GetRow(i) == t2.GetRow(j))
				index.push_back(i);
	res.AddRowFromOther(t1, index);
	return res;
}
Table Union(Table& t1, Table& t2)
{
	Table res = t1;
	res.ClearTable();
	vector<int> index1;
	vector<int> index2;
	for (unsigned int i = 0; i < t1.GetCount(); ++i)
	{
		bool flag = false;
		for (unsigned int j = 0; j < t2.GetCount() && !flag; ++j)
			flag = (t1.GetRow(i) == t2.GetRow(j));
		if (!flag)
			index1.push_back(i);
	}
	for (unsigned int j = 0; j < t2.GetCount(); ++j)
		index2.push_back(j);
	res.AddRowFromOther(t1, index1);
	res.AddRowFromOther(t2, index2);
	return res;
}
