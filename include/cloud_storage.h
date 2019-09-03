#pragma once

#include <string>

#include <was/blob.h>

#include <credentials.h>


class CloudStorage {
    static constexpr auto CONTAINER_NAME = "test-task-container";
public:
    CloudStorage(Credentials credentials, bool quiet = false);

    bool add_file(const std::string &path);
    bool delete_file(const std::string &path);

protected:
    //report to the command line if not in quiet mode
    void _report_to_user(const std::string &str) const;

    azure::storage::cloud_blob_container
    _create_container_if_not_exist(const std::string &account,
            const std::string &key,
            const std::string &container_name);

    azure::storage::cloud_blob_container _container;
    bool _quiet;
};

