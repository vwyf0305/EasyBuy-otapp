//
// Created by 电脑 on 2023/11/12.
//

#ifndef SHOPPING_MALL_SELLERCONTROLLER_H
#define SHOPPING_MALL_SELLERCONTROLLER_H

#include "../AppComponent.h"
#include "../dto/AddProduct.h"
#include <memory>
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

class SellerController:public oatpp::web::server::api::ApiController{
private:
    AddProduct add_product;
    std::shared_ptr<AuthorizationHandler> m_bearerAuthHandler = std::make_shared<oatpp::web::server::handler::BearerAuthorizationHandler>("shopping-mall");
public:
    explicit SellerController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
    : oatpp::web::server::api::ApiController(objectMapper)
            {}
    ENDPOINT("POST", "seller/add/product", add_product_, BODY_DTO(Object<NewProduct>, product),
             AUTHORIZATION(std::shared_ptr<oatpp::web::server::handler::DefaultBearerAuthorizationObject>, authObject, m_bearerAuthHandler /* qualifier */)){
        std::string token;
        auto product_dto = add_product.GetProduct(product, token);
        if(token.empty())
            return createDtoResponse(Status::CODE_404, product_dto);
        OATPP_ASSERT_HTTP(authObject->token == token, Status::CODE_401, "Unauthorized");
        return createDtoResponse(Status::CODE_200,  product_dto);
    }
};

#include OATPP_CODEGEN_END(ApiController) ///< End Codegen


#endif //SHOPPING_MALL_SELLERCONTROLLER_H
