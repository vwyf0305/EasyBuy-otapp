//
// Created by 电脑 on 2023/11/4.
//

#ifndef OATPP_TEST_DTO_H
#define OATPP_TEST_DTO_H

#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <oatpp/core/macro/codegen.hpp>


/* Begin DTO code-generation */
#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * Message Data-Transfer-Object
 */
class MessageDto : public oatpp::DTO {

    DTO_INIT(MessageDto, DTO /* Extends */)

    DTO_FIELD(Int32, statusCode);   // Status code field
    DTO_FIELD(String, message);     // Message field

};

/* End DTO code-generation */


#endif //OATPP_TEST_DTO_H
