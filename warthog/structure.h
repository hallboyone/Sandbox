


class building{
 private:
  class vertex{
    int x;
    int y;
    vertex * point_cw;
    vertex * point_ccw;
  };

  vertex * head;

 public:

 building():head(NULL) {}
  
  building(std::vector 
