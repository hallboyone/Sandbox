#ifndef DICT_TREE
#define DICT_TREE

namespace HB1{
  class DictTree{
  public:
    DictTree();
    ~DictTree();
    
    void addWord(const char * word, int len);
    char * findCompletion(const char * seed, bool resetSearch);
    
  private:
    class DictNode{
    public:
      bool eow_; //Is this node an end of a word
      DictNode * branchNodes_[36]; //one for each letter and digit

      DictNode();
      void addWord(char * word);
      int findCompletion(char * seed, char * dest, int skips);
      ~DictNode();
    };
    DictNode * root_;
    int tryNum_;
    int maxDepth_;
  };
}
#endif
