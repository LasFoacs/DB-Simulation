# DB-Simulation
a work for elective course DB    
第一学期数据库选修课的作业，实现了对表内数据的insert, delete, updata, select 
    
1.InterM文件用 shared_ptr<void> 模拟了内存，提供了读写操作    
2.Table实现了具有基本功能的Table类    
3.SetOperator文件实现了集合的Union, Intersection, Difference操作    
4.RelOperator文件实现了关系表达式中基本选择，投影，笛卡尔积的操作    
5.Expression文件实现了对于关系表达式的计算    
6.SqlLanguage文件实现了解析并执行sql语句    
    
将table里的txt文件和code放进同一文件夹就可以运行，会根据sql语句读取表文件。     
也可以使用WriteToFile函数写一个新的表，详见代码。     
     
由于没学过编译原理，该程序效率较为低下    
