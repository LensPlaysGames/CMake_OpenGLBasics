#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <map>
#include <set>

#include "Camera.h"
#include "Object.h"

struct Light {
    float intensity;
    glm::vec3 position;
    glm::vec3 color;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    Light() {
        intensity = 50.0f;
        position = glm::vec3(0.0f);
        color = glm::vec3(1.0f);
        ambient = glm::vec3(0.1f);
        diffuse = glm::vec3(0.9f);
        specular = glm::vec3(0.5f);
    }

    Light(glm::vec3 _position) {
        intensity = 50.0f;
        position = _position;
        color = glm::vec3(1.0f);
        ambient = glm::vec3(0.1f);
        diffuse = glm::vec3(0.9f);
        specular = glm::vec3(0.5f);
    }

    Light(float _intensity, glm::vec3 _position, glm::vec3 _color, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular) {
        intensity = _intensity;
        position = _position;
        color = _color;
        ambient = _ambient;
        diffuse = _diffuse;
        specular = _specular;
    }
};

class LightObject {
public:
    Object* Obj;
    Light* ObjLight;
    Shader* ObjShader;

    LightObject() {
        Obj = new Object();
        ObjLight = new Light();
        ObjShader = new Shader();
    }

    LightObject(Object* obj, Light* light, Shader* shader) {
        Obj = obj;
        ObjLight = light;
        ObjShader = shader;
    }

    void MoveLight(glm::vec3 position) {
        Obj->Position = position;
        ObjLight->position = position;
    }

    void SetColor(glm::vec3 color) {
        Material* material = Obj->ObjModel.Materials[0];
        material->color = color;
        Obj->ObjModel.SetMaterial(material);
        ObjLight->color = color;
    }
};

/* Scene Data */
class Scene {
public:
    Camera MainCamera;                                      // SCENE CAMERA (CONTROLLABLE WITH KEYBOARD + MOUSE)
    LightObject* MainLight;                                 // SCENE LIGHT (USED WITH LIT SHADERS)
    std::map<Shader*, std::vector<Object*>> Objects;        // OBJECTS THAT ARE DRAWN USING SHADER EVERY FRAME
    unsigned int NumberOfObjects;                           // TOTAL NUMBER OF OBJECTS IN SCENE (1 INCLUDES LIGHT)
    glm::vec3 BackgroundColor;                              // CLEAR COLOR (EVERYTHING THAT ISN'T AN OBJECT WILL BE THIS COLOR)

    Scene(Camera mainCamera, LightObject* mainLight) : MainCamera(mainCamera) {
        MainLight = mainLight;
        BackgroundColor = glm::vec3(0.0f);
        NumberOfObjects = 1;
    };

    void AddObject(Shader* shader, Object* object) {
        NumberOfObjects++;
        Objects[shader].push_back(object);
    }
};

class Renderer {
public:
    void DrawScene(Scene scene);
};

#endif