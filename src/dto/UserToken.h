//
// Created by 电脑 on 2023/11/4.
//

#ifndef SHOPPING_MALL_USERTOKEN_H
#define SHOPPING_MALL_USERTOKEN_H


#include <sqlite_orm/sqlite_orm.h>
#include <oatpp/web/protocol/http/incoming/Request.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <oatpp/core/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

class UserToken:public oatpp::DTO{
    DTO_INIT(UserToken, DTO)
    DTO_FIELD(String, Token);
};

#include OATPP_CODEGEN_END(DTO)

#endif //SHOPPING_MALL_USERTOKEN_H
