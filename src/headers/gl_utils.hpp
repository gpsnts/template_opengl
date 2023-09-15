#ifndef __GL_UTILS_HPP__
#define __GL_UTILS_HPP__

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "pch/glad_pch.hpp"
#include "pch/glfw_pch.hpp"

#include "stb_image.h"

namespace fs = std::filesystem;

class GlUtils
{
private:
	static bool init_glfw();

  GlUtils() {}
public:
	static bool init_project();
	template<typename T> void static debug_print(T arg)
	{ 
		#ifdef DEBUG_MODE
			std::cout << "Debug: " << arg << std::endl;
		#else
			return;
		#endif // DEBUG_PRINT
	}

	static std::string get_file_content(const char* path_to_file);
	static GLFWwindow* create_window(int width, int height, const char* title);
};

#endif // __GL_UTILS_HPP__
