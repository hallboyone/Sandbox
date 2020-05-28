#include <SharkPlot/Coord/Coord.hpp>

#include <exception>
#include <math.h>     //fabs
#include <iomanip>    // std::setprecision

namespace SharkPlot{
  /**
   * Unit Coord constructor pointing in the norm_dir direction.
   * norm_dir can be positive or negative values ranging from 1 to 
   * dim.
   */
  Coord::Coord(const size_t dim, int norm_dir): dim_(dim){
    if (abs(norm_dir) > dim)
      throw(std::out_of_range("Normal diminsion larger than possible dimensions."));
    vals_ = new double[dim];
    
    if (norm_dir < 0) vals_[abs(norm_dir)-1] = -1;
    else vals_[norm_dir - 1] = 1;
  }
			       
  /**
   * Initializeation constructor creating an Coord with the values in vals
   */
  Coord::Coord(const size_t dim, const double * vals): dim_(dim){
    vals_ = new double[dim];
    for (size_t i = 0; i<dim; i++){
      vals_[i] = vals[i];
    }
  }

  /**
   * Initializeation constructor creating an Coord with the values in vals
   */
  Coord::Coord(const std::vector<double> & val) : dim_(val.size()){
    vals_ = new double[dim_];
    for(size_t i = 0; i<dim_; i++){
      vals_[i] = val[i];
    }
  }

  /**
   * Copy constructor
   */
  Coord::Coord(const Coord & c): dim_(c.dim()){
    vals_ = new double[dim_];
    for (size_t i = 0; i<dim_; i++){
      vals_[i] = c[i];
    }
  }

  Coord & Coord::operator=(const Coord & rhs){
    if (this != &rhs){
      ensureDimsMatch(rhs);
      for (size_t i = 0; i<dim_; i++){
	vals_[i] = rhs[i];
      }
    }
    return *this;
  }
      
    
  //Relationship operators
  bool Coord::operator==(const Coord & rhs) const{
    ensureDimsMatch(rhs);
    for (size_t i = 0; i<dim_; i++){
      if (fabs(vals_[i] - rhs[i]) > COORD_TOL) return false;
    }
    return true;
  }
  
  bool Coord::operator!=(const Coord & rhs) const{
    return !(*this==rhs);
  }
  
  bool Coord::operator<(const Coord & rhs) const{
    ensureDimsMatch(rhs);
    for (size_t i = 0; i<dim_; i++){
      if(fabs(vals_[i] - rhs[i]) > COORD_TOL) return vals_[i] < rhs[i];
    }
    return false; //They are equal
  }
  
  bool Coord::operator>(const Coord & rhs) const{
    ensureDimsMatch(rhs);
    for (size_t i = 0; i<dim_; i++){
      if(fabs(vals_[i] - rhs[i]) > COORD_TOL) return vals_[i] > rhs[i];
    }
    return false; //They are equal
  }
  
  bool Coord::operator<=(const Coord & rhs) const{
    return (*this<rhs || *this==rhs);
  }
  
  bool Coord::operator>=(const Coord & rhs) const{
    return (*this>rhs || *this==rhs);
  }
  
  //Mathematical
  Coord Coord::operator-(const Coord & rhs) const{
    ensureDimsMatch(rhs);
    Coord result(rhs);
    return (result -= *this);
  }
  
  Coord Coord::operator+(const Coord & rhs) const{
    ensureDimsMatch(rhs);
    Coord result(rhs);
    return (result += *this);
  }
  
  Coord & Coord::operator-=(const Coord & rhs){
    ensureDimsMatch(rhs);
    for (size_t i = 0; i<dim_; i++){
      vals_[i] -= rhs[i];
    }
    return *this;
  }
  
  Coord & Coord::operator+=(const Coord & rhs){
    ensureDimsMatch(rhs);
    for (size_t i = 0; i<dim_; i++){
      vals_[i] += rhs[i];
    }
    return *this;
  }
  
  double Coord::dot(const Coord & rhs) const{
    double result = 0;
    ensureDimsMatch(rhs);
    for (size_t i = 0; i<dim_; i++){
      result += vals_[i] * rhs[i];
    }
    return result;
  }
  
  //Shifts the coordinate by the passed in values. A lot like += 
  Coord & Coord::shiftBy(const double * shift_dist){
    for (size_t i = 0; i<dim_; i++){
      vals_[i] += shift_dist[i];
    }
    return *this;
  }
  
  Coord & Coord::shiftBy(const Coord & shift_dist){
    return (*this += shift_dist);
  }

  //Scale the coord by n
  Coord & Coord::scale(const double n){
    for (size_t i = 0; i<dim_; i++){
      vals_[i] *= n;
    }
    return *this;
  }
  
  //Sets the coords so its length is 1
  Coord & Coord::normalize(){
    scale(1/len());
    return *this;
  }

  //Element access 
  double & Coord::operator[](size_t idx){
    if (idx >= dim_) throw std::out_of_range("idx too large for diminsion of Coord");

    return vals_[idx];
  }
  
  const double & Coord::operator[](size_t idx) const{
    if (idx >= dim_) throw std::out_of_range("idx too large for diminsion of Coord");

    return vals_[idx];
  }

  double Coord::norm1() const{
    double n = 0;
    for (size_t i = 0; i<dim_; i++){
      n += fabs(vals_[i]);
    }
    return n;
  }
  
  double Coord::norm2() const{
    double n = 0;
    for (size_t i = 0; i<dim_; i++){
      n += (vals_[i] * vals_[i]);
    }
    return sqrt(n);
  }
  
  double Coord::normInf() const{
    double n = fabs(vals_[0]);
    for (size_t i = 1; i<dim_; i++){
      if (fabs(vals_[i]) > n) n = fabs(vals_[i]);
    }
    return n;
  }

  void Coord::ensureDimsMatch(const Coord & rhs) const{
    if (rhs.dim() != dim_)
      throw std::invalid_argument("Coord diminsions do not match");
  }

  Coord::~Coord(){
    delete []vals_;
  }
}
