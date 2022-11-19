#include "ErrorHandler.hpp"
#include "dto/StatusDto.hpp"
#include <string>

ErrorHandler::ErrorHandler(
    const std::shared_ptr<oatpp::data::mapping::ObjectMapper> &objectMapper)
    : m_objectMapper(objectMapper) {}

std::shared_ptr<ErrorHandler::OutgoingResponse>
ErrorHandler::handleError(const Status &status, const oatpp::String &message,
                          const Headers &headers) {

  auto error = StatusDto::createShared();
  error->status = "ERROR";
  error->code = status.code;
  error->message = message;

  auto response =
      ResponseFactory::createResponse(status, error, m_objectMapper);

  for (const auto &pair : headers.getAll()) {
    response->putHeader(pair.first.toString(), pair.second.toString());
  }
  std::string errorMessage =
      error->status + std::to_string(error->code) + " => " + error->message;
  OATPP_LOGE(typeid(ErrorHandler).name(), errorMessage.c_str());
  return response;
}