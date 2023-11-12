//
// Created by 电脑 on 2023/11/12.
//

#ifndef SHOPPING_MALL_NEWPRODUCT_H
#define SHOPPING_MALL_NEWPRODUCT_H

#include <string>
#include <oatpp/web/protocol/http/incoming/Request.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <oatpp/core/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

class NewProduct:public oatpp::DTO {
    DTO_INIT(NewProduct, DTO);
    DTO_FIELD(String, Name);
    DTO_FIELD(String, Password);
    DTO_FIELD(String, ProductName);
    DTO_FIELD(Float64 , Price);
};

#include OATPP_CODEGEN_END(DTO)

#endif //SHOPPING_MALL_NEWPRODUCT_H
