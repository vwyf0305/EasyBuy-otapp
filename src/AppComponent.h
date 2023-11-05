//
// Created by 电脑 on 2023/11/4.
//

#ifndef OATPP_TEST_APPCOMPONENT_H
#define OATPP_TEST_APPCOMPONENT_H

#include <memory>
#include <oatpp/core/macro/component.hpp>
#include <oatpp/web/server/HttpConnectionHandler.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <oatpp/network/tcp/server/ConnectionProvider.hpp>

class AppComponent {
public:

    /**
     *  Create ConnectionProvider component which listens on the port
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, serverConnectionProvider)([] {
        return oatpp::network::tcp::server::ConnectionProvider::createShared({"localhost", 8080, oatpp::network::Address::IP_4});
    }());

    /**
     *  Create Router component
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, httpRouter)([] {
        return oatpp::web::server::HttpRouter::createShared();
    }());

    /**
     *  Create ConnectionHandler component which uses Router component to route requests
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, serverConnectionHandler)([] {
        OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router); // get Router component
        return oatpp::web::server::HttpConnectionHandler::createShared(router);
    }());

    /**
     *  Create ObjectMapper component to serialize/deserialize DTOs in Contoller's API
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, apiObjectMapper)([] {
        return oatpp::parser::json::mapping::ObjectMapper::createShared();
    }());

};



#endif //OATPP_TEST_APPCOMPONENT_H
