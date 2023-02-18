#include "DataBase.h"

/// @brief 构造类并连接数据库（主机名默认为localhost，端口号默认为3306）
/// @param user 用户名
/// @param password 密码
DataBase::DataBase(std::string user, std::string password, std::string database)
{
    DataBase("localhost", user, password, database, 3306);
}
/// @brief 构造类并连接数据库
/// @param host 主机名
/// @param user 用户名
/// @param password 密码
/// @param database 数据库名
/// @param port 端口号
/// @return
DataBase::DataBase(std::string host, std::string user, std::string password, std::string database, unsigned int port)
{
    _isConnect = false;
    mysql_init(&mysql);
    if (!ConnectSQL(host.c_str(), user.c_str(), password.c_str(), database.c_str(), port))
    {
        printf("数据库连接失败：ConnectSQL(%s, %s, %s, %s, %d) 返回 false", host, user, password, database, port);
    }
    //! 在第一次配置时执行(等初次设置的函数完成后)
    mysql_set_character_set(&mysql, "utf8mb3");
}

/// @brief 析构类
DataBase::~DataBase()
{
    // 释放结果集
    mysql_free_result(res);
    // 关闭数据库连接
    mysql_close(&mysql);
    // 标记断开连接
    _isConnect = false;
}

/// @brief 连接数据库
/// @param host 主机名
/// @param user 用户名
/// @param password 密码
/// @param database 数据库名
/// @param port 端口号
/// @return true : 已连接   false : 未连接
bool DataBase::ConnectSQL(std::string host, std::string user, std::string password, std::string database, unsigned int port)
{
    if (isConnect())
    {
        printf("数据库已连接，请勿重复连接\n");
        return false;
    }
    // 连接数据库（句柄、主机名、用户名、密码、数据库名、端口号、socket指针、标记）
    // 返回 0 连接失败
    if (!mysql_real_connect(&mysql, host.c_str(), user.c_str(), password.c_str(), database.c_str(), port, nullptr, 0))
    {
        printf("数据库连接失败（%n）：%s\n", mysql_errno(&mysql), mysql_error(&mysql));
        return false;
    }
    _isConnect = true;
    printf("数据库连接成功\n");
    return true;
}

/// @brief 获取相应的表的字段的个数
/// @param table_name 需要获取的表
/// @return 相应的表的字段个数
int DataBase::GetTableField(std::string table_name)
{
    if (!isConnect())
    {
        printf("数据库未连接\n");
        return -1;
    }
    // 查询内容
    sprintf_s(query, "desc %s", table_name.c_str());

    // 返回 0 查询成功，返回 1 查询失败
    if (mysql_real_query(&mysql, query, (unsigned int)strlen(query)))
    {
        printf("查询失败（%n）：%s\n", mysql_errno(&mysql), mysql_error(&mysql));
        return false;
    }
    // 获取结果集
    if (!(res = mysql_store_result(&mysql)))
    {
        printf("无法获取结果集（%n）：%s\n", mysql_errno(&mysql), mysql_error(&mysql));
        return false;
    }
    // 数据行数即为字段个数
    return mysql_affected_rows(&mysql);
}

/// @brief 决定查询数据库的返回类型
/// @tparam T 返回类型（为 int 或 string）
/// @param table_name 需要获取的表
/// @return 查询的数据
template <>
int DataBase::QueryField(std::string table_name)
{
    if (!isConnect())
    {
        printf("数据库未连接\n");
        return -1;
    }
    return -1;
}

/// @brief 决定查询数据库的返回类型
/// @tparam T 返回类型（为 int 或 string）
/// @param table_name 需要获取的表
/// @return 查询的数据
template <>
std::string DataBase::QueryField(std::string table_name)
{
    if (!isConnect())
    {
        printf("数据库未连接\n");
        return "";
    }
    return "";
}

/// @brief 决定查询数据库的返回类型
/// @tparam T 返回类型（为 int 或 string）
/// @param table_name 需要获取的表
/// @return 查询的数据（当前返回类型无效）
template <typename T>
T DataBase::QueryField(std::string table_name)
{
    printf("无效返回类型\n");
    return -1;
}

/// @brief 数据库连接状态
/// @return true : 已连接   false : 未连接
bool DataBase::isConnect()
{
    return _isConnect;
}