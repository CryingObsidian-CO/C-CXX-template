#ifndef DATA_BASE_H
#define DATA_BASE_H

#include <string>
#include <mysql.h>
#include <iostream>

class DataBase
{
public:
private:
    bool _isConnect;
    // 创建数据库句柄
    MYSQL mysql;
    // 创建数据库查询结果集
    MYSQL_RES *res = nullptr;
    // 一个行数据的类型安全(type-safe)的表示
    MYSQL_ROW row;
    // 查询语句
    char query[300];

public:
    ~DataBase();
    DataBase(std::string user, std::string password, std::string database);
    DataBase(std::string host, std::string user, std::string password, std::string database, unsigned int port);

    template <typename T>
    T QueryField(std::string table_name);

    int GetTableField(std::string table_name);

    bool isConnect();

private:
    bool ConnectSQL(std::string host, std::string user, std::string password, std::string database, unsigned int port);
};

#endif