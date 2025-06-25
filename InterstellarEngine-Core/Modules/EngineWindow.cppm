#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

export module EngineWindow;

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

    private:

        static void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
            auto app = reinterpret_cast<engineWindow*>(glfwGetWindowUserPointer(window));
            app->framebufferResized = true;
        }
	};
}