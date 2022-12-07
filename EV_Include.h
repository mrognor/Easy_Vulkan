#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>

// Vector with all required validation layers
const std::vector<const char*> RequiredValidationLayers = {"VK_LAYER_KHRONOS_validation"};