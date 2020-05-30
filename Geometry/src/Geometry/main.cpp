#include <iostream>

#include <Geometry/Line.hpp>

int main(){
  SharkPlot::Line<3> l1;
  l1.root() << 1, 3, -5;
  l1.normalize();
  l1.setRoot(Eigen::Vector3d(1,0,0));
  l1.setTip(Eigen::Vector3d(1,0,2));
  l1.normalize();
  
  l1.setRoot(Eigen::Vector3d(1,0,0));
  l1.setTip(Eigen::Vector3d(1,0,2));
  l1.normalize(true);
  std::cout<<l1<<std::endl;

  SharkPlot::Line<4> l2;
  l2.root() << 0,0,0,0;
  l2.tip() << 1,1,1,1;
  std::cout<<l2<<std::endl;

  SharkPlot::Line<3> l3(l1);
  l3.tip() << 1, 2, 3;
  std::cout<<l1<<std::endl<<l3<<std::endl;
  std::cout<<l3.lpNorm<1>()<<" "<<l3.lpNorm<Eigen::Infinity>()<<std::endl;

  std::cout<<(l3<l1)<<std::endl;

  l1.root() << 1,2,3;
  l1.tip() << 4,5,6;
  l3.root() << 7,8,9;
  l3.tip() << 10,11,12;

  std::cout<<"l1 = "<<l1<<std::endl;
  std::cout<<"l3 = "<<l3<<std::endl;
  std::cout<<"l1<l3 = "<<(l1<l3)<<std::endl;
  std::cout<<"l1<=l3 = "<<(l1<=l3)<<std::endl;
  std::cout<<"l1>l3 = "<<(l1>l3)<<std::endl;
  std::cout<<"l1>=l3 = "<<(l1>=l3)<<std::endl;
  std::cout<<"l1==l3 = "<<(l1==l3)<<std::endl;
  std::cout<<"l1!=l3 = "<<(l1!=l3)<<std::endl;

  l1.root() << 1,2,3;
  l1.tip() << 4,5,6;
  l3.root() << 0,8,9;
  l3.tip() << 10,11,12;

  std::cout<<"l1 = "<<l1<<std::endl;
  std::cout<<"l3 = "<<l3<<std::endl;
  std::cout<<"l1<l3 = "<<(l1<l3)<<std::endl;
  std::cout<<"l1<=l3 = "<<(l1<=l3)<<std::endl;
  std::cout<<"l1>l3 = "<<(l1>l3)<<std::endl;
  std::cout<<"l1>=l3 = "<<(l1>=l3)<<std::endl;
  std::cout<<"l1==l3 = "<<(l1==l3)<<std::endl;
  std::cout<<"l1!=l3 = "<<(l1!=l3)<<std::endl;

  l1.root() << 1,2,3;
  l1.tip()  << 4,5,6;
  l3.root() << 1,8,9;
  l3.tip()  << 10,11,12;

  std::cout<<"l1 = "<<l1<<std::endl;
  std::cout<<"l3 = "<<l3<<std::endl;
  std::cout<<"l1<l3 = "<<(l1<l3)<<std::endl;
  std::cout<<"l1<=l3 = "<<(l1<=l3)<<std::endl;
  std::cout<<"l1>l3 = "<<(l1>l3)<<std::endl;
  std::cout<<"l1>=l3 = "<<(l1>=l3)<<std::endl;
  std::cout<<"l1==l3 = "<<(l1==l3)<<std::endl;
  std::cout<<"l1!=l3 = "<<(l1!=l3)<<std::endl;

  l1.root() << 1,1,1;
  l1.tip()  << 1,1,1;
  l3.root() << 1,1,1;
  l3.tip()  << 1,1,1;

  std::cout<<"l1 = "<<l1<<std::endl;
  std::cout<<"l3 = "<<l3<<std::endl;
  std::cout<<"l1<l3 = "<<(l1<l3)<<std::endl;
  std::cout<<"l1<=l3 = "<<(l1<=l3)<<std::endl;
  std::cout<<"l1>l3 = "<<(l1>l3)<<std::endl;
  std::cout<<"l1>=l3 = "<<(l1>=l3)<<std::endl;
  std::cout<<"l1==l3 = "<<(l1==l3)<<std::endl;
  std::cout<<"l1!=l3 = "<<(l1!=l3)<<std::endl;

  l1.root() << 1,1,1;
  l1.tip()  << 1,1,0;
  l3.root() << 1,1,1;
  l3.tip()  << 1,1,1;

  std::cout<<"l1 = "<<l1<<std::endl;
  std::cout<<"l3 = "<<l3<<std::endl;
  std::cout<<"l1<l3 = "<<(l1<l3)<<std::endl;
  std::cout<<"l1<=l3 = "<<(l1<=l3)<<std::endl;
  std::cout<<"l1>l3 = "<<(l1>l3)<<std::endl;
  std::cout<<"l1>=l3 = "<<(l1>=l3)<<std::endl;
  std::cout<<"l1==l3 = "<<(l1==l3)<<std::endl;
  std::cout<<"l1!=l3 = "<<(l1!=l3)<<std::endl;

  std::cout<<"l1.root->l3 = "<<(l1.links2Root(l3))<<std::endl;
  std::cout<<"l1.tip->l3 = "<<(l1.links2Tip(l3))<<std::endl;
  l1.root() << 1,1,1;
  l1.tip()  << 1,1,0;
  l3.root() << 1,1,1;
  l3.tip()  << 1,1,0;
  std::cout<<"l1 = "<<l1<<std::endl;
  std::cout<<"l3 = "<<l3<<std::endl;
  std::cout<<"l1.root->l3 = "<<(l1.links2Root(l3))<<std::endl;
  std::cout<<"l1.tip->l3 = "<<(l1.links2Tip(l3))<<std::endl;

  //Assignment
  l3.root()  << 10,10,10;
  l3.tip()  << 0,0,0;
  std::cout<<"Pre assignement: "<<l1<<"!="<<l3<<std::endl;
  l1 = l3;
  std::cout<<"Post assignement: "<<l1<<"=="<<l3<<std::endl;
  l3.tip()[2] = 3.14159265;
  std::cout<<"Changed l3\n";
  std::cout<<"l1 = "<<l1<<std::endl;
  std::cout<<"l3 = "<<l3<<std::endl;

  SharkPlot::Line<2> l_2d;
  l_2d.root() << 0,0;
  l_2d.tip()  << 1,0;
  std::cout<<"theta("<<l_2d<<") = "<<l_2d.theta()<<std::endl;
  l_2d.tip()  << 0,1;
  std::cout<<"theta("<<l_2d<<") = "<<l_2d.theta()<<std::endl;
  l_2d.tip() << -1,0;
  std::cout<<"theta("<<l_2d<<") = "<<l_2d.theta()<<std::endl;
  l_2d.tip() << 0,-1;
  std::cout<<"theta("<<l_2d<<") = "<<l_2d.theta()<<std::endl;
}
