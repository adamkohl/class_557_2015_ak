//  Adam Kohl, Fei X, and Jiazhong Z.
//  main.cpp
//  HCI 557 Final Project
//
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
#include <glm/gtx/transform.hpp>

// glfw includes
#include <GLFW/glfw3.h>


// include local files
#include "controls.h"
#include "HCI557Common.h"
#include "CoordSystem.h"
#include "GLObjectObjFl.h"
#include "BeerPint.h"
#include "Plane3D.h" 
#include "Table.h"

using namespace std;


// The handle to the window object
GLFWwindow*         window;

// Define some of the global variables we're using for this sample
GLuint program;

float  target1[3];
float  origin[3];
float  time0;
// this flag is initialized as 0; once we update the tee(after each move animation);
// set it to 1, so that the update only happens onces.
int update_flag= 0;
// this flag will only allow the delete after you hit the keboard
int delete_act = 0;

/* A trackball to move and rotate the camera view */
extern Trackball trackball;

void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if((key == GLFW_KEY_F5 && action == GLFW_PRESS) ) // key w
    {
        target1[0] =10.0;
        target1[1] =17.33;
        target1[2] =0.0;
        time0 = glfwGetTime();
        update_flag=0;
        delete_act = 1;
    }
    if((key == GLFW_KEY_5 && action == GLFW_PRESS) ) // key Q
    {
        target1[0] =7.5;
        target1[1] =13;
        target1[2] =0.0;
        time0 = glfwGetTime();
        update_flag=0;
        delete_act = 1;
    }
    if((key == GLFW_KEY_6 && action == GLFW_PRESS) ) // key w
    {
        target1[0] =12.5;
        target1[1] =13;
        target1[2] =0.0;
        time0 = glfwGetTime();
        update_flag=0;
        delete_act = 1;
    }
    if((key == GLFW_KEY_R && action == GLFW_PRESS) ) // key Q
    {
        target1[0] =5.0;
        target1[1] =8.66;
        target1[2] =0.0;
        time0 = glfwGetTime();
        update_flag=0;
        delete_act = 1;
    }
    if((key == GLFW_KEY_T && action == GLFW_PRESS) ) // key w
    {
        target1[0] =10.0;
        target1[1] =8.66;
        target1[2] =0.0;
        time0 = glfwGetTime();
        update_flag=0;
        delete_act = 1;
    }
    if((key == GLFW_KEY_Y && action == GLFW_PRESS) ) // key Q
    {
        target1[0] =15.0;
        target1[1] =8.66;
        target1[2] =0.0;
        time0 = glfwGetTime();
        update_flag=0;
        delete_act = 1;
    }
    if((key == GLFW_KEY_D && action == GLFW_PRESS) ) // key w
    {
        target1[0] =2.5;
        target1[1] =4.33;
        target1[2] =0.0;
        time0 = glfwGetTime();
        update_flag=0;
        delete_act = 1;
    }
    if((key == GLFW_KEY_F && action == GLFW_PRESS) ) // key Q
    {
        target1[0] =7.5;
        target1[1] =4.33;
        target1[2] =0.0;
        time0 = glfwGetTime();
        update_flag=0;
        delete_act = 1;
    }
    if((key == GLFW_KEY_G && action == GLFW_PRESS) ) // key w
    {
        target1[0] =12.5;
        target1[1] =4.33;
        target1[2] =0.0;
        time0 = glfwGetTime();
        update_flag=0;
        delete_act = 1;
    }
    if((key == GLFW_KEY_H && action == GLFW_PRESS) ) // key Q
    {
        target1[0] =17.5;
        target1[1] =4.33;
        target1[2] =0.0;
        time0 = glfwGetTime();
        update_flag=0;
        delete_act = 1;
    }
    if((key == GLFW_KEY_X && action == GLFW_PRESS) ) // key w
    {
        target1[0] =0.0;
        target1[1] =0.0;
        target1[2] =0.0;
        time0 = glfwGetTime();
        update_flag=0;
        delete_act = 1;
    }
    if((key == GLFW_KEY_C && action == GLFW_PRESS) ) // key Q
    {
        target1[0] =5.0;
        target1[1] =0.0;
        target1[2] =0.0;
        time0 = glfwGetTime();
        update_flag=0;
        delete_act = 1;
    }
    if((key == GLFW_KEY_V && action == GLFW_PRESS) ) // key w
    {
        target1[0] =10.0;
        target1[1] =0.0;
        target1[2] =0.0;
        time0 = glfwGetTime();
        update_flag=0;
        delete_act = 1;
    }
    if((key == GLFW_KEY_B && action == GLFW_PRESS) ) // key Q
    {
        target1[0] =15.0;
        target1[1] =0.0;
        target1[2] =0.0;
        time0 = glfwGetTime();
        update_flag=0;
        delete_act = 1;
    }
    if((key == GLFW_KEY_N && action == GLFW_PRESS) ) // key Q
    {
        target1[0] =20.0;
        target1[1] =0.0;
        target1[2] =0.0;
        time0 = glfwGetTime();
        update_flag=0;
        delete_act = 1;
    }
    
}

GLfloat* vector_diff = 0;
GLfloat* vector_result = 0;

/*!
 @brief returns the time fraction for a given time and animation duration
 @param time - the current animation time, application runtime, etc. in seconds
 @param duration - the duration of the animation in seconds
 @return the time fraction in an interval between 0 and 1.
 */
float getTimeFraction(const float time, const float time0, const float duration)
{
    // we calculate the time difference
    float diff = time - time0;
    
    // return the fraction / position in our current timeline, with respect to the duration
    float fraction = diff / duration;
    //
    return fraction;
}



/*!
 This initializes the difference vector for the morphing operation
 */
void init_morphing(GLObjectObjFl* lm1, float xn, float yn,float zn)
{
    // allocate memory for the difference vector.
    vector_diff = (GLfloat*)malloc(sizeof(GLfloat) * 3 * lm1->size());
    
    int size = lm1->size();
    // calculate the difference vector
    for (int i=0; i<size; i++) {
        vector_diff[i*3+0] = xn - lm1->center[0];
        vector_diff[i*3+1] = yn - lm1->center[1];
        vector_diff[i*3+2] = zn - lm1->center[2];
    }
    
}


/*!
 This function processes the morphing operation
 */
