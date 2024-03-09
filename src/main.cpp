#include <stdlib.h>
#include <iostream>
#include <Eigen/Dense>
 

#include <SDL2/SDL.h>
#include "shapes.h"
//using Eigen::MatrixXd;

#define WINDOW_WIDTH 2
#define camoffset 5.0
#define FOV 1.0

struct scene {
    Eigen::MatrixXd rays;
    const int* screen[WINDOW_WIDTH*WINDOW_WIDTH] = { };
    std::vector<Sphere> objects;
} ;

scene getmindist(scene sceneref) {
    Eigen::IOFormat CleanFmt(3, 0, ", ", "\n", "[", "]");
    //for(int i=0; i<(sceneref.rays).rows(); i++){
    for (int i=0; i<sceneref.rays.rows();i++){
        double curstep = HUGE_VAL;
        Eigen::Vector3d ray = sceneref.rays.row(i); 
        double nstep;
        for(auto obj: sceneref.objects) {
            //std::cout << "Get sdf" << std::endl;

            //std::cout << "Obj" << std::endl;
            nstep = obj.sdf(ray);
            if (nstep< 0.05) { 
                curstep = 0.0;
                sceneref.screen[i] = obj.color();
                }
            else if (nstep<curstep) {
                curstep = nstep;
            }
        }
        //std::cout << nstep << std::endl;
    }
    return sceneref;
}

int main(void) {
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;
    int i;
    Eigen::MatrixXd camrays(WINDOW_WIDTH*WINDOW_WIDTH, 3);
    //std::vector<const int*> screen;
    //screen.reserve(WINDOW_WIDTH*WINDOW_WIDTH);
    
    //x, y, z
    const double x = WINDOW_WIDTH*FOV/2, y=x;
    //INIT RAYS
    for(int k=0;k<WINDOW_WIDTH;k++){ //row
        for(int j=0;j<WINDOW_WIDTH;j++){ //col
            camrays(WINDOW_WIDTH*k+j, 0) = camoffset;
            camrays(WINDOW_WIDTH*k+j, 1) = x-k*FOV;
            camrays(WINDOW_WIDTH*k+j, 2) = y-j*FOV;
        }
    }
    std::vector<Sphere> objects;
    objects.insert(
        objects.end(),
        {
            Sphere(Eigen::Vector3d(2.0,3.3,0.0), std::initializer_list<int>({100, 100, 250}).begin(), 1.0),
            Sphere(Eigen::Vector3d(1.0,1.0,0.0), std::initializer_list<int>({250, 250, 0}).begin(), 1.0)
        }
    );
    //
    scene scenerender;
    scenerender.rays = camrays;
    std::cout << "rays" << std::endl << scenerender.rays << std::endl;
    //scenerender.screen = int [WINDOW_WIDTH*WINDOW_WIDTH];
    
    
    //scenerender.screen[0] = sp1.color();
    //std::cout << "screen" << &scenerender.screen << std::endl;
    scenerender.objects = objects;

    //scene* sceneref = &scenerender;
    int itersteps = 50;
    for (int i=0; i<itersteps; i++){
        scenerender = getmindist(scenerender);
    }
    
    //std::cout << scenerender.screen << std::endl;
    //printf("%d\n", *scenerender.screen[0]);
    
    //const int* col = scenerender.screen[0];
    //int tt = scenerender.screen[0][2];
    //printf("%d\n", tt);
    for (int y = 0 ; y<=WINDOW_WIDTH*WINDOW_WIDTH; y++){
        printf("%d:", scenerender.screen[y]);
        //std::cout << scenerender.screen[0][y];//printf("%d,", col[y]);
        //std::cout << ",";
    }
    printf("\n");
    return 0;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_WIDTH, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (i = 0; i < WINDOW_WIDTH; ++i)
        SDL_RenderDrawPoint(renderer, i, i);
    SDL_RenderPresent(renderer);
    while (1) {
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}