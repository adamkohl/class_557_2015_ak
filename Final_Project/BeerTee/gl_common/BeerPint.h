//  Adam Kohl, Fei X, and Jiazhong Z.
//  main.cpp
//  HCI 557 Final Project
//

#pragma once


// stl include
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// GLEW include
#include <GL/glew.h>

// GLM include files
#define GLM_FORCE_INLINE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


// locals
#include "GLObject.h"
#include "GLSphere.h"
#include "Shaders.h"

#include "HCI557Datatypes.h"





class GLBeerPint : public GLObject
{
public:

    GLBeerPint(float center_x, float center_y, float center_z, float radius, float length, int rows = 10, int segments = 10 );
    
    GLBeerPint(){};
    
    ~GLBeerPint();
    
    void init(void);
    
    void initShader(void);
    
    virtual  void draw(void);
    
    /*!
     Set the model matrix for this object
     @param modelmatrix: 4x4 model matrix
     */
    void setModelMatrix(glm::mat4& modelmatrix);
    
    /*!
     Retursn the model matrix.
     */
    inline glm::mat4& getModelMatrix(void){return _modelMatrix;};
    
    /*!
     Enables or disables the normal vector renderer
     @param value = true -> enables the renderer, false -> disables the renderer
     */
    void enableNormalVectorRenderer(bool value = true);
    
protected:
    
    virtual void initVBO(void);
    
    void initVBONormals(void);
    
    void initShaderNormal(void);
    
    void make_BeerCan(Vertex center, double r, double l, std::vector<Vertex> &spherePoints, std::vector<Vertex> &normals);
    
    // the program
    GLuint                  _program;
    
    
    
    unsigned int            _vaoID[1]; // Our Vertex Array Object
    unsigned int            _vboID[3]; // Our Vertex Buffer Object
    
    
    // The light source
    GLLightSource           _light_source0;
    
    
    // The program and data to render normal vectors as lines
    GLuint                  _program_normals;
    unsigned int            _viewMatrixLocationN;
    unsigned int            _modelMatrixLocationN;
    unsigned int            _vaoIDNormals[1];
    unsigned int            _vboIDNormals[2]; // Our Vertex Buffer Object for normal vectors
    
    
    // the dimensions of the sphere
    int                     _segments;
    int                     _rows;
    
    int                     _num_vertices;
    int                     _num_vertices_normals;
    
    Vertex                  _center;
    float                   _radius;
    float                   _length;
    
    // variables to generate the sphere
    vector<Vertex>          _spherePoints;
    vector<Vertex>          _normalVectors;
    
    
    // value to switch the normal renderer on / off
    bool                    _render_normal_vectors;
};














