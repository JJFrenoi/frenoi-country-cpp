#include "CountryService.hpp"
#include "dto/Country.hpp"
#include "dto/CountryContent.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <oatpp/core/Types.hpp>
#include <oatpp/core/data/mapping/type/Object.hpp>
#include <oatpp/core/data/stream/FileStream.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <string>
#include <utility>

CountryService::CountryService() { mapper = new ObjectMapper(); }
DTOWrapper<Country> CountryService::getByCode(string code) const {
  transform(code.begin(), code.end(), code.begin(), ::toupper);
  auto countryMap =
      mapper->readFromString<Fields<Object<CountryContent>>>(readJsonFile());
  auto countryList = countryMap.get();
  hasCode(code, countryList);
  auto content = countryMap.getValueByKey(code);
  return mapToCountry(code, content);
}
DTOWrapper<Country>
CountryService::mapToCountry(string code,
                             DTOWrapper<CountryContent> content) const {
  auto dto = Country::createShared();
  dto->code = code;
  dto->unicode = content->unicode;
  dto->emoji = content->emoji;
  dto->image = content->image;
  dto->name = content->name;
  return dto;
}
string CountryService::readJsonFile() const {
  ifstream countryJson(countryJsonPath);
  string strjson((istreambuf_iterator<char>(countryJson)),
                 istreambuf_iterator<char>());
  countryJson.close();
  return strjson;
}
void CountryService::hasCode(
    String code,
    list<pair<String, DTOWrapper<CountryContent>>> *mapContent) const {
  auto countryMap =
      mapper->readFromString<Fields<Object<CountryContent>>>(readJsonFile());
  auto containKey = [code](pair<String, DTOWrapper<CountryContent>> i) {
    return i.first == code;
  };
  auto hasCode = find_if(mapContent->begin(), mapContent->end(), containKey);

  OATPP_ASSERT_HTTP(hasCode != mapContent->end(), Status::CODE_404,
                    "No country found with code: " + code);
}
CountryService::~CountryService() { delete mapper; }