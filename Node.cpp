#include <iostream>
#include <iterator>
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
      return weightList[index]; 
    }
    index++;
  }

  //find corresponding index of weightList
  return 0;
  
}

void Node::addConnection(Node* connecting){
 connectList.push_back(connecting);
}


void Node::deleteConnection(Node* deleting){
cout << "deleting connection" << endl;
 vector<Node*>::iterator ptr;
 int index = 0;
 bool connection = false;
 for(ptr = connectList.begin(); ptr < connectList.end(); ptr++){
   if((*ptr) == deleting){
     connection = true;
     connectList.erase(connectList.begin() + index);
     break;
   }else{
    index++;
  }
 }
cout << "index: " << index << endl;
  if(connection == true){
    deleteWeight(index);
  }

}

void Node::deleteWeight(int index){
cout << "deleting weight" << endl;
   weightList.erase(weightList.begin() + index);//removes 
}

