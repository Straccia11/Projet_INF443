#include "main.hpp"

#include <random>


#ifdef SCENE_3D_GRAPHICS
#define M_PI 3.14159265358979323846

// Add vcl namespace within the current one - Allows to use function from vcl library without explicitely preceeding their name with vcl::
using namespace vcl;


void scene_model::setup_data(std::map<std::string,GLuint>& shaders, scene_structure& scene, gui_structure& gui)
{
    // Setup initial camera mode and position
    scene.camera.camera_type = camera_control_spherical_coordinates;
    scene.camera.scale = 50.0f;
    /*scene.camera.apply_translation_orthogonal_to_screen_plane(-1.0f);
    scene.camera.apply_rotation(0,0,0,1.0f);
    scene.camera.apply_rotation(0,0,1.8f,0);*/

    landscape.setup_terrain(scene);

    //Bonhomme
    Jack.setup_dude(shaders);
    Jack.hierarchy["body"].transform.translation = {0,0,3};

    //Swarm
    miel_pops.setup_swarm(shaders);

    gui.show_frame_camera = false;

}


void scene_model::frame_draw(std::map<std::string,GLuint>& shaders, scene_structure& scene, gui_structure& )
{
    timer.update();
    timer.t_max = 4.0f;
    set_gui();

    glEnable( GL_POLYGON_OFFSET_FILL ); // avoids z-fighting when displaying wireframe
    glPolygonOffset( 1.0, 1.0 );

    //Display swarm
    miel_pops.draw_swarm(shaders, scene, timer);


    glBindTexture(GL_TEXTURE_2D, scene.texture_white);

    //Display dude
    if(gui_scene.sbdy)
        Jack.draw_dude(shaders, scene, timer, landscape.points);

    //Draw terrain
    landscape.draw_terrain(shaders, scene, landscape.gui_ter, timer.t);


    //arranger le shader sea et ajouter le shader sea_wireframe
    //prendre en compte le choix de shader surface ou wireframe
    //La structure gui_terrain_structure est inutile?

 }



void scene_model::set_gui()
{
    //landscape.gui_ter.set_gui_terrain();
    ImGui::Spacing();
    ImGui::Checkbox("Wireframe", &gui_scene.wireframe);
    ImGui::SameLine();
    ImGui::Checkbox("Surface", &gui_scene.surface);

    ImGui::Spacing();
    ImGui::Text("Display : ");
    ImGui::SameLine();
    ImGui::Checkbox("Jack", &gui_scene.sbdy);
    ImGui::SameLine();
    //ImGui::Checkbox("Surface", &gui_scene.surface);

    landscape.gui_ter.set_gui_terrain(gui_scene.surface, gui_scene.wireframe, landscape.vegetation_position);
    Jack.gui_bon.set_gui_bonhomme(gui_scene.surface, gui_scene.wireframe);

    //ImGui::SliderFloat("Time", &timer.t, timer.t_min, timer.t_max);
    //ImGui::SliderFloat("Time scale", &timer.scale, 0.1f, 3.0f);


    ImGui::Spacing();
    ImGui::Text("                       -------");
    ImGui::Spacing();
    ImGui::Text("Up/Left/Right : Move Jack");
    ImGui::Text("P : Activate/deactivate Third Person Camera");
    ImGui::Text("Shift + Left Click : Add an element of vegetation");


}


/////////////////////////////////////////////////////////////////////// INTERPOLATION

void scene_model::keyboard_input(scene_structure& scene, GLFWwindow* window, int key, int scancode, int action, int mods)
{
    //Move forward
    if (key == GLFW_KEY_UP && action == GLFW_PRESS)
    {
        Jack.gui_bon.running = true;
    }

    else if (key == GLFW_KEY_UP && action == GLFW_RELEASE)
    {
        Jack.gui_bon.running = false;
    }

    //Turn right
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
    {
        Jack.gui_bon.turn = -1;
    }

    else if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE)
    {
        Jack.gui_bon.turn = 0;
    }


    //Turn left
    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
    {
        Jack.gui_bon.turn = 1;
    }

    else if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE)
    {
        Jack.gui_bon.turn = 0;
    }

    //Third person camera
    if (key == GLFW_KEY_P && action == GLFW_PRESS)
    {
        Jack.gui_bon.third_person = !Jack.gui_bon.third_person;
    }

}

void scene_model::mouse_click(scene_structure& scene, GLFWwindow* window, int a, int b, int c)
{
    landscape.mouse_click(scene, window, a, b, c);
}

#endif

