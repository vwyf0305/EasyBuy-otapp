#include <oatpp/web/server/HttpConnectionHandler.hpp>
#include <oatpp/network/tcp/server/ConnectionProvider.hpp>
#include <oatpp/network/Server.hpp>
#include <memory>
#include "controller/MyController.h"
#include "controller/LoginController.h"
#include "controller/ProductController.h"
#include "controller/SellerController.h"

void run()
{
    AppComponent components;

    /* Get router component */
    OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);
    auto my_controller = std::make_shared<MyController>();
    auto login_controller = std::make_shared<LoginController>();
    auto product_controller = std::make_shared<ProductController>();
    auto seller_controller = std::make_shared<SellerController>();
    /* Route GET - "/hello" requests to Handler */
    // router->route("GET", "/hello", std::make_shared<Handler_DTO>());
    router->addController(my_controller);
    router->addController(login_controller);
    router->addController(product_controller);
    router->addController(seller_controller);
    /* Get connection handler component */
    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, connectionHandler);

    /* Get connection provider component */
    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider);

    /* Create server which takes provided TCP connections and passes them to HTTP connection handler */
    oatpp::network::Server server(connectionProvider, connectionHandler);

    /* Priny info about server port */
    OATPP_LOGI("MyApp", "Server running on port %s", connectionProvider->getProperty("port").getData());

    /* Run server */
    server.run();
}

int main()
{

    oatpp::base::Environment::init();
    run();
    oatpp::base::Environment::destroy();

    return 0;
}
