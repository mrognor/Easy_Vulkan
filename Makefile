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
bin/libEasyVulkan.a: bin/EV_App.o bin/EV_Window.o bin/EV_Instance.o bin/EV_Functions.o bin/EV_Device.o bin/EV_Swapchain.o bin/EV_GraphicsPipeline.o
	ar rc bin/libEasyVulkan.a bin/EV_App.o bin/EV_Window.o bin/EV_Instance.o bin/EV_Functions.o bin/EV_Device.o bin/EV_Swapchain.o bin/EV_GraphicsPipeline.o
	ranlib bin/libEasyVulkan.a

# EV_App binary
bin/EV_App.o: EV_App.cpp EV_App.h
	mkdir -p bin
	g++ -c $(CXXFLAGS) EV_App.cpp -o bin/EV_App.o $(LDFLAGS)

# EV_Functions binary
bin/EV_Functions.o: EV_Functions.cpp EV_Functions.h
	mkdir -p bin
	g++ -c $(CXXFLAGS) EV_Functions.cpp -o bin/EV_Functions.o $(LDFLAGS)

# EV_Window binary
bin/EV_Window.o: EV_Window.cpp EV_Window.h
	mkdir -p bin
	g++ -c $(CXXFLAGS) EV_Window.cpp -o bin/EV_Window.o $(LDFLAGS)

# EV_Instance binary
bin/EV_Instance.o: EV_Instance.cpp EV_Instance.h
	mkdir -p bin
	g++ -c $(CXXFLAGS) EV_Instance.cpp -o bin/EV_Instance.o $(LDFLAGS)

# EV_Device binary
bin/EV_Device.o: EV_Device.cpp EV_Device.h
	mkdir -p bin
	g++ -c $(CXXFLAGS) EV_Device.cpp -o bin/EV_Device.o $(LDFLAGS)

# EV_Swapchain binary
bin/EV_Swapchain.o: EV_Swapchain.cpp EV_Swapchain.h
	mkdir -p bin
	g++ -c $(CXXFLAGS) EV_Swapchain.cpp -o bin/EV_Swapchain.o $(LDFLAGS)

# EV_GraphicsPipeline binary
bin/EV_GraphicsPipeline.o: EV_GraphicsPipeline.cpp EV_GraphicsPipeline.h
	mkdir -p bin
	g++ -c $(CXXFLAGS) EV_GraphicsPipeline.cpp -o bin/EV_GraphicsPipeline.o $(LDFLAGS)

clean:
	rm -rf bin