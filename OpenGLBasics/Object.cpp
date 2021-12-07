#include "Object.h"

Object::Object(){}

Object::Object(Object* object)
{
    ObjModel = object->ObjModel;
    Position = object->Position;
    Rotation = object->Rotation;
    Scale = object->Scale;
}

Object::Object(glm::vec3 position) {
    Position = position;
    Rotation = glm::quat();
    Scale = glm::vec3(1.0f);
}

Object::Object(glm::vec3 position, glm::vec3 scale) {
    Position = position;
    Rotation = glm::quat();
    Scale = scale;
}

Object::Object(glm::vec3 position, glm::quat rotation) {
    Position = position;
    Rotation = rotation;
    Scale = glm::vec3(1.0f);
}

Object::Object(glm::vec3 position, glm::quat rotation, glm::vec3 scale) {
    Position = position;
    Rotation = rotation;
    Scale = scale;
}

Object::Object(Model model) : ObjModel(model) {
    Position = glm::vec3(0.0f);
    Rotation = glm::quat();
    Scale = glm::vec3(1.0f);
}

Object::Object(Model model, glm::vec3 position) : ObjModel(model) {
    Position = position;
    Rotation = glm::quat();
    Scale = glm::vec3(1.0f);
}

Object::Object(Model model, glm::quat rotation) : ObjModel(model) {
    Position = glm::vec3(0.0f);
    Rotation = rotation;
    Scale = glm::vec3(1.0f);
}

Object::Object(Model model, glm::vec3 position, glm::vec3 scale) : ObjModel(model) {
    Position = position;
    Rotation = glm::quat();
    Scale = scale;
}

Object::Object(Model model, glm::vec3 position, glm::quat rotation) : ObjModel(model) {
    Position = position;
    Rotation = rotation;
    Scale = glm::vec3(1.0f);
}

Object::Object(Model model, glm::vec3 position, glm::quat rotation, glm::vec3 scale) : ObjModel(model) {
    Position = position;
    Rotation = rotation;
    Scale = scale;
}