//
// Created by 电脑 on 2023/11/4.
//

#ifndef SHOPPING_MALL_USERS_ENGINE_H
#define SHOPPING_MALL_USERS_ENGINE_H

#include <string>
#include <sqlite_orm/sqlite_orm.h>

const std::string DbPath = R"(G:\C++ Files\shopping-mall\db\shopping-mall.db)";

struct UserTable{
    int ID;
    std::string Name;
    std::string Password;
    std::string Role;
    std::string CreatedTime;
};

class UsersEngine{
public:
    explicit UsersEngine(const std::string db_path): db_path(db_path){

    }

    decltype(storage) create_engine(){
        auto storage = sqlite_orm::make_storage(db_path,
                                                sqlite_orm::make_table("users",
                                                                       sqlite_orm::make_column("ID", &UserTable::ID, sqlite_orm::primary_key().autoincrement()),
                                                                       sqlite_orm::make_column("UserName", &UserTable::Name),
                                                                       sqlite_orm::make_column("Password", &UserTable::Password),
                                                                       sqlite_orm::make_column("Role", &UserTable::Role),
                                                                       sqlite_orm::make_column("CreatedTime", &UserTable::CreatedTime)
                                                ));
    }
private:
    std::string db_path;
};

#endif //SHOPPING_MALL_USERS_ENGINE_H
