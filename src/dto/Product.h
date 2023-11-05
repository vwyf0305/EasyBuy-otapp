//
// Created by 电脑 on 2023/11/5.
//

#ifndef SHOPPING_MALL_PRODUCT_H
#define SHOPPING_MALL_PRODUCT_H

#include <string>
#include <oatpp/web/protocol/http/incoming/Request.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <oatpp/core/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

class Product :public oatpp::DTO{
    DTO_INIT(Product, DTO);
    DTO_FIELD(String, Name);
    DTO_FIELD(String, Password);
    DTO_FIELD(String, ProductName);
};


#include OATPP_CODEGEN_END(DTO)

struct ProductTable{
    int ID;
    std::string Name;
    double Price;
    int Quantity;
    int Favorites;
};




#endif //SHOPPING_MALL_PRODUCT_H
