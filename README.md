To prepare the project for work, you must do the following:
1. Install a vulkan. You can do it yourself or use a script install vulkan.bat from this folder
2. Install glfw and glm. Use the install_glfw_and_glm.bat script from this folder
3. Run configure.bat to make sln project using cmake

If you want to remove or update glfw and glm, you can remove them using a delete_glfw_and_glm.bat script
To change the version of the volcano being installed, or glfw or glm, you can open .bat files and specify the desired version there

If any errors occurred during the download, then the .downloading file remains in the folder, which you can delete

If you want to configure the project for MinGW or for a 32 bit system, you can simply use cmake for this

The directories of the included files of all libraries are located in the folder with the Vulkan SDK. 
Vulkan files are stored in the include folder. Third-party library files are stored in the EasyVulkanLibs folder. 
To add them to Visual Studio Code, open the settings, 
find the C_Cpp " Default: Include Path" item there and add all the paths to the include folders there