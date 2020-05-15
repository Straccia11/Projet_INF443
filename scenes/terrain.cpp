#include "main/scene_base/base.hpp"
#include "terrain.hpp"

using namespace vcl;



// Evaluate height of the terrain for any (u,v) \in [0,1]
float evaluate_terrain_z(float u, float v){

    const vec2 u0[4] = {{0.4f, 0.4f},{0.5f, 0.6f},{0.4f, 0.7f}, {0.8f, 0.2f}};
    const float h0[4] = {3.0f, -1.5f, 1.0f, 2.0f};
    const float sigma0[4] = {0.5f, 0.15f, 0.2f, 0.2f};

    float d = 0.0f;
    float z = 0.0f;

    // Evaluate Perlin noise
    const float noise1 = 0.4f*perlin(1.7f*u, 1.7f*v, 9, 0.56f);
    const float noise2 = perlin(2.7f*u, 2.7f*v, 2, 0.56f);
    const float noise3 = perlin(1.7f*u, 1.7f*v, 1, 0.56f);

    for(int i=0; i<4; i++){
         d = norm(vec2(u,v)-u0[i])/sigma0[i];
         z += h0[i]*std::exp(-d*d);
    }


    //return z + 0.1f*noise*std::abs(z-3.0f);
    return z-2.5f + noise3 + noise1*std::abs(z-1.5f);// + noise2;
}

// Evaluate 3D position of the terrain for any (u,v) \in [0,1]
vec3 evaluate_terrain(float u, float v)
{
    const float x = 20*(u-0.5f);
    const float y = 20*(v-0.5f);
    const float z = evaluate_terrain_z(u,v);

    return {2*x,2*y,3*z};
}

// Generate terrain mesh
mesh create_terrain()
{
    // Number of samples of the terrain is N x N
    const size_t N = 100;
    float c;

    mesh terrain; // temporary terrain storage (CPU only)
    terrain.position.resize(N*N);
    terrain.color.resize(N*N);
    terrain.texture_uv.resize(N*N);

    // Fill terrain geometry
    for(size_t ku=0; ku<N; ++ku)
    {
        for(size_t kv=0; kv<N; ++kv)
        {
            // Compute local parametric coordinates (u,v) \in [0,1]
            const float u = ku/(N-1.0f);
            const float v = kv/(N-1.0f);

            // Compute coordinates
            c = 0.5f+0.6f*perlin(1.7f*u, 1.7f*v, 9, 0.56f);

            terrain.color[kv+N*ku]  = {c,c,c,1.0f};
            terrain.position[kv+N*ku] = evaluate_terrain(u,v);
            terrain.texture_uv[kv+N*ku] = {v, u};
        }
    }


    // Generate triangle organization
    //  Parametric surface with uniform grid sampling: generate 2 triangles for each grid cell
    const unsigned int Ns = N;
    for(unsigned int ku=0; ku<Ns-1; ++ku)
    {
        for(unsigned int kv=0; kv<Ns-1; ++kv)
        {
            const unsigned int idx = kv + N*ku; // current vertex offset

            const uint3 triangle_1 = {idx, idx+1+Ns, idx+1};
            const uint3 triangle_2 = {idx, idx+Ns, idx+1+Ns};

            terrain.connectivity.push_back(triangle_1);
            terrain.connectivity.push_back(triangle_2);
        }
    }

    return terrain;
}

mesh create_sky() {
    mesh cube;
    //float a = 1/(float)3;
    cube.position = {{-50,-50,-50},{-50,-50,50},{-50,50,-50},{-50, 50, 50},{50,50,-50},{50,50,50},{50,-50,-50},{50,-50,50},  {50,50,-50},{50,50,50},{50,-50,-50},{50,-50,50},  {50,-50,-50},{50,-50,50}};
    cube.connectivity = {{0,2,1},{1,2,3},{2,4,3},{3,4,5},{4,6,5},{5,6,7},{12,0,13},{13,0,1},  {1,3,9},{1,9,11}, {0,8,2},{0,10,8}};
    cube.texture_uv = {{0.25f,0.65},{0.25f,0.34},{0.5f,0.65},{0.5f,0.34},{0.75f,0.65},{0.75f,0.34},{1,0.65},{1,0.34}, {0.5f,1},{0.5f,0},{0.25f,1},{0.25f,0},  {0,0.65},{0,0.34}};

    return cube;
}

vcl::mesh create_see(float height)
{
    mesh sea = mesh_primitive_quad({-20.0f,-20.0f, height}, {20.0f,-20.0f, height}, {20.0f,20.0f, height}, {-20.0f,20.0f, height});
    sea.texture_uv *= 4;
    return sea;
}
