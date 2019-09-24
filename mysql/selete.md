# 简介
selete 等系列关键字是sql语言的重要查找工具，也是和开发最近的关键字

# 语法
* 确定数据的来源表，可以是单表或者多表 from
* 初步筛选，根据筛选条件形成新的表单 where
* 是否分组 group by
* 分组后筛选 having
* 确定输出项 selete
* 输出项排序 order by （asc/desc）
实际使用时mysql将根据上文的顺序进行数据的查找作业。其单独一步理论上都可以生成一张全新的表以供下步的操作。

# 使用逻辑

* 确定数据来源，即确定需求之数据表。
* 确定数据表的初步筛选即将条件语句加在where之后
* 是否分组作业，分组是将特定列根据特定属性分组
* 需求数据确认

# 例子
```
 # 统计各部门员工的数量
 select 
      e.department_id as 部门编号,d.department_name as 部门名, count(*)  as 员工数量
 from
      employees e, departments d
 where
      e.department_id=d.department_id
 group by 
 	  e.department_id;
```
# 分组函数
分组是sql查询中的重要概念，mysql也提供了一些分组函数作为分组操作的工具
 * count()
   count 函数的主要功能是统计数量。用在分组中就可以用来统计各组的数量
   在InnoDB engine中 count(*) 的效率是最高的。
 * max()
   max 函数将当前数据中的最大值输出
 * min()
   min 函数将当前数据中的最小值输出
 * avg()
   avg 函数将当前数据的平均值输出
 * sum()
   avg 函数将当前数据的总和输出
 * group_concat() 
   将分组的结果拼接成字符串
