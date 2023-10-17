#ifndef CountryController_hpp
#define CountryController_hpp

#include "dto/Country.hpp"

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/web/server/api/ApiController.hpp"
#include "service/CountryService.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) //<-- Begin Codegen

/**
 * Sample Api Controller.
 */
class CountryController : public oatpp::web::server::api::ApiController {
private:
  CountryService countryService; // Create user service.
public:
  /**
   * Constructor with object mapper.
   * @param objectMapper - default object mapper used to serialize/deserialize
   * DTOs.
   */
  CountryController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>,
                                    objectMapper))
      : oatpp::web::server::api::ApiController(objectMapper) {}

public:
  ENDPOINT_INFO(getByCode) {
    info->summary = "Get country by code";

    info->addConsumes<Object<Country>>("application/json");

    info->addResponse<Object<Country>>(Status::CODE_200, "application/json");
    info->addResponse<Object<Country>>(Status::CODE_404, "application/json");
    info->pathParams["code"].description = "Country code (ex: FR)";
  }
  ENDPOINT("GET", "/country-services/api/country/{code}", getByCode, PATH(String, code)) {
    auto byId = countryService.getByCode(code);
    return createDtoResponse(Status::CODE_200, byId);
  }

  // TODO Insert Your endpoints here !!!
};

#include OATPP_CODEGEN_END(ApiController) //<-- End Codegen

#endif /* CountryController */
