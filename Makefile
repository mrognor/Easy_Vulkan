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

debug: CXXFLAGS += -g 
debug: bin/main$(FileExt)

release: CXXFLAGS += -D NDEBUG -O3
release: bin/main$(FileExt)

bin/main$(FileExt): bin/libEasyVulkan.a
	mkdir -p bin
	g++ $(CXXFLAGS) main.cpp bin/libEasyVulkan.a -o bin/main$(FileExt) $(LDFLAGS)

# Library binary
bin/libEasyVulkan.a: bin/EV_GLFWwindow.o bin/EV_VkInstance.o bin/EV_VkValidationLayers.o
	ar rc bin/libEasyVulkan.a bin/EV_GLFWwindow.o bin/EV_VkInstance.o bin/EV_VkValidationLayers.o
	ranlib bin/libEasyVulkan.a

# VkValidationLayers binary
bin/EV_VkValidationLayers.o: EV_VkValidationLayers.cpp EV_VkValidationLayers.h
	mkdir -p bin
	g++ -c $(CXXFLAGS) EV_VkValidationLayers.cpp -o bin/EV_VkValidationLayers.o $(LDFLAGS) 

# VkInstance binary
bin/EV_VkInstance.o: EV_VkInstance.cpp EV_VkInstance.h
	mkdir -p bin
	g++ -c $(CXXFLAGS) EV_VkInstance.cpp -o bin/EV_VkInstance.o $(LDFLAGS) 

# GLFWwindow binary
bin/EV_GLFWwindow.o: EV_GLFWwindow.cpp EV_GLFWwindow.h
	mkdir -p bin
	g++ -c $(CXXFLAGS) EV_GLFWwindow.cpp -o bin/EV_GLFWwindow.o $(LDFLAGS) 

clean:
	rm -rf bin