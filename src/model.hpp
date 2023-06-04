#ifndef __MODEL_HPP__
#define __MODEL_HPP__

// Standard Libraries
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

// Libraries imports
#include <GLAD/glad.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>

// Local imports
#include "errors.hpp"
#include "mesh.hpp"
#include "shaders.hpp"
#include "textures.hpp"
#include "vertex.hpp"

class Model {
 public:
  // Constructor, expects a filepath to a 3D model.
  Model(std::string path, bool gamma = false);

  // Draws the model, and thus all its meshes
  void Draw(Shader &shader) {
    for (unsigned int i = 0; i < meshes.size(); i++) meshes[i].Draw(shader);
  }

 private:
  // Stores all the textures loaded so far, optimization to
  // make sure textures aren't loaded more than once.
  std::map<std::string, bool> textures_loaded;
  std::vector<Mesh> meshes;
  bool gammaCorrection;

  // Loads a model with supported ASSIMP extensions from file and
  // stores the resulting meshes in the meshes vector.
  void loadModel(std::string path);

  // Processes a node in a recursive fashion. Processes each individual mesh
  // located at the node and repeats this process on its children nodes (if any).
  void processNode(aiNode *node, const aiScene *scene);

  Mesh processMesh(aiMesh *mesh, const aiScene *scene);

  // Checks all material textures of a given type and loads the textures if they're not loaded yet.
  // The required info is returned as a Texture struct.
  std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};

#endif  // __MODEL_HPP__
