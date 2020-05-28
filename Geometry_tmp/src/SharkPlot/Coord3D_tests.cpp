#include <SharkPlot/Geometry.hpp>
#include <SharkPlot/Tests.hpp>
#include <assert.h>
#include <math.h>

void testCoord3D(){
  SharkPlot::Coord3D c1(-2);
  SharkPlot::Coord3D c2(1, 0, 0);
  SharkPlot::Coord3D c3(0, 1, 0);
  SharkPlot::Coord3D c4(1);
  SharkPlot::Coord3D c5(3);
  std::cout<<c1<<std::endl;

  std::cout<<c2<<" x "<<c3<<" = "<<c2.cross(c3)<<std::endl;
  std::cout<<c3<<" x "<<c2<<" = "<<c3.cross(c2)<<std::endl;
  std::cout<<c2<<" x "<<c5.scale(5)<<" = "<<c2.cross(c5)<<std::endl;

  std::cout<<c4<<" == "<<c2<<" = "<<(c4==c2)<<std::endl;
}
