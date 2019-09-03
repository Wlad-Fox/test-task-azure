#include <iostream>

#include <cloud_storage.h>
#include <credentials.h>
#include <options_parser.h>

static constexpr char JSON_CREDENTIALS_FILE_PATH[] = "credentials.json";

int main(int argc, char *argv[]) {
    OptionsParser parser;
    parser.parse(argc, argv);
    if (!parser.parse(argc, argv)) {
        std::cout << "Error while parsing arguments!\n";
        return 1;
    }

    Credentials creds = !parser.credentials().empty() ?
                        parser.credentials() :
                        Credentials::from_json_file(JSON_CREDENTIALS_FILE_PATH);
    if (creds.empty()) {
        std::cout << "Failed to read credentials from file\n";
        return 1;
    }

    CloudStorage cloud(creds);

    bool result = false;
    switch (parser.command()) {
        case parser.ADD:
            result = cloud.add_file(parser.path());
            break;
        case parser.DELETE:
            result = cloud.delete_file(parser.path());
            break;
    }

    return result == true ? 0 : 1;
}
