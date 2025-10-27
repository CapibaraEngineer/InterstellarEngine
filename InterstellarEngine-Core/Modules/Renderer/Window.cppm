module;

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

export module Engine.Renderer.Window;

import Engine.Utils.Logger;
import Engine.Renderer.Camera;

import std;

interstellarEngineCore::Renderer::camera* cameraReference;

void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    using namespace interstellarEngineCore::Renderer;
    static bool firstMouse = true;
    static float lastX = 400.0f;
    static float lastY = 300.0f;

    float xoffset, yoffset;
    if (firstMouse) {
        lastX = (float)xpos;
        lastY = (float)ypos;
        firstMouse = false;
    }

    xoffset = lastX - (float)xpos;
    yoffset = lastY - (float)ypos; // invertido: y cresce para baixo

    lastX = (float)xpos;
    lastY = (float)ypos;
    
    
    cameraReference->processMouse(xoffset, yoffset);
}

export namespace interstellarEngineCore::Renderer {
	class engineWindow {
	public:
		static constexpr uint16_t defaultWindowHeight = 600;
		static constexpr uint16_t defaultWindowWidth = 800;

        bool framebufferResized = false;
        bool mouseEnabled = false;
        GLFWwindow* window;

        void initWindow(camera* camera) {
            cameraReference = camera;

            glfwInit();

            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
            glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

            window = glfwCreateWindow(defaultWindowWidth, defaultWindowHeight, "Interstellar Engine", nullptr, nullptr);
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            glfwSetCursorPosCallback(window, mouseCallback);
            glfwSetWindowUserPointer(window, this);
            glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
        }

        void createSurface(VkInstance instance, VkSurfaceKHR &surface) const {

            if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) [[unlikely]] {
                throw std::runtime_error(utils::writeLogFAIL("Failed to create window surface"));
            }
            else [[likely]] {
                utils::logOK("window surface created sucessfully", "engineWindow.createSurface()");
            }

        }
 
        void terminateEngineWindow() const {
            glfwDestroyWindow(window);
        }

    private:

        static void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
            auto app = reinterpret_cast<engineWindow*>(glfwGetWindowUserPointer(window));
            app->framebufferResized = true;
        }
	};
}