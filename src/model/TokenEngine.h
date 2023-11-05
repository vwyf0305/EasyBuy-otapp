//
// Created by 电脑 on 2023/11/5.
//

#ifndef SHOPPING_MALL_TOKENENGINE_H
#define SHOPPING_MALL_TOKENENGINE_H

#include <spdlog/spdlog.h>
#include <sw/redis++/redis++.h>
#include <string>

class TokenEngine{
private:
    sw::redis::Redis redis_engine{"tcp://127.0.0.1:6379"};
public:
    explicit TokenEngine()  {

    }
    void set_token(const std::string& data, const std::string& token){
        redis_engine.set(data, token);
    }
    std::string get_token(const std::string& data){
        std::optional<std::string> token = redis_engine.get(data);
        if(!token.has_value())
            return "";
        return token.value();
    }
    void del_token(const std::string& data){
        redis_engine.del(data);
    }

};

#endif //SHOPPING_MALL_TOKENENGINE_H
