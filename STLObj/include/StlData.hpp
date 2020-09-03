/**
 * \class StlData
 *
 * \brief Data structure for STL objects
 *
 * This class provides a low memory data structure for STL file objects. 
 * The coordinates of each vertex are stored in a set. On top of that, there
 * is a MergeSet of TriangleEdge objects, each pointing at the two Coords making
 * up the edge and the two Triangles which neighbor the edge. Finally, there is
 * a Set of Triangles, each with a norm Coord and three TriangleEdge pointers 
 * set to the three edges of the triangle. 
 *
 * \author (last to touch it) $Author: Richard Hall $
 *
 * \version $Revision: 0.1 $
 *
 * \date $Date: 2020/08/12 2:24 $
 *
 */

#ifndef STL_DATA
#define STL_DATA

#include "Coord.hpp"
#include "MergeSet.hpp"

#include <set>
#include <vector>
#include <queue>

/// Global typedef of a single coordinate in 3D
typedef Coord<3> Coord3;

class StlData {
public:

  class TriangleEdge;

  class Triangle{
  private:
    const Coord3 norm_;
    TriangleEdge * e_[3];
    int id_;
    static int next_tri_id_;
  public:
    Triangle(Coord3 & n, const Coord3* v1, const Coord3* v2, const Coord3* v3, MergeSet<TriangleEdge> & e_set);
    Triangle(Coord3 & n): norm_(n) {}

    const Coord3 & norm() const { return norm_; }
    int id() const { return id_; }

    bool operator<(const Triangle & rhs) const;

    void print() const;
    
    void getFaceEdges(std::queue<const Triangle *> & tri_q,
		      std::vector<TriangleEdge *> & face_edges,
		      std::vector<bool> & already_examined) const;    
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
    const Triangle * getNeighbor(const Triangle * caller) const {
      if (t_[0] == caller) return t_[1];
      else return t_[0];
    }
  };

  StlData(){
    /*
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

    triangles_.emplace(n1, cp1, cp2, cp4, edges_);
    triangles_.emplace(n2, cp2, cp3, cp4, edges_);
    triangles_.emplace(n3, cp2, cp3, cp5, edges_);
    triangles_.emplace(n4, cp3, cp4, cp5, edges_);
    triangles_.emplace(n5, cp1, cp4, cp5, edges_);
    triangles_.emplace(n6, cp1, cp2, cp5, edges_);
    */

    Coord3 c0( 2, 0, 0);
    Coord3 c1( 0,-2, 0);
    Coord3 c2(-2, 0, 0);
    Coord3 c3( 0, 2, 0);
    Coord3 c4( 1, 0, 0);
    Coord3 c5( 0,-1, 0);
    Coord3 c6(-1, 0, 0);
    Coord3 c7( 0, 1, 0);
    Coord3 c8( 0, 0, 2);
    Coord3 c9( 0, 0, 1);
  
    Coord3 n0_7( 0, 0,-1);
    Coord3 n11( 1, 1,1);
    Coord3 n8( 1,-1,1);
    Coord3 n10(-1, 1,1);
    Coord3 n9(-1,-1,1);

    const Coord3 * cp0 = &(*(coords_.insert(c0)).first);
    const Coord3 * cp1 = &(*(coords_.insert(c1)).first);
    const Coord3 * cp2 = &(*(coords_.insert(c2)).first);
    const Coord3 * cp3 = &(*(coords_.insert(c3)).first);
    const Coord3 * cp4 = &(*(coords_.insert(c4)).first);
    const Coord3 * cp5 = &(*(coords_.insert(c5)).first);
    const Coord3 * cp6 = &(*(coords_.insert(c6)).first);
    const Coord3 * cp7 = &(*(coords_.insert(c7)).first);
    const Coord3 * cp8 = &(*(coords_.insert(c8)).first);
    const Coord3 * cp9 = &(*(coords_.insert(c9)).first);

    triangles_.emplace(n0_7, cp0, cp1, cp4, edges_);
    triangles_.emplace(n0_7, cp1, cp4, cp5, edges_);
    triangles_.emplace(n0_7, cp1, cp2, cp5, edges_);
    triangles_.emplace(n0_7, cp2, cp5, cp6, edges_);
    triangles_.emplace(n0_7, cp2, cp3, cp6, edges_);
    triangles_.emplace(n0_7, cp3, cp6, cp7, edges_);
    triangles_.emplace(n0_7, cp0, cp3, cp7, edges_);
    triangles_.emplace(n0_7, cp0, cp4, cp7, edges_);
    triangles_.emplace(n8,   cp0, cp1, cp8, edges_);
    triangles_.emplace(n9,   cp1, cp2, cp8, edges_);
    triangles_.emplace(n10,  cp2, cp3, cp8, edges_);
    triangles_.emplace(n11,  cp0, cp3, cp8, edges_);
    triangles_.emplace(n8,  cp4, cp5, cp9, edges_);
    triangles_.emplace(n9,  cp5, cp6, cp9, edges_);
    triangles_.emplace(n10,  cp6, cp7, cp9, edges_);
    triangles_.emplace(n11,  cp4, cp7, cp9, edges_);
    //    edges_.printSet();
    for (std::multiset<Triangle>::iterator it = triangles_.begin(); it != triangles_.end(); ++it){
      it->print();
    }
  }

  void parameterOfFace(Coord3 face_norm){
    std::vector<bool> already_examined(triangles_.size(), false);
    std::vector<TriangleEdge *> face_edges;
    std::queue<const Triangle *> tri_q;
    // 1) Find a triangle with face_norm in triangles and add it to stack
    tri_q.push(&(*(triangles_.find(Triangle(face_norm)))));
    already_examined[tri_q.front()->id()] = true;
    while(!tri_q.empty()){
      // a) Pop the next triangle off the stack
      //tri_q.front()->print();
      tri_q.front()->getFaceEdges(tri_q, face_edges, already_examined);
      tri_q.pop();
    }
    std::cout<<face_edges.size()<<std::endl;
    for(size_t i = 0; i<face_edges.size(); i++){
      face_edges[i]->print();
    }
  }
private:
  std::set<Coord3>        coords_;
  std::multiset<Triangle> triangles_;
  MergeSet<TriangleEdge>  edges_;
};

#endif
