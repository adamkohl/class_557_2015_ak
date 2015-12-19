//  Adam Kohl, Fei X, and Jiazhong Z.
//  main.cpp
//  HCI 557 Final Project

#include "BeerPint.h"

static const string vs_string_GLSphere_410 =
"#version 410 core                                                 \n"
"                                                                   \n"
"uniform mat4 projectionMatrixBox;                                    \n"
"uniform mat4 viewMatrixBox;                                           \n"
"uniform mat4 inverseViewMatrix;                                        \n"
"uniform mat4 modelMatrixBox;                                          \n"
"uniform vec3 diffuse_color;                                          \n"
"uniform vec3 ambient_color;                                          \n"
"uniform vec3 specular_color;                                          \n"
"uniform vec4 light_position;                                          \n"
"uniform float diffuse_intensity;                                          \n"
"uniform float ambient_intensity;                                          \n"
"uniform float specular_intensity;                                          \n"
"uniform float shininess;                                          \n"
"in vec3 in_Position;                                               \n"
"in vec3 in_Normal;                                                  \n"
"in vec3 in_Color;                                                  \n"
"out vec3 pass_Color;                                               \n"
"                                                                  \n"
"                                                                 \n"
"                                                                 \n"
"                                                                 \n"
"void main(void)                                                   \n"
"{                                                                 \n"
"    vec3 normal = normalize(in_Normal);                                                                        \n"
"    vec4 transformedNormal =  normalize(transpose(inverse(modelMatrixBox)) * vec4( normal, 1.0 ));             \n"
"    vec4 surfacePostion = modelMatrixBox * vec4(in_Position, 1.0);                             \n"
"                                                                                                               \n"
"    vec4 surface_to_light =   normalize( light_position -  surfacePostion );                         \n"
"                                                                                                               \n"
"    // Diffuse color                                                                                           \n"
"    float diffuse_coefficient = max( dot(transformedNormal, surface_to_light), 0.0);                           \n"
"    vec3 out_diffuse_color = diffuse_color  * diffuse_coefficient * diffuse_intensity;                         \n"
"                                                                                                               \n"
"    // Ambient color                                                                                           \n"
"    vec3 out_ambient_color = vec3(ambient_color) * ambient_intensity;                                          \n"
"                                                                                                               \n"
"    // Specular color                                                                                          \n"
"    vec3 incidenceVector = -surface_to_light.xyz;                                                              \n"
"    vec3 reflectionVector = reflect(incidenceVector, normal);                                   \n"
"    vec3 cameraPosition = vec3( inverseViewMatrix[3][0], inverseViewMatrix[3][1], inverseViewMatrix[3][2]);             \n"
"    vec3 surfaceToCamera = normalize(cameraPosition - surfacePostion.xyz);                                     \n"
"    float cosAngle = max( dot(surfaceToCamera, reflectionVector), 0.0);                                        \n"
"    float specular_coefficient = pow(cosAngle, shininess);                                                     \n"
"    vec3 out_specular_color = specular_color * specular_coefficient * specular_intensity;                      \n"
"                                                                                                               \n"
"    gl_Position = projectionMatrixBox * viewMatrixBox * modelMatrixBox * vec4(in_Position, 1.0);               \n"
"                                                                                                               \n"
"    pass_Color = vec3(out_diffuse_color + out_ambient_color + out_specular_color);                             \n"
"}                                                                                                              \n";



