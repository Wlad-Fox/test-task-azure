#include <options_parser.h>


OptionsParser::OptionsParser()
        : _cli_options_parser("Test app", "App super puper") {
    _clear();
    _cli_options_parser.add_options()
            (ADD_FILE_CLI_ARG, "adds file to cloud", cxxopts::value<std::string>())
            (DEL_FILE_CLI_ARG, "", cxxopts::value<std::string>())
            (LOGIN_CLI_ARG, "", cxxopts::value<std::string>())
            (PASSWORD_CLI_ARG, "", cxxopts::value<std::string>());
}

bool OptionsParser::parse(int argc, char **argv) {
    _clear();

    if (argc < 2) {
        _error_message = "No option specified for options parser";
        return false;
    }

    try {
        auto result = _cli_options_parser.parse(argc, argv);
        for (auto &arg : result.arguments())
            _process_one_argument(arg.key(), arg.value());
        auto login_specified = _login.length() != 0;
        auto password_specified = _password.length() != 0;
        auto specified_only_login_or_password = login_specified ^password_specified;
        if (specified_only_login_or_password) {
            _error_message = SPECIFIED_ONLY_LOGIN_OR_PASSWORD_ERROR_MESSAGE;
            return false;
        }
        if (_option == NOT_SET) {
            _error_message = "No command specified";
            return false;
        }
    } catch (std::exception e) {
        _error_message = e.what();
        return false;
    }
    return true;
}

const OptionsParser::Command& OptionsParser::command() const {
    return _option;
}

const std::string& OptionsParser::path() const {
    return _path;
}

std::string OptionsParser::error_message() const {
    return _error_message;
}

Credentials OptionsParser::credentials() const {
    return Credentials(_login, _password);
}

void OptionsParser::_process_one_argument(const std::string &argument, const std::string &value) {
    if (_option == NOT_SET) {
        if (argument == ADD_FILE_CLI_ARG) {
            _path = value;
            _option = this->ADD;
            return;
        } else if (argument == DEL_FILE_CLI_ARG) {
            _path = value;
            _option = this->DELETE;
            return;
        }
    }
    if (argument == LOGIN_CLI_ARG && _login.length() == 0) {
        _login = value;
        return;
    } else if (argument == PASSWORD_CLI_ARG && _password.length() == 0) {
        _password = value;
        return;
    }

    throw std::invalid_argument("Wrong or repeated argument");
}

void OptionsParser::_clear() {
    _option = NOT_SET;
    _path = "";
    _error_message = "";
    _login = "";
    _password = "";
}



