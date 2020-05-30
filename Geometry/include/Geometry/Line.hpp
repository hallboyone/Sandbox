#ifndef LINE_HPP
#define LINE_HPP

#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Geometry>

#include <iostream>
#include <cmath>
#include <iomanip> //setprecision

#define COORD_TOL 10e-100
#define PI  3.14159265358979323846

namespace SharkPlot{
  
  /** Global typedef used to hold the diminsion*/
  typedef unsigned int dim_t;

  template <dim_t D> class Line;
  template <dim_t D> std::ostream& operator<<(std::ostream & os, const Line<D>& ln);
  
  
  /** A class representing a single, straight, directed line.
   *
   * The line consists of a \link #root_ root\endlink and a \link #tip_ tip\endlink
   * which specify the start and end points of the line. Various transformations
   * and operations can be carried out on the line accourding the the methods below.
   * @tparam DIM A uint specifying the diminsion the line is in. 
   */
  template <dim_t D>
  class Line{
  private:    
    /** Coordinate representing the starting point of the line*/
    Eigen::Matrix<double, D, 1> root_;
    /** Coordinate representing the ending point of the line*/
    Eigen::Matrix<double, D, 1> tip_;
  public:
    /** Typedef of the Eigen Matrix specilization used as the #root_ and #tip_*/
    typedef Eigen::Matrix<double, D, 1> Coord;

    /** @name Member access
     *  Functions used to access the #root_ and #tip_ members 
     */
    ///@{
    /** \brief Returns a ref to the #root_*/
    Coord & root(){return root_;}
    /** \brief Returns a ref to the #tip_*/
    Coord & tip() {return  tip_;}
    /** \brief Returns a const ref to the #root_*/
    const Coord & root()const {return root_;}
    /** \brief Returns a const ref to the #tip_*/
    const Coord & tip() const {return  tip_;}
    ///@}
    
    /** @name Member setting
     *  Functions used to set the #root_ and #tip_ members 
     */
    ///@{
    /** \brief Updates the value of #root_ to match the passed in #Coord
     * @param r #Coord object that #root_ will be set to 
     **/
    void setRoot(const Coord & r){ root_ = r;}
    /** \brief Updates the value of #tip_ to match the passed in #Coord
     * @param t #Coord object that #tip_ will be set to 
     **/
    void setTip (const Coord & t){ tip_ = t;}
    ///@}

    /** @name Norm operations
     * Methods that implement various norm operations on the line
     */
    ///@{
    /** \brief Return the line's 2-norm */
    double len() const {return (root_ - tip_).norm();}
    /** \brief Return the line's 2-norm */
    double norm() const {return len();}
    /** \brief Return the line's p-norm */
    template <int p>
    double lpNorm() const {
      Coord diff = root_-tip_;
      return diff.template lpNorm<p>();}
    ///@}

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
      if (lock_root) tip_ = root_ + n*(tip_ - root_);
      else{
	root_ *= n;
	tip_  *= n;
      }
    }
    /** Scales to line so that its 2-norm is 1
     * @param lock_root If set to true, the line is scaled by only moving the #tip_.
     * Else, the #root_ and #tip_ are scaled evenly.
     */
    void normalize(bool lock_root = false){scale(1/len(), lock_root);}
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

    /** \brief Reverse the #root_ and #tip_ Coords */
    void flip() {
      Coord tmp = root_;
      root_ = tip_;
      tip_ = tmp;
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

#endif //LINE_HPP
