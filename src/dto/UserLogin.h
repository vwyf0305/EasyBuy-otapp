//
// Created by 电脑 on 2023/11/4.
//

#ifndef SHOPPING_MALL_USERLOGIN_H
#define SHOPPING_MALL_USERLOGIN_H
#include "../Timestamp.h"
#include "UserToken.h"
#include "User.h"
#include <spdlog/spdlog.h>
#include <sw/redis++/redis++.h>
#include <jwt-cpp/jwt.h>
#include <blake3.h>
#include <string>
#include "../model//TokenEngine.h"
#include <sqlite_orm/sqlite_orm.h>
#include <oatpp/web/protocol/http/incoming/Request.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <oatpp/core/macro/codegen.hpp>

using namespace sqlite_orm;


class UserLogin{
public:
    oatpp::Object<UserToken> LoginUser(const oatpp::Object<User>& user){
        std::string login_name = user->Name;
        std::string login_password = user->Password;
        // std::string tmp = UserTable::create_blak3(UserTable::clip_password(login_name+login_password));

        auto user_token = UserToken::createShared();
        user_token->Token = UserTable::create_blak3(login_password);

        auto storage = sqlite_orm::make_storage(R"(G:\C++ Files\shopping-mall\db\shopping-mall.db)",
                                                sqlite_orm::make_table("users",
                                                                       sqlite_orm::make_column("ID", &UserTable::ID, sqlite_orm::primary_key().autoincrement()),
                                                                       sqlite_orm::make_column("UserName", &UserTable::Name),
                                                                       sqlite_orm::make_column("Password", &UserTable::Password),
                                                                       sqlite_orm::make_column("Role", &UserTable::Role),
                                                                       sqlite_orm::make_column("CreatedTime", &UserTable::CreatedTime)
                                                ));
        auto user_login_isget = storage.select(&UserTable::ID, sqlite_orm::where(sqlite_orm::c(&UserTable::Name) == login_name  and sqlite_orm::c(&UserTable::Password) == login_password));
        if(user_login_isget.empty()){
            user_token->Token = "";
            return user_token;
        }

        token_engine.set_token(login_name, user_token->Token);
        return user_token;
    }

    oatpp::Object<UserToken> LoginOutUser(const oatpp::Object<User>& user){
        std::string login_name = user->Name;
        std::string login_password = user->Password;
        auto user_token = UserToken::createShared();
        user_token->Token = UserTable::create_blak3(login_password);
        token_engine.del_token(login_name);
        return user_token;
    }
private:
    TokenEngine token_engine;
};

#endif //SHOPPING_MALL_USERLOGIN_H
