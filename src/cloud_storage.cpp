#include <cloud_storage.h>

#include <boost/filesystem.hpp>
#include <cpprest/filestream.h>
#include <was/storage_account.h>
#include <was/blob.h>


CloudStorage::CloudStorage(Credentials credentials, bool quiet)
    : _container(_create_container_if_not_exist(credentials.login, credentials.key, "eskere"))
    , _quiet(quiet)
{
}

namespace fs = boost::filesystem;

bool CloudStorage::add_file(std::string path_string)
{
    try {
        _report_to_user("Started adding file " + path_string + "\n");
        fs::path path(path_string);
        auto filename = path.filename().string();

        concurrency::streams::istream input_stream = concurrency::streams::file_stream<uint8_t>::open_istream(path_string).get();
        _report_to_user("File found, starting loading... ");

        azure::storage::cloud_block_blob blockBlob = _container.get_block_blob_reference(filename);
        blockBlob.upload_from_stream(input_stream);
        input_stream.close().wait();
        _report_to_user("Completed\n");
        return true;
    }
    catch (std::exception&)
    {
        _report_to_user("Failed adding file\n");
        return false;
    }
}

bool CloudStorage::delete_file(std::string path)
{
    try
    {
        _report_to_user("Start file deleting " + path + "\n");
        azure::storage::cloud_block_blob blockBlob = _container.get_block_blob_reference(U("path"));
        blockBlob.delete_blob();
        _report_to_user("Completed\n");
        return true;
    }
    catch(std::exception&)
    {
        _report_to_user("Failed deleting file\n");
    }

}


azure::storage::cloud_blob_container CloudStorage::_create_container_if_not_exist(std::string account, std::string key, std::string container_name)
{
    std::string connection_string =  std::string() +
            "DefaultEndpointsProtocol=https;" +
            "AccountName=" + account + ";" +
            "AccountKey=" + key + ";" +
            "EndpointSuffix=core.windows.net";
    azure::storage::cloud_storage_account storage_account = azure::storage::cloud_storage_account::parse(connection_string);
    azure::storage::cloud_blob_client blob_client = storage_account.create_cloud_blob_client();
    azure::storage::cloud_blob_container container = blob_client.get_container_reference(container_name);
    container.create_if_not_exists();

    return container;
}

void CloudStorage::_report_to_user(std::string str) {
    if (!_quiet)
        std::cout << str;
}
