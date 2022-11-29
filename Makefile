LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

testapp: bin/libEasyVulkan.a
	mkdir -p bin
	g++ main.cpp bin/libEasyVulkan.a -o bin/main $(LDFLAGS)

bin/libEasyVulkan.a: bin/EV_GLFWwindow.o bin/EV_VkInstance.o
	ar rc bin/libEasyVulkan.a bin/EV_GLFWwindow.o bin/EV_VkInstance.o
	ranlib bin/libEasyVulkan.a

bin/EV_GLFWwindow.o: EV_GLFWwindow.cpp
	mkdir -p bin
	g++ -c EV_GLFWwindow.cpp -o bin/EV_GLFWwindow.o $(LDFLAGS) 

bin/EV_VkInstance.o: EV_VkInstance.cpp
	mkdir -p bin
	g++ -c EV_VkInstance.cpp -o bin/EV_VkInstance.o $(LDFLAGS) 

clean:
	rm -rf bin