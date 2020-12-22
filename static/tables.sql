create table   menu(
    id  INTEGER PRIMARY KEY,
    name TEXT NOT NULL,
    price REAL NOT NULL,
    pic BLOB,    -- 展示图片
    type INTEGER -- 类型: 1. 主食 2. 小吃 3. 甜点 4. 汤 等等
);
create table   order_dishes(
    id  INTEGER PRIMARY KEY,
    seat INTEGER NOT NULL,    -- 座位号
    menu_id INTEGER NOT NULL, -- 菜品id
    status INTEGER DEFAULT 1, -- 菜品状态：1. 未确认 2.烹饪中 3. 完成
    create_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    update_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);
create table  business_data(
 id  INTEGER PRIMARY KEY,
 money REAL NOT NULL,    -- 金额费用
 type INTEGER DEFAULT 1, -- 类型: 1. 结账 2. 其他待定
 create_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);
