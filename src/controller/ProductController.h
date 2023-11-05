//
// Created by 电脑 on 2023/11/5.
//

#ifndef SHOPPING_MALL_PRODUCTCONTROLLER_H
#define SHOPPING_MALL_PRODUCTCONTROLLER_H

#include "../AppComponent.h"
#include "../dto/BuyProduct.h"
#include <memory>
#include <jwt-cpp/jwt.h>
#include <oatpp/web/server/api/ApiController.hpp>
#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/web/server/HttpRequestHandler.hpp>
#include <oatpp/web/server/handler/AuthorizationHandler.hpp>
#include <oatpp/web/protocol/http/incoming/SimpleBodyDecoder.hpp>
#include <oatpp/web/protocol/http/outgoing/ResponseFactory.hpp>
#include <oatpp/web/protocol/http/incoming/Request.hpp>
#include <oatpp/web/protocol/http/outgoing/BufferBody.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <oatpp/core/macro/component.hpp>

#include OATPP_CODEGEN_BEGIN(ApiController) ///< Begin Codegen

class ProductController:public oatpp::web::server::api::ApiController {
private:
    BuyProduct buy_product;
    std::shared_ptr<AuthorizationHandler> m_bearerAuthHandler = std::make_shared<oatpp::web::server::handler::BearerAuthorizationHandler>("shopping-mall");
public:
    explicit ProductController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
    : oatpp::web::server::api::ApiController(objectMapper)
            {}
    ENDPOINT("GET", "/user/product", get_product, BODY_DTO(Object<Product>, product),
             AUTHORIZATION(std::shared_ptr<oatpp::web::server::handler::DefaultBearerAuthorizationObject>, authObject, m_bearerAuthHandler /* qualifier */)) {
        std::string token;
        auto product_dto =  buy_product.GetProduct(product, token);
        OATPP_ASSERT_HTTP(authObject->token == token, Status::CODE_401, "Unauthorized");
        return createDtoResponse(Status::CODE_200, product_dto);
    }
};

#include OATPP_CODEGEN_END(ApiController) ///< End Codegen


#endif //SHOPPING_MALL_PRODUCTCONTROLLER_H
