#include "options_parser.h"
#include <cxxopts.hpp>


OptionsParser::OptionsParser(int argc, char **argv)
{
    if (argc < 2)
        throw std::invalid_argument("No option specified for options parser");
    cxxopts::Options options("Test app", "");
    options.add_options()
            ("a,add", "", cxxopts::value<std::string>())
            ("d,delete", "", cxxopts::value<std::string>())
            ("login", "", cxxopts::value<std::string>())
            ("password", "", cxxopts::value<std::string>());
    try {
        auto result = options.parse(argc, argv);
        for (auto& arg : result.arguments())
        {
            if (_option != NOT_SET)
            {
                if (arg.key() == "add") {
                    _path = arg.value();
                    _option = this->ADD;
                }
                else if (arg.key() == "delete") {
                    _path = arg.value();
                    _option = this->DELETE;
                }
            }
            else
            {
                if (arg.key() == "login")
                    _login = arg.value();
                else if (arg.key() == "password")
                    _password = arg.value();
            }
        }
        auto login_specified = _login.length() != 0;
        auto password_specified = _password.length() != 0;
        auto specified_only_login_or_password = login_specified ^ password_specified;
        if (specified_only_login_or_password)
            _parsing_error_message = SPECIFIED_ONLY_LOGIN_OR_PASSWORD_ERROR_MESSAGE;
        return;
    } catch (std::exception e){
        _parsing_error_message = e.what();
    };
}

OptionsParser::Command OptionsParser::command() {
    return _option;
}

std::string OptionsParser::path() {
    return _path;
}

std::optional<std::string> OptionsParser::parsing_error() {
    if (_parsing_error_message.length())
        return _parsing_error_message;
    return std::nullopt;
}

std::optional<Credentials> OptionsParser::credentials() {
    if(_login.length() && _password.length())
        return Credentials(_login, _password);
    return std::nullopt;
}


