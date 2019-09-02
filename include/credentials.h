#pragma once
#include <string>

class Credentials
{
    static constexpr char LOGIN_FIELD_NAME[] = "login";
    static constexpr char PASSWORD_FIELD_NAME[] = "password";
public:
    Credentials(std::string login, std::string key);
    static Credentials from_json(const std::string& json_string);
    static Credentials from_json_file(const std::string& json_file_path);
    std::string login;
    std::string key;
};

