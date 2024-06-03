#include "shapes.h"
#include <Eigen/Dense>
#include <iostream>


Sphere::Sphere(Eigen::Vector3d pos, std::vector<int> color, double radius) :ppos{pos}, pcolor{color}, pradius{radius} {}
double Sphere::sdf(Eigen::Vector3d ray) {
        return (ray - ppos).norm()-pradius;
    }
std::vector<int> Sphere::color(void) {
    return pcolor;
}
double Sphere::shader_brightness(Eigen::Vector3d ray) {
    double normal = Sphere::normal(ray)[2];
    double tt = 15.0;
    double elevation = 0.0;
    elevation = elevation/(90.0) + 1.0;
    double cliprange = 0.2;
    if (elevation < 1.0-cliprange || elevation > 1.0+cliprange)
        elevation = 1.0;
    return elevation;
}


Eigen::Vector3d Sphere::normal(Eigen::Vector3d ray) {
    Eigen::Vector3d normalvec = ray-ppos;
    return normalvec/normalvec.norm();
}


Plane::Plane(Eigen::Vector3d pos, std::vector<Eigen::Vector3d> dim,std::vector<int> color) : Shape(pos, color), span(dim) {};
double Plane::sdf(Eigen::Vector3d ray) {
    return 0.0;
};
