#ifndef Country_hpp
#define Country_hpp

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 *  Data Transfer Object. Object containing fields only.
 *  Used in API for serialization/deserialization and validation
 */
class Country: public oatpp::DTO {

  DTO_INIT(Country, DTO)

  DTO_FIELD(String, code);
  DTO_FIELD(String, name);
  DTO_FIELD(String, emoji);
  DTO_FIELD(String, unicode);
  DTO_FIELD(String, image);
};

#include OATPP_CODEGEN_END(DTO)

#endif /* Country_hpp */
