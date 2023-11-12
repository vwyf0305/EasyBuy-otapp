//
// Created by 电脑 on 2023/11/5.
//

#ifndef SHOPPING_MALL_BUYPRODUCT_H
#define SHOPPING_MALL_BUYPRODUCT_H

#include "../Timestamp.h"
#include "../model/TokenEngine.h"
#include "UserToken.h"
#include "User.h"
#include "Orders.h"
#include "Product.h"
#include <json/json.h>
#include <blake3.h>
#include <string>
#include <spdlog/spdlog.h>
#include <sqlite_orm/sqlite_orm.h>
#include <oatpp/web/protocol/http/incoming/Request.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <oatpp/core/macro/codegen.hpp>

using namespace sqlite_orm;

class BuyProduct{
private:
    TokenEngine token_engine;
public:
    oatpp::Object<UserToken> GetProduct(const oatpp::Object<Product> product, std::string& token){
        std::string login_name = product->Name;
        std::string login_password = product->Password;
        std::string user_product = product->ProductName;
        auto user_token = UserToken::createShared();
        token = token_engine.get_token(login_name);
        user_token->Token = token;
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
        auto orders_storage = sqlite_orm::make_storage(R"(G:\C++ Files\shopping-mall\db\shopping-mall.db)",
                                                     sqlite_orm::make_table("orders",
                                                                            sqlite_orm::make_column("ID", &OrdersTable::ID, sqlite_orm::primary_key().autoincrement()),
                                                                            sqlite_orm::make_column("UserID", &OrdersTable::UserID),
                                                                            sqlite_orm::make_column("ProductID", &OrdersTable::ProductID),
                                                                            sqlite_orm::make_column("Quantity", &OrdersTable::Quantity),
                                                                            sqlite_orm::make_column("CreatedTime", &OrdersTable::Quantity)
                                                     ));
        auto get_user = user_storage.get_all<UserTable>(where(c(&UserTable::Name)==login_name) and c(&UserTable::Password)==login_password);
        int user_id = get_user.at(0).ID;
        auto get_product = product_storage.get_all<ProductTable>(where(c(&ProductTable::Name)==user_product));
        if(get_product.size()>1)
            spdlog::error("More than one product");
        else if(get_product.empty()){
            spdlog::critical("Cannot find this product {}", user_product);
            exit(1);
        }
        else{
            int product_id = get_product.at(0).ID;
            int product_quantity = get_product.at(0).Quantity;
            OrdersTable orders_table{-1, user_id, product_id, product_quantity-1, Timestamp::get_current_time()};
            orders_storage.insert(orders_table);
            ProductTable product_table{product_id, get_product.at(0).Name, get_product.at(0).Price, product_quantity-1, get_product.at(0).Favorites-1, get_product.at(0).SellerID};
            product_storage.update(product_table);
        }
        return user_token;
    }
};

#endif //SHOPPING_MALL_BUYPRODUCT_H
