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
bin/libEasyVulkan.a: bin/EV_App.o bin/EV_GLFW_Window.o bin/EV_VK_Instance.o
	ar rc bin/libEasyVulkan.a bin/EV_App.o bin/EV_GLFW_Window.o bin/EV_VK_Instance.o
	ranlib bin/libEasyVulkan.a

# EV_App binary
bin/EV_App.o: EV_App.cpp EV_App.h
	mkdir -p bin
	g++ -c $(CXXFLAGS) EV_App.cpp -o bin/EV_App.o $(LDFLAGS)

# EV_GLFW_Window binary
bin/EV_GLFW_Window.o: EV_GLFW_Window.cpp EV_GLFW_Window.h
	mkdir -p bin
	g++ -c $(CXXFLAGS) EV_GLFW_Window.cpp -o bin/EV_GLFW_Window.o $(LDFLAGS)

# EV_VK_Instance binary
bin/EV_VK_Instance.o: EV_VK_Instance.cpp EV_VK_Instance.h
	mkdir -p bin
	g++ -c $(CXXFLAGS) EV_VK_Instance.cpp -o bin/EV_VK_Instance.o $(LDFLAGS)

clean:
	rm -rf bin