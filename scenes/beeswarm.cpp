#include "beeswarm.hpp"

using namespace vcl;

void beeswarm::create_ruche(float size)
{
    ruche = mesh_primitive_sphere(size);
    ruche.uniform.color = {0.87f, 0.69f, 0.17f};
    ruche.uniform.shading.specular = 0;
}

void beeswarm::create_bee(float size)
{
    mesh_drawable body = mesh_drawable( mesh_primitive_sphere(size));
    body.uniform.transform.scaling_axis = {1.5,1,1};
    body.uniform.color = {1,1,0};
    mesh_drawable head = mesh_drawable( mesh_primitive_sphere(size/1.5f));
    head.uniform.color = {0,0,0};

    mesh _wing;
    float theta = 2*M_PI/20;
    _wing.position.push_back({0,0,0});
    for(int i=0; i<13; i++)
    {
        _wing.position.push_back(size*vec3(std::cos(theta*(i-2)), std::sin(theta*(i-2)), 0));
        _wing.connectivity.push_back({i+1, i+2, 0});
    }
    _wing.position.push_back(size*vec3(std::cos(theta*12), std::sin(theta*(12)), 0));
    _wing.connectivity.push_back({14, 1, 0});

    mesh_drawable wing = _wing;
    wing.uniform.transform.scaling_axis = {1,2,1};
    wing.uniform.color = {0.2f,1,1};

    bee.add(body, "body");
    bee.add(head, "head", "body", {1.7f*size,0,0});
    bee.add(wing, "left_wing", "body", {0, 0.5f*size, 0});
    bee.add(wing, "right_wing", "body", {{0, -0.5f*size, 0}, {1,0,0, 0,-1,0, 0,0,1}});
}



void beeswarm::setup_swarm(std::map<std::string,GLuint>& shaders)
{
    create_ruche(1.0f);
    create_bee(1.0f);

     bee.set_shader_for_all_elements(shaders["mesh"]);
}

void beeswarm::draw_swarm(std::map<std::string,GLuint>& shaders, scene_structure& scene, vcl::timer_interval timer)
{
    ruche.uniform.transform.translation = {0,0,7};
    ruche.uniform.transform.scaling_axis = {1,1,0.4f};
    draw(ruche, scene.camera, shaders["mesh"]);
    ruche.uniform.transform.scaling_axis = {0.85f, 0.85f, 0.4f};
    ruche.uniform.transform.translation = {0,0,7.3f};
    draw(ruche, scene.camera, shaders["mesh"]);
    ruche.uniform.transform.translation = {0,0,6.7f};
    draw(ruche, scene.camera, shaders["mesh"]);
    ruche.uniform.transform.scaling_axis = {0.6f, 0.6f, 0.3f};
    ruche.uniform.transform.translation = {0,0,6.4f};
    draw(ruche, scene.camera, shaders["mesh"]);

    mat3 const R_y_sym = {1,0,0, 0,-1,0, 0,0,1};
    bee.set_shader_for_all_elements(shaders["mesh"]);
    bee.update_local_to_global_coordinates();
    bee["body"].transform.translation = {0,0,5};
    bee["left_wing"].transform.rotation = rotation_from_axis_angle_mat3({1,0,0}, 0.8f*std::sin(2*M_PI*timer.t));
    bee["right_wing"].transform.rotation = R_y_sym*rotation_from_axis_angle_mat3({1,0,0}, 0.8f*std::sin(2*M_PI*timer.t));
    draw(bee, scene.camera);
}
