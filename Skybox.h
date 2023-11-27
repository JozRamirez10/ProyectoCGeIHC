#pragma once

#include "CommonValues.h"
#include <vector>
#include <string>
#include<glew.h>
#include<glm.hpp>
#include<glfw3.h>
#include <gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
#include "Mesh.h"
#include "Shader_light.h"

class Skybox
{
public:
    Skybox();
    Skybox(std::vector<std::string> faceLocations);
    void DrawSkybox(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
    void setSkyboxTextures(const std::vector<std::string>& faces);  // Agregamos la declaración de la función

    ~Skybox();

private:
    Mesh* skyMesh;
    Shader* skyShader;
    GLuint textureId;
    GLuint uniformProjection, uniformView;
};
