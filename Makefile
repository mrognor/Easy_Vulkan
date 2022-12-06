FileExt = 
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi
CXXFLAGS = 

ifeq ($(OS),Windows_NT)
	WinSDKPath = $(shell echo ${VK_SDK_PATH})
	WinVK = -I$(WinSDKPath)\Include -L$(WinSDKPath)\Lib -lvulkan-1
	WinGLFW = -I$(WinSDKPath)\EasyVulkanLibs\glfw\include -L$(WinSDKPath)\EasyVulkanLibs\glfw\lib-mingw-w64 -lglfw3
	WinGLM = -I$(WinSDKPath)\EasyVulkanLibs\glm\glm
	FileExt = .exe
	LDFLAGS = $(WinGLM) $(WinGLFW) $(WinVK) -lgdi32
endif

debug: CXXFLAGS += -g -D NDEBUG
debug: bin/main$(FileExt)

release: bin/main$(FileExt)

bin/main$(FileExt): bin/libEasyVulkan.a
	mkdir -p bin
	g++ $(CXXFLAGS) main.cpp bin/libEasyVulkan.a -o bin/main$(FileExt) $(LDFLAGS)

# Library binary
bin/libEasyVulkan.a: bin/EV_GLFWwindow.o bin/EV_VkInstance.o
	ar rc bin/libEasyVulkan.a bin/EV_GLFWwindow.o bin/EV_VkInstance.o
	ranlib bin/libEasyVulkan.a

# GLFWwindow binary
bin/EV_GLFWwindow.o: EV_GLFWwindow.cpp
	mkdir -p bin
	g++ -c $(CXXFLAGS) EV_GLFWwindow.cpp -o bin/EV_GLFWwindow.o $(LDFLAGS) 

# VkInstance binary
bin/EV_VkInstance.o: EV_VkInstance.cpp
	mkdir -p bin
	g++ -c $(CXXFLAGS) EV_VkInstance.cpp -o bin/EV_VkInstance.o $(LDFLAGS) 

clean:
	rm -rf bin