static const string vs_string_GLSphere_300 =
"#version 310 core                                                 \n"
"                                                                   \n"
"uniform mat4 projectionMatrixBox;                                    \n"
"uniform mat4 viewMatrixBox;                                           \n"
"uniform mat4 modelMatrixBox;                                          \n"
"uniform mat4 inverseViewMatrix;                                        \n"
"uniform vec3 diffuse_color;                                          \n"
"uniform vec3 ambient_color;                                          \n"
"uniform vec3 specular_color;                                          \n"
"uniform vec4 light_position;                                          \n"
"uniform float diffuse_intensity;                                          \n"
"uniform float ambient_intensity;                                          \n"
"uniform float specular_intensity;                                          \n"
"uniform float shininess;                                          \n"
"in vec3 in_Position;                                               \n"
"in vec3 in_Normal;                                                  \n"
"in vec3 in_Color;                                                  \n"
"                                                                  \n"
"                                                                 \n"
"                                                                 \n"
"void main(void)                                                   \n"
"{                                                                 \n"
"    vec3 normal = normalize(in_Normal);                                                                        \n"
"    vec4 transformedNormal =  normalize(transpose(inverse(modelMatrixBox)) * vec4( normal, 1.0 ));             \n"
"    vec4 surfacePostion = viewMatrixBox * modelMatrixBox * vec4(in_Position, 1.0);                             \n"
"                                                                                                               \n"
"    vec4 surface_to_light =   normalize( light_position -  surfacePostion );                         \n"
"                                                                                                               \n"
"    // Diffuse color                                                                                           \n"
"    float diffuse_coefficient = max( dot(transformedNormal, surface_to_light), 0.0);                           \n"
"    vec3 out_diffuse_color = diffuse_color  * diffuse_coefficient * diffuse_intensity;                         \n"
"                                                                                                               \n"
"    // Ambient color                                                                                           \n"
"    vec3 out_ambient_color = vec3(ambient_color) * ambient_intensity;                                          \n"
"                                                                                                               \n"
"    // Specular color                                                                                          \n"
"    vec3 incidenceVector = -surface_to_light.xyz;                                                              \n"
"    vec3 reflectionVector = reflect(incidenceVector, normal);                                   \n"
"    vec3 cameraPosition = vec3( inverseViewMatrix[3][0], inverseViewMatrix[3][1], inverseViewMatrix[3][2]);             \n"
"    vec3 surfaceToCamera = normalize(cameraPosition - surfacePostion.xyz);                                     \n"
"    float cosAngle = max( dot(surfaceToCamera, reflectionVector), 0.0);                                        \n"
"    float specular_coefficient = pow(cosAngle, shininess);                                                     \n"
"    vec3 out_specular_color = specular_color * specular_coefficient * specular_intensity;                      \n"
"                                                                                                               \n"
"    gl_Position = projectionMatrixBox * viewMatrixBox * modelMatrixBox * vec4(in_Position, 1.0);               \n"
"                                                                                                               \n"
"    gl_FrontColor = vec3(out_diffuse_color + out_ambient_color + out_specular_color);                          \n"
"}                                                                                                              \n";




// Fragment shader source code. This determines the colors in the fragment generated in the shader pipeline. In this case, it colors the inside of our triangle specified by our vertex shader.
static const string fs_string_GLSphere_410  =
"#version 410 core                                                 \n"
"                                                                  \n"
"in vec3 pass_Color;                                                 \n"
"out vec4 color;                                                    \n"
"void main(void)                                                   \n"
"{                                                                 \n"
"    color = vec4(pass_Color, 1.0);                               \n"
"}                                                                 \n";


static const string fs_string_GLSphere_300  =
"#version 310 core                                                 \n"
"                                                                  \n"
"                                                                   \n"
"                                                                   \n"
"void main(void)                                                   \n"
"{                                                                 \n"
"    gl_FragColor = vec4(pass_Color, 1.0);                               \n"
"}                                                                 \n";










GLBeerPint::GLBeerPint(float center_x, float center_y, float center_z, float radius, float length, int rows, int segments )
{
    
    _center.x() = center_x;
    _center.y() = center_y;
    _center.z() = center_z;
    
    _radius = radius;
    _length = length;
    _rows = rows;
    _segments = segments;
    
    _render_normal_vectors = false;
    _program_normals = -1;
    _program = -1;
    
    initShader();
    initVBO();
    
    initShaderNormal();
    initVBONormals();
}


