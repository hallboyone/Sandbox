#ifndef CURVE_HPP
#define CURVE_HPP

#include <Geometry/Line.hpp>

#include <iostream>
#include <cmath>
#include <iomanip> //setprecision
#include <vector>

namespace SharkPlot{
  template <dim_t D> class Curve;
  //template <dim_t D> std::ostream& operator<<(std::ostream & os, const Line<D>& ln);
  
  
  /** A class representing a Curve made up of line segments
   *
   * The line consists of a \link #root_ root\endlink and a \link #tip_ tip\endlink
   * which specify the start and end points of the line. Various transformations
   * and operations can be carried out on the line accourding the the methods below.
   * @tparam DIM A uint specifying the diminsion the line is in. 
   */
  template <dim_t D>
  class Curve{
  private:
    /** Vector of line segments*/
    std::vector<Line<D> > segments_;
    
  public:
    typedef Line<D>::Coord Coord;
    
    /** @name Member access
     *  Functions used to access the #root_ and #tip_ members 
     */
    ///@{
    /** \brief Returns a ref to the #root_ of the first segments*/
    Coord & root(){return segments_[0].root();}
    /** \brief Returns a ref to the #tip_*/
    Coord & tip() {return segments_.back().tip();}
    /** \brief Returns a const ref to the #root_*/
    const Coord & root()const {return segments_[0].root();}
    /** \brief Returns a const ref to the #tip_*/
    const Coord & tip() const {return segments_.back().tip();}
    ///@}

    /** \brief Return the curve's length*/
    double len() const {
      double length = 0;
      for(const Line<D> & ln : segments_) {
	length += ln.len();
      }
      return length;
    }

    /** @name Transformations
     * Methods implementing various transformations on the object
     */
    ///@{
    /** Scales the line by n
     * @param n Amount to scale the line by. If very small, a warning is printed.
     * @param lock_root If set to true, the line is scaled by only moving the #tip_.
     * Else, the #root_ and #tip_ are scaled evenly.
     */
    void scale(double n, bool lock_root = false){
      if (fabs(n) < COORD_TOL)
	std::cerr<<"Warning: Scaling line by very small value. "
		 <<"May lead to numerical errors.\n";
      if (lock_root){
	Coord shift_dist(0,0);
	Coord pre_scale_tip;
	for (Line<D> & ln : segments_){
	  pre_scale_tip = ln.tip();
	  ln += shift_dist;
	  ln.scale(n, true);
	  shift_dist += ln.tip() - pre_scale_tip;
	}
      }
      else{
	for (Line<D> & ln : segments_){
	  ln.scale(n);
	}
      }
    }
    /** Scales to line so that its 2-norm is 1
     * @param lock_root If set to true, the line is scaled by only moving the #tip_.
     * Else, the #root_ and #tip_ are scaled evenly.
     */
    void normalize(bool lock_root = false){scale(1/len(), lock_root);}

    /** \brief Reverse the direction of the curve */
    void flip(){
      for (Line<D> & ln : segments_){
	ln.flip(n);
      }
    }
    ///@}

