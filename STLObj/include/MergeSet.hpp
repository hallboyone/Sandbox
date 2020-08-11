#ifndef MERGE_SET
#define MERGE_SET

template <class MOO>
class MergeSet{
public:
  /**
   * A single node of the BST containing a single instance of a MOO object and 
   * the left and right pointers.
   **/
  class MON{
  public:
    MOO data;
    MON * right;
    MON * left;

    MON(const MOO & d): data(d), right(NULL), left(NULL){}
  };

  MergeSet(): root_(NULL), sz_(0){}
  
  //Add MOO_t to the bst using recursion. Merge if duplicate found
  MOO * insert(const MOO & new_el){
    MON ** add_here = findNode(new_el); // &root_;
    if (*add_here != NULL) {
      (*add_here)->data.merge(new_el);
      return &((*add_here)->data);
    }
    else {
      (*add_here) = new MON(new_el);
      sz_++;
      return &((*add_here)->data);
    }
  }

  void erase(const MOO & el){
    MON ** upstream_pp = findNode(el);
    MON *  node_p  = *upstream_pp;
    if (node_p == NULL) return;

    if (node_p->left != NULL) {
      MON** sub_node_pp = &(node_p->left);
      while ((*sub_node_pp)->right != NULL){
	sub_node_pp = &((*sub_node_pp)->right);
      }

      *upstream_pp = *sub_node_pp;
      *sub_node_pp = (*sub_node_pp)->left;
      (*upstream_pp)->left = node_p->left;
      (*upstream_pp)->right = node_p->right;
    }
    else {
      *upstream_pp = node_p->right;
    }

    delete node_p;
    sz_--;
  }

  MOO * find(const MOO & el){
    return &((findNode(el))->data);
  }

  unsigned int size(){ return sz_; }

  void clear(){
    destroy(root_);
    sz_ = 0;
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
      printNodes(node->left);
      node->data.print();
      printNodes(node->right);
    }
  }
  
  void destroy(MON * node){
    if (node != NULL){
      destroy(node->left);
      destroy(node->right);
      delete node;
    }
    return;
  }

  /**
   * Iterate through BST looking for el. Return pointer to pointer to matching
   * node or pointer to NULL pointer if not found
   **/
  MON ** findNode(const MOO & el){
    MON ** search_ptr = &root_;
    while (*search_ptr != NULL){
      if (el == (*search_ptr)->data) {
	((*search_ptr)->data).print();
	std::cout<<" = ";
	el.print();
	std::cout<<"\n";
	  
        break;
      }
      else if (el < (*search_ptr)->data) {
	search_ptr = &(*search_ptr)->left;
      }
      else {
	search_ptr = &(*search_ptr)->right;
      }
    }
    return search_ptr;
  }
};
#endif