GLBeerPint::~GLBeerPint()
{
    // Program clean up when the window gets closed.
    glDeleteVertexArrays(1, _vaoID);
    glDeleteVertexArrays(1, _vaoIDNormals);
    glDeleteProgram(_program);
    glDeleteProgram(_program_normals);
}

void GLBeerPint::draw(void)
{
    
    //////////////////////////////////////////////////
    // Renders the sphere
    
    // Enable the shader program
    glUseProgram(_program);
    
    // this changes the camera location
    glm::mat4 rotated_view =  rotatedViewMatrix();
    glUniformMatrix4fv(_viewMatrixLocation, 1, GL_FALSE, &rotated_view[0][0]); // send the view matrix to our shader
    glUniformMatrix4fv(_inverseViewMatrixLocation, 1, GL_FALSE, &invRotatedViewMatrix()[0][0]);
    glUniformMatrix4fv(_modelMatrixLocation, 1, GL_FALSE, &_modelMatrix[0][0]); //
    
    // Bind the buffer and switch it to an active buffer
    glBindVertexArray(_vaoID[0]);
    
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE ); // allows to see the primitives
    // Draw the triangles
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 42);
    //Top of can
    glDrawArrays(GL_TRIANGLE_FAN, 43, _num_vertices);

    //////////////////////////////////////////////////
    // Renders the normal vectors
    
    if(_render_normal_vectors)
    {
        
        // Enable the shader program
        glUseProgram(_program_normals);
        
        glUniformMatrix4fv(_viewMatrixLocationN, 1, GL_FALSE, &rotated_view[0][0]); // send the view matrix to our shader
        glUniformMatrix4fv(_modelMatrixLocationN, 1, GL_FALSE, &_modelMatrix[0][0]); //
        
        
        // Bind the buffer and switch it to an active buffer
        glBindVertexArray(_vaoIDNormals[0]);
        glDrawArrays(GL_LINES, 0, _num_vertices_normals);
    }
    
    // Unbind our Vertex Array Object
    glBindVertexArray(0);
    
    // Unbind the shader program
    glUseProgram(0);
    
    
}

/*!
 Set the model matrix for this object
 @param modelmatrix: 4x4 model matrix
 */
void GLBeerPint::setModelMatrix(glm::mat4& modelmatrix)
{
    _modelMatrix=modelmatrix;
    
}


/*!
 Enables or disables the normal vector renderer
 @param value = true -> enables the renderer, false -> disables the renderer
 */
void GLBeerPint::enableNormalVectorRenderer(bool value )
{
    _render_normal_vectors = value;
}


/*!
 Create the vertex buffer object for this element
 */
