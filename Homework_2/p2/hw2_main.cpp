//
//  main.cpp
//  OpenGL4Test
//
//  Created by Rafael Radkowski on 5/28/15.
//  Copyright (c) 2015 -. All rights reserved.
//

// stl include
#include <iostream>
#include <string>

// GLEW include
#include <GL/glew.h>

// GLM include files
#define GLM_FORCE_INLINE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


// glfw includes
#include <GLFW/glfw3.h>


// include local files
#include "controls.h"
#include "HCI557Common.h"


using namespace std;

static const string vs_string =
"#version 410 core                                                 \n"
"                                                                   \n"
"uniform mat4 projectionMatrix;                                    \n"
"uniform mat4 viewMatrix;                                           \n"
"uniform mat4 modelMatrix;                                          \n"
"in vec3 in_Position;                                               \n"
"                                                                   \n"
"in vec3 in_Color;                                                  \n"
"out vec3 pass_Color;                                               \n"
"                                                                  \n"
"void main(void)                                                   \n"
"{                                                                 \n"
"    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(in_Position, 1.0);  \n"
"    pass_Color = in_Color;                                         \n"
"}                                                                 \n";

// Fragment shader source code. This determines the colors in the fragment generated in the shader pipeline. In this case, it colors the inside of our triangle specified by our vertex shader.
static const string fs_string  =
"#version 410 core                                                 \n"
"                                                                  \n"
"in vec3 pass_Color;                                                 \n"
"out vec4 color;                                                    \n"
"void main(void)                                                   \n"
"{                                                                 \n"
"    color = vec4(pass_Color, 1.0);                               \n"
"}                                                                 \n";




/// Camera control matrices
glm::mat4 projectionMatrix; // Store the projection matrix
glm::mat4 viewMatrix; // Store the view matrix
glm::mat4 modelMatrix; // Store the model matrix




// The handle to the window object
GLFWwindow*         window;


// Define some of the global variables we're using for this sample
GLuint program;







///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// Fill this functions with your model code.

// USE THESE vertex array objects to define your objects
unsigned int vaoID[2];
unsigned int vboID[2];

/*!
 ADD YOUR CODE TO CREATE THE TRIANGLE STRIP MODEL TO THIS FUNCTION
 */
