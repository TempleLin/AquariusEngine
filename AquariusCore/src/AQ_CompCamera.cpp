#include "headers/AQ_CompCamera.h"

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

AQ_CompCamera::AQ_CompCamera(glm::vec3 position, glm::vec3 front, glm::vec3 worldUp, 
        float yaw, float pitch, float movementSpeed, float mouseSensitivity, float zoom) {
    this->position = position;
    this->front = front;
    this->worldUp = worldUp;
    this->yaw = yaw;
    this->pitch = pitch;
    this->movementSpeed = movementSpeed;
    this->mouseSensitivity = mouseSensitivity;
    this->zoom = zoom;
    updateCameraVectors();
}

glm::mat4 AQ_CompCamera::getViewMatrix() {
    return glm::lookAt(position, position + front, up);
}

void AQ_CompCamera::processKeyboard(ECameraMovement direction, float deltaTime) {
    float velocity = movementSpeed * deltaTime;
    switch (direction) {
    case ECameraMovement::FORWARD:
        position += front * velocity;
        break;
    case ECameraMovement::BACKWARD:
        position -= front * velocity;
        break;
    case ECameraMovement::LEFT:
        position -= right * velocity;
        break;
    case ECameraMovement::RIGHT:
        position += right * velocity;
        break;
    case ECameraMovement::UP:
        position += worldUp * velocity;
        break;
    case ECameraMovement::DOWN:
        position -= worldUp * velocity;
        break;
    }
}

void AQ_CompCamera::processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch) {
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch) {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}

void AQ_CompCamera::processMouseScroll(float yoffset) {
    zoom -= (float)yoffset;
    if (zoom < 1.0f)
        zoom = 1.0f;
    if (zoom > 45.0f)
        zoom = 45.0f;
}

void AQ_CompCamera::updateCameraVectors() {
    // calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    this->front = glm::normalize(front);
    // also re-calculate the Right and Up vector
    right = glm::normalize(glm::cross(this->front, worldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    up = glm::normalize(glm::cross(right, this->front));
}