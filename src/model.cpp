#include "model.hpp"

Model::Model(std::string path, bool gamma) {
  gammaCorrection = gamma;
  loadModel(path);
  glCheckError();
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
  glCheckError();
}

void Model::processNode(aiNode *node, const aiScene *scene) {
  // std::cout << "-> Processing node: " << node->mName.C_Str() << std::endl;
  // std::cout << "Number of meshes: " << node->mNumMeshes << std::endl;

  // Process each mesh located at the current node.
  for (unsigned int i = 0; i < node->mNumMeshes; i++) {
    // The node object only contains indices to index the actual objects in the scene.
    // The scene contains all the data, node is just to keep stuff organized (like
    // relations between nodes).
    aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
    meshes.push_back(processMesh(mesh, scene));
  }

  // std::cout << "Number of children: " << node->mNumChildren << std::endl;

  // After we've processed all of the meshes (if any) we then recursively process each
  // of the children nodes
  for (unsigned int i = 0; i < node->mNumChildren; i++) {
    std::cout << std::endl;
    processNode(node->mChildren[i], scene);
  }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene) {
  // Data to fill
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  std::vector<Texture> textures;

  // std::cout << "-> Processing mesh: " << mesh->mName.C_Str() << std::endl;
  // std::cout << "Number of vertices: " << mesh->mNumVertices << std::endl;

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

  // std::cout << "Number of faces: " << mesh->mNumFaces << std::endl;

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

  glCheckError();

  // Return a mesh object created from the extracted mesh data
  return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                                 std::string typeName) {
  std::vector<Texture> textures;
  for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
    aiString texture_path;
    mat->GetTexture(type, i, &texture_path);
    glCheckError();

    // If texture hasn't been loaded already, load it
    if (!textures_loaded[texture_path.C_Str()]) {
      // std::cout << "Loading texture: " << texture_path.C_Str() << std::endl;
      Texture texture(texture_path.C_Str(), type, typeName);
      // glCheckError();
      textures.push_back(texture);
      // glCheckError();
      textures_loaded[texture_path.C_Str()] = true;
      // glCheckError();
    }
  }

  glCheckError();

  return textures;
}
