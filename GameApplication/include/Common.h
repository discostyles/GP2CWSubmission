#ifndef _COMMON_H
#define _COMMON_H

//Common C++ Header files
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <memory>
#include <map>
#include <thread>
#include <mutex>
#include <queue>
#include <chrono>
#include <ctime>
#include <cstdarg>

//Name space std, so we don't need to do std::vector
using namespace std;

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_opengl.h>
//#include <windows.h>

#define GLM_FORCE_RADIANS
//maths headers
#include <glm/glm.hpp>
using namespace glm;

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/ext.hpp>
//#include "SDL.h"
#include "../Utils/include/Utils.h"
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#endif