    /** @name Relational operators
     * Compares edges element wise starting with the first dim in #root_ and going
     * through the last dim in #tip_. 
     */
    ///@{
    /** \brief Returns true if the first non-equal dim of object is less than same dim in rhs*/ 
    bool operator<(const Line<D> & rhs){
      if (coordEqual(root_, rhs.root())) return coordSmaller(tip_, rhs.tip());
      else return coordSmaller(root_, rhs.root());
    }
    /** \brief Returns true if the first non-equal dim of object is greater than same dim in rhs*/
    bool operator>(const Line<D> & rhs){
      if (coordEqual(root_, rhs.root())) return coordSmaller(rhs.tip(), tip_);
      else return coordSmaller(rhs.root(), root_);
    }
    /** \brief Returns true if all values are equal*/
    bool operator==(const Line<D> & rhs){
      return coordEqual(root_, rhs.root()) && coordEqual(tip_, rhs.tip());
    }
    /** \brief Returns true if edges match either > or ==*/
    bool operator>=(const Line<D> & rhs){
      return (*this==rhs) || (*this) > rhs;
    }
    /** \brief Returns true if edges match either < or ==*/
    bool operator<=(const Line<D> & rhs){
      return (*this==rhs) || (*this) < rhs;
    }
    /** \brief Returns true if any coords do not math ==*/
    bool operator!=(const Line<D> & rhs){
      return !(*this==rhs);
    }
    /** \brief Checks if the lhs #Coord is smaller than the rhs.*/
    static bool coordSmaller(const Coord & lhs, const Coord & rhs){
      for(dim_t i = 0; i<D; i++){
	if (fabs(lhs(i) - rhs(i)) > COORD_TOL) return lhs(i) < rhs(i);
      }
      return false;
    }
    /** \brief Checks if two #Coord objects are equal in value*/
    static bool coordEqual(const Coord & lhs, const Coord & rhs){
      for(dim_t i = 0; i<D; i++){
	if (fabs(lhs(i) - rhs(i)) > COORD_TOL) return false;
      }
      return true;
    }
    ///@}
    /** @name Mathematical operators
     * Implementation of simple math functions such as addition.
     */
    ///@{
    /** Returns an edge shifted by the values of Coord*/
    Line<D> operator+(const Coord & rhs) const{
      Line<D> result(*this);
      result.root() += rhs;
      result.tip() += rhs;
      return result;
    }
    /** Returns an edge shifted by the values of Coord*/
    Line<D> operator-(const Coord & rhs) const{
      Line<D> result(*this);
      result.root() -= rhs;
      result.tip() -= rhs;
      return result;
    }
    /** Returns this object shifted by the values of Coord*/
    Line<D> & operator+=(const Coord & rhs){
      root_ += rhs;
      tip_  += rhs;
      return *this;
    }
    /** Returns this object shifted by the values of Coord*/
    Line<D> & operator-=(const Coord & rhs){
      root_ -= rhs;
      tip_  -= rhs;
      return *this;
    }
    ///@}

    /**
     *  Checks if \p ln can link to #root_. 
     * \returns 1 if the #root_ is equal to the rhs #tip_
     * \returns -1 if the #root_ is equal to the rhs #root_
     * \returns 0 else
     */
    int links2Root(const Line<D>& ln) const {
      if (coordEqual(ln.tip(), root_)) return 1;
      else if (coordEqual(ln.root(), root_)) return -1;
      else return 0;
    }
    /**
     * Checks if \p ln can link to #tip_. 
     * \returns 1 if the #root_ is equal to the rhs #tip_
     * \returns -1 if the #root_ is equal to the rhs #root_
     * \returns 0 else
     */
    int links2Tip(const Line<D>& ln) const {
      if (coordEqual(ln.root(), tip_)) return 1;
      else if (coordEqual(ln.tip(), tip_)) return -1;
      else return 0;
    }

    /** \brief Returns the angle between 0 and 1 of a 2D edge around the z-axis.
     * The positive direction is CCW with 0 being the positive x-axis and 0.25 being
     * the positive y-axis
     */
    double theta();

    /**\brief Write line to ostream object */
    friend std::ostream& operator<< <D>(std::ostream& os, const Line<D>& ln);
  };
  
  template <dim_t D>
  std::ostream & operator<<(std::ostream & os, const Line<D>& ln){
    if (D > 3){
      os<<"[ln: Dim="<<D<<": len="<<ln.len()<<"]\n";
    }
    else {
      os<<std::setprecision(5)<<"[";
      for(dim_t i = 0; i<D; i++){
	os<<ln.root()[i];
	if (i<D-1) os<<",";
      }
      os<<"]--[";
      for(dim_t i = 0; i<D; i++){
	os<<ln.tip()[i];
	if (i<D-1) os<<",";
      }
      os<<"]"<<std::setprecision(10);
    }
    return os;
    }

  template <>
  double Line<2>::theta(){
    Coord ln = tip_ - root_;
    if(fabs(ln[0]) < COORD_TOL && fabs(ln[1]) < COORD_TOL){
      throw(std::domain_error("Attempted to get theta for (0,0)"));
    }
    double theta = atan2(ln[1],ln[0]) / (2*PI);
    if(theta < 0) theta += 1;
    return theta;
  }
}//Sharkplot

#endif //CURVE_HPP
