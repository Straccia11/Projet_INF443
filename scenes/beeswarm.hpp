#pragma once
#include "main/scene_base/base.hpp"

struct gui_beeswarm_structure
{
    bool surface = true;
    bool wireframe = false;
};

struct beeswarm
{
    vcl::mesh_drawable ruche;
    vcl::hierarchy_mesh_drawable bee;
    vcl::hierarchy_mesh_drawable swarm;
    gui_beeswarm_structure gui_bee;
    std::vector<vcl::vec3> pos_bees;

    vcl::vec3* target;

    void setup_swarm(std::map<std::string,GLuint>& shaders);
    void draw_swarm(std::map<std::string,GLuint>& shaders, scene_structure& scene, vcl::timer_interval timer);

    void create_ruche(float size);
    void create_bee(float size);
    void set_hierarchy(int N);
};
