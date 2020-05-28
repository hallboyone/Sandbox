#include <SharkPlot/Coord/Coord3D.hpp>

#include <iomanip>    // std::setprecision
#include <cmath>      // std::fabs
namespace SharkPlot{
  /**
   * Initialization constructor given two doubles
   */
  Coord3D::Coord3D(const double x, const double y, const double z): Coord(3){
    vals_[0] = x;
    vals_[1] = y;
    vals_[2] = z;
  }

  double & Coord3D::x(){
    if (fabs(vals_[0]) < COORD_TOL) vals_[0] = 0;
    return vals_[0];
  }
  double & Coord3D::y(){
    if (fabs(vals_[1]) < COORD_TOL) vals_[1] = 0;
    return vals_[1];
  }
  double & Coord3D::z(){
    if (fabs(vals_[2]) < COORD_TOL) vals_[2] =  0;
    return vals_[2];
  }
  const double & Coord3D::x() const{
    if (fabs(vals_[0]) < COORD_TOL) vals_[0] = 0;
    return vals_[0];
  }
  const double & Coord3D::y() const{
    if (fabs(vals_[1]) < COORD_TOL) vals_[1] = 0;
    return vals_[1];
  }
  const double & Coord3D::z() const{
    if (fabs(vals_[2]) < COORD_TOL) vals_[2] = 0;
    return vals_[2];
  }

  Coord3D Coord3D::cross(const Coord3D & rhs) const{
    Coord3D cross_product(y()*rhs.z() - z()*rhs.y(), // y1*z2 - z1*y2
			 z()*rhs.x() - x()*rhs.z(), // z1*x2 - x1*z2
			 x()*rhs.y() - y()*rhs.x());// x1*y2 - y1*x2
    return cross_product;
  }

  
  std::ostream & operator<<(std::ostream & os, const Coord3D & c){
    os<<std::setprecision(5)<<"["<<c.x()<<", "<<c.y()<<", "<<c.z()<<"]"<<std::setprecision(10);
    return os;
  }
}
