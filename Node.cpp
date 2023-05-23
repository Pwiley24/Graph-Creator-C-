#include <iostream>
#include <vector>
#include "Node.h"

using namespace std;

Node::Node(){
  point = 'A';
}

void Node::setPoint(char newPt){
  point = newPt;
}

char Node::getPoint(){
  return point;
}

void Node::addWeight(int w){
  weightList.push_back(w);
}

int Node::getWeight(Node* endPt){
  int index = 0;
  vector<Node*>::iterator ptr;
  for(ptr = connectList.begin(); ptr < connectList.end(); ptr++){
    //find the point it is connected to
    //find the index of this point
    if((*ptr) == endPt){
      break; 
    }
    index++;
  }

  //find corresponding index of weightList
  return weightList[index];
  
}

void Node::addConnection(Node* connecting){
  connectList.push_back(connecting);
}
