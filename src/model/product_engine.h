//
// Created by 电脑 on 2023/11/4.
//

#ifndef SHOPPING_MALL_PRODUCT_ENGINE_H
#define SHOPPING_MALL_PRODUCT_ENGINE_H

#include <string_view>
#include <sqlite3.h>
#include <sqlite_orm/sqlite_orm.h>

using namespace sqlite_orm;

struct product{
    int ID;
    std::string_view Name;
    double Price;
    int Quantity;
    int Favorites;
};




#endif //SHOPPING_MALL_PRODUCT_ENGINE_H
