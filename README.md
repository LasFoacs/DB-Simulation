# DB-Simulation
a work for elective course DB
第一学期数据库选修课的作业，实现了对表内数据的insert, delete, updata, select
InterM文件用 shared_ptr<void> 模拟了内存，提供了读写操作
Table实现了具有基本功能的Table类
SetOperator文件实现了集合的Union, Intersection, Difference操作
RelOperator文件实现了关系表达式中基本选择，投影，笛卡尔积的操作
Expression文件实现了对于关系表达式的计算
SqlLanguage文件实现了解析并执行sql语句

由于没学过编译原理，该程序效率较为低下
