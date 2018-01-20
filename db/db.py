# -*- coding: utf-8 -*-
#python operate mysql database
import MySQLdb
from numpy import *
#数据库名称
DATABASE_NAME = 'arm'
#host = 'localhost' or '172.0.0.1'
HOST = 'localhost'
#端口号
PORT = '3306'
#用户名称
USER_NAME = 'root'
#数据库密码
PASSWORD = 'xxx'
#数据库编码
CHAR_SET = 'utf8'

#初始化参数
def init():
    global DATABASE_NAME
    DATABASE_NAME = 'arm'
    global HOST
    HOST = 'localhost'
    global PORT
    PORT = '3306'
    global USER_NAME
    USER_NAME = 'root'
    global PASSWORD
    PASSWORD = 'ybj'
    global CHAR_SET
    CHAR_SET = 'utf8'
    
#获取数据库连接
def get_conn():
    init()
    return MySQLdb.connect(host = HOST, user = USER_NAME, passwd = PASSWORD, db = DATABASE_NAME, charset = CHAR_SET)

#获取cursor
def get_cursor(conn):
    return conn.cursor()

#关闭连接
def conn_close(conn):
    if conn != None:
        conn.close()

#关闭cursor
def cursor_close(cursor):
    if cursor != None:
        cursor.close()

#关闭所有
def close(cursor, conn):
    cursor_close(cursor)
    conn_close(conn)

#创建表
def create_table():
    sql = '''
    CREATE TABLE  if not exists `point_data`(
    `id` int(8) NOT NULL,
    `alpha` numeric(20,10) NOT NULL,
    `beta` numeric(20,10) NOT NULL,
    `real_x` numeric(20,10) NOT NULL,
    `real_y` numeric(20,10) NOT NULL,
    PRIMARY KEY (`id`)
    ) ENGINE=InnoDB DEFAULT CHARSET=utf8
    '''
    conn = get_conn()
    cursor = get_cursor(conn)
    result = cursor.execute(sql)
    conn.commit()
    close(cursor, conn)
    return result

def delete_table():
    sql = '''
    DROP TABLE  point_data;
    '''
    conn = get_conn()
    cursor = get_cursor(conn)
    result = cursor.execute(sql)
    conn.commit()
    close(cursor, conn)
    return result    
#查询表信息
def query_table(table_name):
    if table_name != '':
        sql = 'select * from ' + table_name
        conn = get_conn()
        cursor = get_cursor(conn)
        result = cursor.execute(sql)
        for row in cursor.fetchall():
            print(row)
            #for r in row:      #循环每一条数据
                #print(r)
        close(cursor, conn)
    else:
        print('table name is empty!')

#插入数据
db_data = dict(id=1,alpha=0,beta=0,real_x=0,real_y=0)
def insert_table(db_data):
    sql = 'insert into point_data(id, alpha, beta, real_x, real_y) values(%s, %s, %s, %s, %s)'
    params = (db_data['id'], db_data['alpha'], db_data['beta'], db_data['real_x'], db_data['real_y'])
    conn = get_conn()
    cursor = get_cursor(conn)
    result = cursor.execute(sql, params)
    conn.commit()
    close(cursor, conn)
    return result

#更新数据
def update_table():
    sql = 'update student set name = %s where id = 1'
    params = ('HONGTEN')
    conn = get_conn()
    cursor = get_cursor(conn)
    result = cursor.execute(sql, params)
    conn.commit()
    close(cursor, conn)
    return result

#删除数据
def delete_data(id):
    sql = 'delete from point_data where id = %s'
    params = (id)
    conn = get_conn()
    cursor = get_cursor(conn)
    result = cursor.execute(sql, params)
    conn.commit()
    close(cursor, conn)
    return result

#数据库连接信息   
def print_info():
    print('数据库连接信息:' + DATABASE_NAME + HOST + PORT + USER_NAME + PASSWORD + CHAR_SET)

#打印出数据库中表情况
def show_databases():
    sql = 'show databases'
    conn = get_conn()
    cursor = get_cursor(conn)
    result = cursor.execute(sql)
    for row in cursor.fetchall():
        print(row)
        
#数据库中表情况
def show_tables():
    sql = 'show tables'
    conn = get_conn()
    cursor = get_cursor(conn)
    result = cursor.execute(sql)
    for row in cursor.fetchall():
        print(row)

   
def main():
    show_tables()
    #创建表
    result = create_table()
    print(result)
    #查询表
    query_table('point_data')
    #插入数据
    db_data = dict(id=1,alpha=2,beta=3,real_x=0,real_y=0)
    print(insert_table(db_data))
    print('插入数据后....')
    query_table('point_data')
    
    #删除数据
    # delete_data(0)
    # print('删除数据后....')
    query_table('point_data')
    print_info()
    #数据库中表情况
    show_tables()
    

if __name__ == '__main__':
    main()