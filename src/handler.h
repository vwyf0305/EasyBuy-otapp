#ifndef HANDLER_H
#define HANDLER_H

#include <memory>
#include <oatpp/web/server/HttpRequestHandler.hpp>

#define O_UNUSED(x) (void)x;

// �Զ������������
class Handler : public oatpp::web::server::HttpRequestHandler
{
public:
    // ����������󣬲�������Ӧ
    std::shared_ptr<OutgoingResponse> handle(const std::shared_ptr<IncomingRequest>& request) override {
        O_UNUSED(request);

        return ResponseFactory::createResponse(Status::CODE_200, "Hello, World!");
    }
};

#endif // HANDLER_H