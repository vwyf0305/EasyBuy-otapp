//
// Created by 电脑 on 2023/11/4.
//

#ifndef SHOPPING_MALL_USER_H
#define SHOPPING_MALL_USER_H

#include "../Timestamp.h"
#include "UserToken.h"
#include <blake3.h>
#include <jwt-cpp/jwt.h>
#include <vector>
#include <string>
#include <sqlite_orm/sqlite_orm.h>
#include <oatpp/web/protocol/http/incoming/Request.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <oatpp/core/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

class User : public oatpp::DTO {

    DTO_INIT(User, DTO)
    DTO_FIELD(String, Name); // 姓名
    DTO_FIELD(String, Role); // 身份
    DTO_FIELD(String, Password);
};



#include OATPP_CODEGEN_END(DTO)

struct UserTable {
    int ID;
    std::string Name;
    std::string Password;
    std::string Role;
    std::string CreatedTime;

    static std::string create_blak3(const std::string &data) {
        uint8_t hash[BLAKE3_OUT_LEN];

        // 创建blake3_hasher对象
        blake3_hasher hasher;
        blake3_hasher_init(&hasher);

        // 添加数据到blake3_hasher对象
        blake3_hasher_update(&hasher, data.c_str(), data.length());

        // 生成哈希值
        blake3_hasher_finalize(&hasher, hash, BLAKE3_OUT_LEN);

        // 将哈希值转换为token（使用Base64编码）
        std::string token;
        const char *base64_alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
        for (int i = 0; i < BLAKE3_OUT_LEN; i += 3) {
            uint32_t index = (hash[i] << 16) | (hash[i + 1] << 8) | hash[i + 2];
            token += base64_alphabet[(index >> 18) & 0x3F];
            token += base64_alphabet[(index >> 12) & 0x3F];
            token += base64_alphabet[(index >> 6) & 0x3F];
            token += base64_alphabet[index & 0x3F];
        }
        return token;
    }
    static std::string clip_password(const std::string& data){
        int data_length = static_cast<int>(data.length());
        int half_index{data_length/2};
        std::string data_clip = data.substr(half_index);
        std::string res;
        for(int i{1};i!=data_clip.length();i+2)
            res += data_clip.at(i);
        return res;

    }

};




#endif //SHOPPING_MALL_USER_H
