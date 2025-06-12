export module InterstellarEngine_Core; 

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

import <vulkan/vulkan.h>;

import <iostream>;
import <vector>;

export namespace insterstellarEngineCore {

	const uint16_t windowHeight = 600;
	const uint16_t windowWidth = 800;

	class engineCore
	{
	public:

		void run() {
			initWindow();
			initVulkan();
			mainLoop();
			cleanup();
		}


	private:

		void initWindow() {
			glfwInit();

			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

			window = glfwCreateWindow(windowWidth, windowHeight, "InterstellarEngine", nullptr, nullptr);
		}

		void initVulkan() {
			createInstance();
		}

		void mainLoop() {
			while (!glfwWindowShouldClose(window)) {
				glfwPollEvents();
			}
		}

		void cleanup() {
			vkDestroyInstance(instance, nullptr);
			
			glfwDestroyWindow(window);

			glfwTerminate();
		}

		void createInstance() {

			VkApplicationInfo appInfo{};
			appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
			appInfo.pApplicationName = "Interstellar Engine";
			appInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
			appInfo.pEngineName = "InterstellarEngine";
			appInfo.engineVersion = VK_MAKE_VERSION(0, 1, 0);
			appInfo.apiVersion = VK_API_VERSION_1_4;

			VkInstanceCreateInfo createInfo{};
			createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			createInfo.pApplicationInfo = &appInfo;

			uint32_t glfwExtensionCount = 0;
			const char** glfwExtensions;
			glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

			createInfo.enabledExtensionCount = glfwExtensionCount;
			createInfo.ppEnabledExtensionNames = glfwExtensions;

			createInfo.enabledLayerCount = 0;

			if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
				throw std::runtime_error("failed to create instance!");
			}

			// extension checking
			uint32_t extensionCount = 0;
			
			vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
			std::vector<VkExtensionProperties> extensions(extensionCount);
			vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

			std::cout << "Extension checks:" << "\n" << "extension count : " << extensionCount << "\n" << "available extensions : \n";

			for (const auto& extension : extensions) {
				std::cout << '\t' << extension.extensionName << '\n';
			}

		}

		VkInstance instance = nullptr;
		GLFWwindow* window;

	};
}