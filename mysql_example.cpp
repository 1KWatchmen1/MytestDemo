#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <iostream>

using namespace std;
using namespace sql::mysql;

int main() {
    try {
        // 获取 MySQL 驱动程序实例
        MySQL_Driver *driver = sql::mysql::get_mysql_driver_instance();

        // 创建连接对象
        std::unique_ptr<sql::Connection> con(driver->connect("tcp://127.0.0.1:3306", "root", "000522"));

        // 使用指定的数据库
        con->setSchema("test");

        // 执行查询
        std::unique_ptr<sql::Statement> stmt(con->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT 'Hello World!' AS message"));

        // 处理查询结果
        while (res->next()) {
            cout << "MySQL replies: " << res->getString("message") << endl;
        }
    } catch (sql::SQLException &e) {
        cerr << "SQLException: " << e.what() << endl;
        return 1;
    }

    return 0;
}

