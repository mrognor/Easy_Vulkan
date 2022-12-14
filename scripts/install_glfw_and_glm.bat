@echo off
setlocal ENABLEEXTENSIONS

:: Configure vulkan version
set glmVersion=0.9.9.8
set glfw64Version=3.3.8
set glfw32Version=3.3.8

set KEY_NAME=HKLM\SYSTEM\CurrentControlSet\Control\Session Manager\Environment
set VALUE_NAME=VK_SDK_PATH

:: Find vulkan path in reg
for /F "usebackq tokens=1,2,*" %%A IN (`reg query "%KEY_NAME%" /v "%VALUE_NAME%" 2^>nul ^| find "%VALUE_NAME%"`) do (
	set VK_SDK_PATH=%%C
)


if defined VK_SDK_PATH (
	:: Install glm
	if not exist %VK_SDK_PATH%\EasyVulkanLibs\glm (
		if exist glm-%glmVersion%.zip.downloading rm glm-%glmVersion%.zip.downloading
		
		powershell -command "Invoke-WebRequest https://github.com/g-truc/glm/releases/download/%glmVersion%/glm-%glmVersion%.zip -OutFile glm-%glmVersion%.zip.downloading"
		
		if not exist glm-%glmVersion%.zip.downloading (
			echo Failed to download glm. Check your internet connection
			pause
		) else (
			move glm-%glmVersion%.zip.downloading glm-%glmVersion%.zip
			powershell -command "& { Add-Type -A 'System.IO.Compression.FileSystem'; [IO.Compression.ZipFile]::ExtractToDirectory('glm-%glmVersion%.zip', '%VK_SDK_PATH%\EasyVulkanLibs'); }"
			del "glm-%glmVersion%.zip"
		)
	) else echo glm alredy installed

	:: Install glfw
	if not exist %VK_SDK_PATH%\EasyVulkanLibs\glfw (
		if exist glfw-%glfw64Version%.bin.WIN64.zip.downloading rm glfw-%glfw64Version%.bin.WIN64.zip.downloading
		
		powershell -command "Invoke-WebRequest https://github.com/glfw/glfw/releases/download/%glfw64Version%/glfw-%glfw64Version%.bin.WIN64.zip -OutFile glfw-%glfw64Version%.bin.WIN64.zip.downloading"
		
		if not exist glfw-%glfw64Version%.bin.WIN64.zip.downloading (
			echo Failed to download glfw. Check you internet connection
			pause
		) else (
			move glfw-%glfw64Version%.bin.WIN64.zip.downloading glfw-%glfw64Version%.bin.WIN64.zip
			powershell -command "& { Add-Type -A 'System.IO.Compression.FileSystem'; [IO.Compression.ZipFile]::ExtractToDirectory('glfw-%glfw64Version%.bin.WIN64.zip', '%VK_SDK_PATH%\EasyVulkanLibs'); }"
			move %VK_SDK_PATH%\EasyVulkanLibs\glfw-%glfw64Version%.bin.WIN64 %VK_SDK_PATH%\EasyVulkanLibs\glfw
			del "glfw-%glfw64Version%.bin.WIN64.zip"
		)
	) else echo glfw alredy installed

	:: Install glfw32
	if not exist %VK_SDK_PATH%\EasyVulkanLibs\glfw32 (
		if exist glfw-%glfw32Version%.bin.WIN32.zip.downloading rm glfw-%glfw32Version%.bin.WIN32.zip.downloading
		
		powershell -command "Invoke-WebRequest https://github.com/glfw/glfw/releases/download/%glfw32Version%/glfw-%glfw32Version%.bin.WIN32.zip -OutFile glfw-%glfw32Version%.bin.WIN32.zip.downloading"
		
		if not exist glfw-%glfw32Version%.bin.WIN32.zip.downloading (
			echo Failed to download glfw32. Check you internet connection
			pause
		) else (
			move glfw-%glfw32Version%.bin.WIN32.zip.downloading glfw-%glfw32Version%.bin.WIN32.zip
			powershell -command "& { Add-Type -A 'System.IO.Compression.FileSystem'; [IO.Compression.ZipFile]::ExtractToDirectory('glfw-%glfw32Version%.bin.WIN32.zip', '%VK_SDK_PATH%\EasyVulkanLibs'); }"
			move %VK_SDK_PATH%\EasyVulkanLibs\glfw-%glfw32Version%.bin.WIN32 %VK_SDK_PATH%\EasyVulkanLibs\glfw32
			del "glfw-%glfw32Version%.bin.WIN32.zip"
		)
	) else echo glfw32 alredy installed
	exit
) else (
	echo You dont install vulkan. Install it first. You can make it by yourself or by install_vulkan.bat file from this directory
	pause
)

		
	:: https://github.com/glfw/glfw/releases/download/3.3.8/glfw-3.3.8.bin.WIN64.zip
	:: https://github.com/glfw/glfw/releases/download/3.3.8/glfw-3.3.8.bin.WIN32.zip
	:: https://github.com/glfw/glfw/releases/download/3.3.7/glfw-3.3.7.bin.WIN64.zip