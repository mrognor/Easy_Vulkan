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
        set(WindowsGLFWPath "lib-mingw-w64/libglfw3.a")
    endif()
else()
    set(StandartIncludeLibraries glfw vulkan dl pthread X11 Xxf86vm Xrandr Xi)
endif()

# Demo app binary
project(EasyVulkanDemoApp)

add_executable(EasyVulkanDemoApp main.cpp)

# Include windows libraries 
if(WIN32)
    target_include_directories(EasyVulkanDemoApp PUBLIC ${VK_SDK_PATH}/EasyVulkanLibs/glm/)

    target_include_directories(EasyVulkanDemoApp PUBLIC ${VK_SDK_PATH}/include)
    target_link_libraries(EasyVulkanDemoApp ${VK_SDK_PATH}/Lib/vulkan-1.lib)

    target_include_directories(EasyVulkanDemoApp PUBLIC ${VK_SDK_PATH}/EasyVulkanLibs/glfw64/include)
    target_link_libraries(EasyVulkanDemoApp ${VK_SDK_PATH}/EasyVulkanLibs/glfw64/${WindowsGLFWPath})
endif()

target_link_libraries(EasyVulkanDemoApp EasyVulkan ${StandartIncludeLibraries})

# Library binary
project(EasyVulkan)

set(LibHeaders EV_GLFWwindow.h)

set(LibSources EV_GLFWwindow.cpp)

add_library(EasyVulkan STATIC ${LibSources} ${LibHeaders})

target_link_libraries(EasyVulkan ${StandartIncludeLibraries})

# Include windows libraries 
if(WIN32)
    target_include_directories(EasyVulkan PUBLIC ${VK_SDK_PATH}/EasyVulkanLibs/glm/)

    target_include_directories(EasyVulkan PUBLIC ${VK_SDK_PATH}/include)

    target_include_directories(EasyVulkan PUBLIC ${VK_SDK_PATH}/EasyVulkanLibs/glfw64/include)
endif()