#include <Eigen/Dense>

class Shape {
public:
    virtual double sdf();


};
class Sphere 
{
private:
    Eigen::Vector3d ppos;
    const int *pcolor;
    double pradius;
    
public:
    Sphere(Eigen::Vector3d pos, const int *color, double radius);
    const int* color();
    double sdf(Eigen::Vector3d ray);
};