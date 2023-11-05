//
// Created by 电脑 on 2023/11/4.
//

#ifndef SHOPPING_MALL_USERDAO_H
#define SHOPPING_MALL_USERDAO_H
#include "../Timestamp.h"
#include "UserToken.h"
#include "User.h"
#include <blake3.h>
#include <string>
#include <sqlite_orm/sqlite_orm.h>
#include <oatpp/web/protocol/http/incoming/Request.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <oatpp/core/macro/codegen.hpp>



class UserDao {
public:

    oatpp::Object<User> CreateUser(const oatpp::Object<User>& user) {

        // user->Password = UserTable::create_blak3(user->Password);
        auto storage = sqlite_orm::make_storage(R"(G:\C++ Files\shopping-mall\db\shopping-mall.db)",
                                                sqlite_orm::make_table("users",
                                                                       sqlite_orm::make_column("ID", &UserTable::ID, sqlite_orm::primary_key().autoincrement()),
                                                                       sqlite_orm::make_column("UserName", &UserTable::Name),
                                                                       sqlite_orm::make_column("Password", &UserTable::Password),
                                                                       sqlite_orm::make_column("Role", &UserTable::Role),
                                                                       sqlite_orm::make_column("CreatedTime", &UserTable::CreatedTime)
                                                ));
        UserTable user_ {-1, user->Name, user->Password, user->Role,Timestamp::get_current_time()};
        storage.insert(user_);
        return user;
    }

private:


};

#endif //SHOPPING_MALL_USERDAO_H
