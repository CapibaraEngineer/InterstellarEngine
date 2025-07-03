#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

export module Engine.Renderer.Window;

import Engine.Utils.Logger;

import <iostream>;

export namespace interstellarEngineCore {
	class engineWindow {
	public:
		static constexpr uint16_t windowHeight = 600;
		static constexpr uint16_t windowWidth = 800;

        bool framebufferResized = false;
        GLFWwindow* window;

        void initWindow() {
            glfwInit();

            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
            glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

            window = glfwCreateWindow(windowWidth, windowHeight, "Interstellar Engine", nullptr, nullptr);
            glfwSetWindowUserPointer(window, this);
            glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
        }

        void createSurface(VkInstance instance, VkSurfaceKHR &surface) const {

            if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) [[unlikely]] {
                throw std::runtime_error("failed to create window surface!");
            }
            else [[likely]] {
                logOK("window surface created sucessfully", "engineWindow.createSurface()");
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