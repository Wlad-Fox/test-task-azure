# Azure test task

Here is the result of completing the test task from one company. It is not so primitive as usual test tasks so I decided to upload it here so that you could instantly check my skills.

There is no complex code in terms of algorithms. 

Before completing this task I had no experience with Azure.

## Task

Using Azure SDK for C++ (https://github.com/Azure/azure-storage-cpp) please create application which allows to communicate with Azure Blob Storage.  

Requirements:

1.  Platform - Windows or Linux or MacOS
2.  Create appropriate Storage Account in Azure
3.  Account name/access key to Azure Storage Account:
	a.	can be hardcoded
	b.	command line for account name/key:
	`--login <name> --password <key>`
	* Both account_name/account_key can be stored locally in the same location as application (i.e. in json file).
	* Application should verify if config json with account_name/account_key exists
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

## How to run

You need to have Cmake and C++17 compiler installed.

1. Clone repo to ubuntu machine:
    
    `git clone https://github.com/Wlad-Fox/test-task-azure && cd test-task-azure`
2. Initialize and update submodules:
    
    `git submodule init && git submodule update`
3. Run instal_dependencies.sh:
    
    `bash install_dependencies.sh`
4. Create build directory and cd inside:
    
    `mkdir build && cd build`
5. Configure cmake and build:
    
    `cmake .. -DCMAKE_BUILD_TYPE=Release`
    `cmake --build .`

6. Get Azure storage account access credentials

	If you don't have Azure account create it following instructions [here](https://docs.microsoft.com/en-us/azure/storage/common/storage-quickstart-create-account?tabs=azure-portal).  
	[Here](https://docs.microsoft.com/en-us/azure/storage/common/storage-configure-connection-string) you can find how to get storage account's name and key.


6. Run the app file with following command line arguments:

	```
	--add <filename>      (to add file to azure storage)  
	--delete <filename>   (to delete file from azure storage)  
	--login <login>       (azure storage account name)  
	--password <password> (azure storage account key)  
	```

	if login and password arguments are omitted, they're taken from file credentials.json, so you need to create it within app's directory:
	
	```
	//credentials.json
	{
		"login" : "...",
		"password" : "..."
	}
	```

## Design decisions

### Testing

As you may notice there is no tests in repo. This is because the system is quite small and there are no plans to change it. It was faster to test all classes manually. In complex projects I always use unit testing for classes that may change in future or that has tricky logic.

### JSON library for simply reading two lines of text

My first idea was to write simple parser for only this two lines "login" and "password". But there are some points against this decision:
* as it will be json file with configuration, it may contain other values besides "login" and "password", I needed to handle them correctly;
* possibility of having login and password separately in different json objects like that:
```
{
	"object1" : {
		"login" : "object1's login"
	},
	"object2" : {
		"password" : "object2's password"
	}
}
```
taking this into account I've decided to take full-featured json library for this task.

## P.S.

If you think something is bad, feel free to leave the comment or mail to restfoks@gmail.com, I would be grateful for any feedback!