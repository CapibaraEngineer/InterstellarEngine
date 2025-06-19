export module EngineRenderer;

import InterstellarEngine_Core;
import VulkanValidator;

#define GLFW_INCLUDE_VULKAN
import <GLFW/glfw3.h>;

import <vulkan/vulkan.h>;

import <iostream>;
import <stdlib.h>;
import <vector>;
import <cstring>;

export namespace insterstellarEngineCore {
    class engineRenderer {
    public:

        void run() {
            initWindow();
            initVulkan();
            mainLoop();
            cleanup();
        }


    private:

        vulkanValidator theVulkanValidator;

        GLFWwindow* window;

        VkInstance instance;
        
        void initWindow() {
            glfwInit();

            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
            glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

            window = glfwCreateWindow(windowWidth, windowHeight, "Interstellar Engine", nullptr, nullptr);
        }

        void initVulkan() {
            if (!enableValidationLayers) {
                std::cerr << "Release Build - validation layers disabled\n";
            }
            else {
                std::cerr << "Debug Build - validation layers enabled\n";
            }
            createInstance();
            theVulkanValidator.setupDebugMessenger(instance);
        }

        void mainLoop() {
            while (!glfwWindowShouldClose(window)) {
                glfwPollEvents();
            }
        }

        void cleanup() {
            if (enableValidationLayers) {
                DestroyDebugUtilsMessengerEXT(instance, theVulkanValidator.debugMessenger, nullptr);
            }

            vkDestroyInstance(instance, nullptr);
                
            glfwDestroyWindow(window);

            glfwTerminate();
        }

        void createInstance() {

            if (enableValidationLayers && !theVulkanValidator.checkValidationLayerSupport()) {
                throw std::runtime_error("validation layers requested, but not available!");
            }

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

            auto extensions = theVulkanValidator.getRequiredExtensions();
            createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
            createInfo.ppEnabledExtensionNames = extensions.data();

            VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
            if (enableValidationLayers) {
                createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
                createInfo.ppEnabledLayerNames = validationLayers.data();

                theVulkanValidator.populateDebugMessengerCreateInfo(debugCreateInfo);
                createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
            }
            else {
                createInfo.enabledLayerCount = 0;

                createInfo.pNext = nullptr;
            }

            if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
                throw std::runtime_error("failed to create instance!");
            }
        }
    };
}