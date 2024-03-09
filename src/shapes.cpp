#include "shapes.h"
#include <Eigen/Dense>
#include <iostream>


Sphere::Sphere(Eigen::Vector3d pos, const int* color, double radius) :ppos{pos}, pcolor{color}, pradius{radius} {}
double Sphere::sdf(Eigen::Vector3d ray) {
        //std::cout << "Ray" << ray << std::endl;
        //std::cout << "dist" << ray - ppos << std::endl;
        //std::cout << "norm" << (ray - ppos).norm()<< std::endl;
        //std::cout << "sdf" << (ray - ppos).norm()-pradius<< std::endl;
        return (ray - ppos).norm()-pradius;
    }
const int* Sphere::color(void) {
    return pcolor;
}
