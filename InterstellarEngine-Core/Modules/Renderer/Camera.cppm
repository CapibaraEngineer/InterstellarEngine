module;
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

export module Engine.Renderer.Camera;

import std;

export namespace interstellarEngineCore::Renderer {
    class camera {
    public:
        glm::vec3 position;
        glm::vec3 front;
        glm::vec3 up;

        float yaw = 0.0f;
        float pitch = 0.0f;
        constexpr static float speed = 2.5f;
        constexpr static float sensitivity = 0.1f;

        camera(glm::vec3 startPos = { 2.0f, 2.0f, 2.0f }, glm::vec3 upVec = { 0.0f, 0.0f, 1.0f }) {
            position = startPos; 
            up = upVec;
            yaw = -135.0f,
            pitch = -30.0f;
            updateVectors();
        }

        void processKeyboard(int key, float deltaTime) {
            float velocity = speed * deltaTime;
            if (key == GLFW_KEY_W) position += front * velocity;
            if (key == GLFW_KEY_S) position -= front * velocity;
            if (key == GLFW_KEY_A) position -= glm::normalize(glm::cross(front, up)) * velocity;
            if (key == GLFW_KEY_D) position += glm::normalize(glm::cross(front, up)) * velocity;
            if (key == GLFW_KEY_SPACE) position += up * velocity;
            if (key == GLFW_KEY_LEFT_CONTROL) position -= up * velocity;
        }

        void processMouse(float xoffset, float yoffset) {
            xoffset *= sensitivity;
            yoffset *= sensitivity;
            yaw += xoffset;
            pitch += yoffset;
            pitch = glm::clamp(pitch, -89.0f, 89.0f);
            updateVectors();
        }

        glm::mat4 getViewMatrix() const {
            return glm::lookAt(position, position + front, up);
        }

    private:
        void updateVectors() {
            glm::vec3 vector;
            vector.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
            vector.y = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
            vector.z = sin(glm::radians(pitch));
            front = glm::normalize(vector);
        }
    };
}
