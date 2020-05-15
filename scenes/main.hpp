#pragma once

#include "main/scene_base/base.hpp"
#include "terrain.hpp"

#ifdef SCENE_3D_GRAPHICS



struct gui_scene_structure
{
    bool wireframe;
    bool display_keyframe = false;
    bool display_polygon  = false;
};

struct scene_model : scene_base
{

    /** A part must define two functions that are called from the main function:
     * setup_data: called once to setup data before starting the animation loop
     * frame_draw: called at every displayed frame within the animation loop
     *
     * These two functions receive the following parameters
     * - shaders: A set of shaders.
     * - scene: Contains general common object to define the 3D scene. Contains in particular the camera.
     * - data: The part-specific data structure defined previously
     * - gui: The GUI structure allowing to create/display buttons to interact with the scene.
    */

    void setup_data(std::map<std::string,GLuint>& shaders, scene_structure& scene, gui_structure& gui);
    void frame_draw(std::map<std::string,GLuint>& shaders, scene_structure& scene, gui_structure& gui);

    void set_gui();
    void create_sky1();

    // Called every time the mouse is clicked
    void mouse_click(scene_structure& scene, GLFWwindow* window, int button, int action, int mods);
    // Called every time the mouse is moved
    void mouse_move(scene_structure& scene, GLFWwindow* window);


    // visual representation of a surface
    vcl::mesh_drawable terrain;
    vcl::mesh_drawable sky1;
    vcl::mesh_drawable see;

    GLuint texture_id_terrain;
    GLuint texture_id_sky;
    GLuint texture_id_sea;



    gui_scene_structure gui_scene;

    vcl::timer_interval timer;
    vcl::timer_event timer2;    // Timer allowing to indicate periodic events
};



#endif


