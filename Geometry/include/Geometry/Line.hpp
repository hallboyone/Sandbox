#ifndef LINE_HPP
#define LINE_HPP

#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Geometry>
#include <cmath>
#include <iostream>

#define COORD_TOL 10e-100

namespace SharkPlot{
  template <unsigned int DIM>
  class Line{
  private:
    typedef Eigen::Matrix<double, DIM, 1> Coord;
    
    Eigen::Matrix<double, DIM, 1> root_;
    Eigen::Matrix<double, DIM, 1> tip_;
  public:
    
    Coord & root(){return root_;}
    Coord & tip() {return tip_;}
    void setRoot(const Coord & r){ root_ = r;}
    void setTip (const Coord & t){ tip_ = t;}
    
    double len(){return (root_ - tip_).norm();}
    double norm(){return len();}

    void scale(double n, bool hold_root_ = false){
      if (fabs(n) < COORD_TOL)
	std::cerr<<"Warning: Scaling line by very small value. May lead to numerical errors.\n";
      if (hold_root_){//Scale without shifting the root
	tip_ = root_ + n*(tip_ - root_);
      }
      else{
	root_ *= n;
	tip_  *= n;
      }
    }
    
    void normalize(bool lock_root_ = false){scale(1/len(), lock_root_);}
      
  };
}//Sharkplot
    
#endif //LINE_HPP
