CFLAGS = -std=c++11 -O2
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

Sources = main.cpp EV_InitWindow.cpp

VulkanTest: $(Sources)
	g++ $(CFLAGS) -o VulkanTest.sh $(Sources) $(LDFLAGS)

Debug: main.cpp
	g++ $(CFLAGS) -g -o VulkanTest.sh $(Sources) $(LDFLAGS)

clean:
	rm -f VulkanTest