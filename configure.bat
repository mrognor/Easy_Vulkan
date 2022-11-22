if not exist build mkdir build

cd build

cmake -E env VK_SDK_PATH="%VK_SDK_PATH%" cmake ..

cd ..