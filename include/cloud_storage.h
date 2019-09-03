#pragma once
#include <string>

#include <was/blob.h>

#include <credentials.h>


class CloudStorage
{
    static constexpr auto CONTAINER_NAME = "test-task-container";
public:
    CloudStorage(Credentials credentials, bool quiet = false);
    bool add_file(std::string path);
    bool delete_file(std::string path);

protected:
    //report to the command line if not in quiet mode
    void _report_to_user(std::string str);
    azure::storage::cloud_blob_container _container;
    azure::storage::cloud_blob_container _create_container_if_not_exist(std::string account, std::string key, std::string container_name);
    bool _quiet;
};

