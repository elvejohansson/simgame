#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION

#include <OpenGL/gl3.h>
#endif

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader/shader.h"

static const GLfloat g_vertex_buffer_data[] = {
    // Vertex positions (x, y, z) for each triangle face
    0.0f,  0.0f,  1.0f,  // Top vertex
    -1.0f, -1.0f, -1.0f, // Bottom-left
     1.0f, -1.0f, -1.0f, // Bottom-right

    0.0f,  0.0f,  1.0f,  // Top vertex
     1.0f, -1.0f, -1.0f, // Bottom-right
     0.0f,  1.0f, -1.0f, // Back

    0.0f,  0.0f,  1.0f,  // Top vertex
     0.0f,  1.0f, -1.0f, // Back
    -1.0f, -1.0f, -1.0f, // Bottom-left

    -1.0f, -1.0f, -1.0f, // Bottom-left
     1.0f, -1.0f, -1.0f, // Bottom-right
     0.0f,  1.0f, -1.0f, // Back
};

static const GLfloat g_color_buffer_data[] = {
    // Colors for each vertex (r, g, b, a)
    1.0f,  0.0f,  0.0f,  1.0f, // Red
    0.0f,  1.0f,  0.0f,  1.0f, // Green
    0.0f,  0.0f,  1.0f,  1.0f, // Blue

    1.0f,  1.0f,  0.0f,  1.0f, // Yellow
    0.0f,  1.0f,  1.0f,  1.0f, // Cyan
    1.0f,  0.0f,  1.0f,  1.0f, // Magenta

    0.5f,  0.5f,  0.5f,  1.0f, // Gray
    0.0f,  0.5f,  0.5f,  1.0f, // Teal
    0.5f,  0.0f,  0.5f,  1.0f, // Purple

    0.1f,  0.6f,  0.4f,  1.0f, // Random color
    0.9f,  0.3f,  0.2f,  1.0f, // Random color
    0.2f,  0.8f,  0.5f,  1.0f, // Random color
};


int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
    {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    #endif

    window = glfwCreateWindow(1280, 800, "simgame", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    GLuint programID = LoadShaders("shader.vertexshader", "shader.fragmentshader");

    GLuint vertexbuffer, colorbuffer;

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

    GLuint modelMatrixID = glGetUniformLocation(programID, "model");
    GLuint viewMatrixID = glGetUniformLocation(programID, "view");
    GLuint projectionMatrixID = glGetUniformLocation(programID, "projection");

    glm::mat4 projectionMatrix = glm::perspective(glm::radians(70.0f), 1280.0f / 800.0f, 0.3f, 100.0f);

    glm::mat4 viewMatrix = glm::lookAt(
        glm::vec3(0, 0, 5),
        glm::vec3(0, 0, 0),
        glm::vec3(0, 1, 0)
    );

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(programID);

        glm::mat4 modelMatrix = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime(), glm::vec3(1, 1, 1));

        glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, glm::value_ptr(viewMatrix));
        glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)32);

        glDrawArrays(GL_TRIANGLES, 0, 4*3);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

	glDeleteBuffers(1, &vertexbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(programID);

    glfwTerminate();
    return 0;
}
