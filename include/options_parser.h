#pragma once

#include <string>
#include <optional>

#include <cxxopts.hpp>

#include <credentials.h>


class OptionsParser {
    static constexpr char *SPECIFIED_ONLY_LOGIN_OR_PASSWORD_ERROR_MESSAGE =
            "Please, specify both login and password with --login and --password flags\n";
    static constexpr auto LOGIN_CLI_ARG = "login";
    static constexpr auto PASSWORD_CLI_ARG = "password";
    static constexpr auto ADD_FILE_CLI_ARG = "add";
    static constexpr auto DEL_FILE_CLI_ARG = "delete";

public:
    enum Command {
        NOT_SET = 0,
        ADD,
        DELETE,
    };

    OptionsParser();

    bool parse(int argc, char *argv[]);
    std::string error_message() const;

    const Command&     command() const;
    const std::string& path() const;
    Credentials        credentials() const;

protected:
    void _process_one_argument(const std::string &argument, const std::string &value);
    void _clear();

    cxxopts::Options _cli_options_parser;
    Command _option = NOT_SET;
    std::string _path;
    std::string _error_message;
    std::string _login;
    std::string _password;
};