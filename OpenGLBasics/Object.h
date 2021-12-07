#ifndef OBJECT_H
#define OBJECT_H

#include "Model.h"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

class Object {
public:
    Model ObjModel;
    glm::vec3 Position;
    glm::quat Rotation;
    glm::vec3 Scale;

    Object();

    Object(Object* object);

    Object(glm::vec3 position);

    Object(glm::vec3 position, glm::vec3 scale);

    Object(glm::vec3 position, glm::quat rotation);

    Object(glm::vec3 position, glm::quat rotation, glm::vec3 scale);

    Object(Model model);

    Object(Model model, glm::vec3 position);

    Object(Model model, glm::quat rotation);

    Object(Model model, glm::vec3 position, glm::vec3 scale);

    Object(Model model, glm::vec3 position, glm::quat rotation);

    Object(Model model, glm::vec3 position, glm::quat rotation, glm::vec3 scale);
};

#endif