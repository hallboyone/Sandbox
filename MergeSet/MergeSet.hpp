#ifndef MERGESET
#define MERGESET

template <class MOO>
class MergeSet{
public:
  class MON{
  public:
    MOO data_;
    MON * r_;
    MON * l_;
    MON(const MOO & data): data_(data){
      r_ = NULL;
      l_ = NULL;
    }
  };

  MergeSet(){
    root_ = NULL;
    sz_ = 0;
  }
  //Add MOO_t to the bst using recursion. Merge if duplicate found
  MOO * insert(const MOO & new_el){
    MON ** add_here = &root_;
    while (*add_here != NULL){
      if (new_el == (*add_here)->data_) {
	(*add_here)->data_.merge(new_el);
	return &((*add_here)->data_);
      }
      else if (new_el < (*add_here)->data_) add_here = &(*add_here)->l_;
      else add_here = &(*add_here)->r_;
    }
    
    (*add_here) = new MON(new_el);
    sz_++;
    return &((*add_here)->data_);
  }

  void printNodes(){
    printNodes(root_);
  }
  
  ~MergeSet(){
    destroy(root_);
    return;
  }
	      
private:
  MON * root_;
  unsigned int sz_;

  void printNodes(MON * node){
    if (node != NULL){
      printNodes(node->l_);
      node->data_.print();
      printNodes(node->r_);
    }
  }
  
  void destroy(MON * node){
    if (node != NULL){
      destroy(node->l_);
      destroy(node->r_);
      delete node;
    }
    return;
  }

};
#endif
