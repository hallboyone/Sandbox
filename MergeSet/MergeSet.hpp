#ifndef MERGESET
#define MERGESET

template <class MOO>
class MergeSet{
public:
  class MON{
  public:
    MOO data_;
    MON * r_ptr_;
    MON * l_ptr_;
    MON(const MOO & data): data_(data), r_ptr_(NULL), l_ptr_(NULL){}
  };

  MergeSet(): root_(NULL), sz_(0){}
  
  //Add MOO_t to the bst using recursion. Merge if duplicate found
  MOO * insert(const MOO & new_el){
    MON ** add_here = &root_;
    while (*add_here != NULL){
      if (new_el == (*add_here)->data_) {
	(*add_here)->data_.merge(new_el);
	return &((*add_here)->data_);
      }
      else if (new_el < (*add_here)->data_) add_here = &(*add_here)->l_ptr_;
      else add_here = &(*add_here)->r_ptr_;
    }
    
    (*add_here) = new MON(new_el);
    sz_++;
    return &((*add_here)->data_);
  }

  void printSet(){
    std::cout<<"MergeSet with "<<sz_<<" elements.\n";
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
      printNodes(node->l_ptr_);
      node->data_.print();
      printNodes(node->r_ptr_);
    }
  }
  
  void destroy(MON * node){
    if (node != NULL){
      destroy(node->l_ptr_);
      destroy(node->r_ptr_);
      delete node;
    }
    return;
  }

};
#endif
