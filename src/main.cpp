#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "headers/gl_utils.hpp"

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float cameraSpeed = 0.05f;

// Função de callback para tratar eventos de teclado
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        switch (key) {
            case GLFW_KEY_W:
                cameraPos += cameraSpeed * cameraFront;
                break;
            case GLFW_KEY_S:
                cameraPos -= cameraSpeed * cameraFront;
                break;
            case GLFW_KEY_A:
                cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
                break;
            case GLFW_KEY_D:
                cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
                break;
        }
    }
}

int main() {
    // Inicialização do GLFW
    if (!GlUtils::init_project()) {
        std::cerr << "Error initializing project" << std::endl;
        return -1;
    }

    // Criação de uma janela
    GLFWwindow* window = GlUtils::create_window(800, 600, "Cubo Giratório");
    
    // Init GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Erro ao inicializar o GLAD" << std::endl;
        return -1;
    }

    // // Definição da função de callback para eventos de teclado
    // glfwSetKeyCallback(window, key_callback);

    // Definição das coordenadas dos vértices do cubo
    float vertices[] = {
        // Posições
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f
    };

    // Definição dos índices para formar as faces do cubo
    unsigned int indices[] = {
        0, 1, 2, 2, 3, 0,
        1, 5, 6, 6, 2, 1,
        5, 4, 7, 7, 6, 5,
        4, 0, 3, 3, 7, 4,
        3, 2, 6, 6, 7, 3,
        4, 5, 1, 1, 0, 4
    };

    GLuint frag_shader, vert_shader;
    GLint success;
    char log[512];

    std::string vertex_shader = GlUtils::get_file_content("src/shaders/vertex.glsl");
    std::string fragment_shader = GlUtils::get_file_content("src/shaders/frag.glsl");
    
    vertex_shader = vertex_shader + "\n";
    fragment_shader = fragment_shader + "\n";
    
    const char* vertexShaderSource = vertex_shader.c_str();
    const char* fragmentShaderSource = fragment_shader.c_str();

    GlUtils::debug_print(vertexShaderSource);
    GlUtils::debug_print(fragmentShaderSource);

    // // // Vertex Shader
    vert_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert_shader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vert_shader);
    glGetShaderiv(vert_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vert_shader, 512, nullptr, log);
        std::cout << "Erro ao compilar o Vertex Shader:\n" << log << std::endl;
    }

    // Fragment Shader
    frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag_shader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(frag_shader);
    glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(frag_shader, 512, nullptr, log);
        std::cout << "Erro ao compilar o Fragment Shader:\n" << log << std::endl;
    }

    // // Programa de shader
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vert_shader);
    glAttachShader(shaderProgram, frag_shader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, log);
        std::cout << "Erro ao linkar o programa de shader:\n" << log << std::endl;
    }
    glDeleteShader(vert_shader);
    glDeleteShader(frag_shader);

    // // Configuração do buffer de vértices e elementos
    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // // Habilita o teste de profundidade
    glEnable(GL_DEPTH_TEST);

    // // Loop principal
    while (!glfwWindowShouldClose(window)) {
    //     // Entrada e manipulação de eventos
        glfwPollEvents();


        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //     // Configuração das matrizes de transformação
        float time = glfwGetTime();
        float angle = glm::radians(20.0f) * time; // Ângulo de rotação
        glm::mat4 model = glm::rotate(glm::mat4(1.0f), angle * 15.f, glm::vec3(0.5f, 1.0f, 0.0f)); // Matriz de modelo
        // glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // Matriz de visualização
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f); // Matriz de projeção

    //     // Configuração do shader e das matrizes uniformes
        glUseProgram(shaderProgram);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    //     // Desenha o cubo
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

    //     // Troca os buffers e verifica os eventos
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // // Libera os recursos
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    // Destroy window pointer
    glfwDestroyWindow(window);

    // GLFW terminate
    glfwTerminate();

    return 0;
}