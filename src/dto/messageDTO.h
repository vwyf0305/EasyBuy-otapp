//
// Created by 电脑 on 2023/11/4.
//

#ifndef OATPP_TEST_MESSAGEDTO_H
#define OATPP_TEST_MESSAGEDTO_H

#include "DTO.h"
#include "../AppComponent.h"
#include <memory>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <oatpp/web/server/HttpConnectionHandler.hpp>
#include <oatpp/network/Server.hpp>
#include <oatpp/network/tcp/server/ConnectionProvider.hpp>
#include <oatpp/core/macro/codegen.hpp>


class Handler_DTO : public oatpp::web::server::HttpRequestHandler {
private:
    OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, m_objectMapper);
public:

    /**
     * Constructor with object mapper.
     * @param objectMapper - object mapper used to serialize objects.
     */


    /**
     * Handle incoming request and return outgoing response.
     */
    std::shared_ptr<OutgoingResponse> handle(const std::shared_ptr<IncomingRequest>& request) override {
        auto message = MessageDto::createShared();
        message->statusCode = 1024;
        message->message = "Hello DTO!";
        return ResponseFactory::createResponse(Status::CODE_200, message, m_objectMapper);
    }

};

#endif //OATPP_TEST_MESSAGEDTO_H
