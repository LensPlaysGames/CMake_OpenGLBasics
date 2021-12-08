#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>

class Shader
{
public:
    unsigned int ID;

    Shader();
    // Constructor reads and builds the shader.
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

    void Use();

    // utility uniform functions
    void SetBool(const std::string& name, bool value) const;
    void SetInt(const std::string& name, int value) const;
    void SetFloat(const std::string& name, float value) const;

    void SetFloatVector2(const std::string& name, glm::vec2 value) const;
    void SetFloatVector2(const std::string& name, GLfloat value0, GLfloat value1) const;

    void SetFloatVector3(const std::string& name, glm::vec3 value) const;
    void SetFloatVector3(const std::string& name, GLfloat value0, GLfloat value1, GLfloat value2) const;

    void SetFloatMatrix2(const std::string& name, glm::mat2 value) const;
    void SetFloatMatrix3(const std::string& name, glm::mat3 value) const;
    void SetFloatMatrix4(const std::string& name, glm::mat4 value) const;

private:
    GLint GetUniformLocation(const std::string& name) const;
    mutable std::unordered_map<std::string, GLint> uniformLocationsCache;
};

#endif

