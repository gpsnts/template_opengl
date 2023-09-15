#include "headers/gl_utils.hpp"



bool GlUtils::init_glfw()
{
  if (!glfwInit()) {
    std::cerr << "Erro ao inicializar o GLFW" << std::endl;
    return false;
  }
  return true;
}


bool GlUtils::init_project()
{
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  GlUtils::debug_print("Profile set");

  bool up_glfw = GlUtils::init_glfw();
  GlUtils::debug_print("GLFW initialized");
  
  return up_glfw;
}

std::string GlUtils::get_file_content(const char* path_to_file)
{
  fs::path directory_path = fs::current_path().parent_path() / path_to_file;

  if (!fs::exists(directory_path)) {
    std::cout << "Directory/File: " << path_to_file << " does not exist" << std::endl;
  }

  std::ifstream file_stream(directory_path);

  file_stream.seekg(0, std::ios::end);
  std::streampos size = file_stream.tellg();
  file_stream.seekg(0, std::ios::beg);

  std::vector<char> data(size);
  file_stream.read(data.data(), size);

  file_stream.close();

  return data.data();
}

GLFWwindow* GlUtils::create_window(int width, int height, const char* title)
{
  GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
  if (!window) {
    std::cerr << "Error creating GLFW window" << std::endl;
    glfwTerminate();
    return nullptr;
  }
  glfwMakeContextCurrent(window);
  return window;
}