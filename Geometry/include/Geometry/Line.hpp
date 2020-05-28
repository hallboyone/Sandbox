#ifndef LINE_HPP
#define LINE_HPP

#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Geometry>

#include <iostream>
#include <cmath>
#include <iomanip> //setprecision

#define COORD_TOL 10e-100

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
    /** Typedef of the Eigen Matrix specilization used as the #root_ and #tip_*/
    typedef Eigen::Matrix<double, D, 1> Coord;
    
    /** Coordinate representing the starting point of the line*/
    Eigen::Matrix<double, D, 1> root_;
    /** Coordinate representing the ending point of the line*/
    Eigen::Matrix<double, D, 1> tip_;
  public:
    /** @name Member access
     *  Functions used to access the #root_ and #tip_ members 
     */
    ///@{
    /** Returns a ref to the #root_*/
    Coord & root(){return root_;}
    /** Returns a ref to the #tip_*/
    Coord & tip() {return  tip_;}
    /** Returns a const ref to the #root_*/
    const Coord & root()const {return root_;}
    /** Returns a const ref to the #tip_*/
    const Coord & tip() const {return  tip_;}
    ///@}
    
    /** @name Member setting
     *  Functions used to set the #root_ and #tip_ members 
     */
    ///@{
    /** Updates the value of #root_ to match the passed in #Coord
     * @param r #Coord object that #root_ will be set to 
     **/
    void setRoot(const Coord & r){ root_ = r;}
    /** Updates the value of #tip_ to match the passed in #Coord
     * @param t #Coord object that #tip_ will be set to 
     **/
    void setTip (const Coord & t){ tip_ = t;}
    ///@}

    /** @name Norm operations
     * Methods that implement various norm operations on the line
     */
    ///@{
    /** Return the line's 2-norm */
    double len() const {return (root_ - tip_).norm();}
    /** Return the line's 2-norm */
    double norm() const {return len();}
    /** Return the line's inf-norm */
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
}//Sharkplot

#endif //LINE_HPP
