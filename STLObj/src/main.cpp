#include <array>
#include <set>
#include <vector>
#include <exception>
#include <iostream>
#include <fstream>
#include <string>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Geometry>

class Coord : public Eigen::Matrix<double, 3, 1>{
private:
  const double double_tol_ = 10e-10;
  friend std::ostream& operator<<(std::ostream& os, const Coord& c);

  static bool eq(double d1, double d2){
    return fabs(d1-d2) < 10e-10;
  }
public:
  Coord(): Eigen::Matrix<double, 3, 1>(){}
  Coord(int n1, int n2, int n3): Eigen::Matrix<double, 3, 1>(n1, n2, n3){};
  bool operator<(const Coord & rhs) const{
    if(!eq((*this)[0], rhs[0])) return (*this)[0] < rhs[0];
    if(!eq((*this)[1], rhs[1])) return (*this)[1] < rhs[1];
    if(!eq((*this)[2], rhs[2])) return (*this)[2] < rhs[2];
    return false;
  }
  bool operator>(const Coord & rhs) const{
    if(!eq((*this)[0], rhs[0])) return (*this)[0] > rhs[0];
    if(!eq((*this)[1], rhs[1])) return (*this)[1] > rhs[1];
    if(!eq((*this)[2], rhs[2])) return (*this)[2] > rhs[2];
    return false;
  }
  bool operator==(const Coord & rhs) const{
    return
      eq((*this)[0], rhs[0]) &&
      eq((*this)[1], rhs[1]) &&
      eq((*this)[2], rhs[2]);
  }
  bool operator!=(const Coord & rhs) const{
    return !((*this)==rhs);
  }
};

std::ostream& operator<<(std::ostream& os, const Coord& c){
  os << "[ "<<c[0]<<", "<<c[1]<<", "<<c[2]<<" ]";
  return os;
}

class STLData{
private:
  class TriangleEdge;
  class Triangle;

  //typedef Eigen::Matrix<double, 3, 1> Coord;
  typedef std::array<std::set<TriangleEdge>::iterator, 3> EdgeIterators;
  typedef std::array<std::set<Coord>::iterator, 2> CoordIterators;
  typedef std::array<Triangle const *, 2> TriPointers;

  class Triangle{
  private:
    EdgeIterators edges_;
    Coord norm_;
  public:
    Triangle(Coord & norm, EdgeIterators edges): edges_(edges), norm_(norm){
      setEdges();
    }
    void setEdges(){
      std::cout<<"Setting neighbors\n";
      edges_[0]->setAsNeighbor(this);
      edges_[1]->setAsNeighbor(this);
      edges_[2]->setAsNeighbor(this);
    } 
  };
  
  class TriangleEdge{
  public:
    CoordIterators coords_;
    TriPointers neighbors_;
    
    TriangleEdge(std::set<Coord>::iterator & it1, std::set<Coord>::iterator & it2){
      if ((*it1) < (*it2)){
	coords_[0] = it1;
	coords_[1] = it2;
      }
      else {
	coords_[1] = it1;
	coords_[0] = it2;
      }
      neighbors_[0] = NULL;
      neighbors_[1] = NULL;
    }

    bool operator<(const TriangleEdge & rhs) const{
      if(*(coords_[0]) != *(rhs.coords_[0])) return *(coords_[0]) < *(rhs.coords_[0]);
      else return *(coords_[1]) < *(rhs.coords_[1]);
    }
    
    void setAsNeighbor(Triangle * tri) const{
      if (neighbors_[0] == NULL) neighbors_[0] = &tri;
      else if (neighbors_[1] == NULL) neighbors_[1] = &tri;
      else throw(std::exception());
    }
  };

  std::vector<Triangle> triangles_;
  std::set<TriangleEdge> edges_;
  std::set<Coord> points_;

public:
  STLData(){
    std::ifstream f;
    f.open("test_data.txt");
    readTestData(f);
    f.close();
  }

  void readTestData(std::ifstream & f){
    std::string cur_ln;
    size_t num_tri;
    
    //First line is # triangles
    getline(f, cur_ln);
    num_tri = std::stoul(cur_ln);
    std::cout<<"Triangle Count: "<<num_tri<<std::endl;

    //Read in the next triangles
    for (size_t i = 0; i<num_tri; i++){
      readTriangle(f);
    }
    std::cout<<"Num Tri    = "<<triangles_.size()<<std::endl;
    std::cout<<"Num Edges  = "<<edges_.size()<<std::endl;
    std::cout<<"Num Points = "<<points_.size()<<std::endl;
  }

  void readTriangle(std::ifstream & f){
    EdgeIterators new_edges;
    Coord cur_coord;
    Coord norm;
    std::array<std::set<Coord>::iterator, 3> coords_it;

    //Read the norm
    readCoord(f, norm);
    
    //Add each of the 3 coords to the set of coords
    for (size_t i = 0; i<3; i++){
      readCoord(f, cur_coord);
      coords_it[i] = points_.insert(cur_coord).first;
    }

    new_edges[0] = edges_.insert(TriangleEdge(coords_it[0], coords_it[1])).first;
    new_edges[1] = edges_.insert(TriangleEdge(coords_it[0], coords_it[2])).first;
    new_edges[2] = edges_.insert(TriangleEdge(coords_it[1], coords_it[2])).first;

    triangles_.push_back(Triangle(norm, new_edges));
  }

  void readCoord(std::ifstream & f, Coord & c){
    std::string buf;
    std::getline(f, buf, ',');
    c[0] = std::stod(buf);
    std::getline(f, buf, ',');
    c[1] = std::stod(buf);
    std::getline(f, buf);
    c[2] = std::stod(buf);
  }
};

int main(){
  STLData obj;
  return 1;
}

  
  
    