void GLBeerPint::initVBO(void)
{
    
    
    _spherePoints.clear();
    _normalVectors.clear();
    
    make_BeerCan(_center, _radius, _length, _spherePoints, _normalVectors);
    
    _num_vertices = _spherePoints.size();
    
    
    // create memory for the vertices, etc.
    float* vertices = new float[_spherePoints.size() * 5];
    float* normals = new float[_spherePoints.size() * 3];
    
    
    // copy the data to the vectors
    for(int i=0; i<_spherePoints.size() ; i++)
    {
        Vertex v = _spherePoints[i];
        vertices[(i*5)] = v.x(); vertices[(i*5)+1] = v.y(); vertices[(i*5)+2] = v.z();
        vertices[(i*5)+3] = v.u(); vertices[(i*5)+4] = v.v();
        
        Vertex n = _normalVectors[i];
        normals[(i*3)] = n.x(); normals[(i*3)+1] = n.y(); normals[(i*3)+2] = n.z();
        
    }
    
    glUseProgram(_program);
    
    
    glGenVertexArrays(1, _vaoID); // Create our Vertex Array Object
    glBindVertexArray(_vaoID[0]); // Bind our Vertex Array Object so we can use it
    
    
    glGenBuffers(3, _vboID); // Generate our Vertex Buffer Object
    
    // vertices
    glBindBuffer(GL_ARRAY_BUFFER, _vboID[0]); // Bind our Vertex Buffer Object
    glBufferData(GL_ARRAY_BUFFER, _num_vertices * 5 * sizeof(GLfloat), vertices, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
    
    int locPos = glGetAttribLocation(_program, "in_Position");
    glVertexAttribPointer((GLuint)locPos, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0); // Set up our vertex attributes pointer
    glEnableVertexAttribArray(locPos); //
    
    int tex_idx = glGetAttribLocation(_program, "in_TexCoord");
    glVertexAttribPointer((GLuint)tex_idx, 2, GL_FLOAT, GL_TRUE, 5*sizeof(GLfloat),(const GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(tex_idx);
    
    //Normals
    glBindBuffer(GL_ARRAY_BUFFER, _vboID[1]); // Bind our second Vertex Buffer Object
    glBufferData(GL_ARRAY_BUFFER, _num_vertices * 3 *  sizeof(GLfloat), normals, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
    
    int locNorm = glGetAttribLocation(_program, "in_Normal");
    glVertexAttribPointer((GLuint)locNorm, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
    glEnableVertexAttribArray(locNorm); //
    
    glBindVertexArray(0); // Disable our Vertex Buffer Object
    
    // delete the memory
    delete vertices;
    delete normals;
}


/*!
 Init a frame buffer object to draw normal vectors
 */
void GLBeerPint::initVBONormals(void)
{
    
    // create the normal vector lines
    vector<Vertex> normalVectorLines;
    for(int i=0; i<_spherePoints.size() ; i++)
    {
        Vertex v = _spherePoints[i];
        Vertex n = _normalVectors[i];
        
        normalVectorLines.push_back(v);
        normalVectorLines.push_back(v+n);
        
    }
    
    float *normal_lines = new float[normalVectorLines.size() * 3];
    float *colors = new float[normalVectorLines.size() * 3];
    
    for(int i=0; i<normalVectorLines.size() ; i++)
    {
        normal_lines[(i*3)] = normalVectorLines[i].x();
        normal_lines[(i*3)+1] = normalVectorLines[i].y();
        normal_lines[(i*3)+2] = normalVectorLines[i].z();
        
        colors[(i*3)] = 0.0; colors[(i*3)+1] = 0.0; colors[(i*3)+2] = 1.0;
    }
    
    _num_vertices_normals = normalVectorLines.size();
    
    glUseProgram(_program_normals);
    
    glGenVertexArrays(1, _vaoIDNormals); // Create our Vertex Array Object
    glBindVertexArray(_vaoIDNormals[0]); // Bind our Vertex Array Object so we can use it
    
    
    glGenBuffers(2, _vboIDNormals); // Generate our Vertex Buffer Object
    
    // vertices
    glBindBuffer(GL_ARRAY_BUFFER, _vboIDNormals[0]); // Bind our Vertex Buffer Object
    glBufferData(GL_ARRAY_BUFFER, normalVectorLines.size() * 3 * sizeof(GLfloat), normal_lines, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
    
    glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
    glEnableVertexAttribArray(0); //
    
    
    //Color
    glBindBuffer(GL_ARRAY_BUFFER, _vboIDNormals[1]); // Bind our second Vertex Buffer Object
    glBufferData(GL_ARRAY_BUFFER, normalVectorLines.size() * 3 *  sizeof(GLfloat), colors, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
    
    glVertexAttribPointer((GLuint)glGetAttribLocation(_program, "in_Color"), 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
    glEnableVertexAttribArray(glGetAttribLocation(_program, "in_Color")); //
    
    glBindVertexArray(0); // Disable our Vertex Buffer Object
    
    delete normal_lines;
    delete colors;
}

/*!
 Shader for the normal vector renderer
 */
void GLBeerPint::initShaderNormal(void)
{
    _program_normals = CreateShaderProgram(vs_string_simple_shader_410, fs_string_simple_shader_410);
    
    glUseProgram(_program_normals);
    
    unsigned int projectionMatrixLocation = glGetUniformLocation(_program_normals, "projectionMatrix"); // Get the location of our projection matrix in the shader
    _viewMatrixLocationN = glGetUniformLocation(_program_normals, "viewMatrix"); // Get the location of our view matrix in the shader
    _modelMatrixLocationN = glGetUniformLocation(_program_normals, "modelMatrix"); // Get the location of our model matrix in the shader
    
    
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix()[0][0] ); // Send our projection matrix to the shader
    glUniformMatrix4fv(_viewMatrixLocationN, 1, GL_FALSE, &viewMatrix()[0][0]); // Send our view matrix to the shader
    glUniformMatrix4fv(_modelMatrixLocationN, 1, GL_FALSE, &_modelMatrix[0][0]); // Send our model matrix to the shader
    
    
    glBindAttribLocation(_program_normals, 0, "in_Position");
    glBindAttribLocation(_program_normals, 1, "in_Color");
    
    glUseProgram(0);
}




void GLBeerPint::make_BeerCan(Vertex center, double r, double l, std::vector<Vertex> &spherePoints, std::vector<Vertex> &normals)
{
    const double PI = 3.141592653589793238462643383279502884197;
    spherePoints.clear();
    
    int current_size = 0;
    int count = 0;
    current_size = spherePoints.size();

    //Perimeter of the can
    // Iterate through phi, theta then convert r,theta,phi to  XYZ
    for (double phi = 0.; phi < 2*PI + PI/float(_segments) ; phi += PI/float(_segments)) // Azimuth [0, 2PI]
    {
        
        // Bottom of the can
        Vertex point;
        point.x() = r * cos(phi) + center.x();
        point.y() = r * sin(phi) + center.y();
        point.z() = center.z();
        point.u() = sin(phi);
        point.v() = 0;
        spherePoints.push_back(point); count++;
        std::cout<<point.u()<<std::endl;
        // Top of the can
        Vertex point2;
        point2.x() = 2 * r * cos(phi) + center.x();
        point2.y() = 2 * r * sin(phi) + center.y();
        point2.z() = center.z()+l;
        point.u() = sin(phi);
        point.v() = 1;
        spherePoints.push_back(point2); count++;
        
        Vertex normal;
        normal.x() =  cos(phi);
        normal.y() =  sin(phi);
        normal.z() =  -1;
        normals.push_back(normal);
        
        Vertex normal2;
        normal2.x() =  cos(phi);
        normal2.y() =  sin(phi);
        normal2.z() =  -1;
        normals.push_back(normal2);
        
    }
    
    //Top of can
    Vertex point;
    point.x() = center.x();
    point.y() = center.y();
    point.z() = center.z()+l;
    spherePoints.push_back(point);
    for (double phi = 0.; phi < 2*PI + PI/float(_segments) ; phi += PI/float(_segments)) // Azimuth [0, 2PI]
    {
        Vertex point;
        point.x() = 2 * r * cos(phi) + center.x();
        point.y() = 2 * r * sin(phi) + center.y();
        point.z() = center.z()+l;
        spherePoints.push_back(point);
        
        Vertex normal;
        normal.x() =  sin(phi);
        normal.y() =  cos(phi);
        normal.z() =  1;
        normals.push_back(normal);

    }
    std::cout<<"i"<<spherePoints.size()<<"\n"<<std::endl;


    return;
}

void GLBeerPint::init(void)
{
    initShader();
    initVBO();
    
    initShaderNormal();
    initVBONormals();
}

void GLBeerPint::initShader(void)
{
    if(!_apperance.exists())return;
    
    // This loads the shader program from a file
    _program = _apperance.getProgram();
    
    
    glUseProgram(_program);
    
    
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Vertex information / names
    
    glBindAttribLocation(_program, 0, "in_Position");
    glBindAttribLocation(_program, 1, "in_Normal");
    glBindAttribLocation(_program, 2, "in_TextCoord");
    
    
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Define the model view matrix.
    _modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)); // Create our model matrix which will halve the size of our model
    addModelViewMatrixToProgram(_program);
    

    glUseProgram(0);
}































