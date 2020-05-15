#pragma once
#include "main/scene_base/base.hpp"

//Model ground
float evaluate_terrain_z(float u, float v);
vcl::vec3 evaluate_terrain(float u, float v);
vcl::mesh create_terrain();

//Model sky
vcl::mesh create_sky();

//Model sea
vcl::mesh create_see(float height);
