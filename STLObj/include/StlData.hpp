#ifndef STL_DATA
#define STL_DATA

#include "Coord.hpp"
#include "MergeSet.hpp"

#include <set>

class StlData {
public:
  typedef Coord<3> Coord3;

  class TriangleEdge;

  class Triangle{
  private:
    const Coord3 norm_;
    TriangleEdge * e_[3];
    int id_;
    static int next_tri_id_;
  public:
    Triangle(Coord3 & n, const Coord3* v1, const Coord3* v2, const Coord3* v3, MergeSet<TriangleEdge> & e_set);
    const Coord3 & norm() const { return norm_; }
    int id(){ return id_; }
    bool operator<(const Triangle & rhs) const;
    void print() const;
  };

  class TriangleEdge{
  private:
    const Coord3 *const v_[2];
    bool first_v_smallest;
    Triangle * t_[2];
  public:
    TriangleEdge(const Coord<3> * v1, const Coord<3> * v2, Triangle * t);
    Triangle * t(int n) const { return t_[n]; };
    const Coord<3> *const vSmall() const{ return v_[1 - first_v_smallest]; };
    const Coord<3> *const vLarge() const{ return v_[first_v_smallest]; };
    void merge(const TriangleEdge & rhs);
    bool operator<(const TriangleEdge & rhs) const;
    bool operator==(const TriangleEdge & rhs) const{
      return (!((*this < rhs)) && !(rhs < (*this)));
    }
    bool operator!=(const TriangleEdge & rhs) const{
      return (*this < rhs || rhs < (*this));
    }
    bool operator>(const TriangleEdge & rhs) const{
      return rhs < (*this);
    }
    void print() const;
  };

  StlData(){
    Coord3 c1(-1,-1, 0);
    Coord3 c2(-1, 1, 0);
    Coord3 c3( 1, 1, 0);
    Coord3 c4( 1,-1, 0);
    Coord3 c5( 0, 0, 2);
  
    Coord3 n1( 0, 0,-1);
    Coord3 n2( 0, 0,-1);
    Coord3 n3( 0, 1, 1);
    Coord3 n4( 1, 0, 1);
    Coord3 n5( 0,-1, 1);
    Coord3 n6(-1, 0, 1);
  
    const Coord<3> * cp1;
    const Coord<3> * cp2;
    const Coord<3> * cp3;
    const Coord<3> * cp4;
    const Coord<3> * cp5;
  
    cp1 = &(*(coords_.insert(c1)).first);
    cp2 = &(*(coords_.insert(c2)).first);
    cp3 = &(*(coords_.insert(c3)).first);
    cp4 = &(*(coords_.insert(c4)).first);
    cp5 = &(*(coords_.insert(c5)).first);

    /*
    std::multiset<Triangle>::iterator tri_it;
    tri_it = triangles_.insert(Triangle(n1));
    tri_it->setCoords(cp1, cp2, cp4, edges_);
    tri_it = triangles_.insert(Triangle(n2));
    tri_it->setCoords(cp2, cp3, cp4, edges_);
    tri_it = triangles_.insert(Triangle(n3));
    tri_it->setCoords(cp2, cp3, cp5, edges_);
    tri_it = triangles_.insert(Triangle(n4));
    tri_it->setCoords(cp3, cp4, cp5, edges_);
    tri_it = triangles_.insert(Triangle(n5));
    tri_it->setCoords(cp1, cp4, cp5, edges_);
    tri_it = triangles_.insert(Triangle(n6));
    tri_it->setCoords(cp1, cp2, cp5, edges_);
    */
    /*
    triangles_.insert(Triangle(n1, cp1, cp2, cp4, edges_));
    triangles_.insert(Triangle(n2, cp2, cp3, cp4, edges_));
    triangles_.insert(Triangle(n3, cp2, cp3, cp5, edges_));
    triangles_.insert(Triangle(n4, cp3, cp4, cp5, edges_));
    triangles_.insert(Triangle(n5, cp1, cp4, cp5, edges_));
    triangles_.insert(Triangle(n6, cp1, cp2, cp5, edges_));
    */

    triangles_.emplace(n1, cp1, cp2, cp4, edges_);
    triangles_.emplace(n2, cp2, cp3, cp4, edges_);
    triangles_.emplace(n3, cp2, cp3, cp5, edges_);
    triangles_.emplace(n4, cp3, cp4, cp5, edges_);
    triangles_.emplace(n5, cp1, cp4, cp5, edges_);
    triangles_.emplace(n6, cp1, cp2, cp5, edges_);
    
    //    edges_.printSet();
    for (std::multiset<Triangle>::iterator it = triangles_.begin(); it != triangles_.end(); ++it){
      it->print();
    }
  }

  
private:
  std::set<Coord3>        coords_;
  std::multiset<Triangle> triangles_;
  MergeSet<TriangleEdge>  edges_;
};

#endif
