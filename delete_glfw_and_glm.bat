@echo off

if exist "%VK_SDK_PATH%" (
	rd /Q /S %VK_SDK_PATH%\EasyVulkanLibs\
)