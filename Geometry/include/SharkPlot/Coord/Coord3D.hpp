#ifndef COORD_3D_HPP
#define COORD_3D_HPP

#include <SharkPlot/Coord/Coord.hpp>

namespace SharkPlot{
  /**
   * Class implements an n-diminsional coord. All the basic vector operations can
   * be called on it such as dot product, normalize, etc.
   */
  class Coord3D : public Coord {
  private:
    friend std::ostream & operator<<(std::ostream & os, const Coord3D & c);
  public:
    /**
     * Empty Coord constructor
     */
    Coord3D(): Coord(3){}
    /**
     * Initialization constructor given two doubles
     */
    Coord3D(const double x, const double y, const double z);
    /**
     * Unit Coord constructor pointing in the norm_dir direction
     */
    Coord3D(int norm_dir): Coord(3, norm_dir) {}
    /**
     * Initializeation constructor creating an Coord with the values in vals
     */
    Coord3D(const double * vals): Coord(3, vals){}

    virtual Coord3D & scale(const double n){
      vals_[0] *= n;
      vals_[1] *= n;
      vals_[2] *= n;
      return *this;
    }
    
    double & x();
    double & y();
    double & z();
    const double & x() const;
    const double & y() const;
    const double & z() const;

    Coord3D cross(const Coord3D & rhs) const;
  };
}
#endif  