void my_morphing_callback(float duration, float time0, GLObjectObjFl* lm1, float xn, float yn,float zn)
{
    // get the current system time
    float time = glfwGetTime();
    
    // calcualte the time fraction
    float fraction = getTimeFraction(time, time0, duration);
    
    // get the number of vertices.
    int size = lm1->size();
    
    // init the vector the first time we call this function.
    if(vector_result == NULL)
    {
        vector_result = (GLfloat*)malloc(sizeof(GLfloat) * 3 * lm1->size());
    }
    float factor1 = 50.0;
    if (vector_diff[0] == 0.0 and vector_diff[1] == 0.0)
    {
        factor1 = 0.0;
    }
    
    float dx = xn-lm1->center[0];
    float dy = yn-lm1->center[1];
    float dz = zn-lm1->center[2];
    
    //    if (fraction <= 1.0)
    //    {
    //        cout<< fraction<<endl;
    //    }
    if (fraction >= 1.0 and update_flag==0)
    {
        
        // change the update flag so that we only update once
        update_flag = 1;
        // update the center and vertices, to where it should be
        lm1->updatecenter(dx,dy,dz);
        
        //        lm1->draw();
    }
    
    if (fraction <=1.0 )
    {
        for (int i=0; i<size; i++) {
            vector_result[i*3+0] = lm1->getVertices()[i].x + fraction * vector_diff[i*3+0];
            vector_result[i*3+1] = lm1->getVertices()[i].y + fraction * vector_diff[i*3+1];
            vector_result[i*3+2] = lm1->getVertices()[i].z + fraction * (1.0f-fraction) * factor1;
        }
    }
    else
    {
        for (int i=0; i<size; i++) {
            vector_result[i*3+0] = lm1->getVertices()[i].x;
            vector_result[i*3+1] = lm1->getVertices()[i].y;
            vector_result[i*3+2] = lm1->getVertices()[i].z;
        }
    }
    
    //---------------------------
    // Draw the output
    
    lm1->updateVertices(vector_result);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Scissor Functions
int g_selected_object_id = 101010;
int g_selected_object_id_1 = 101010;

GLObjectObjFl* tee1 = NULL;
GLObjectObjFl* tee2 = NULL;
GLObjectObjFl* tee3 = NULL;
GLObjectObjFl* tee4 = NULL;
GLObjectObjFl* tee5 = NULL;
GLObjectObjFl* tee6 = NULL;
GLObjectObjFl* tee7 = NULL;
GLObjectObjFl* tee8 = NULL;
GLObjectObjFl* tee9 = NULL;
GLObjectObjFl* tee10 = NULL;
GLObjectObjFl* tee11 = NULL;
GLObjectObjFl* tee12 = NULL;
GLObjectObjFl* tee13 = NULL;
GLObjectObjFl* tee14 = NULL;
GLObjectObjFl* pad = NULL;

/**
 This functions converts four integer digits, to an integer value.
 */

int colorToInteger(float r, float g, float b, float a)
{
    int selected_object_id = 101010;
    
    int f_red = r*800000.0+100000.0;
    int f_grn = g*8000.0+1000.0;
    int f_blu = b*80.0+10.0;
    
    selected_object_id =  f_red+f_grn+f_blu;
    return selected_object_id;
}

/*!
 @brief - indicate that this object has been selected.
 @param shader_program - the number of the glsl shader program
 @param value - set is_selected true or false
 */
void setSelectColor(int shader_program,  bool value)
{
    glUseProgram(shader_program);
    int uniform_id = glGetUniformLocation(shader_program, "is_selected");
    
    glUniform1i(uniform_id, value);
    glUseProgram(0);
}


void handle_pick(int selected_object_id)
{

    // first, detect whether a pick event occured.
    // If the same object is picked of the clear color shows up, we return. No state change.
    if(selected_object_id == g_selected_object_id)
    {
        return;
    }
    
    // consider, an object is already picked, disable the pick color.
    // g_selected_object_id == 0, means, no object selected
    if(g_selected_object_id > 101010)
    {
        // Note, this can be optimized/
        // We need a list that keeps an association between model and its id.
        // this can be an additional list or part of the object itself.
        // In this case, and for training reasonse (not hiding the code, this is a switch-case control flow.
        switch(g_selected_object_id)
        {
            case 101017:
                setSelectColor(tee1->getProgram(), false);
                g_selected_object_id = 101010;
                break;
            case 101026:
                setSelectColor(tee2->getProgram(), false);
                g_selected_object_id = 101010;
                break;
            case 101033:
                setSelectColor(tee3->getProgram(), false);
                g_selected_object_id = 101010;
                break;
            case 101042:
                setSelectColor(tee4->getProgram(), false);
                g_selected_object_id = 101010;
                break;
            case 101049:
                setSelectColor(tee5->getProgram(), false);
                g_selected_object_id = 101010;
                break;
            case 101058:
                setSelectColor(tee6->getProgram(), false);
                g_selected_object_id = 101010;
                break;
            case 101065:
                setSelectColor(tee7->getProgram(), false);
                g_selected_object_id = 101010;
                break;
            case 101074:
                setSelectColor(tee8->getProgram(), false);
                g_selected_object_id = 101010;
                break;
            case 101081:
                setSelectColor(tee9->getProgram(), false);
                g_selected_object_id = 101010;
                break;
            case 101794:
                setSelectColor(tee10->getProgram(), false);
                g_selected_object_id = 101010;
                break;
            case 101801:
                setSelectColor(tee11->getProgram(), false);
                g_selected_object_id = 101010;
                break;
            case 101810:
                setSelectColor(tee12->getProgram(), false);
                g_selected_object_id = 101010;
                break;
            case 101817:
                setSelectColor(tee13->getProgram(), false);
                g_selected_object_id = 101010;
                break;
            case 101826:
                setSelectColor(tee14->getProgram(), false);
                g_selected_object_id = 101010;
                break;
                
        }
    }
    
    // only update the select id when you select a different one
    // this is for the morphing to complete normally
    if (selected_object_id != 101010)
    {
        g_selected_object_id_1 = selected_object_id;
    }
    
    // Now we change the color of the selected object
    switch(selected_object_id)
    {
        case 101017:
            setSelectColor(tee1->getProgram(), true);
            g_selected_object_id = selected_object_id;
            break;
        case 101026:
            setSelectColor(tee2->getProgram(), true);
            g_selected_object_id = selected_object_id;
            break;
        case 101033:
            setSelectColor(tee3->getProgram(), true);
            g_selected_object_id = selected_object_id;
            break;
        case 101042:
            setSelectColor(tee4->getProgram(), true);
            g_selected_object_id = selected_object_id;
            break;
        case 101049:
            setSelectColor(tee5->getProgram(), true);
            g_selected_object_id = selected_object_id;
            break;
        case 101058:
            setSelectColor(tee6->getProgram(), true);
            g_selected_object_id = selected_object_id;
            break;
        case 101065:
            setSelectColor(tee7->getProgram(), true);
            g_selected_object_id = selected_object_id;
            break;
        case 101074:
            setSelectColor(tee8->getProgram(), true);
            g_selected_object_id = selected_object_id;
            break;
        case 101081:
            setSelectColor(tee9->getProgram(), true);
            g_selected_object_id = selected_object_id;
            break;
        case 101794:
            setSelectColor(tee10->getProgram(), true);
            g_selected_object_id = selected_object_id;
            break;
        case 101801:
            setSelectColor(tee11->getProgram(), true);
            g_selected_object_id = selected_object_id;
            break;
        case 101810:
            setSelectColor(tee12->getProgram(), true);
            g_selected_object_id = selected_object_id;
            break;
        case 101817:
            setSelectColor(tee13->getProgram(), true);
            g_selected_object_id = selected_object_id;
            break;
        case 101826:
            setSelectColor(tee14->getProgram(), true);
            g_selected_object_id = selected_object_id;
            break;
    }
    
    // get the original location, to determine the one to delete
    // this will not change during the morphing
    switch(g_selected_object_id_1)
    {
        case 101017:
            origin[0] = tee1->center[0];
            origin[1] = tee1->center[1];
            origin[2] = tee1->center[2];
            break;
        case 101026:
            origin[0] = tee2->center[0];
            origin[1] = tee2->center[1];
            origin[2] = tee2->center[2];
            break;
        case 101033:
            origin[0] = tee3->center[0];
            origin[1] = tee3->center[1];
            origin[2] = tee3->center[2];
            break;
        case 101042:
            origin[0] = tee4->center[0];
            origin[1] = tee4->center[1];
            origin[2] = tee4->center[2];
            break;
        case 101049:
            origin[0] = tee5->center[0];
            origin[1] = tee5->center[1];
            origin[2] = tee5->center[2];
            break;
        case 101058:
            origin[0] = tee6->center[0];
            origin[1] = tee6->center[1];
            origin[2] = tee6->center[2];
            break;
        case 101065:
            origin[0] = tee7->center[0];
            origin[1] = tee7->center[1];
            origin[2] = tee7->center[2];
            break;
        case 101074:
            origin[0] = tee8->center[0];
            origin[1] = tee8->center[1];
            origin[2] = tee8->center[2];
            break;
        case 101081:
            origin[0] = tee9->center[0];
            origin[1] = tee9->center[1];
            origin[2] = tee9->center[2];
            break;
        case 101794:
            origin[0] = tee10->center[0];
            origin[1] = tee10->center[1];
            origin[2] = tee10->center[2];
            break;
        case 101801:
            origin[0] = tee11->center[0];
            origin[1] = tee11->center[1];
            origin[2] = tee11->center[2];
            break;
        case 101810:
            origin[0] = tee12->center[0];
            origin[1] = tee12->center[1];
            origin[2] = tee12->center[2];
            break;
        case 101817:
            origin[0] = tee13->center[0];
            origin[1] = tee13->center[1];
            origin[2] = tee13->center[2];
            break;
        case 101826:
            origin[0] = tee14->center[0];
            origin[1] = tee14->center[1];
            origin[2] = tee14->center[2];
            break;
    }
}

int getDeleteID(const float ori[3], const float tar[3], const int D_flag[14])
{
    // we calculate the center
    
    float mid[3];
    
    mid[0] = (ori[0]+tar[0])*0.5;
    mid[1] = (ori[1]+tar[1])*0.5;
    mid[1] = (ori[1]+tar[1])*0.5;
    
    float dis[14];
    
    float dis_ori_tar = sqrt((ori[0]-tar[0])*(ori[0]-tar[0])\
                             +(ori[1]-tar[1])*(ori[1]-tar[1]) \
                             +(ori[2]-tar[2])*(ori[2]-tar[2]));
    
    
    dis[0] = sqrt((tee1->center[0]-mid[0])*(tee1->center[0]-mid[0])+(tee1->center[1]-mid[1])*(tee1->center[1]-mid[1]) \
                  +(tee1->center[2]-mid[2])*(tee1->center[2]-mid[2]));
    dis[1] = sqrt((tee2->center[0]-mid[0])*(tee2->center[0]-mid[0])+(tee2->center[1]-mid[1])*(tee2->center[1]-mid[1]) \
                  +(tee2->center[2]-mid[2])*(tee2->center[2]-mid[2]));
    dis[2] = sqrt((tee3->center[0]-mid[0])*(tee3->center[0]-mid[0])+(tee3->center[1]-mid[1])*(tee3->center[1]-mid[1]) \
                  +(tee3->center[2]-mid[2])*(tee3->center[2]-mid[2]));
    dis[3] = sqrt((tee4->center[0]-mid[0])*(tee4->center[0]-mid[0])+(tee4->center[1]-mid[1])*(tee4->center[1]-mid[1]) \
                  +(tee4->center[2]-mid[2])*(tee4->center[2]-mid[2]));
    dis[4] = sqrt((tee5->center[0]-mid[0])*(tee5->center[0]-mid[0])+(tee5->center[1]-mid[1])*(tee5->center[1]-mid[1]) \
                  +(tee5->center[2]-mid[2])*(tee5->center[2]-mid[2]));
    dis[5] = sqrt((tee6->center[0]-mid[0])*(tee6->center[0]-mid[0])+(tee6->center[1]-mid[1])*(tee6->center[1]-mid[1]) \
                  +(tee6->center[2]-mid[2])*(tee6->center[2]-mid[2]));
    dis[6] = sqrt((tee7->center[0]-mid[0])*(tee7->center[0]-mid[0])+(tee7->center[1]-mid[1])*(tee7->center[1]-mid[1]) \
                  +(tee7->center[2]-mid[2])*(tee7->center[2]-mid[2]));
    dis[7] = sqrt((tee8->center[0]-mid[0])*(tee8->center[0]-mid[0])+(tee8->center[1]-mid[1])*(tee8->center[1]-mid[1]) \
                  +(tee8->center[2]-mid[2])*(tee8->center[2]-mid[2]));
    dis[8] = sqrt((tee9->center[0]-mid[0])*(tee9->center[0]-mid[0])+(tee9->center[1]-mid[1])*(tee9->center[1]-mid[1]) \
                  +(tee9->center[2]-mid[2])*(tee9->center[2]-mid[2]));
    dis[9] = sqrt((tee10->center[0]-mid[0])*(tee10->center[0]-mid[0])+(tee10->center[1]-mid[1])*(tee10->center[1]-mid[1]) \
                  +(tee10->center[2]-mid[2])*(tee10->center[2]-mid[2]));
    dis[10] = sqrt((tee11->center[0]-mid[0])*(tee11->center[0]-mid[0])+(tee11->center[1]-mid[1])*(tee11->center[1]-mid[1]) \
                   +(tee11->center[2]-mid[2])*(tee11->center[2]-mid[2]));
    dis[11] = sqrt((tee12->center[0]-mid[0])*(tee12->center[0]-mid[0])+(tee12->center[1]-mid[1])*(tee12->center[1]-mid[1]) \
                   +(tee12->center[2]-mid[2])*(tee12->center[2]-mid[2]));
    dis[12] = sqrt((tee13->center[0]-mid[0])*(tee13->center[0]-mid[0])+(tee13->center[1]-mid[1])*(tee13->center[1]-mid[1]) \
                   +(tee13->center[2]-mid[2])*(tee13->center[2]-mid[2]));
    dis[13] = sqrt((tee14->center[0]-mid[0])*(tee14->center[0]-mid[0])+(tee14->center[1]-mid[1])*(tee14->center[1]-mid[1]) \
                   +(tee14->center[2]-mid[2])*(tee14->center[2]-mid[2]));
    
    int delete_id;
    
    for (int i=0; i<=13; i++)
    {
        // if it hasn't been deleted..
        if (dis[i] <= 0.1 and D_flag[i] == 0 and dis_ori_tar > 1.0 and delete_act == 1)
        {
            delete_id = i + 1;
            //            cout<< dis[i] << 'hehe' << endl;
        }
    }
    
    return delete_id;
    
}

int main(int argc, const char * argv[])
{
    int delete_flag[14];
    for (int i = 0; i<=13; i++)
    {
        delete_flag[i] = 0;
    }
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Init glfw, create a window, and init glew
    
    // Init the GLFW Window
    window = initWindow();
    
    // Init the glew api
    initGlew();
    SetCameraManipulator(CameraTypes::CAMERA_MANIPULATOR);
    // this is for the initialization of target, we initialize it to the location of
    // first bject we pick, so there will not be strange animation path
    int init_tar = 0;
    
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Create materials, light and load models
    
    // coordinate system
    CoordSystem* cs = new CoordSystem(600.0);

    // Tee 1.
    GLAppearance* apperance_0 = new GLAppearance("../../data/shaders/tee_shader.vs", "../../data/shaders/tee_shader.fs");
    GLDirectLightSource  light_source;
    light_source._lightPos = glm::vec4(10.0, 10.0, 30.0, 0.0);
    light_source._ambient_intensity = 0.05;
    light_source._specular_intensity = 0.5;
    light_source._diffuse_intensity = 2.0;
    light_source._attenuation_coeff = 0.0;
    apperance_0->addLightSource(light_source);
    
    // Create a material object
    GLMaterial material_0;
    material_0._diffuse_material = glm::vec3(0.5, 0.0, 0.0);
    material_0._ambient_material = glm::vec3(0.5, 0.0, 0.0);
    material_0._specular_material = glm::vec3(0.0, 0.0, 0.0);
    material_0._shininess = 1.0;
    material_0._transparency = 1.0;
    apperance_0->setMaterial(material_0);
    apperance_0->finalize();
    
    // Tee 2
    GLAppearance* apperance_1 = new GLAppearance("../../data/shaders/tee_shader.vs", "../../data/shaders/tee_shader.fs");
    apperance_1->addLightSource(light_source);
    apperance_1->setMaterial(material_0);
    apperance_1->finalize();
    
    // Tee 3
    GLAppearance* apperance_2 = new GLAppearance("../../data/shaders/tee_shader.vs", "../../data/shaders/tee_shader.fs");
    apperance_2->addLightSource(light_source);
    apperance_2->setMaterial(material_0);
    apperance_2->finalize();
    
    // Tee 4
    GLAppearance* apperance_3 = new GLAppearance("../../data/shaders/tee_shader.vs", "../../data/shaders/tee_shader.fs");
    apperance_3->addLightSource(light_source);
    apperance_3->setMaterial(material_0);
    apperance_3->finalize();
    
    // Tee 5
    GLAppearance* apperance_4 = new GLAppearance("../../data/shaders/tee_shader.vs", "../../data/shaders/tee_shader.fs");
    apperance_4->addLightSource(light_source);
    apperance_4->setMaterial(material_0);
    apperance_4->finalize();
    
    // Tee 6
    GLAppearance* apperance_5 = new GLAppearance("../../data/shaders/tee_shader.vs", "../../data/shaders/tee_shader.fs");
    apperance_5->addLightSource(light_source);
    apperance_5->setMaterial(material_0);
    apperance_5->finalize();
    
    // Tee 7
    GLAppearance* apperance_6 = new GLAppearance("../../data/shaders/tee_shader.vs", "../../data/shaders/tee_shader.fs");
    apperance_6->addLightSource(light_source);
    apperance_6->setMaterial(material_0);
    apperance_6->finalize();
    
    // Tee 8
    GLAppearance* apperance_7 = new GLAppearance("../../data/shaders/tee_shader.vs", "../../data/shaders/tee_shader.fs");
    apperance_7->addLightSource(light_source);
    apperance_7->setMaterial(material_0);
    apperance_7->finalize();
    
    // Tee 9
    GLAppearance* apperance_8 = new GLAppearance("../../data/shaders/tee_shader.vs", "../../data/shaders/tee_shader.fs");
    apperance_8->addLightSource(light_source);
    apperance_8->setMaterial(material_0);
    apperance_8->finalize();
    
    // Tee 10
    GLAppearance* apperance_9 = new GLAppearance("../../data/shaders/tee_shader.vs", "../../data/shaders/tee_shader.fs");
    apperance_9->addLightSource(light_source);
    apperance_9->setMaterial(material_0);
    apperance_9->finalize();
    
    // Tee 11
    GLAppearance* apperance_10 = new GLAppearance("../../data/shaders/tee_shader.vs", "../../data/shaders/tee_shader.fs");
    apperance_10->addLightSource(light_source);
    apperance_10->setMaterial(material_0);
    apperance_10->finalize();
    
    // Tee 12
    GLAppearance* apperance_11 = new GLAppearance("../../data/shaders/tee_shader.vs", "../../data/shaders/tee_shader.fs");
    apperance_11->addLightSource(light_source);
    apperance_11->setMaterial(material_0);
    apperance_11->finalize();
    
    // Tee 13
    GLAppearance* apperance_12 = new GLAppearance("../../data/shaders/tee_shader.vs", "../../data/shaders/tee_shader.fs");
    apperance_12->addLightSource(light_source);
    apperance_12->setMaterial(material_0);
    apperance_12->finalize();
    
    // Tee 14
    GLAppearance* apperance_13 = new GLAppearance("../../data/shaders/tee_shader.vs", "../../data/shaders/tee_shader.fs");
    apperance_13->addLightSource(light_source);
    apperance_13->setMaterial(material_0);
    apperance_13->finalize();
    
    // Traingle Pad
    GLAppearance* apperance_15 = new GLAppearance("../../data/shaders/tee_shader.vs", "../../data/shaders/tee_shader.fs");
    apperance_15->addLightSource(light_source);
    GLMaterial material_15 = material_0;
    material_15._diffuse_material = glm::vec3(1.0, 1.0, 1.0);
    material_15._ambient_material = glm::vec3(1.0, 1.0, 1.0);
    apperance_15->setMaterial(material_15);
    apperance_15->finalize();
    
    // Beer Can
    GLAppearance* apperance_16 = new GLAppearance("../../data/shaders/beer_shader.vs", "../../data/shaders/beer_shader.fs");
    
    GLDirectLightSource  light_source1;
    light_source1._lightPos = glm::vec4(17.0,10.0,22.50, 0.0);
    light_source1._ambient_intensity = 0.2;
    light_source1._specular_intensity = 1.2;
    light_source1._diffuse_intensity = 5.0;
    light_source1._attenuation_coeff = 0.0;
    apperance_16->addLightSource(light_source1);
    
    GLSpotLightSource spotlight_source;
    spotlight_source._lightPos = glm::vec4(17.0,10.0,20.0, 1.0);
    spotlight_source._ambient_intensity = 0.0;
    spotlight_source._specular_intensity = 1.8;
    spotlight_source._diffuse_intensity = 2.0;
    spotlight_source._attenuation_coeff = 0.0002;
    spotlight_source._cone_direction = glm::vec3(0.0, 1.0,0.0);
    spotlight_source._cone_angle = 10.0;
    apperance_16->addLightSource(spotlight_source);

    GLMaterial material_16;
    material_16._diffuse_material = glm::vec3(0.5, 0.5, 0.5);
    material_16._specular_material = glm::vec3(0.0, 0.0, 0.0);
    material_16._shininess = 2.0;
    material_16._transparency = 1.0;
    apperance_16->setMaterial(material_16);
 
    GLTexture* texture = new GLTexture();
    texture->loadAndCreateTexture("../../data/textures/beer-bubbles.bmp");
    apperance_16->setTexture(texture);
    apperance_16->finalize();
    
    // Table
//    GLAppearance* apperance_17 = new GLAppearance("../../data/shaders/directlight.vs", "../../data/shaders/directlight.fs");
//    apperance_17->addLightSource(light_source);
//
//    GLMaterial material_17;
//    material_17._diffuse_material = glm::vec3(0.5, 0.0, 1.0);
//    material_17._ambient_material = glm::vec3(0.5, 0.0, 1.0);
//    material_17._specular_material = glm::vec3(0.0, 0.0, 0.0);
//    material_17._shininess = 1.0;
//    material_17._transparency = 1.0;
//    apperance_17->setMaterial(material_17);
//    apperance_17->finalize();
    
    GLAppearance* apperance_17 = new GLAppearance("../../data/shaders/table_shader.vs", "../../data/shaders/table_shader.fs");
    
    GLDirectLightSource  light_source2;
    light_source2._lightPos = glm::vec4(00.0,5.0,20.0, 0.0);
    light_source2._ambient_intensity = 0.2;
    light_source2._specular_intensity = 7.5;
    light_source2._diffuse_intensity = 1.0;
    light_source2._attenuation_coeff = 0.0;
    
    // add the light to this apperance object
    apperance_17->addLightSource(light_source);
    
    
    GLSpotLightSource spotlight_source2;
    spotlight_source2._lightPos = glm::vec4(0.0,20.0,20.0, 1.0);
    spotlight_source2._ambient_intensity = 0.2;
    spotlight_source2._specular_intensity = 1.0;
    spotlight_source2._diffuse_intensity = 8.0;
    spotlight_source2._attenuation_coeff = 0.0002;
    spotlight_source2._cone_direction = glm::vec3(-1.0, -1.0,-1.0);
    spotlight_source2._cone_angle = 20.0;
    
    apperance_2->addLightSource(spotlight_source);
    
    // Create a material object
    GLMaterial material_2;
    material_2._diffuse_material = glm::vec3(0.8, 0.8, 0.8);
    material_2._ambient_material = glm::vec3(0.8, 0.8, 0.8);
    material_2._specular_material = glm::vec3(1.0, 1.0, 1.0);
    material_2._shininess = 12.0;
    material_2._transparency = 1.0;
    
    // Add the material to the apperance object
    apperance_17->setMaterial(material_2);
    
    
    //************************************************************************************************
    // Add a texture
    GLMultiTexture* texture17 = new GLMultiTexture();
    int texid = texture17->loadAndCreateTextures("../../data/textures/water-texture.bmp", "../../data/maps/water_NRM.bmp");
    apperance_17->setTexture(texture);
    apperance_17->finalize();
    
    // If you want to change appearance parameters after you init the object, call the update function
    apperance_0->updateLightSources();
    apperance_1->updateLightSources();
    apperance_2->updateLightSources();
    apperance_3->updateLightSources();
    apperance_4->updateLightSources();
    apperance_5->updateLightSources();
    apperance_6->updateLightSources();
    apperance_7->updateLightSources();
    apperance_8->updateLightSources();
    apperance_9->updateLightSources();
    apperance_10->updateLightSources();
    apperance_11->updateLightSources();
    apperance_12->updateLightSources();
    apperance_13->updateLightSources();
    apperance_15->updateLightSources();
    apperance_16->updateLightSources();

    tee1 = new GLObjectObjFl("../../data/Tee.obj", 0.0, 0.0, 0.0);
    tee1->setApperance(*apperance_0);
    tee1->init();
    
    tee2 = new GLObjectObjFl("../../data/Tee.obj", 5.0, 0.0, 0.0);
    tee2->setApperance(*apperance_1);
    tee2->init();
    
    tee3 = new GLObjectObjFl("../../data/Tee.obj", 10.0, 0.0, 0.0);
    tee3->setApperance(*apperance_2);
    tee3->init();
    
    tee4 = new GLObjectObjFl("../../data/Tee.obj", 15.0, 0.0, 0.0);
    tee4->setApperance(*apperance_3);
    tee4->init();
    
    tee5 = new GLObjectObjFl("../../data/Tee.obj", 20.0, 0.0, 0.0);
    tee5->setApperance(*apperance_4);
    tee5->init();
    
    tee6 = new GLObjectObjFl("../../data/Tee.obj", 2.5, 4.33, 0.0);
    tee6->setApperance(*apperance_5);
    tee6->init();
    
    tee7 = new GLObjectObjFl("../../data/Tee.obj", 7.5, 4.33, 0.0);
    tee7->setApperance(*apperance_6);
    tee7->init();
    
    tee8 = new GLObjectObjFl("../../data/Tee.obj", 12.5, 4.33, 0.0);
    tee8->setApperance(*apperance_7);
    tee8->init();
    
    tee9 = new GLObjectObjFl("../../data/Tee.obj", 17.5, 4.33, 0.0);
    tee9->setApperance(*apperance_8);
    tee9->init();
    
    tee10 = new GLObjectObjFl("../../data/Tee.obj", 5.0, 8.66, 0.0);
    tee10->setApperance(*apperance_9);
    tee10->init();
    
    tee11 = new GLObjectObjFl("../../data/Tee.obj", 10.0, 8.66, 0.0);
    tee11->setApperance(*apperance_10);
    tee11->init();
    
    tee12 = new GLObjectObjFl("../../data/Tee.obj", 15.0, 8.66, 0.0);
    tee12->setApperance(*apperance_11);
    tee12->init();
    
    tee13 = new GLObjectObjFl("../../data/Tee.obj", 12.5, 12.99, 0.0);
    tee13->setApperance(*apperance_12);
    tee13->init();
    
    tee14 = new GLObjectObjFl("../../data/Tee.obj", 10.0, 17.32, 0.0);
    tee14->setApperance(*apperance_13);
    tee14->init();
    
    pad = new GLObjectObjFl("../../data/pad.obj", 0.0, 0.0, 0.0);
    pad->setApperance(*apperance_15);
    pad->init();
    
    glm::mat4 tranform = glm::translate(glm::vec3(-10.0f, -5.7737f, 0.0f)) * glm::scale(glm::vec3(1.0, 1.0f, 1.0f)) ;
    tee1->setMatrix(tranform);
    tee2->setMatrix(tranform);
    tee3->setMatrix(tranform);
    tee4->setMatrix(tranform);
    tee5->setMatrix(tranform);
    tee6->setMatrix(tranform);
    tee7->setMatrix(tranform);
    tee8->setMatrix(tranform);
    tee9->setMatrix(tranform);
    tee10->setMatrix(tranform);
    tee11->setMatrix(tranform);
    tee12->setMatrix(tranform);
    tee13->setMatrix(tranform);
    tee14->setMatrix(tranform);
    pad->setMatrix(tranform);
    
    // Initialize Beer Can
    GLBeerPint* beer1 = new GLBeerPint(17,10,0,3,20);
    beer1->setApperance(*apperance_16);
    beer1->init();
    apperance_16->updateLightSources();
    
    // Initialize Table
    GLTable* table1 = new GLTable(50,50,2,10,10);
    table1->setApperance(*apperance_17);
    table1->init();
    apperance_17->updateLightSources();

    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Main render loop
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Prepare the shader for the scissor test
    //// 1. Color ID is specific to the output of the hashing function
    
    glUseProgram(apperance_0->getProgram());
    int l0 = glGetUniformLocation(apperance_0->getProgram(), "select_mode");
    int sel0 = glGetUniformLocation(apperance_0->getProgram(), "is_selected");
    glUniform1i(l0, false);
    glUniform1i(sel0, false);
    glUniform4f( glGetUniformLocation(apperance_0->getProgram(), "select_color_id"), 0.0, 0.0, 0.1,1.0 );
    
    glUseProgram(apperance_1->getProgram());
    int l1 = glGetUniformLocation(apperance_1->getProgram(), "select_mode");
    int sel1 = glGetUniformLocation(apperance_1->getProgram(), "is_selected");
    glUniform1i(l1, false);
    glUniform1i(sel1, false);
    glUniform4f( glGetUniformLocation(apperance_1->getProgram(), "select_color_id"), 0.0, 0.0, 0.2,1.0 );
    glUseProgram(0);
    
    glUseProgram(apperance_2->getProgram());
    int l2 = glGetUniformLocation(apperance_2->getProgram(), "select_mode");
    int sel2 = glGetUniformLocation(apperance_2->getProgram(), "is_selected");
    glUniform1i(l2, false);
    glUniform1i(sel2, false);
    glUniform4f( glGetUniformLocation(apperance_2->getProgram(), "select_color_id"), 0.0, 0.0, 0.3,1.0 );
    glUseProgram(0);
    
    glUseProgram(apperance_3->getProgram());
    int l3 = glGetUniformLocation(apperance_3->getProgram(), "select_mode");
    int sel3 = glGetUniformLocation(apperance_3->getProgram(), "is_selected");
    glUniform1i(l3, false);
    glUniform1i(sel3, false);
    glUniform4f( glGetUniformLocation(apperance_3->getProgram(), "select_color_id"), 0.0,0.0,0.4,1.0 );
    glUseProgram(0);
    
    glUseProgram(apperance_4->getProgram());
    int l4 = glGetUniformLocation(apperance_4->getProgram(), "select_mode");
    int sel4 = glGetUniformLocation(apperance_4->getProgram(), "is_selected");
    glUniform1i(l4, false);
    glUniform1i(sel4, false);
    glUniform4f( glGetUniformLocation(apperance_4->getProgram(), "select_color_id"), 0.0, 0.0, 0.5,1.0 );
    glUseProgram(0);
    
    glUseProgram(apperance_5->getProgram());
    int l5 = glGetUniformLocation(apperance_5->getProgram(), "select_mode");
    int sel5 = glGetUniformLocation(apperance_5->getProgram(), "is_selected");
    glUniform1i(l5, false);
    glUniform1i(sel5, false);
    glUniform4f( glGetUniformLocation(apperance_5->getProgram(), "select_color_id"), 0.0, 0.0, 0.6, 1.0 );
    glUseProgram(0);
    
    glUseProgram(apperance_6->getProgram());
    int l6 = glGetUniformLocation(apperance_6->getProgram(), "select_mode");
    int sel6 = glGetUniformLocation(apperance_6->getProgram(), "is_selected");
    glUniform1i(l6, false);
    glUniform1i(sel6, false);
    glUniform4f( glGetUniformLocation(apperance_6->getProgram(), "select_color_id"), 0.0, 0.0, 0.7,1.0 );
    glUseProgram(0);
    
    glUseProgram(apperance_7->getProgram());
    int l7 = glGetUniformLocation(apperance_7->getProgram(), "select_mode");
    int sel7 = glGetUniformLocation(apperance_7->getProgram(), "is_selected");
    glUniform1i(l7, false);
    glUniform1i(sel7, false);
    glUniform4f( glGetUniformLocation(apperance_7->getProgram(), "select_color_id"), 0.0, 0.0, 0.8,1.0 );
    glUseProgram(0);
    
    glUseProgram(apperance_8->getProgram());
    int l8 = glGetUniformLocation(apperance_8->getProgram(), "select_mode");
    int sel8 = glGetUniformLocation(apperance_8->getProgram(), "is_selected");
    glUniform1i(l8, false);
    glUniform1i(sel8, false);
    glUniform4f( glGetUniformLocation(apperance_8->getProgram(), "select_color_id"), 0.0, 0.0, 0.9,1.0 );
    glUseProgram(0);
    
    glUseProgram(apperance_9->getProgram());
    int l9 = glGetUniformLocation(apperance_9->getProgram(), "select_mode");
    int sel9 = glGetUniformLocation(apperance_9->getProgram(), "is_selected");
    glUniform1i(l9, false);
    glUniform1i(sel9, false);
    glUniform4f( glGetUniformLocation(apperance_9->getProgram(), "select_color_id"), 0.0, 0.1, 0.0,1.0 );
    glUseProgram(0);
    
    glUseProgram(apperance_10->getProgram());
    int l10 = glGetUniformLocation(apperance_10->getProgram(), "select_mode");
    int sel10 = glGetUniformLocation(apperance_10->getProgram(), "is_selected");
    glUniform1i(l10, false);
    glUniform1i(sel10, false);
    glUniform4f( glGetUniformLocation(apperance_10->getProgram(), "select_color_id"), 0.0, 0.1, 0.1,1.0 );
    glUseProgram(0);
    
    glUseProgram(apperance_11->getProgram());
    int l11 = glGetUniformLocation(apperance_11->getProgram(), "select_mode");
    int sel11 = glGetUniformLocation(apperance_11->getProgram(), "is_selected");
    glUniform1i(l11, false);
    glUniform1i(sel11, false);
    glUniform4f( glGetUniformLocation(apperance_11->getProgram(), "select_color_id"), 0.0, 0.1, 0.2,1.0 );
    glUseProgram(0);
    
    glUseProgram(apperance_12->getProgram());
    int l12 = glGetUniformLocation(apperance_12->getProgram(), "select_mode");
    int sel12 = glGetUniformLocation(apperance_12->getProgram(), "is_selected");
    glUniform1i(l12, false);
    glUniform1i(sel12, false);
    glUniform4f( glGetUniformLocation(apperance_12->getProgram(), "select_color_id"), 0.0, 0.1, 0.3,1.0 );
    glUseProgram(0);
    
    glUseProgram(apperance_13->getProgram());
    int l13 = glGetUniformLocation(apperance_13->getProgram(), "select_mode");
    int sel13 = glGetUniformLocation(apperance_13->getProgram(), "is_selected");
    glUniform1i(l13, false);
    glUniform1i(sel13, false);
    glUniform4f( glGetUniformLocation(apperance_13->getProgram(), "select_color_id"), 0.0, 0.1, 0.4,1.0 );
    glUseProgram(0);
    
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Set up our green background color
    static const GLfloat clear_color_white[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    static const GLfloat clear_color_black[] = { 0.0f, 0.0f, 0.0f, 0.0f };
    static const GLfloat clear_depth[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    
    // This sets the camera to a new location
    // the first parameter is the eye position, the second the center location, and the third the up vector.
    SetViewAsLookAt(glm::vec3(20.0f, 20.0f, 45.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    
    
    // Enable depth test
    // ignore this line, it allows us to keep the distance value after we proejct each object to a 2d canvas.
    glEnable(GL_DEPTH_TEST);
    
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Blending
    
    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glfwSetKeyCallback(window, keyboard_callback);
    
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Main render loop
    
    // This is our render loop. As long as our window remains open (ESC is not pressed), we'll continue to render things.
    while(!glfwWindowShouldClose(window))
    {
        
        // Clear the entire buffer with our green color (sets the background to be green).
        glClearBufferfv(GL_COLOR , 0, clear_color_black);
        glClearBufferfv(GL_DEPTH , 0, clear_depth);
    
        SetTrackballLocation(GetCurrentCameraMatrix(),GetCurrentCameraTranslation());
        /////////////////////////////////////////////////////
        // For selection.
        // FIRST, RENDER IN SELECT MODE
        
        // 1. start the scissor test
        glEnable(GL_SCISSOR_TEST);
        // 2. Set the window with window size 1x1
        // 600 is the size of the frame, make sure you know it.
        glScissor(GetMouseX(), (600-GetMouseY()), 1, 1);
        
        if (delete_flag[0] != 1)
        {
            glUseProgram(apperance_0->getProgram());
            glUniform1i(l0, true);
            tee1->draw();
            glUniform1i(l0, false); // and switch to regular mode.
        }
        
        //Tee
        
        if (delete_flag[1] != 1)
        {
            glUseProgram(apperance_1->getProgram());
            glUniform1i(l1, true);
            tee2->draw();
            glUniform1i(l1, false);
        }
        
        //Tee
        if (delete_flag[2] != 1)
        {
            glUseProgram(apperance_2->getProgram());
            glUniform1i(l2, true);
            tee3->draw();
            glUniform1i(l2, false);
        }
        
        //Tee
        if (delete_flag[3] != 1)
        {
            glUseProgram(apperance_3->getProgram());
            glUniform1i(l3, true);
            tee4->draw();
            glUniform1i(l3, false);
            glUseProgram(0);
        }
        
        //Tee
        if (delete_flag[4] != 1)
        {
            glUseProgram(apperance_4->getProgram());
            glUniform1i(l4, true);
            tee5->draw();
            glUniform1i(l4, false);
        }
        
        //Tee
        
        if (delete_flag[5] != 1)
        {
            glUseProgram(apperance_5->getProgram());
            glUniform1i(l5, true);
            tee6->draw();
            glUniform1i(l5, false);
            //Tee
        }
        if (delete_flag[6] != 1)
        {
            glUseProgram(apperance_6->getProgram());
            glUniform1i(l6, true);
            tee7->draw();
            glUniform1i(l6, false);
        }
        //Tee
        if (delete_flag[7] != 1)
        {
            glUseProgram(apperance_7->getProgram());
            glUniform1i(l7, true);
            tee8->draw();
            glUniform1i(l7, false);
        }
        //Tee
        if (delete_flag[8] != 1)
        {
            glUseProgram(apperance_8->getProgram());
            glUniform1i(l8, true);
            tee9->draw();
            glUniform1i(l8, false);
        }
        
        //Tee
        if (delete_flag[9] != 1)
        {
            glUseProgram(apperance_9->getProgram());
            glUniform1i(l9, true);
            tee10->draw();
            glUniform1i(l9, false);
        }
        
        //Tee
        if (delete_flag[10] != 1)
        {
            glUseProgram(apperance_10->getProgram());
            glUniform1i(l10, true);
            tee11->draw();
            glUniform1i(l10, false);
        }
        //Tee
        if (delete_flag[11] != 1)
        {
            glUseProgram(apperance_11->getProgram());
            glUniform1i(l11, true);
            tee12->draw();
            glUniform1i(l11, false);
        }
        
        //Tee
        if (delete_flag[12] != 1)
        {
            glUseProgram(apperance_12->getProgram());
            glUniform1i(l12, true);
            tee13->draw();
            glUniform1i(l12, false);
        }
        
        //Tee
        if (delete_flag[13] != 1)
        {
            glUseProgram(apperance_13->getProgram());
            glUniform1i(l13, true);
            tee14->draw();
            glUniform1i(l13, false);
        }
        glUseProgram(0);
        glDisable(GL_SCISSOR_TEST);
        /////////////////////////////////////////////////////////
        // Read the color information at that pixel.
        float col[4];
        glReadPixels(GetMouseX(), (600-GetMouseY()), 1, 1, GL_RGB,GL_FLOAT,&col);
        cout << "COLOR:\t" << col[0] << "\t" << col[1] << "\t" << col[2]  << "\t" << col[3] << "\n" << endl;
        
        int object_id = colorToInteger(col[0], col[1], col[2], col[3]);
        cout << "Found object with id: " << object_id << endl;
        
        /////////////////////////////////////////////////////////
        // Process the color information
        // Change the color of the selected object
        handle_pick(object_id);
        
    
        /////////////////////////////////////////////////////////
        // Render the visible scene

        // Clear the entire buffer with our green color (sets the background to be green).
        glClearBufferfv(GL_COLOR , 0, clear_color_white);
        glClearBufferfv(GL_DEPTH , 0, clear_depth);
        // initailize the target according to picking so nothing strange will happen
        if (g_selected_object_id_1 !=101010 and init_tar == 0)
        {
            switch(g_selected_object_id_1)
            {
                case 101017:
                    target1[0]=0.0;  target1[1]=0.0;  target1[2]=0.0;
                    break;
                case 101026:
                    target1[0]=5.0;  target1[1]=0.0;  target1[2]=0.0;
                    break;
                case 101033:
                    target1[0]=10.0;  target1[1]=0.0;  target1[2]=0.0;
                    break;
                case 101042:
                    target1[0]=15.0;  target1[1]=0.0;  target1[2]=0.0;
                    break;
                case 101049:
                    target1[0]=20.0;  target1[1]=0.0;  target1[2]=0.0;
                    break;
                case 101058:
                    target1[0]=2.5;  target1[1]=4.33;  target1[2]=0.0;
                    break;
                case 101065:
                    target1[0]=7.5;  target1[1]=4.33;  target1[2]=0.0;
                    break;
                case 101074:
                    target1[0]=12.5;  target1[1]=4.33;  target1[2]=0.0;
                    break;
                case 101081:
                    target1[0]=17.5;  target1[1]=4.33;  target1[2]=0.0;
                    break;
                case 101794:
                    target1[0]=5.0;  target1[1]=8.66;  target1[2]=0.0;
                    break;
                case 101801:
                    target1[0]=10.0;  target1[1]=8.66;  target1[2]=0.0;
                    break;
                case 101810:
                    target1[0]=15.0;  target1[1]=8.66;  target1[2]=0.0;
                    break;
                case 101817:
                    target1[0]=12.5;  target1[1]=13.0;  target1[2]=0.0;
                    break;
                case 101826:
                    target1[0]=10.0;  target1[1]=17.33;  target1[2]=0.0;
                    break;
                    
            }
            init_tar = 1;
            
        }
        
        
        //         morphing for different selection
        switch(g_selected_object_id_1)
        {
            case 101017:
                init_morphing(tee1,target1[0],target1[1],target1[2]);
                my_morphing_callback(1.0, time0, tee1,target1[0],target1[1],target1[2]);
                break;
            case 101026:
                init_morphing(tee2,target1[0],target1[1],target1[2]);
                my_morphing_callback(1.0, time0, tee2,target1[0],target1[1],target1[2]);
                break;
            case 101033:
                init_morphing(tee3,target1[0],target1[1],target1[2]);
                my_morphing_callback(1.0, time0, tee3,target1[0],target1[1],target1[2]);
                break;
            case 101042:
                init_morphing(tee4,target1[0],target1[1],target1[2]);
                my_morphing_callback(1.0, time0, tee4,target1[0],target1[1],target1[2]);
                break;
            case 101049:
                init_morphing(tee5,target1[0],target1[1],target1[2]);
                my_morphing_callback(1.0, time0, tee5,target1[0],target1[1],target1[2]);
                break;
            case 101058:
                init_morphing(tee6,target1[0],target1[1],target1[2]);
                my_morphing_callback(1.0, time0, tee6,target1[0],target1[1],target1[2]);
                break;
            case 101065:
                init_morphing(tee7,target1[0],target1[1],target1[2]);
                my_morphing_callback(1.0, time0, tee7,target1[0],target1[1],target1[2]);
                break;
            case 101074:
                init_morphing(tee8,target1[0],target1[1],target1[2]);
                my_morphing_callback(1.0, time0, tee8,target1[0],target1[1],target1[2]);
                break;
            case 101081:
                init_morphing(tee9,target1[0],target1[1],target1[2]);
                my_morphing_callback(1.0, time0, tee9,target1[0],target1[1],target1[2]);
                break;
            case 101794:
                init_morphing(tee10,target1[0],target1[1],target1[2]);
                my_morphing_callback(1.0, time0, tee10,target1[0],target1[1],target1[2]);
                break;
            case 101801:
                init_morphing(tee11,target1[0],target1[1],target1[2]);
                my_morphing_callback(1.0, time0, tee11,target1[0],target1[1],target1[2]);
                break;
            case 101810:
                init_morphing(tee12,target1[0],target1[1],target1[2]);
                my_morphing_callback(1.0, time0, tee12,target1[0],target1[1],target1[2]);
                break;
            case 101817:
                init_morphing(tee13,target1[0],target1[1],target1[2]);
                my_morphing_callback(1.0, time0, tee13,target1[0],target1[1],target1[2]);
                break;
            case 101826:
                init_morphing(tee14,target1[0],target1[1],target1[2]);
                my_morphing_callback(1.0, time0, tee14,target1[0],target1[1],target1[2]);
                break;
                
        }
        
        
        // delete the tee that is eaten
        int DeleteID = getDeleteID(origin, target1, delete_flag);
        
        if (glfwGetTime() - 1.0 > time0 and DeleteID != 0 and DeleteID <15 and delete_flag[DeleteID-1] == 0 and delete_act == 1)
        {
            //            cout<< DeleteID << endl;
            delete_flag[DeleteID-1] = 1;
            switch (DeleteID)
            {
                case 1 :
                    delete tee1;
                    break;
                case 2 :
                    delete tee2;
                    break;
                case 3 :
                    delete tee3;
                    break;
                case 4 :
                    delete tee4;
                    break;
                case 5 :
                    delete tee5;
                    break;
                case 6 :
                    delete tee6;
                    break;
                case 7 :
                    delete tee7;
                    break;
                case 8 :
                    delete tee8;
                    break;
                case 9 :
                    delete tee9;
                    break;
                case 10 :
                    delete tee10;
                    break;
                case 11 :
                    delete tee11;
                    break;
                case 12 :
                    delete tee12;
                    break;
                case 13 :
                    delete tee13;
                    break;
                case 14 :
                    delete tee14;
                    break;
            }
            DeleteID = 1000;
            target1[0] = -100;
            target1[1] = -100;
            target1[2] = -100;
        }
        
        /////////////////////////////////////////////////////////
        // Render the visible scene
        
        // Clear the entire buffer with our green color (sets the background to be green).
        glClearBufferfv(GL_COLOR , 0, clear_color_white);
        glClearBufferfv(GL_DEPTH , 0, clear_depth);
        if (delete_flag[0] != 1)
        {
            tee1->draw();
        }
        if (delete_flag[1] != 1)
        {
            tee2->draw();
        }
        if (delete_flag[2] != 1)
        {
            tee3->draw();
        }
        if (delete_flag[3] != 1)
        {
            tee4->draw();
        }
        if (delete_flag[4] != 1)
        {
            tee5->draw();
        }
        if (delete_flag[5] != 1)
        {
            tee6->draw();
        }
        if (delete_flag[6] != 1)
        {
            tee7->draw();
        }
        if (delete_flag[7] != 1)
        {
            tee8->draw();
        }
        if (delete_flag[8] != 1)
        {
            tee9->draw();
        }
        if (delete_flag[9] != 1)
        {
            tee10->draw();
        }
        if (delete_flag[10] != 1)
        {
            tee11->draw();
        }
        if (delete_flag[11] != 1)
        {
            tee12->draw();
        }
        if (delete_flag[12] != 1)
        {
            tee13->draw();
        }
        if (delete_flag[13] != 1)
        {
            tee14->draw();
        }
        pad->draw();
        beer1->draw();
        table1->draw();
        
        //// This renders the objects
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        
        
        // Swap the buffers so that what we drew will appear on the screen.
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }
    
    
    delete cs;
    
    
}

