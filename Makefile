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
debug: bin/EasyVulkanApp$(FileExt)

release: CXXFLAGS += -D NDEBUG -O3
release: bin/EasyVulkanApp$(FileExt)

bin/EasyVulkanApp$(FileExt): bin/libEasyVulkan.a EasyVulkanApp.cpp
	mkdir -p bin
	g++ $(CXXFLAGS) EasyVulkanApp.cpp bin/libEasyVulkan.a -o bin/EasyVulkanApp$(FileExt) $(LDFLAGS)

# Library binary
bin/libEasyVulkan.a: bin/EV_App.o bin/EV_VkClassContainer.o
	ar rc bin/libEasyVulkan.a bin/EV_App.o bin/EV_VkClassContainer.o
	ranlib bin/libEasyVulkan.a

# Functions binary
bin/EV_App.o: EV_App.cpp EV_App.h
	mkdir -p bin
	g++ -c $(CXXFLAGS) EV_App.cpp -o bin/EV_App.o $(LDFLAGS)

# VkValidationLayers binary
bin/EV_VkClassContainer.o: EV_VkClassContainer.cpp EV_VkClassContainer.h
	mkdir -p bin
	g++ -c $(CXXFLAGS) EV_VkClassContainer.cpp -o bin/EV_VkClassContainer.o $(LDFLAGS) 

clean:
	rm -rf bin