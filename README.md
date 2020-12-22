# 电子点菜系统客户端

相关数据库表(sqlite3)

````sqlite
-- 菜单表
create table  IF NOT EXISTS menu(
	id      INTEGER PRIMARY KEY,
    name 	TEXT NOT NULL,
    price 	REAL NOT NULL,
    pic 	BLOB,    -- 展示图片
    type 	INTEGER -- 类型: 1. 主食 2. 小吃 3. 甜点 4. 汤 等等
);
INSERT INTO menu(name,price,type) VALUES("番茄炒马铃薯","10.0",1);
INSERT INTO menu(name,price,type) VALUES("土豆炒西红柿","11.0",1);

-- 菜品订单表
create table  IF NOT EXISTS order_dishes(
	id   		INTEGER PRIMARY KEY,
    seat 		INTEGER NOT NULL,    -- 座位号
    menu_id 	INTEGER NOT NULL, -- 菜品id
    status 		INTEGER DEFAULT 1, -- 菜品状态：1. 未确认 2.烹饪中 3. 完成
    create_time  TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    update_time  TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);
INSERT INTO order_dishes(seat,menu_id) VALUES(5,1);
INSERT INTO order_dishes(seat,menu_id) VALUES(5,2);
INSERT INTO order_dishes(seat,menu_id) VALUES(7,2);

-- 营业数据表 
create table IF NOT EXISTS business_data(
 id   		INTEGER PRIMARY KEY,
 money 		REAL NOT NULL,    -- 金额费用
 type 		INTEGER DEFAULT 1, -- 类型: 1. 结账 2. 其他待定
 create_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

````

作品介绍





## 参考

1. Qt教程，Qt5编程入门教程 http://c.biancheng.net/qt/
2. Qt中文文档 https://www.qtdoc.cn/
3. Qt5之使用sqlite3数据库  https://blog.csdn.net/hk_5788/article/details/80959076

