#include "Renderer.h"

void Renderer::DrawScene(Scene scene)
{
    /* Clear render buffer from last frame */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Set everywhere on the screen that isn't rendered to to Scene background color */
    glClearColor(scene.BackgroundColor.r, scene.BackgroundColor.g, scene.BackgroundColor.b, 1.0f);

    #pragma region Draw All Objects
    /* Draw all objects in Objects map of scene */
    /* OBJECT RENDERING
        *   To reduce shader swaps (which are slow), Objects are stored in a map<Shader*, vector<Object*>>
        *   For every [key, value] pair in the map:
        *       - the shader is activated,
        *       - it's uniforms updated,
        *       - and a list of Objects are drawn using that shader and the Object's material.
        */
    for (auto& i : scene.Objects)
    {
        Shader* shader = i.first;
        shader->Use();

        shader->SetFloatMatrix4("view", scene.MainCamera.view);
        shader->SetFloatMatrix4("projection", scene.MainCamera.projection);

        /* Lighting */
        Light* light = scene.MainLight->ObjLight;

        shader->SetFloatVector3("_ViewerPosition", scene.MainCamera.Position);
        shader->SetFloatVector3("_Light.position", light->position);
        shader->SetFloatVector3("_Light.color", light->color);
        shader->SetFloat("_Light.intensity", light->intensity);
        shader->SetFloatVector3("_Light.ambient", light->ambient);
        shader->SetFloatVector3("_Light.diffuse", light->diffuse);
        shader->SetFloatVector3("_Light.specular", light->specular);

        /* Draw all objects */
        for (auto& object : i.second)
        {
            /* Use GLM to calculate model matrix from object data */
            glm::mat4 translate = glm::translate(glm::mat4(1.0f), object->Position);
            glm::mat4 scale = glm::scale(glm::mat4(1.0f), object->Scale);

            shader->SetFloatMatrix4("model", translate * glm::toMat4(object->Rotation) * scale);

            /* Draw all Meshes */
            for (unsigned int i = 0; i < object->ObjModel.Meshes.size(); i++) {
                Mesh* mesh = object->ObjModel.Meshes[i];

                /* Use Mesh's Material */
                Material* material = object->ObjModel.Materials[mesh->materialIndex];   // This would explode if a mesh had a material index that doesn't exist.
                shader->SetFloatVector3("_Material.color", material->color);
                shader->SetFloatVector3("_Material.ambient", material->ambient);
                shader->SetFloatVector3("_Material.diffuse", material->diffuse);
                shader->SetFloatVector3("_Material.specular", material->specular);
                shader->SetFloat("_Material.shininess", material->shininess);

                /* Draw call */
                glBindVertexArray(mesh->VAO);
                glDrawElements(GL_TRIANGLES, (GLsizei)mesh->Indices.size(), GL_UNSIGNED_INT, 0);
                glBindVertexArray(0);
            }
        }
    }
    #pragma endregion

    #pragma region Draw Light
    /* DRAW SCENE MAIN LIGHT */
    Object* lightObj = scene.MainLight->Obj;
    Light* light = scene.MainLight->ObjLight;
    Shader* lightShader = scene.MainLight->ObjShader;
    lightShader->Use();

    /* Use Scene.MainCamera matrices to render this object from 3D to 2D space */
    lightShader->SetFloatMatrix4("view", scene.MainCamera.view);
    lightShader->SetFloatMatrix4("projection", scene.MainCamera.projection);
    /* Use Scene.MainLight Object to render object at correct transform. */
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), lightObj->Position);
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), lightObj->Scale);
    lightShader->SetFloatMatrix4("model", translate * glm::toMat4(lightObj->Rotation) * scale);

    /* Draw all Meshes of Light Object */
    for (unsigned int i = 0; i < lightObj->ObjModel.Meshes.size(); i++) {
        Mesh* mesh = lightObj->ObjModel.Meshes[i];

        /* Use Mesh's Material */
        Material* material = lightObj->ObjModel.Materials[mesh->materialIndex];
        lightShader->SetFloatVector3("_Material.color", material->color);
        lightShader->SetFloatVector3("_Material.ambient", material->ambient);
        lightShader->SetFloatVector3("_Material.diffuse", material->diffuse);
        lightShader->SetFloatVector3("_Material.specular", material->specular);
        lightShader->SetFloat("_Material.shininess", material->shininess);

        /* Draw call */
        glBindVertexArray(mesh->VAO);
        glDrawElements(GL_TRIANGLES, (GLsizei)mesh->Indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
    #pragma endregion
}