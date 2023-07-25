#include "utils.h"
#include "config/config.h"

std::shared_ptr<odb::database> getDB() {
    auto config = getConfig();
    auto mysqlConfig = config["mysql"];
    // database (const char* user,
    //             const char* passwd,
    //             const char* db,
    //             const char* host = 0,
    //             unsigned int port = 0,
    auto user = mysqlConfig["user"].as<std::string>();
    auto password = mysqlConfig["password"].as<std::string>();
    auto database = mysqlConfig["database"].as<std::string>();
    auto host = mysqlConfig["host"].as<std::string>();
    auto port = mysqlConfig["port"].as<unsigned int>();

    std::shared_ptr<odb::database> db(new odb::mysql::database(
        user.c_str(), password.c_str(), database.c_str(), host.c_str(), port));
    return db;
}