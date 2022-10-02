#include "model.hpp"

Model::Model(std::string path, bool gamma) {
  gammaCorrection = gamma;
  loadModel(path);
}

void Model::loadModel(std::string path) {
  // Read file via ASSIMP.
  Assimp::Importer importer;
  const aiScene *scene =
      importer.ReadFile(path.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals |
                                          aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
  // Check for errors.
  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
    std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
    return;
  }

  // Process ASSIMP's root node recursively.
  processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene) {
  // Process each mesh located at the current node.
  for (unsigned int i = 0; i < node->mNumMeshes; i++) {
    // The node object only contains indices to index the actual objects in the scene.
    // The scene contains all the data, node is just to keep stuff organized (like
    // relations between nodes).
    aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
    meshes.push_back(processMesh(mesh, scene));
  }

  // After we've processed all of the meshes (if any) we then recursively process each
  // of the children nodes
  for (unsigned int i = 0; i < node->mNumChildren; i++) {
    processNode(node->mChildren[i], scene);
  }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene) {
  // Data to fill
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  std::vector<Texture> textures;

  // Walk through each of the mesh's vertices
  for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
    Vertex vertex;

    // Position
    vertex.position = Position{mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z};

    // Normals
    if (mesh->HasNormals()) {
      vertex.normal = Normal{mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z};
    }

    // A vertex can contain up to 8 different texture coordinates. We thus make the assumption that
    // we won't use models where a vertex can have multiple texture coordinates so we always take the
    // first set (0).
    if (mesh->mTextureCoords[0]) {
      // Texture coordinates.
      vertex.textureCoords = TextureCoords{mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y};

      // Tangent.
      vertex.tangent = Tangent{mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z};

      // Bitangent.
      vertex.bitangent =
          Bitangent{mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z};
    }

    vertices.push_back(vertex);
  }

  // Now walk through each of the mesh's faces and retrieve the corresponding vertex indices.
  for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
    aiFace face = mesh->mFaces[i];
    // Retrieve all indices of the face and store them in the indices vector
    for (unsigned int j = 0; j < face.mNumIndices; j++) indices.push_back(face.mIndices[j]);
  }

  // Process materials.
  aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
  // We assume a convention for sampler names in the shaders. Each diffuse texture should be named
  // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER.
  // Same applies to other texture as the following list summarizes:
  // - diffuse: texture_diffuseN
  // - specular: texture_specularN
  // - normal: texture_normalN

  // 1. Diffuse maps
  std::vector<Texture> diffuseMaps =
      loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
  textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
  // 2. Specular maps
  std::vector<Texture> specularMaps =
      loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
  textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
  // 3. Normal maps
  std::vector<Texture> normalMaps =
      loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
  textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
  // 4. Height maps
  std::vector<Texture> heightMaps =
      loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
  textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

  // Return a mesh object created from the extracted mesh data
  return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                                 std::string typeName) {
  std::vector<Texture> textures;
  for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
    aiString str;
    mat->GetTexture(type, i, &str);
    // Check if texture was loaded before and if so, continue to next iteration:
    // skip loading a new texture
    bool skip = false;

    // TODO: Improve this by using a MAP instead of a for loop.
    for (unsigned int j = 0; j < textures_loaded.size(); j++) {
      if (std::strcmp(textures_loaded[j].getPath().c_str(), str.C_Str()) == 0) {
        textures.push_back(textures_loaded[j]);
        // A texture with the same filepath has already been loaded, continue
        // to next one. (optimization)
        skip = true;

        break;
      }
    }

    // If texture hasn't been loaded already, load it
    if (!skip) {
      Texture texture(str.C_Str(), type, typeName);  // TODO: Check str.C_Str() is correct
      textures.push_back(texture);
      // Store it as texture loaded for entire model, to
      // ensure we won't unnecesery load duplicate textures.
      textures_loaded.push_back(texture);
    }
  }

  return textures;
}