unsigned int createTriangleStripModel(void)
{
    // use the vertex array object vaoID[0] for this model representation
    float* vertices = new float[144];  // Vertices
    float *colors = new float[144]; // Colors
    
    //Front of small rectangle
    vertices[0] = 1.0; vertices[1] = 0.0; vertices[2] = -2.0;
    colors[0] = 0.0; colors[1] = 0.0; colors[2] = 1.0;
    
    vertices[3] = 1.0; vertices[4] = 1.0; vertices[5] = -2.0;
    colors[3] = 0.0; colors[4] = 0.0; colors[5] = 1.0;
    
    vertices[6] = 1.0; vertices[7] = 0.0; vertices[8] = 0.0;
    colors[6] = 0.0; colors[7] = 0.0; colors[8] = 1.0;
    
    vertices[9] = 1.0; vertices[10] = 1.0; vertices[11] = 0.0;
    colors[9] = 0.0; colors[10] = 0.0; colors[11] = 1.0;
    
    //Left side of small rectangle
    vertices[12] = 0.0; vertices[13] = 0.0; vertices[14] = 0.0;
    colors[12] = 0.0; colors[13] = 0.0; colors[14] = 1.0;
    
    vertices[15] = 0.0; vertices[16] = 1.0; vertices[17] = 0.0;
    colors[15] = 0.0; colors[16] = 0.0; colors[17] = 1.0;
    
    //Back side of small rectangle
    vertices[18] = 0.0; vertices[19] = 0.0; vertices[20] = -2.0;
    colors[18] = 0.0; colors[19] = 0.0; colors[20] = 1.0;

    vertices[21] = 0.0; vertices[22] = 1.0; vertices[23] = -2.0;
    colors[21] = 0.0; colors[22] = 0.0; colors[23] = 1.0;
    
    //Top side of small rectangle
    vertices[24] = 1.0; vertices[25] = 1.0; vertices[26] = 0.0;
    colors[24] = 0.0; colors[25] = 0.0; colors[26] = 1.0;

    vertices[27] = 1.0; vertices[28] = 1.0; vertices[29] = -2.0;
    colors[27] = 0.0; colors[28] = 0.0; colors[29] = 1.0;
    
    //Left pentagon face (small square)
    vertices[30] = 0.0; vertices[31] = 1.0; vertices[32] = -2.0;
    colors[30] = 0.0; colors[31] = 0.0; colors[32] = 1.0;
    
    vertices[33] = 0.0; vertices[34] = 2.0; vertices[35] = -2.0;
    colors[33] = 0.0; colors[34] = 0.0; colors[35] = 1.0;
    
    vertices[36] = 1.0; vertices[37] = 1.0; vertices[38] = -2.0;
    colors[36] = 0.0; colors[37] = 0.0; colors[38] = 1.0;
    
    vertices[39] = 1.0; vertices[40] = 2.0; vertices[41] = -2.0;
    colors[39] = 0.0; colors[40] = 0.0; colors[41] = 1.0;
    
    //Left pentagon top rectangle
    vertices[42] = 3.0; vertices[43] = 1.0; vertices[44] = -2.0;
    colors[42] = 0.0; colors[43] = 0.0; colors[44] = 1.0;
    
    vertices[45] = 1.0; vertices[46] = 1.0; vertices[47] = -2.0;
    colors[45] = 0.0; colors[46] = 0.0; colors[47] = 1.0;
    
    vertices[48] = 3.0; vertices[49] = 0.0; vertices[50] = -2.0;
    colors[48] = 0.0; colors[49] = 0.0; colors[50] = 1.0;
    
    vertices[51] = 1.0; vertices[52] = 0.0; vertices[53] = -2.0;
    colors[51] = 0.0; colors[52] = 0.0; colors[53] = 1.0;
    
    //Bottom 2/3s of pentagon
    vertices[54] = 1.0; vertices[55] = 0.0; vertices[56] = -3.0;
    colors[54] = 0.0; colors[55] = 0.0; colors[56] = 1.0;
    
    vertices[57] = 3.0; vertices[58] = 0.0; vertices[59] = -2.0;
    colors[57] = 0.0; colors[58] = 0.0; colors[59] = 1.0;
    
    vertices[60] = 3.0; vertices[61] = 0.0; vertices[62] = -3.0;
    colors[60] = 0.0; colors[61] = 0.0; colors[62] = 1.0;
    
    //Small face rectangle of pentagon
    vertices[63] = 3.0; vertices[64] = 1.0; vertices[65] = -2.0;
    colors[63] = 0.0; colors[64] = 0.0; colors[65] = 1.0;
    
    vertices[66] = 3.0; vertices[67] = 1.0; vertices[68] = -3.0;
    colors[66] = 0.0; colors[67] = 0.0; colors[68] = 1.0;
    
    //Top face of pentagon
    vertices[69] = 1.0; vertices[70] = 2.0; vertices[71] = -2.0;
    colors[69] = 0.0; colors[70] = 0.0; colors[71] = 1.0;
    
    vertices[72] = 1.0; vertices[73] = 2.0; vertices[74] = -3.0;
    colors[72] = 0.0; colors[73] = 0.0; colors[74] = 1.0;
    
    vertices[75] = 0.0; vertices[76] = 2.0; vertices[77] = -2.0;
    colors[75] = 0.0; colors[76] = 0.0; colors[77] = 1.0;
    
    vertices[78] = 0.0; vertices[79] = 2.0; vertices[80] = -3.0;
    colors[78] = 0.0; colors[79] = 0.0; colors[80] = 1.0;
    
    //Back face of pentagon
    vertices[81] = 0.0; vertices[82] = 0.0; vertices[83] = -3.0;
    colors[81] = 0.0; colors[82] = 0.0; colors[83] = 1.0;
    
    vertices[84] = 0.0; vertices[85] = 2.0; vertices[86] = -2.0;
    colors[84] = 0.0; colors[85] = 0.0; colors[86] = 1.0;
    
    vertices[87] = 0.0; vertices[88] = 0.0; vertices[89] = -2.0;
    colors[87] = 0.0; colors[88] = 0.0; colors[89 ] = 1.0;
    
    glGenVertexArrays(2, &vaoID[0]); // Create our Vertex Array Object
    glBindVertexArray(vaoID[0]); // Bind our Vertex Array Object so we can use it

    glGenBuffers(2, vboID); // Generate our Vertex Buffer Object
    
    // vertices
    glBindBuffer(GL_ARRAY_BUFFER, vboID[0]); // Bind our Vertex Buffer Object
    glBufferData(GL_ARRAY_BUFFER, 144 * sizeof(GLfloat), vertices, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
    
    glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
    glEnableVertexAttribArray(0); // Disable our Vertex Array Object
    
    
    //Color
    glBindBuffer(GL_ARRAY_BUFFER, vboID[1]); // Bind our second Vertex Buffer Object
    glBufferData(GL_ARRAY_BUFFER, 144 * sizeof(GLfloat), colors, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
    
    glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
    glEnableVertexAttribArray(1); // Enable the second vertex attribute array
    
    glBindVertexArray(0); // Disable our Vertex Buffer Object
    
    delete [] vertices; // Delete our vertices from memory
    
    return 1;
}

/*!
 ADD YOUR CODE TO CREATE A MODEL USING PRIMITIVES OF YOUR CHOISE TO THIS FUNCTION
 */
unsigned int createMyModel(void)
{
    // use the vertex array object vaoID[1] for this model representation
        
    //TODO:
    vaoID[1];
    
    return 1;
}



/*!
 ADD YOUR CODE TO RENDER THE TRIANGLE STRIP MODEL TO THIS FUNCTION
 */
void renderTriangleStripModel(void)
{
    // Bind the buffer and switch it to an active buffer
    glBindVertexArray(vaoID[0]);
    
    // Draw the triangles
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 30);
}

/*!
 ADD YOUR CODE TO RENDER YOUR MODEL TO THIS FUNCTION
 */
void renderMyModel(void)
{


    
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/*!
 This function creates the two models
 */
void setupScene(void) {
    
    createTriangleStripModel();
    createMyModel();
    
}


/*!
 This function updates the virtual camera
 */
bool updateCamera()
{
    // Compute the MVP matrix from keyboard and mouse input
    computeMatricesFromInputs();
    viewMatrix =  getViewMatrix(); // get the current view matrix
    
    return true;
}





int main(int argc, const char * argv[])
{
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Init glfw, create a window, and init glew
    
    // Init the GLFW Window
    window = initWindow();
    
    
    // Init the glew api
    initGlew();
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// The Shader Program starts here
    
    // Vertex shader source code. This draws the vertices in our window. We have 3 vertices since we're drawing an triangle.
    // Each vertex is represented by a vector of size 4 (x, y, z, w) coordinates.
    static const string vertex_code = vs_string;
    static const char * vs_source = vertex_code.c_str();
    
    // Fragment shader source code. This determines the colors in the fragment generated in the shader pipeline. In this case, it colors the inside of our triangle specified by our vertex shader.
    static const string fragment_code = fs_string;
    static const char * fs_source = fragment_code.c_str();
    
    // This next section we'll generate the OpenGL program and attach the shaders to it so that we can render our triangle.
    program = glCreateProgram();
    
    // We create a shader with our fragment shader source code and compile it.
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fs_source, NULL);
    glCompileShader(fs);
    
    // We create a shader with our vertex shader source code and compile it.
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vs_source, NULL);
    glCompileShader(vs);
    
    // We'll attach our two compiled shaders to the OpenGL program.
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    
    glLinkProgram(program);
    
    // We'll specify that we want to use this program that we've attached the shaders to.
    glUseProgram(program);
    
    //// The Shader Program ends here
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    
    /// IGNORE THE NEXT PART OF THIS CODE
    /// IGNORE THE NEXT PART OF THIS CODE
    /// IGNORE THE NEXT PART OF THIS CODE
    // It controls the virtual camera
    
    // Set up our green background color
    static const GLfloat clear_color[] = { 0.6f, 0.7f, 1.0f, 1.0f };
    static const GLfloat clear_depth[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    
    
    projectionMatrix = glm::perspective(1.1f, (float)800 / (float)600, 0.1f, 100.f);
    modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)); // Create our model matrix which will halve the size of our model
    viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    
    int projectionMatrixLocation = glGetUniformLocation(program, "projectionMatrix"); // Get the location of our projection matrix in the shader
    int viewMatrixLocation = glGetUniformLocation(program, "viewMatrix"); // Get the location of our view matrix in the shader
    int modelMatrixLocation = glGetUniformLocation(program, "modelMatrix"); // Get the location of our model matrix in the shader
    
    
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]); // Send our projection matrix to the shader
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]); // Send our view matrix to the shader
    glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader
    
    
    glBindAttribLocation(program, 0, "in_Position");
    glBindAttribLocation(program, 1, "in_Color");
    
    //// The Shader Program ends here
    //// START TO READ AGAIN
    //// START TO READ AGAIN
    //// START TO READ AGAIN
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    
    // this creates the scene
    setupScene();
    
    

    // Enable depth test
    // ignore this line, it allows us to keep the distance value after we proejct each object to a 2d canvas.
    glEnable(GL_DEPTH_TEST);
    
    // This is our render loop. As long as our window remains open (ESC is not pressed), we'll continue to render things.
    while(!glfwWindowShouldClose(window))
    {
        
        // Clear the entire buffer with our green color (sets the background to be green).
        glClearBufferfv(GL_COLOR , 0, clear_color);
        glClearBufferfv(GL_DEPTH , 0, clear_depth);
        
        
        // update the virtual camera
        // ignore this line since we did not introduced cameras.
        updateCamera();
        
        
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //// This generate the object
        // Enable the shader program
        glUseProgram(program);
        
        // this changes the camera location
        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]); // send the view matrix to our shader
        
        // This moves the model to the right
        modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader
        
        renderTriangleStripModel();
        
        // This moves the model to the left
        modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, -0.0f, 0.0f));
        glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader
        
        renderMyModel();
        
        
        glUseProgram(0);
        //// This generate the object
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        
        
        // Swap the buffers so that what we drew will appear on the screen.
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }
    
    // Program clean up when the window gets closed.
    glDeleteVertexArrays(2, vaoID);
    glDeleteProgram(program);
}

