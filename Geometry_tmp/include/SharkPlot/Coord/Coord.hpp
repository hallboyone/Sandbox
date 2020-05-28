#ifndef COORD_HPP
#define COORD_HPP

#define COORD_TOL 1.0e-14

#ifndef PI
#define PI 3.1415926535897932384626433832
#endif

#include <stdlib.h> //size_t
#include <iostream> //cout, NULL
#include <vector>

namespace SharkPlot{
  /**
   * Class implements an n-diminsional coord. All the basic vector operations can
   * be called on it such as dot product, normalize, etc.
   */
  class Coord{
  protected:
    /** 
     * An array of the coordinate values in each diminsion
     */
    double * vals_;
    /**
     * The number of diminsions for this Coord object
     */
    const size_t dim_;

    void ensureDimsMatch(const Coord & rhs) const;
  public:
    /**
     * Empty Coord constructor
     */
    Coord(const size_t dim): dim_(dim){
      vals_ = new double[dim_]();
    }
    /**
     * Unit Coord constructor pointing in the norm_dir direction
     */
    Coord(const size_t dim, int norm_dir);
    /**
     * Initializeation constructor creating an Coord with the values in vals
     */
    Coord(const size_t dim, const double * vals);

    /**
     * Initializeation constructor creating an Coord with the values in vals
     */
    Coord(const std::vector<double> & val);
    /**
     * Copy constructor
     */
    Coord(const Coord & c);

    Coord & operator=(const Coord & rhs);
    
    /** @name Relationship operators
     * Function which define the relationship operator between Coord objects.
     * the comparision must be with a Coord object with an equal diminsion.
     *  @{
     */    
    /** \brief Returns true if Coords are equivalent*/
    bool operator==(const Coord & rhs) const;
    /** \brief Returns false if Coords are equivalent*/
    bool operator!=(const Coord & rhs) const;
    /** \brief Returns true if Coords are equivalent*/
    bool operator<(const Coord & rhs) const;
    bool operator>(const Coord & rhs) const;
    bool operator<=(const Coord & rhs) const;
    bool operator>=(const Coord & rhs) const;
    /** @} */
    
    //Mathematical
    Coord operator-(const Coord & rhs) const; //Elementwise subtraction
    Coord operator+(const Coord & rhs) const; //Elementwise addition
    Coord & operator-=(const Coord & rhs);
    Coord & operator+=(const Coord & rhs);
    double dot(const Coord & rhs) const; //dot product of two coords
    Coord  cross(const Coord & rhs) const;//Cross product. Creates new coord
    
    //Shifts the coordinate by the passed in values. A lot like += 
    Coord & shiftBy(const double * shift_dist);
    Coord & shiftBy(const Coord & shift_dist);

    //Scale the coord by n
    virtual Coord & scale(const double n);
    
    //Sets the coords so its length is 1
    Coord & normalize();

    //Element access 
    double & operator[](size_t idx);
    const double & operator[](size_t idx) const;
    double dim() const {return dim_;}

    //Distance from origin
    double len() const;
    double norm() const;
    double norm1() const;
    double norm2() const;
    double normInf() const;
    
    void print(const char * ps = NULL) const;

    ~Coord();
  };
}
#endif  
