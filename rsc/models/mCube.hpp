#ifndef __MCUBE_HPP__
#define __MCUBE_HPP__

#include "../../src/vertex.hpp"

// Texture coordinates
float grass[2] = {0.0f, 1.0f / 3.0f};
float side[2] = {1.0f / 3.0f, 2.0f / 3.0f};
float dirt[2] = {2.0f / 3.0f, 1.0f};

// Coordinates of the vertices of the triangle
Vertex modelVertices[24] = {

    // -------- Front and Back ------- //

    Vertex(Position{-0.5f, -0.5f, -0.5f}, Color{1.0f, 0.0f, 1.0f}, TextureCoords{side[0], 0.0f}),
    Vertex(Position{+0.5f, -0.5f, -0.5f}, Color{0.0f, 0.0f, 1.0f}, TextureCoords{side[1], 0.0f}),
    Vertex(Position{+0.5f, +0.5f, -0.5f}, Color{1.0f, 0.0f, 1.0f}, TextureCoords{side[1], 1.0f}),
    Vertex(Position{-0.5f, +0.5f, -0.5f}, Color{0.0f, 0.0f, 1.0f}, TextureCoords{side[0], 1.0f}),

    Vertex(Position{-0.5f, -0.5f, +0.5f}, Color{1.0f, 0.0f, 1.0f}, TextureCoords{side[0], 0.0f}),
    Vertex(Position{+0.5f, -0.5f, +0.5f}, Color{0.0f, 0.0f, 1.0f}, TextureCoords{side[1], 0.0f}),
    Vertex(Position{+0.5f, +0.5f, +0.5f}, Color{1.0f, 0.0f, 1.0f}, TextureCoords{side[1], 1.0f}),
    Vertex(Position{-0.5f, +0.5f, +0.5f}, Color{0.0f, 0.0f, 1.0f}, TextureCoords{side[0], 1.0f}),

    // -------- Left and Right ------- //

    Vertex(Position{-0.5f, -0.5f, -0.5f}, Color{1.0f, 0.0f, 1.0f}, TextureCoords{side[1], 0.0f}),
    Vertex(Position{+0.5f, -0.5f, -0.5f}, Color{0.0f, 0.0f, 1.0f}, TextureCoords{side[0], 0.0f}),
    Vertex(Position{+0.5f, +0.5f, -0.5f}, Color{1.0f, 0.0f, 1.0f}, TextureCoords{side[0], 1.0f}),
    Vertex(Position{-0.5f, +0.5f, -0.5f}, Color{0.0f, 0.0f, 1.0f}, TextureCoords{side[1], 1.0f}),

    Vertex(Position{-0.5f, -0.5f, +0.5f}, Color{1.0f, 0.0f, 1.0f}, TextureCoords{side[0], 0.0f}),
    Vertex(Position{+0.5f, -0.5f, +0.5f}, Color{0.0f, 0.0f, 1.0f}, TextureCoords{side[1], 0.0f}),
    Vertex(Position{+0.5f, +0.5f, +0.5f}, Color{1.0f, 0.0f, 1.0f}, TextureCoords{side[1], 1.0f}),
    Vertex(Position{-0.5f, +0.5f, +0.5f}, Color{0.0f, 0.0f, 1.0f}, TextureCoords{side[0], 1.0f}),

    // -------- Top and Bottom ------- //

    Vertex(Position{-0.5f, -0.5f, -0.5f}, Color{1.0f, 0.0f, 1.0f}, TextureCoords{dirt[0], 0.0f}),
    Vertex(Position{+0.5f, -0.5f, -0.5f}, Color{0.0f, 0.0f, 1.0f}, TextureCoords{dirt[1], 0.0f}),
    Vertex(Position{+0.5f, +0.5f, -0.5f}, Color{1.0f, 0.0f, 1.0f}, TextureCoords{grass[1], 0.0f}),
    Vertex(Position{-0.5f, +0.5f, -0.5f}, Color{0.0f, 0.0f, 1.0f}, TextureCoords{grass[0], 0.0f}),

    Vertex(Position{-0.5f, -0.5f, +0.5f}, Color{1.0f, 0.0f, 1.0f}, TextureCoords{dirt[0], 1.0f}),
    Vertex(Position{+0.5f, -0.5f, +0.5f}, Color{0.0f, 0.0f, 1.0f}, TextureCoords{dirt[1], 1.0f}),
    Vertex(Position{+0.5f, +0.5f, +0.5f}, Color{1.0f, 0.0f, 1.0f}, TextureCoords{grass[1], 1.0f}),
    Vertex(Position{-0.5f, +0.5f, +0.5f}, Color{0.0f, 0.0f, 1.0f}, TextureCoords{grass[0], 1.0f}),

};

// Indices of the vertices of the triangle
unsigned int modelIndicesCount = 36;
unsigned int modelIndices[36] = {
    // Front face of square
    0, 1, 2,  // Lower triangle
    0, 2, 3,  // Upper triangle

    // Back face of square
    4, 5, 7,  // Lower triangle
    5, 6, 7,  // Upper triangle

    // Left face of square
    8, 11, 12,   // Lower triangle
    11, 12, 15,  // Upper triangle

    // Right face of square
    9, 13, 14,  // Lower triangle
    9, 10, 14,  // Upper triangle

    // Top face of square
    18, 19, 22,  // Lower triangle
    19, 22, 23,  // Upper triangle

    // Bottom face of square
    16, 17, 20,  // Lower triangle
    17, 20, 21,  // Upper triangle
};

#endif  // __MCUBE_HPP__