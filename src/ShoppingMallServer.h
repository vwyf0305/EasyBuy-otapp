//
// Created by 电脑 on 2023/11/12.
//

#ifndef SHOPPING_MALL_SHOPPINGMALLSERVER_H
#define SHOPPING_MALL_SHOPPINGMALLSERVER_H

#include <oatpp/web/server/HttpConnectionHandler.hpp>
#include <oatpp/network/tcp/server/ConnectionProvider.hpp>
#include <oatpp/network/Server.hpp>
#include <memory>
#include "AppComponent.h"
#include "controller/MyController.h"
#include "controller/LoginController.h"
#include "controller/ProductController.h"
#include "controller/SellerController.h"

class ShoppingMallServer {
public:
    explicit ShoppingMallServer();
    ~ShoppingMallServer();
    void run();
private:


};


#endif //SHOPPING_MALL_SHOPPINGMALLSERVER_H
