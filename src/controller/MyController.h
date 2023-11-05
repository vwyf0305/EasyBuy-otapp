//
// Created by 电脑 on 2023/11/4.
//

#ifndef OATPP_TEST_MYCONTROLLER_H
#define OATPP_TEST_MYCONTROLLER_H

#include "../dto/DTO.h"
#include "../AppComponent.h"
#include <oatpp/web/server/api/ApiController.hpp>
#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/macro/component.hpp>

#include OATPP_CODEGEN_BEGIN(ApiController) ///< Begin Codegen

/**
 * Sample Api Controller.
 */
class MyController : public oatpp::web::server::api::ApiController {
public:
    /**
     * Constructor with object mapper.
     * @param objectMapper - default object mapper used to serialize/deserialize DTOs.
     */
    explicit MyController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
            : oatpp::web::server::api::ApiController(objectMapper)
    {}
public:

    ENDPOINT("GET", "/hello", root) {
        auto dto = MessageDto::createShared();
        dto->statusCode = 200;
        dto->message = "Hello World!";
        return createDtoResponse(Status::CODE_200, dto);
    }

    // TODO Insert Your endpoints here !!!

};

#include OATPP_CODEGEN_END(ApiController) ///< End Codegen

#endif //OATPP_TEST_MYCONTROLLER_H
