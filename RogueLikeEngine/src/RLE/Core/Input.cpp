// THIS IS ALL TEMP AS THIS USES NON API AGNOSTIC CODE

#include "RLEpch.hpp"
#include "Input.hpp"

// --- External --- 
#include <GLFW/glfw3.h> // non-agnostic

// --- RLE ---
#include "Engine.hpp"



bool rle::input::isKeyPressed(const KeyCode code)
{
    auto* win = static_cast<GLFWwindow*>(Engine::get()->window()->nativeHandle());
    return glfwGetKey(win, to_code(code)) == GLFW_PRESS;
}
