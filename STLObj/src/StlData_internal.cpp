#include "StlData.hpp"

int StlData::Triangle::next_tri_id_ = 0;

StlData::Triangle::Triangle(Coord3 & n, const Coord3* v1, const Coord3* v2, const Coord3* v3, MergeSet<TriangleEdge> & e_set): norm_(n){
  id_ = next_tri_id_;
  next_tri_id_++;
  e_[0] = e_set.insert(TriangleEdge(v1, v2, this));
  e_[1] = e_set.insert(TriangleEdge(v1, v3, this));
  e_[2] = e_set.insert(TriangleEdge(v2, v3, this));
}

bool StlData::Triangle::operator<(const Triangle & rhs) const{
  return (norm_ < rhs.norm());
}

void StlData::Triangle::print() const{
  std::cout<<"Tri #"<<id_<<"\n";
  e_[0]->print();
  e_[1]->print();
  e_[2]->print();
  return;
}

/**
 * For each edge joining triangles with different norms, add its address to
 * face_edges. Add the neighbor accross all other edges to the tri_q if not
 * already examined (as told by its slot inside already_examined)
 */
void StlData::Triangle::getFaceEdges(std::queue<const Triangle *> & tri_q,
				     std::vector<TriangleEdge *> & face_edges,
				     std::vector<bool> & already_examined) const{
  const Triangle * neighbor_tri;
  for (int i=0; i<3; i++){
    neighbor_tri = e_[i]->getNeighbor(this);
    if (neighbor_tri->norm() != norm_){ //add edge to face_edges
      face_edges.push_back(e_[i]);
    }
    else if (!already_examined[neighbor_tri->id()]) { //add tri to stack
      tri_q.push(neighbor_tri);
      already_examined[neighbor_tri->id()] = true;
    }
  }
}

StlData::TriangleEdge::TriangleEdge(const Coord<3> * v1, const Coord<3> * v2, Triangle * t): v_{v1,v2}{
  t_[0] = t;
  t_[1] = NULL;
  if (v_[0] < v_[1]) first_v_smallest = true;
  else first_v_smallest = false;
}

void StlData::TriangleEdge::merge(const TriangleEdge & rhs){
  if (*this != rhs) throw std::invalid_argument("Trying to merge unequal edges");
  if (t_[1] != NULL) throw std::invalid_argument("Edge used by more than 2 tri");
  if (rhs.t(1) != NULL) throw std::invalid_argument("Edge used by more than 2 tri");
  
  t_[1] = rhs.t(0);
}

bool StlData::TriangleEdge::operator<(const TriangleEdge & rhs) const{
  if (*(this->vSmall()) != *(rhs.vSmall()))
    return ((*(this->vSmall())) < (*(rhs.vSmall())));
  else
    return ((*(this->vLarge())) < (*(rhs.vLarge())));
}

void StlData::TriangleEdge::print() const{
  std::cout<<*(vSmall())<<"--"<<*(vLarge());
  if (t_[0] != NULL && t_[1] != NULL){
    std::cout<<" between t"<<((t_[0])->id())<<" and t"<<((t_[1])->id());
  }
  std::cout<<std::endl;
}
