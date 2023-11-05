//
// Created by 电脑 on 2023/11/4.
//

#ifndef SHOPPING_MALL_ENGINE_H
#define SHOPPING_MALL_ENGINE_H

#include <memory>
#include <string>
#include <spdlog/spdlog.h>
#include <sqlite3.h>

class Engine{
private:
    sqlite3* engine{};
public:
    explicit Engine(std::string& db_path){
        int rc = sqlite3_open(db_path.c_str(), &engine);
        if(rc!=SQLITE_OK){
            spdlog::critical("DB OPEN ERROR");
            exit(1);
        }
    }
    ~Engine(){
        sqlite3_close(engine);
    }
};

#endif //SHOPPING_MALL_ENGINE_H
