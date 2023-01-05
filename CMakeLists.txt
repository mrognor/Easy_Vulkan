set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMakePredefinedTargets")

# Checks platform
if(WIN32)
    set(StandartIncludeLibraries "")
	
    # Change vulkan sdk path to proper path
	string(REPLACE "\\" "/" VK_SDK_PATH $ENV{VK_SDK_PATH})
	
    # Checks ide
    if(CMAKE_GENERATOR MATCHES "Visual Studio")
        string(REGEX MATCH "....$" WindowsGLFWPath ${CMAKE_GENERATOR})
        string(CONCAT WindowsGLFWPath "lib-vc" ${WindowsGLFWPath} "/glfw3.lib")
    else()
		# Checks architecture
		if (${CMAKE_GENERATOR_PLATFORM} MATCHES Win32)
			set (WindowsGLFWPath "lib-mingw/libglfw3.a")
		else()
			set(WindowsGLFWPath "lib-mingw-w64/libglfw3.a")
		endif()
    endif()
	
	# Checks architecture
	if (${CMAKE_GENERATOR_PLATFORM} MATCHES Win32)
		set (BuildArchitecture "32")
	else()
		set (BuildArchitecture "")
	endif()
else()
    set(StandartIncludeLibraries glfw vulkan dl pthread X11 Xxf86vm Xrandr Xi)
endif()

# Demo app binary
project(EasyVulkanApp)

add_executable(EasyVulkanApp EasyVulkanApp.cpp)

# Include windows libraries 
if(WIN32)
    target_include_directories(EasyVulkanApp PUBLIC ${VK_SDK_PATH}/EasyVulkanLibs/glm/)

    target_include_directories(EasyVulkanApp PUBLIC ${VK_SDK_PATH}/include)
    target_link_libraries(EasyVulkanApp ${VK_SDK_PATH}/Lib${BuildArchitecture}/vulkan-1.lib)

    target_include_directories(EasyVulkanApp PUBLIC ${VK_SDK_PATH}/EasyVulkanLibs/glfw${BuildArchitecture}/include)
    target_link_libraries(EasyVulkanApp ${VK_SDK_PATH}/EasyVulkanLibs/glfw${BuildArchitecture}/${WindowsGLFWPath})
endif()

target_link_libraries(EasyVulkanApp EasyVulkan ${StandartIncludeLibraries})

# Library binary
project(EasyVulkan)

# Set library files
set(LibHeaders EV_App.h EV_Functions.h EV_GLFW_Window.h EV_VK_Instance.h EV_VK_ValidationLayers.h)

set(LibSources EV_App.cpp EV_Functions.cpp EV_GLFW_Window.cpp EV_VK_Instance.cpp EV_VK_ValidationLayers.cpp)

add_library(EasyVulkan STATIC ${LibSources} ${LibHeaders})

target_link_libraries(EasyVulkan ${StandartIncludeLibraries})

# Include windows libraries 
if(WIN32)
    target_include_directories(EasyVulkan PUBLIC ${VK_SDK_PATH}/EasyVulkanLibs/glm/)

    target_include_directories(EasyVulkan PUBLIC ${VK_SDK_PATH}/include)
	target_link_libraries(EasyVulkanApp ${VK_SDK_PATH}/Lib${BuildArchitecture}/vulkan-1.lib)

    target_include_directories(EasyVulkan PUBLIC ${VK_SDK_PATH}/EasyVulkanLibs/glfw${BuildArchitecture}/include)
	target_link_libraries(EasyVulkanApp ${VK_SDK_PATH}/EasyVulkanLibs/glfw${BuildArchitecture}/${WindowsGLFWPath})
endif()