dir=$(dirname $0)
glslangValidator -V $dir/../shaders/shader.frag -o $dir/../shaders/frag.spv
glslangValidator -V $dir/../shaders/shader.vert -o $dir/../shaders/vert.spv
