#include "camera.hpp"
// STL
#include <algorithm>
#include <iostream>

using namespace std;
using namespace glm;

mat4 Camera::GetViewMatrix()
{
    // cout << "Raw : " << yaw << " " << pitch << endl;
    // cout << "Position : " << position.x << " " << position.y << "   " << position.z << endl;
    // position = vec3(0.0, 0.0, 47);
    // position = vec3(0.0, -1.5, 43);
    // position = vec3(0.0, 8.5, 43);
    // front = vec3(0, 0, -1);
    // up = vec3(0, 1, 0);
    return lookAt(position, position + front, up);
}

vec3 Camera::GetViewPosition()
{
    return position;
}

vec3 Camera::GetViewDirection()
{
    return front;
}

void Camera::ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime)
{
    GLfloat velocity = movementSpeed * deltaTime;
    if (direction == CAM_FORWARD)
    {
        position += front * velocity;
    }
    if (direction == CAM_BACKWARD)
    {
        position -= front * velocity;
    }
    if (direction == CAM_LEFT)
    {
        position -= right * velocity;
    }
    if (direction == CAM_RIGHT)
    {
        position += right * velocity;
    }
}

void Camera::ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainpitch)
{
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (constrainpitch)
    {
        pitch = std::min(pitch, (GLfloat)89);
        pitch = std::max(pitch, (GLfloat)-89);
    }

    updateCameraVectors();
}

void Camera::ProcessMouseScroll(GLfloat yoffset)
{
    if (zoom >= 1 && zoom <= 45)
    {
        zoom -= yoffset;
    }
    zoom = std::min(zoom, (GLfloat)45);
    zoom = std::max(zoom, (GLfloat)1);
}

void Camera::updateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    front.y = sin(glm::radians(this->pitch));
    front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    this->front = glm::normalize(front);
    this->right = glm::normalize(glm::cross(this->front, this->worldUp));
    this->up = glm::normalize(glm::cross(this->right, this->front));
}
