class Vertex {
 private:
  // Positions of the vertices in (x,y,z,w) coordinate system.
  float positionArray[4] = {0.0f, 0.0f, 0.0f, 1.0f};
  // Colors of the vertex in RGBA.
  float colorArray[4] = {1.0f, 1.0f, 1.0f, 1.0f};
  // Texture coordenates of vertex.
  float textureArray[3] = {0.0f, 0.0f, 0.0f};

 public:
  // Create a new Vertex object.
  Vertex();
  // Delete created Vertex object.
  ~Vertex();

  // Set the position of the vertex.
  void setPosition(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f);
  // Set the color of the vertex.
  void setColor(float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);
  // Set the texture coordenates of the vertex.
  void setTexture(float u = 0.0f, float v = 0.0f, float w = 0.0f);

  // Get the color of the vertex.
  float* getColor();
  // Get the position of the vertex.
  float* getPosition();
  // Get the color of the vertex.
  float* getTexture();
};
