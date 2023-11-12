//
// Created by 电脑 on 2023/11/12.
//

#ifndef SHOPPING_MALL_ADDPRODUCT_H
#define SHOPPING_MALL_ADDPRODUCT_H

#include "../Timestamp.h"
#include "../model/TokenEngine.h"
#include "UserToken.h"
#include "User.h"
#include "Orders.h"
#include "Product.h"
#include "NewProduct.h"
#include <json/json.h>
#include <blake3.h>
#include <string>
#include <spdlog/spdlog.h>
#include <sqlite_orm/sqlite_orm.h>
#include <oatpp/web/protocol/http/incoming/Request.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <oatpp/core/macro/codegen.hpp>
using namespace sqlite_orm;


class AddProduct{
private:
    TokenEngine token_engine;
public:
    oatpp::Object<UserToken> GetProduct(const oatpp::Object<NewProduct> product, std::string& token) {
        auto user_token = UserToken::createShared();
        std::string login_name = product->Name;
        std::string login_password = product->Password;
        std::string user_product = product->ProductName;
        double price = product->Price;

        auto product_storage = sqlite_orm::make_storage(R"(G:\C++ Files\shopping-mall\db\shopping-mall.db)",
                                                        sqlite_orm::make_table("product",
                                                                               sqlite_orm::make_column("ID", &ProductTable::ID, sqlite_orm::primary_key().autoincrement()),
                                                                               sqlite_orm::make_column("Name", &ProductTable::Name),
                                                                               sqlite_orm::make_column("Price", &ProductTable::Price),
                                                                               sqlite_orm::make_column("Quantity", &ProductTable::Quantity),
                                                                               sqlite_orm::make_column("Favorites", &ProductTable::Favorites),
                                                                               sqlite_orm::make_column("SellerID", &ProductTable::SellerID)
                                                        ));
        auto user_storage = sqlite_orm::make_storage(R"(G:\C++ Files\shopping-mall\db\shopping-mall.db)",
                                                     sqlite_orm::make_table("users",
                                                                            sqlite_orm::make_column("ID", &UserTable::ID, sqlite_orm::primary_key().autoincrement()),
                                                                            sqlite_orm::make_column("UserName", &UserTable::Name),
                                                                            sqlite_orm::make_column("Password", &UserTable::Password),
                                                                            sqlite_orm::make_column("Role", &UserTable::Role),
                                                                            sqlite_orm::make_column("CreatedTime", &UserTable::CreatedTime)
                                                     ));
        auto get_user = user_storage.get_all<UserTable>(where(c(&UserTable::Name)==login_name) and c(&UserTable::Password)==login_password);
        if(get_user.empty())
            token = "";
        token = token_engine.get_token(login_name);
        user_token->Token = token;
        std::string user_role = get_user.at(0).Role;
        if(user_role!="seller")
            user_role = "seller/customer";
        ProductTable productTable{-1, user_product, price, 0,0, get_user.at(0).ID};
        UserTable userTable{get_user.at(0).ID, get_user.at(0).Name,get_user.at(0).Password, user_role, get_user.at(0).CreatedTime};
        product_storage.insert(productTable);
        user_storage.update(userTable);
        return user_token;
    }
};

#endif //SHOPPING_MALL_ADDPRODUCT_H
