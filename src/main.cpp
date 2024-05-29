#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include "glad.h"
#include <GLFW/glfw3.h>
#include "linmath.h"
#include "glm/glm.hpp"
#include "stb_image.h"
#include <chrono>


double _xpos, _ypos;
bool inside;
double changeX, changeY;



    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 640.0f / 480.0f, 0.1f, 100.0f);

// Or, for an ortho camera:
//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

// Camera matrix
    glm::mat4 View = glm::lookAt(
        glm::vec3(4,-3,3), // Camera is at (4,3,3), in World Space
        glm::vec3(0,0,0), // and looks at the origin
        glm::vec3(0,-1,0)  // Head is up (set to 0,-1,0 to look upside-down)
        );
    
    // Model matrix: an identity matrix (model will be at the origin)
    glm::mat4 Model = glm::mat4(1.0f);
    // Our ModelViewProjection: multiplication of our 3 matrices
    glm::mat4 mvp = Projection * View * Model;


static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}
 
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) 
    {
       inside=true;
       //getting cursor position
       glfwGetCursorPos(window, &_xpos, &_ypos);

    }
    else if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) 
    {
       inside=false;

    }
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
  if(inside){
    if(xpos-_xpos>0)
      changeX=1;
    else
      changeX=-1;

    if(ypos-_ypos>0)
      changeY=1;
    else
      changeY=-1;
    mvp = glm::rotate(mvp, (float)changeX/100.0f, glm::vec3(0.0f,1.0f,0.0f));
   // mvp = glm::rotate(mvp, (float)changeY/100.0f, glm::vec3(1.0f,0.0f,0.0f));
    _xpos=xpos;
    _ypos=ypos;
  }
}
int main(void)
{
  std::string images[337];
  DIR *dp;
  int i = 0;
  struct dirent *ep;    
  dp = opendir ("./sequence");

  if (dp != NULL)
  {
    while (ep = readdir (dp)){
      if(ep->d_name[0]!='.'){
      images[i] = ep->d_name;
      i++;}
    }
    (void) closedir (dp);
  }
  else
    perror ("Couldn't open the directory");

  printf("There's %d files in the current directory.\n", i);
 




    glfwSetErrorCallback(error_callback);
 
    if (!glfwInit())
        exit(EXIT_FAILURE);
 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
 
    GLFWwindow* window = glfwCreateWindow(640, 480, "freshLow", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwMakeContextCurrent(window);
    gladLoadGL();
    glfwSwapInterval(1);
    //Defining vertices for triangle                          
    GLfloat points[] = {
    -1.0f,-1.0f,1.0f, 0.0f, 0.0f, 
    1.0f,-1.0f, 1.0f, 1.0f, 0.0f,
    -1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    1.0f,-1.0f,1.0f,1.0f, 0.0f, 
    1.0f, 1.0f,1.0f, 1.0f, 1.0f, 

    1.0f,-1.0f,-1.0f, 0.0f, 0.0f,
    -1.0f,-1.0f, -1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, -1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, -1.0f, 0.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,1.0f, 0.0f, 
    -1.0f, 1.0f,-1.0f, 1.0f, 1.0f,
    
    -1.0f,-1.0f,-1.0f, 0.0f, 0.0f, 
    -1.0f,-1.0f, 1.0f, 1.0f, 0.0f,
    -1.0f, 1.0f, -1.0f, 0.0f, 1.0f,
    -1.0f, 1.0f, -1.0f, 0.0f, 1.0f,
    -1.0f,-1.0f,1.0f,1.0f, 0.0f, 
    -1.0f, 1.0f,1.0f, 1.0f, 1.0f, 

    1.0f,-1.0f,1.0f, 0.0f, 0.0f, 
    1.0f,-1.0f, -1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    1.0f,-1.0f,-1.0f,1.0f, 0.0f, 
    1.0f, 1.0f,-1.0f, 1.0f, 1.0f,

    -1.0f,-1.0f,-1.0f, 0.0f, 0.0f, 
    1.0f,-1.0f, -1.0f, 1.0f, 0.0f,
    -1.0f, -1.0f, 1.0f, 0.0f, 1.0f,
    -1.0f, -1.0f, 1.0f, 0.0f, 1.0f,
    1.0f,-1.0f,-1.0f,1.0f, 0.0f, 
    1.0f, -1.0f,1.0f, 1.0f, 1.0f, 
  };


      GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points)*sizeof(float), points, GL_STATIC_DRAW);

    //Vertex attribute object creation
    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(0 * sizeof(float)));

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1); 
    //Loading shaders - Vertex shader
    const char* vertex_shader =
        "#version 410\n"
        "layout (location=0) in vec3 vp; "
        "layout (location=1) in vec2 aTexCoord;"
        "out vec3 color;"
        "out vec2 texCoord;"
        "uniform mat4 mvp;"
        "void main() {"
        " gl_Position = mvp * vec4 (vp, 1.0);"
        " color=vp;"
        " texCoord=aTexCoord;"
        " }";

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);

    //Loading shaders - Fragment shader
    const char* fragment_shader =
        "#version 410\n"
        "in vec3 color;"
        "in vec2 texCoord;"
        "uniform sampler2D myTexture;"

        "out vec4 frag_colour; "
        "void main() {"
        " frag_colour = texture(myTexture, texCoord);"
        " }";

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);

    //Attach shaders
    GLuint shader_programme = glCreateProgram();
    glAttachShader(shader_programme, fs);
    glAttachShader(shader_programme, vs);
    glLinkProgram(shader_programme);
    
    std::string path = "./sequence/";

    unsigned char *frame_data;
    unsigned int texture;
    int tw,th,nrChannels;
    frame_data = stbi_load((path+images[0]).c_str(), &tw, &th, nullptr, 0);
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tw, th, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if(!frame_data)
      std::cout << "ERROR";
    stbi_image_free(frame_data);


        using namespace std::chrono;
      uint64_t ms = duration_cast< milliseconds >(
        system_clock::now().time_since_epoch()
    ).count();
    //std::cout << ms;


  int k=0;
  int w1,h1;
   while (!glfwWindowShouldClose(window))
  {
      if(k<0)
        k=336;

        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_CULL_FACE);
        
       // glActiveTexture(GL_TEXTURE0);
          glUseProgram(shader_programme);
      if(duration_cast< milliseconds >(system_clock::now().time_since_epoch()).count()-ms>33){
            path="./sequence/";
            path+=images[k];
            frame_data = stbi_load(path.c_str(), &w1, &h1, nullptr, 0);
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, tw, th, GL_RGB, GL_UNSIGNED_BYTE, frame_data);
            stbi_image_free(frame_data);
            ms=duration_cast< milliseconds >(
        system_clock::now().time_since_epoch()
    ).count();
      }
        glBindVertexArray(vao);
        mvp = glm::rotate(mvp, 0.01f, glm::vec3(0.0f,1.0f,0.0f));

        GLint mvpLoc = glGetUniformLocation(shader_programme, "mvp");
        glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));
        
        glDrawArrays(GL_TRIANGLES, 0, (sizeof(points)/sizeof(float))/5);
        //glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        
        glfwPollEvents();
        glfwSwapBuffers(window);
      k--;  
  }

    glfwTerminate();
    return 0;
}
