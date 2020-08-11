#ifndef TRI_PTR
#define TRI_PTR

#include "fwrd_decl.hpp"
#include "MergeSet.hpp"

class TriPtr{
private:
  const Coord<3> norm_;
  LinePtr * e_[3];
  int tri_num;
  static int next_tri_num;
public:
  TriPtr(Coord<3> & n): norm_(n){
    tri_num = next_tri_num;
    next_tri_num++;
  }

  void addData(const Coord<3> * v1, const Coord<3> * v2, const Coord<3> * v3, MergeSet<LinePtr> & edge_set){
    e_[0] = edge_set.insert(LinePtr(v1, v2, this));
    e_[1] = edge_set.insert(LinePtr(v1, v3, this));
    e_[2] = edge_set.insert(LinePtr(v2, v3, this));
  }
  
  const Coord<3> & norm() const { return norm_; }
  int id(){ return tri_num; }
  
  bool operator<(const TriPtr & rhs) const{
    return (norm_ < rhs.norm());
  }
};

int TriPtr::next_tri_num = 1;
#endif
