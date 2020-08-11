#include <array>
#include <set>
#include <vector>
#include <exception>
#include <iostream>
#include <fstream>
#include <string>
#include "LinePtr.hpp"
#include "TriPtr.hpp"
#include "MergeSet.hpp"

int main(){
  std::set<Coord<3>> c;
  std::multiset<TriPtr> tri;
  MergeSet<LinePtr> ln;
  
  Coord<3> c1(-1,-1, 0);
  Coord<3> c2(-1, 1, 0);
  Coord<3> c3( 1, 1, 0);
  Coord<3> c4( 1,-1, 0);
  Coord<3> c5( 0, 0, 2);
  
  Coord<3> n1( 0, 0,-1);
  Coord<3> n2( 0, 0,-1);
  Coord<3> n3( 0, 1, 1);
  Coord<3> n4( 1, 0, 1);
  Coord<3> n5( 0,-1, 1);
  Coord<3> n6(-1, 0, 1);
  
  const Coord<3> * c_p_1;
  const Coord<3> * c_p_2;
  const Coord<3> * c_p_3;
  const Coord<3> * c_p_4;
  const Coord<3> * c_p_5;
  
  c_p_1 = &(*(c.insert(c1)).first);
  c_p_2 = &(*(c.insert(c2)).first);
  c_p_3 = &(*(c.insert(c3)).first);
  c_p_4 = &(*(c.insert(c4)).first);
  c_p_5 = &(*(c.insert(c5)).first);

  std::multiset<TriPtr>::iterator tri_it;
  tri_it = (tri.insert(TriPtr(n1))).first;
  tri_it->addData(c_p_1, c_p_2, c_p_4, ln);
  tri_it = (tri.insert(TriPtr(n2))).first;
  tri_it->addData(c_p_2, c_p_3, c_p_4, ln);
  tri_it = (tri.insert(TriPtr(n3))).first;
  tri_it->addData(c_p_2, c_p_3, c_p_5, ln);
  tri_it = (tri.insert(TriPtr(n4))).first;
  tri_it->addData(c_p_3, c_p_4, c_p_5, ln);
  tri_it = (tri.insert(TriPtr(n5))).first;
  tri_it->addData(c_p_1, c_p_4, c_p_5, ln);
  tri_it = (tri.insert(TriPtr(n6))).first;
  tri_it->addData(c_p_1, c_p_2, c_p_5, ln);
  /*
  LinePtr ln1(c_p_1, c_p_2);
  LinePtr ln2(c_p_1, c_p_4);
  LinePtr ln3(c_p_1, c_p_5);
  LinePtr ln4(c_p_2, c_p_3);
  LinePtr ln5(c_p_2, c_p_4);
  LinePtr ln6(c_p_2, c_p_5);
  LinePtr ln7(c_p_3, c_p_4);
  LinePtr ln8(c_p_3, c_p_5);
  LinePtr ln9(c_p_4, c_p_5);

  ln.insert(ln1);
  ln.insert(ln2);
  ln.insert(ln3);
  ln.insert(ln4);
  ln.insert(ln5);
  ln.insert(ln6);
  ln.insert(ln7);
  ln.insert(ln8);
  ln.insert(ln9);
  */
  
  ln.printSet();
  return 1;
}

  
  
    
