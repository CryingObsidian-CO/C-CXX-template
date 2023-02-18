#include <iostream>
#include "DataBase.h"

DataBase MySql = DataBase("MyBlogTest", "123456", "MyBlog_Test");

int main()
{
    std::cout << "test OK\n";
    return 0;
}