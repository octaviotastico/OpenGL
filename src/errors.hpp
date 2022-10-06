#ifndef __ERRORS_HPP__
#define __ERRORS_HPP__

// Standard Libraries
#include <iostream>
#include <string>
#include <vector>

// Libraries imports
#include <GLAD/glad.h>

#define glCheckError() glCheckError_(__FILE__, __LINE__)

GLenum glCheckError_(const char *file, int line);

#endif  // __ERRORS_HPP__