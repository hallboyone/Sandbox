#ifndef DICT_TREE
#define DICT_TREE

class DictTree{
private:
  class DictNode{
  public:
    bool EOW; //Is this node an end of a word
    DictNode * branchNodes_[36]; //one for each letter and digit

    DictNode();
    void addWord(char * word);
    int findCompletion(char * seed, char * dest, int skips);
    ~DictNode();
  };
  DictNode * root;
  int num2Skip;

public:
  DictTree();
  ~DictTree();

  int addWord(const char * word);
}
#endif
