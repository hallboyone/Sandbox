#ifndef COORD_2D_HPP
#define COORD_2D_HPP

#include <SharkPlot/Coord/Coord.hpp>

namespace SharkPlot{
  /**
   * Class implements an n-diminsional coord. All the basic vector operations can
   * be called on it such as dot product, normalize, etc.
   */
  class Coord2D : public Coord {
  private:
    friend std::ostream & operator<<(std::ostream & os, const Coord2D & c);
  public:
    /**
     * Empty Coord constructor
     */
    Coord2D(): Coord(2){}
    /**
     * Initialization constructor given two doubles
     */
    Coord2D(const double x, const double y);
    /**
     * Unit Coord constructor pointing in the norm_dir direction
     */
    Coord2D(int norm_dir);
    /**
     * Initializeation constructor creating an Coord with the values in vals
     */
    Coord2D(const double * vals);

    
    double & x(){return vals_[0];}
    double & y(){return vals_[1];}
    const double & x() const {return vals_[0];}
    const double & y() const {return vals_[1];}

    Coord2D & operator=(const Coord & rhs);
    
    virtual Coord2D & scale(const double n){
      vals_[0] *= n;
      vals_[1] *= n;
      return *this;
    }
    
    double theta() const;
  };
}
#endif  
