#pragma once

// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>
// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum Camera_Movement
{
    CAM_FORWARD,
    CAM_BACKWARD,
    CAM_LEFT,
    CAM_RIGHT
};

const GLfloat DEFAULT_YAW = -90.0f;
const GLfloat DEFAULT_PITCH = 0.0f;
const GLfloat DEFAULT_SPEED = 10.0f;
const GLfloat DEFAULT_SENSITIVTY = 0.25f;
const GLfloat DEFAULT_ZOOM = 45.0f;

class Camera
{
  public:
    Camera(glm::vec3 position = glm::vec3(25.7611,25.8858,32.1424), 
           glm::vec3 up = glm::vec3(0, 1, 0),
           GLfloat yaw = -130.25, GLfloat pitch = -22.75)
        : front(0, 0, -1), movementSpeed(DEFAULT_SPEED), 
          mouseSensitivity(DEFAULT_SENSITIVTY), zoom(DEFAULT_ZOOM)
    {
        this->position = glm::vec3(0.0, 8.5, 43);
        this->worldUp = up;
        this->yaw = yaw;
        this->pitch = pitch;
        updateCameraVectors();

        // this->position = glm::vec3(-31.993, 61.0408, -32.77);
        // this->front = glm::vec3(0.640856, -0.422618, 0.640856);
    }

    glm::mat4 GetViewMatrix();
    glm::vec3 GetViewPosition();
    glm::vec3 GetViewDirection();
    void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime);
    void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true);
    void ProcessMouseScroll(GLfloat yoffset);

  private:
    void updateCameraVectors();

    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    GLfloat yaw;
    GLfloat pitch;
    GLfloat movementSpeed;
    GLfloat mouseSensitivity;
    GLfloat zoom;
};