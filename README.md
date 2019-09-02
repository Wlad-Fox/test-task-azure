# test-task-azure

Hello! Here is the result of completing one of the test tasks i've got.

## Task

Using Azure SDK for C++ (https://github.com/Azure/azure-storage-cpp) please create application which allows to communicate with Azure Blob Storage.  

Requirements:

1.  Platform - Windows or Linux or MacOS
2.  Create appropriate Storage Account in Azure
3.  Account name/access key to Azure Storage Account:
	a.  can be hardcoded
	b.  command line for account name/key:
	    --account_name <name> --account_key <key>
	* Both account_name/account_key can be stored locally in the same location as application (i.e. in json file).
	* Application should verify if config json with account_name/account_key exists, i.e.:
	    application --account_name "qwerty123" --account_key "pass123"
4.  Application should support command line with following options:
	* add data to Azure

        `--add <local path to file>`
	
	* delete data from Azure:
    
        `--delete <filename>`

    Each command should print information, if ended properly or with error i.e.:
            
        application --add /user/test/file.txt
        Copying "file.txt" to Azure service ... OK

        application --add /user/test/file1.txt
        Copying "file1.txt" to Azure service ... OK

        application --add /user/test/file2.txt
        Copying "file2.txt" to Azure service ... Error

        application --delete file.txt
        Delete "file.txt" from Azure service ... OK

5.  Please assume that application support
	*  max. file size 2MB
	*  there is no need to handle scenario when user try to upload file with the same name, file names are unique

## How-to-run

1. Clone repo to ubuntu machine
    
    `git clone https://github.com/Wlad-Fox/test-task-azure && cd test-task-azure`
2. Initialize and update submodules
    
    `git submodule init && git submodule update`
3. Run instal_dependencies.sh
    
    `bash install_dependencies.sh`
4. Create build directory and cd inside
    
    `mkdir build && cd build`
5. Configure cmake and build
    
    `cmake .. -DCMAKE_BUILD_TYPE=Release`
    `cmake --build .`
6. Run the app file with following command line arguments:

	```
	--add <filename>      (to add file to azure storage)  
	--delete <filename>   (to delete file from azure storage)  
	--login <login>       (azure storage account name)  
	--password <password> (azure storage account key)  
	```

	if login and password are omitted, they're taken from file credentials.json:
	
	```
	//credentials.json
	{
		"login" : "...",
		"password" : "..."
	}
	```