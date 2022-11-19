#ifndef CRUD_COUNTRYSERVICE_HPP
#define CRUD_COUNTRYSERVICE_HPP
#include "dto/Country.hpp"
#include "dto/CountryContent.hpp"
#include <map>
#include <oatpp/core/Types.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <oatpp/web/protocol/http/Http.hpp>
#include <string>
using namespace oatpp;
using namespace std;
using data::mapping::type::DTOWrapper;
using oatpp::data::mapping::type::String;
using parser::json::mapping::ObjectMapper;
class CountryService {
private:
  typedef web::protocol::http::Status Status;
  void
  hasCode(String code,
          list<pair<String, DTOWrapper<CountryContent>>> *mapContent) const;
  ObjectMapper *mapper;
  DTOWrapper<Country> mapToCountry(string code,
                                   DTOWrapper<CountryContent> content) const;
  string readJsonFile() const;
  inline static const std::string countryJsonPath = "resources/by-code.json";

public:
  CountryService();
  DTOWrapper<Country> getByCode(std::string code) const;
  ~CountryService();
};
#endif // CRUD_COUNTRYSERVICE_HPP