//
// Created by 电脑 on 2023/11/4.
//

#ifndef SHOPPING_MALL_TIMESTAMP_H
#define SHOPPING_MALL_TIMESTAMP_H

#include <ctime>
#include <string>

class Timestamp{
private:
    static std::string current_time;
public:
    Timestamp()= default;
    static std::string get_current_time(){
        time_t currentTime;
        struct tm *timeInfo;
        char timeString[20];

        // 获取当前时间
        time(&currentTime);
        timeInfo = localtime(&currentTime);

        // 格式化时间字符串
        strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M", timeInfo);
        std::string res = timeString;
        return res;
    }
};

#endif //SHOPPING_MALL_TIMESTAMP_H
