#include "SqlLanguage.h"
#include <fstream>


int main()
{
	/*
//	string exp = "(#[s.Sno, s.Sname]@[s.Sname = qq or s.Sno = 3]@[c.Cname = math and sc.Cno = c.Cno and s.Sno = sc.Sno]s*(sc*c))*c";
//	string exp = "#[s.Sno]@[s.Sno = sc.Sno]s*sc";
//	string exp = "((#[s.Sno]s)*(#[c.Cno]@[c.Cname = math]c))";
//	string exp = "@[(c.Cname = \'math\' or sc.Sno == 1) and c.Cno == sc.Cno] c*sc";
	auto res = Compute(exp);
	*/
	string sql = "select * from c*sc where (c.Cname = \'math\' or sc.Sno == 1) and c.Cno == sc.Cno";
//	string sql = "insert into s (Sno) values (12)";
//	string sql = "delete from s where s.Sno = 3 or s.Sno = 2";
//	string sql = "updata s set s.Sname = 'tt' where s.Sno = 2";
//	string sql = "updata s*sc set s.Sname = 'qq' where s.Sno = 1";
//	string sql = "select * from s*sc";
//	string sql = "delete from s*sc where (s.Sno = 3 or s.Sno = 2) and s.Sno = sc.Sno";

	auto res = DoSql(sql);
	cout << res << endl;
}


