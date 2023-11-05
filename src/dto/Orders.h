//
// Created by 电脑 on 2023/11/5.
//

#ifndef SHOPPING_MALL_ORDERS_H
#define SHOPPING_MALL_ORDERS_H

#include <string>

struct OrdersTable{
    int ID;
    int UserID;
    int ProductID;
    int Quantity;
    std::string CreatedTime;
};


#endif //SHOPPING_MALL_ORDERS_H
