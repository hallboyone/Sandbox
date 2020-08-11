#include <array>
#include <set>
#include <vector>
#include <exception>
#include <iostream>
#include <fstream>
#include <string>
#include "Coord.hpp"

class STLData{
private:
  class TriangleEdge;
  class Triangle;
  struct Line_;
  
  //typedef Eigen::Matrix<double, 3, 1> Coord;
  typedef std::set<Coord>::iterator CoordItr;
  typedef std::set<Line_>::iterator LineItr;
  typedef std::array<CoordItr, 2> CoordItrArr;
  typedef std::array<TriangleEdge *, 3> EdgePtr;
  
  typedef std::array<Triangle *, 2> TriPtr;

  class Triangle{
  private:
    EdgePtr edges_;
    Coord norm_;
  public:
    Triangle(Coord & norm, EdgePtr edges): edges_(edges), norm_(norm){
      setEdges();
    }
    void setEdges(){
      std::cout<<"Setting neighbors\n";
      edges_[0]->setAsNeighbor(this);
      edges_[1]->setAsNeighbor(this);
      edges_[2]->setAsNeighbor(this);
    }
  };

  typedef struct Line_{
    CoordItr coords_;
    Line_(){};
    Line_(CoordItr it1, CoordItr it2){
      setCoords(it1, it2);
    }

    Line_ & setCoords(CoordItr it1, CoordItr it2){
      if ((*it1) < (*it2)){
	coords_[0] = it1;
	coords_[1] = it2;
      }
      else {
	coords_[1] = it1;
	coords_[0] = it2;
      }
      return *this;
    }
    
    bool operator<(const Line_ & rhs) const{
      if(*(coords_[0]) != *(rhs.coords_[0])) return *(coords_[0]) < *(rhs.coords_[0]);
      else return *(coords_[1]) < *(rhs.coords_[1]);
    }
  } Line;
    
  class TriangleEdge{
  public:
    std::set<Line>::iterator coord_data_;
    TriPtr neighbors_;
    
    TriangleEdge

    
    void setAsNeighbor(Triangle * tri) const{
      if (neighbors_[0] == NULL) neighbors_[0] = tri;
      else if (neighbors_[1] == NULL) neighbors_[1] = tri;
      else throw(std::exception());
    }
  };

  std::vector<Triangle> triangles_;
  std::vector<TriangleEdge> edges_;
  std::set<Line> lines_;
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
    /*
      1) Read in the 3 coords
      2) Add the 3 coords to set and save iterators
      3) For each combination of points
      | 3.a) Create a line
      | 3.b) Search for line in set of lines
      | 3.c) If set does not contain line
      | | 3.c.1) Create an edge and add to edge vector
      | | 3.c.2) Set the line's pointer to the edge
      | | 3.c.3) Add the line to the set of lines and save its iterator
      | | 3.c.4) Set the edge's itr to the line's iterator
      | Else
      | | 3.c.1) Retrive from the line its pointer to an edge
      | 3.d) Save the pointer to the edge
      4) Create a triangle with the three edge pointers
     */
    EdgePtr new_edges;
    Coord cur_coord;
    Coord norm;
    Line = new_line;
    std::array<std::set<Coord>::iterator, 3> coords_it;

    //Read the norm
    readCoord(f, norm);
    
    //Add each of the 3 coords to the set of coords
    for (size_t i = 0; i<3; i++){
      readCoord(f, cur_coord);
      coords_it[i] = points_.insert(cur_coord).first;
    }
    
    new_edges[0] = createNewEdge(new_line.setCoords(coords_it[0], coord_it[1]));
    new_edges[1] = createNewEdge(new_line.setCoords(coords_it[0], coord_it[2]));
    new_edges[2] = createNewEdge(new_line.setCoords(coords_it[1], coord_it[2]));

    triangles_.push_back(Triangle(norm, new_edges));
  }

  TriangleEdge * createNewEdge(Line & ln){
    /*| 3.b) Search for line in set of lines
      | 3.c) If set does not contain line
      | | 3.c.1) Create an edge and add to edge vector
      | | 3.c.2) Set the line's pointer to the edge
      | | 3.c.3) Add the line to the set of lines and save its iterator
      | | 3.c.4) Set the edge's itr to the line's iterator
      | Else
      | | 3.c.1) Retrive from the line its pointer to an edge
      | 3.d) Save the pointer to the edge*/
    if (lines_.count(ln) == 0){
      edges_.push_back(TriangleEdge(ln));
      ln

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

  
  
    
