#include <Eigen/Dense>

//#include <iostream>

class Shape {
protected:
    Eigen::Vector3d obj_pos= {0,0,0};
    const std::vector<int> obj_color = {0,0,0,0};
    bool solid = false;
public:
    Shape (Eigen::Vector3d pos, std::vector<int> color) : obj_pos(pos), obj_color(color) {};
    virtual double sdf(Eigen::Vector3d ray) =0;
    //virtual Eigen::Vector3d normal(Eigen::Vector3d ray) =0;
    virtual std::vector<int> color() {return obj_color;};

    //virtual friend std::ostream& operator<<(std::ostream& out, const Shape& shape);
};
class Sphere 
{
private:
    Eigen::Vector3d ppos;
    std::vector<int> pcolor; //const int *
    double pradius;
    
public:
    Sphere(Eigen::Vector3d pos, std::vector<int> color, double radius);
    std::vector<int> color();
    double sdf(Eigen::Vector3d ray);
    double shader_brightness(Eigen::Vector3d ray);
    Eigen::Vector3d normal(Eigen::Vector3d ray);
};

class Plane: public Shape
{
private:
    std::vector<Eigen::Vector3d> span;
public:
    Plane(Eigen::Vector3d pos, std::vector<Eigen::Vector3d> dim, std::vector<int> color);
    double sdf(Eigen::Vector3d ray);
    Eigen::Vector3d normal(Eigen::Vector3d ray);
};