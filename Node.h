#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <vector>

using namespace std;

class Node{
 public:
  Node();
  ~Node();
  void setPoint(char newPt);
  char getPoint();
  int getWeight(Node* endPt);
  void addWeight(int w);
  void addConnection(Node* connecting);
  void deleteConnection(Node* deleting);
  void deleteWeight(int index);  
  void setDistance(int num);
  int getDistance();
  void setPrevious(Node* prev);
  Node* getPrevious();
  vector<Node*> getConnection();
  

 private:
  char point;
  vector<Node*> connectList;
  vector<int> weightList;
  int distance;
  Node* previous;
};

#endif
