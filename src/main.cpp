#include <stdlib.h>
#include <iostream>

 

#include <SDL2/SDL.h>
#include <Eigen/Dense>
#include "shapes.h"
//using Eigen::MatrixXd;

#define WINDOW_WIDTH 400
#define camoffset 2.0
#define FOV 2.0
//#define stepsize 0.1


int main(void) {
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;
    
    Eigen::MatrixXd camrays(WINDOW_WIDTH*WINDOW_WIDTH, 3);
    //std::vector<const int*> screen;
    //screen.reserve(WINDOW_WIDTH*WINDOW_WIDTH);
    
    //x, y, z
    const double x = FOV, y=x; //WINDOW_WIDTH*FOV/2
    //INIT RAYS
    for(int k=0;k<WINDOW_WIDTH;k++){ //row
        for(int j=0;j<WINDOW_WIDTH;j++){ //col
            camrays(WINDOW_WIDTH*k+j, 0) = camoffset;
            camrays(WINDOW_WIDTH*k+j, 1) = (double)x-((double)k/(double)WINDOW_WIDTH*FOV*2.0);
            camrays(WINDOW_WIDTH*k+j, 2) = (double)y-((double)j/(double)WINDOW_WIDTH*FOV*2.0);
        }
    }

    if (false){
    for (int y = 0 ; y<camrays.rows(); y++){

        std::cout << camrays.row(y)<<std::endl;
        //std::cout << scenerender.screen[0][y];//printf("%d,", col[y]);
        //std::cout << ",";
    }return 0;}
    //std::vector<int> r = 
    std::vector<Sphere> objects;
    objects.insert(
        objects.end(),
        {   
            Sphere(Eigen::Vector3d(0.5+camoffset,1.0,0.0), std::vector<int>({100, 100, 250, 255}), 0.5),
            Sphere(Eigen::Vector3d(1.0+camoffset,0.5,0.0), std::vector<int>({250, 250, 0, 255}), 0.5)
        }
    );
    //
    std::cout << "camrays dim " << (bool)(camrays.rows()==WINDOW_WIDTH*WINDOW_WIDTH) << std::endl;
    std::cout << "col " << objects[1].color()[1] << std::endl;

    std::vector<std::vector<int>> screen = {};
    std::vector<bool> mask = {};
    //init screen & mask

    std::vector<int> t = {20, 20, 40, 255}; 
    for (int i=0; i<WINDOW_WIDTH*WINDOW_WIDTH;i++){
        
        screen.push_back(t);
        mask.push_back(false);
    }
    

    int itersteps = 10;
    for (int iter=0; iter<itersteps; iter++){
        for (int i=0; i<camrays.rows();i++){
            double curstep = 10.0;//HUGE_VAL;
            Eigen::Vector3d ray = camrays.row(i); 
            if(mask[i] || ray.norm() > 20.0){
                //collided ray
                continue;
            }

            //std::cout << "ray" << ray.format(CleanFmt) << std::endl;
            double nstep;  
            bool collision = false;
            
            if (ray[2] < 0.0){
                screen[i] = {190,190,190, 255};
                //mask[i] = true;
                //collision = true;
                //break;
            }
            for(auto obj: objects) {
                nstep = obj.sdf(ray);
                //std::cout << "sdf" << nstep << std::endl;
                if (nstep< 0.1) { 
                    curstep = nstep;
                    Eigen::Vector3d normal = obj.normal(ray);

                    screen[i] = obj.color();
                    
                    mask[i] = true;
                    collision = true;
                    break;
                }
                else if (nstep<curstep) {
                    curstep = nstep;
                }
            }
            
            if (!collision){
                Eigen::MatrixXd step = ray / ray.norm() * curstep;
                camrays(i, Eigen::all) = ray + step;
                //std::cout << nstep << std::endl;
            }
        }
    }
    
    //Debug Prints
    if (false){
        bool any = false;
        for (int y = 0 ; y<WINDOW_WIDTH*WINDOW_WIDTH; y++){
            //printf("%\n:", scenerender.screen[y]);
            //printf("%d\n", y);
            any = any || screen[y]!=t;
            if (screen[y]!=t){
                std::cout << "Diff at " <<  y << std::endl;
                
                std::cout << screen[y][0] << std::endl;
                //for (int n : screen[y])
                //    std::cout << n << ' ';
                std::cout << '\n';
                
            }
            //std::cout << scenerender.screen[0][y];//printf("%d,", col[y]);
            //std::cout << ",";
        }
        std::cout << "any " <<  any << std::endl;
        
    }
    



    //original code
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_WIDTH, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    
    for (int i = 0 ; i<WINDOW_WIDTH*WINDOW_WIDTH; i++){
        //if (!mask[i])
        //    continue;
        std::vector<int> tmp = (screen[i]);
        SDL_SetRenderDrawColor(renderer, tmp[0], tmp[1], tmp[2], tmp[3]); //tmp[0], tmp[1], tmp[2]
        int x = (int)i/WINDOW_WIDTH;
        int y = i%WINDOW_WIDTH;

        SDL_RenderDrawPoint(renderer, x, y);
    }
    std::cout << "render complete" << std::endl;
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