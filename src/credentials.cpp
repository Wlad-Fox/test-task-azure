#include <credentials.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

Credentials::Credentials(std::string login, std::string key)
    : login(login)
    , key(key)
{
}

Credentials Credentials::from_json(const std::string& json_string) {
    auto creds_json = json::parse(json_string);
    bool contains_credentials = creds_json.contains(LOGIN_FIELD_NAME) && creds_json.contains(PASSWORD_FIELD_NAME);
    if (!contains_credentials)
    {
        auto err = std::string("Json string doesn't contains fields \"") + LOGIN_FIELD_NAME + "\" and \"" + PASSWORD_FIELD_NAME + "\"";
        throw std::invalid_argument(std::move(err));
    }
    return Credentials(creds_json[LOGIN_FIELD_NAME], creds_json[PASSWORD_FIELD_NAME]);
}

Credentials Credentials::from_json_file(const std::string &json_file_path) {
    std::ifstream file(json_file_path);
    if (!file.is_open())
        throw std::invalid_argument(std::string("Cannot open file \"" + json_file_path + "\""));
    std::stringstream sstream;
    sstream << file.rdbuf();
    std::string json_string(sstream.str());
    return Credentials::from_json(json_string);
}
