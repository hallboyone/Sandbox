#include <SharkPlot/Coord/Coord2D.hpp>
#include <math.h> //atan2
#include <iomanip>    // std::setprecision

namespace SharkPlot{
  /**
   * Initialization constructor given two doubles
   */
  Coord2D::Coord2D(const double x, const double y): Coord(2){
    vals_[0] = x;
    vals_[1] = y;
  }

  /**
   * Unit Coord constructor pointing in the norm_dir direction
   */
  Coord2D::Coord2D(int norm_dir): Coord(2, norm_dir){}
  
  /**
   * Initializeation constructor creating an Coord with the values in vals
   */
  Coord2D::Coord2D(const double * vals): Coord(2, vals){}

  /*
    Returns the angle of the coord around the z-axis.
    Angle is scaled between 0 and 1 with 0 being the 
    positive x-axis, 0.25 being the positive y, etc
  */
  double Coord2D::theta() const{
    //Make sure x or y are not 0
    if(x()==0 && y()==0){
      throw(std::domain_error("Attempted to get theta for (0,0)"));
    }
  
    double theta = atan2(y(),x()) / (2*PI);
    if(theta < 0) theta += 1;
    return theta;
  }

  std::ostream & operator<<(std::ostream & os, const Coord2D & c){
    os<<std::setprecision(5)<<"["<<c.x()<<", "<<c.y()<<"]"<<std::setprecision(10);
    return os;
  }

}
