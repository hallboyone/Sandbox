#include <iostream>

#include <Geometry/Line.hpp>

int main()
{
  SharkPlot::Line<3> l1;
  l1.root() << 1, 3, -5;
  //std::cout<<l1.root()<<std::endl;
  //std::cout<<l1.len()<<std::endl;
  l1.normalize();
  //std::cout<<l1.len()<<std::endl;
  //std::cout<<l1.root()<<std::endl<<std::endl;
  l1.setRoot(Eigen::Vector3d(1,0,0));
  l1.setTip(Eigen::Vector3d(1,0,2));
  l1.normalize();
  
  //std::cout<<l1.root()<<"|-|"<<l1.tip()<<std::endl<<std::endl;
  l1.setRoot(Eigen::Vector3d(1,0,0));
  l1.setTip(Eigen::Vector3d(1,0,2));
  //std::cout<<l1.root()<<"|-|"<<l1.tip()<<std::endl<<std::endl;
  l1.normalize(true);
  //std::cout<<l1.root()<<"|-|"<<l1.tip()<<std::endl;
  std::cout<<l1<<std::endl;

  SharkPlot::Line<4> l2;
  l2.root() << 0,0,0,0;
  l2.tip() << 1,1,1,1;
  std::cout<<l2<<std::endl;

  SharkPlot::Line<3> l3(l1);
  l3.tip() << 1, 2, 3;
  std::cout<<l1<<std::endl<<l3<<std::endl;
  std::cout<<l3.lpNorm<1>()<<" "<<l3.lpNorm<Eigen::Infinity>()<<std::endl;
}
