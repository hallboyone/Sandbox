#include <SharkPlot/Geometry.hpp>
#include <SharkPlot/Tests.hpp>
#include <assert.h>
#include <math.h>

void testCoord2D(){
  std::cout<<" Running Coord2D tests...\n";
  std::cout<<" Constructors...\n";
  double vals[2] = {2313.341, 43.2};
  SharkPlot::Coord2D c_1;
  SharkPlot::Coord2D c_2(0.1231, -3.1415);
  SharkPlot::Coord2D c_3(-2);
  SharkPlot::Coord2D c_4(vals);
  SharkPlot::Coord2D c_5(c_3);
  c_5.x() = 1;
  std::cout<<" Default: "<<c_1<<std::endl;
  std::cout<<" c_2(0.1231, -3.1415): "<<c_2<<std::endl;
  std::cout<<" c_3(-2): "<<c_3<<std::endl;
  std::cout<<" c_4(vals): "<<c_4<<std::endl;
  std::cout<<" c_5(c_3) -> c_5.x=1: "<<c_5<<std::endl;
  std::cout<<" c_3 after copy: "<<c_3<<std::endl;

  std::cout<<" Element access...\n";
  std::cout<<" c_3[0]: "<<c_3[0]<<std::endl;
  std::cout<<" c_4.x(),c_4.y(): "<<c_4.x()<<","<<c_4.y()<<std::endl;

  
  SharkPlot::Coord c(2);
  SharkPlot::Coord c_3D(3);
  c_3D[0] = 1;
  c_1 = c_3D;
  SharkPlot::Coord2D c1(0,1);
  SharkPlot::Coord2D c1_copy(c1);
  
  assert(fabs(c1.len() - 1) < COORD_TOL);      //[0,1]
  assert(fabs(c1.theta() - 0.25) < COORD_TOL);//[0,1]

  c1_copy.x() = 1; //[1,1]
  c1_copy.normalize();
  assert(fabs(c1_copy.len()-1) < COORD_TOL);
  assert(fabs(c1_copy.theta()-0.125) < COORD_TOL);
  
  assert(!(c1_copy==c1));
  c1_copy = c1;
  assert(c1_copy==c1);

  SharkPlot::Coord2D c2(-1);
  std::cout<<c2<<std::endl;
  c2.y() = 1;
  c1.x() = -21.231;
  std::cout<<c2<<"*"<<c1<<" = "<<c2.dot(c1)<<std::endl;
  
  std::cout<<" All tests passed\n";
}
