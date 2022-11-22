set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMakePredefinedTargets")

string(REGEX MATCH "....$" VisualStudioVersion ${CMAKE_GENERATOR})

# Demo app binary
project(EasyVulkanDemoApp)

add_executable(EasyVulkanDemoApp main.cpp)

target_include_directories(EasyVulkanDemoApp PUBLIC $ENV{VK_SDK_PATH}/EasyVulkanLibs/glm/)

target_include_directories(EasyVulkanDemoApp PUBLIC $ENV{VK_SDK_PATH}/include)
target_link_libraries(EasyVulkanDemoApp $ENV{VK_SDK_PATH}/Lib/vulkan-1.lib)

target_include_directories(EasyVulkanDemoApp PUBLIC $ENV{VK_SDK_PATH}/EasyVulkanLibs/glfw64/include)
target_link_libraries(EasyVulkanDemoApp $ENV{VK_SDK_PATH}/EasyVulkanLibs/glfw64/lib-vc${VisualStudioVersion}/glfw3.lib)

target_link_libraries(EasyVulkanDemoApp EasyVulkan)

# Library binary
project(EasyVulkan)

set(LibHeaders EV_InitWindow.h)

set(LibSources EV_InitWindow.cpp)

add_library(EasyVulkan STATIC ${LibSources} ${LibHeaders})

target_include_directories(EasyVulkan PUBLIC $ENV{VK_SDK_PATH}/EasyVulkanLibs/glm/)

target_include_directories(EasyVulkan PUBLIC $ENV{VK_SDK_PATH}/include)
target_link_libraries(EasyVulkan $ENV{VK_SDK_PATH}/Lib/vulkan-1.lib)

target_include_directories(EasyVulkan PUBLIC $ENV{VK_SDK_PATH}/EasyVulkanLibs/glfw64/include)
target_link_libraries(EasyVulkan $ENV{VK_SDK_PATH}/EasyVulkanLibs/glfw64/lib-vc${VisualStudioVersion}/glfw3.lib)