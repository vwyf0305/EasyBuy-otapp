//
// Created by 电脑 on 2023/11/4.
//

#ifndef SHOPPING_MALL_LOGINCONTROLLER_H
#define SHOPPING_MALL_LOGINCONTROLLER_H

#include "../AppComponent.h"
#include "../dto/User.h"
#include "../dto/UserDao.h"
#include "../dto/UserLogin.h"
#include <jwt-cpp/jwt.h>
#include <oatpp/web/server/api/ApiController.hpp>
#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/web/server/HttpRequestHandler.hpp>
#include <oatpp/web/protocol/http/incoming/SimpleBodyDecoder.hpp>
#include <oatpp/web/protocol/http/outgoing/ResponseFactory.hpp>
#include <oatpp/web/protocol/http/incoming/Request.hpp>
#include <oatpp/web/protocol/http/outgoing/BufferBody.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <oatpp/core/macro/component.hpp>

#include OATPP_CODEGEN_BEGIN(ApiController) ///< Begin Codegen

class LoginController : public oatpp::web::server::api::ApiController{
public:
    explicit LoginController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
            : oatpp::web::server::api::ApiController(objectMapper)
    {}



    ENDPOINT("POST", "user/register", register_, BODY_DTO(Object<User>, user)){

        auto user_dto = user_dao.CreateUser(user);
        return createDtoResponse(Status::CODE_200, user_dto);
    }
    ENDPOINT("POST", "user/login", login_, BODY_DTO(Object<User>, user)){

        auto user_login_dto = user_login.LoginUser(user);
        if(user_login_dto->Token=="")
            return createDtoResponse(Status::CODE_401, user_login_dto);
        return createDtoResponse(Status::CODE_200, user_login_dto);
    }
    ENDPOINT("POST", "user/login_out", login_out, BODY_DTO(Object<User>, user)){

        auto user_login_dto = user_login.LoginOutUser(user);
        return createDtoResponse(Status::CODE_200, user_login_dto);
    }
private:
    UserDao user_dao;
    UserLogin user_login;
};

#include OATPP_CODEGEN_END(ApiController) ///< End Codegen

#endif //SHOPPING_MALL_LOGINCONTROLLER_H
