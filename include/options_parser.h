#pragma once
#include <string>
#include <optional>

#include <credentials.h>


class OptionsParser
{
    static constexpr char* SPECIFIED_ONLY_LOGIN_OR_PASSWORD_ERROR_MESSAGE =
            "Please, specify both login and password with -login and -password flags\n";
public:
    OptionsParser(int argc, char *argv[]);
    std::optional<std::string> parsing_error();
    enum Command
    {
        NOT_SET = 0,
        ADD,
        DELETE,
    };
    Command command();
    std::string path();

    std::optional<Credentials> credentials();

protected:
    Command _option = NOT_SET;
    std::string _path;
    std::string _parsing_error_message;
    std::string _login;
    std::string _password;
};