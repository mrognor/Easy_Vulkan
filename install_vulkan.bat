@echo off

:: Configure vulkan version
set VulkanVersion=1.3.231.1

:: Checking whether the vulkan is installed
if not exist "%VK_SDK_PATH%" (
	:: Checking if the last download failed
	if exist VulkanSDK.exe.downloading rm VulkanSDK.exe.downloading
	
	:: Checking if there is no downloaded vulkan installer
	if not exist VulkanSDK.exe (
		:: Vulkan installer download
		powershell -command "Invoke-WebRequest https://sdk.lunarg.com/sdk/download/%VulkanVersion%/windows/VulkanSDK-%VulkanVersion%-Installer.exe -OutFile VulkanSDK.exe.downloading"
		
		:: Making sure that the vulkan installer download was successful
		if not exist VulkanSDK.exe.downloading (
			echo Failed to download vulkan installer. Check your internet connection
			pause
		) else (
			echo The vulkan installer download was completed successfully
			move VulkanSDK.exe.downloading VulkanSDK.exe
		)
	) 
	
	if exist VulkanSDK.exe (
		echo The vulkan installer will be launched now. If you don't know what to choose, then I recommend not touching anything, except of course the installation path
		timeout 10
		
		:: Vulkan installation
		start /wait VulkanSDK.exe
		
		:: We ask the user whether it is necessary to remove the vulkan installer
		choice /T 10 /D yes /M "Delete vulkan installator ?"
		:: 
		if %ERRORLEVEL% == 1 rm VulkanSDK.exe
	)
) else (	
	echo The vulkan is already installed
	pause
)