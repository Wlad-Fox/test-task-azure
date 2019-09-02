#include <iostream>

#include <cloud_storage.h>
#include <credentials.h>
#include <options_parser.h>

static constexpr char JSON_CREDENTIALS_FILE_PATH[] = "credentials.json";

int main(int argc, char *argv[])
{
    OptionsParser p(argc, argv);
    if (auto err = p.parsing_error())
    {
        std::cout << err.value();
        return 1;
    }

    Credentials creds = p.credentials() ?
            p.credentials().value() :
            Credentials::from_json_file(JSON_CREDENTIALS_FILE_PATH);

    CloudStorage cloud(creds);

    bool result = false;
    switch (p.command())
    {
        case p.ADD:
            result = cloud.add_file(p.path());
            break;
        case p.DELETE:
            result = cloud.delete_file(p.path());
            break;
    }

    return result == true ? 0 : 1;
}
