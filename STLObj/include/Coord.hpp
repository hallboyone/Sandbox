#ifndef COORD
#define COORD

#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Geometry>

typedef unsigned int dim_t;
template <dim_t D> class Coord;
template <dim_t D> std::ostream& operator<<(std::ostream& os, const Coord<D>& c);

template <dim_t D>
class Coord : public Eigen::Matrix<double, D, 1>{
private:
  const double double_tol_ = 10e-10;
  friend std::ostream& operator<< <D>(std::ostream& os, const Coord<D>& c); 

  static bool eq(double d1, double d2){
    return fabs(d1-d2) < 10e-10;
  }
public:
  Coord(): Eigen::Matrix<double, D, 1>(){}
  Coord(const double & n1, const double & n2): Eigen::Matrix<double, D, 1>(n1, n2){};
  Coord(const double & n1, const double & n2, const double & n3):
    Eigen::Matrix<double, D, 1>(n1, n2, n3){};
  bool operator<(const Coord & rhs) const{
    for(dim_t i = 0; i<D; i++){
      if(!eq((*this)[i], rhs[i])) return (*this)[i] < rhs[i];
    }
    return false;
  }
  bool operator>(const Coord & rhs) const{
    return rhs<(*this);
  }
  bool operator==(const Coord & rhs) const{
    for(dim_t i = 0; i<D; i++){
      if (!eq((*this)[i], rhs[i])) return false;
    }
    return true;
  }
  bool operator!=(const Coord & rhs) const{
    return !((*this)==rhs);
  }
};

template <dim_t D>
std::ostream& operator<<(std::ostream& os, const Coord<D>& c){
  os <<"[ "<<c[0];
  for (dim_t i = 1; i<D; i++) os << ", "<<c[i];
  os<<" ]";
  return os;
}
#endif
