#include "Model.h"

Model::Model() {
    filePath = ""; 
}

Model::Model(const char* filePath) {
    // load model using assimp
    Model::filePath = filePath;
    LoadModel(Model::filePath);
}

Model::Model(Mesh* mesh) {
    filePath = "";
    Materials.push_back(new Material());
    Meshes.push_back(mesh);
}

Model::Model(Mesh* mesh, Material* material) {
    filePath = "";
    Materials.push_back(material);
    Meshes.push_back(mesh);
}

Model::Model(std::vector<Mesh*>& meshes, Material* material)
{
    filePath = "";
    Meshes = meshes;
    Materials.push_back(material);
    // Ensure all meshes have the only material set as it's index
    for (unsigned int i = 0; i < Meshes.size(); i++)
        Meshes[i]->materialIndex = 0;
}

Model::Model(std::vector<Mesh*>& meshes, std::vector<Material*> materials)
{
    filePath = "";
    Meshes = meshes;
    Materials = materials;
}

Model::Model(std::vector<Mesh*>& meshes) {
    filePath = "";
    Meshes = meshes;
    Materials.push_back(new Material());
    for (unsigned int i = 0; i < Meshes.size(); i++)
        Meshes[i]->materialIndex = 0;
}

/* Sets all materials in list to material */
void Model::SetMaterial(Material* material)
{
    for (unsigned int i = 0; i < Materials.size(); i++)
        Materials[i] = material;
}

/* Sets material in list at index to material */
void Model::SetMaterial(unsigned int materialIndex, Material* material)
{
    if (materialIndex < Materials.size()){ Materials[materialIndex] = material; }
}

void Model::LoadModel(std::string path)
{
    printf("\nAttempting to load model from %s\n", path.c_str());
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, 
        aiProcess_Triangulate 
        | aiProcess_FixInfacingNormals 
        | aiProcess_FlipUVs 
        | aiProcess_CalcTangentSpace 
        | aiProcess_JoinIdenticalVertices
        | aiProcess_GenNormals
    );
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        printf("ERROR::ASSIMP::%s\n", importer.GetErrorString());
        return;
    }
    directory = path.substr(0, path.find_last_of('/'));

    if(scene->HasMeshes()) { ProcessScene(scene); }
    printf("Successfully loaded 3D-model from %s\n", path.c_str());
}

void Model::ProcessScene(const aiScene* scene) {
    if (scene->HasMaterials()) {
        printf("Found %i materials on scene\n", scene->mNumMaterials);
        for (unsigned int j = 0; j < scene->mNumMaterials; j++)
            Materials.push_back(ProcessMaterial(scene->mMaterials[j]));
        printf("Processed %i materials\n", (int)Materials.size());
    }
    if (scene->HasMeshes()) {
        printf("Found %i meshes on scene\n", scene->mNumMeshes);
        for (unsigned int i = 0; i < scene->mNumMeshes; i++)
            Meshes.push_back(ProcessMesh(scene->mMeshes[i], scene));
        printf("Processed %i meshes\n", (int)Meshes.size());
    }
}

Material* Model::ProcessMaterial(aiMaterial* aimaterial) {
    int shadingMode;
    aimaterial->Get(AI_MATKEY_SHADING_MODEL, shadingMode);
    if (shadingMode != aiShadingMode_Blinn && shadingMode != aiShadingMode_Phong && shadingMode != aiShadingMode_Gouraud) {
        printf("Shading mode of this model is not supported! Returning default material.\n");
        return new Material();
    }
    else {
        aiColor4D baseColor;
        aiColor4D ambientColor;
        aiColor4D diffuseColor;
        aiColor4D specularColor;
        float shininess;

        glm::vec3 color(1.0f);
        glm::vec3 ambient(0.15f);
        glm::vec3 diffuse(0.85f);
        glm::vec3 specular(0.5f);

        if (AI_SUCCESS != aimaterial->Get(AI_MATKEY_COLOR_AMBIENT, ambientColor)) {
            printf("Failed to get ambient color from material!\n");
        } 
        else ambient = glm::vec3(ambientColor.r, ambientColor.g, ambientColor.b);

        if (AI_SUCCESS != aimaterial->Get(AI_MATKEY_COLOR_DIFFUSE, diffuseColor)) {
            printf("Failed to get diffuse color from material!\n");
        }
        else diffuse = glm::vec3(diffuseColor.r, diffuseColor.g, diffuseColor.b);

        if (AI_SUCCESS != aimaterial->Get(AI_MATKEY_COLOR_SPECULAR, specularColor)) {
            printf("Failed to get specular color from material!\n");
        } 
        else specular = glm::vec3(specularColor.r, specularColor.g, specularColor.b);

        if (AI_SUCCESS != aimaterial->Get(AI_MATKEY_BASE_COLOR, baseColor)) {
            printf("Failed to get base color from material, setting to white!\n");
            color = glm::vec3(1.0f);
        }
        else color = glm::vec3(baseColor.r, baseColor.g, baseColor.b);

        if (AI_SUCCESS != aimaterial->Get(AI_MATKEY_SHININESS, shininess)) {
            printf("Failed to get shininess value from material, returning default!\n");
            return new Material();
        }

        if (shininess == 0.0f) { shininess = 32.0f; }

        return new Material(color, ambient, diffuse, specular, shininess);
    }
}

Mesh* Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    if (mesh->HasPositions()) {
        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            glm::vec3 position(0.0f, 0.0f, 0.0f);
            glm::vec3 normal(0.0f, 0.0f, 0.0f);
            glm::vec3 color(1.0f, 1.0f, 1.0f);
            glm::vec2 texCoords(0.0f, 0.0f);

            position.x = mesh->mVertices[i].x;
            position.y = mesh->mVertices[i].y;
            position.z = mesh->mVertices[i].z;

            if (mesh->HasNormals()) {
                normal.x = mesh->mNormals[i].x;
                normal.y = mesh->mNormals[i].y;
                normal.z = mesh->mNormals[i].z;
            }

            if (mesh->HasVertexColors(0)) {
                color.r = mesh->mColors[0][i].r;
                color.g = mesh->mColors[0][i].g;
                color.b = mesh->mColors[0][i].b;
            }
            else {
                // Generate random color
                color = glm::vec3((float)(rand() % 2), (float)(rand() % 2), (float)(rand() % 2));
            }

            if (mesh->HasTextureCoords(0)) {
                texCoords.x = mesh->mTextureCoords[0][i].x;
                texCoords.y = mesh->mTextureCoords[0][i].y;
            }

            Vertex vertex = Vertex();
            vertex.Position = position;
            vertex.Normal = normal;
            vertex.Color = color;
            vertex.TexCoords = texCoords;
            vertices.push_back(vertex);
        }
    }
    else {
        printf("Mesh has no positions, can not create vertices!");
        return new Mesh();
    }

    if (mesh->HasFaces()) {
        for (unsigned int j = 0; j < mesh->mNumFaces; j++)
        {
            for (unsigned int k = 0; k < mesh->mFaces[j].mNumIndices; k++)
                indices.push_back(mesh->mFaces[j].mIndices[k]);
        }
    }
    else {
        printf("Mesh has no faces, can not create indices!");
        return new Mesh();
    }
    

    if (scene->HasMaterials()) {
        return new Mesh(vertices, indices, mesh->mMaterialIndex);
    }
    return new Mesh(vertices, indices);
}
