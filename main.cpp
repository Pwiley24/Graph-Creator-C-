#include <iostream>
#include <vector>
#include <cstring>
#include "Node.h"

using namespace std;

int main(){
  bool running = true;
  vector<Node*> pointList; //contains nodes present in graph

  while(running){
    char input[10];
    cout << "Enter a command (ADD, QUIT)" << endl;
    cin.get(input, 10);
    cin.ignore(10, '\n');

    //Adding to Graph
    if(strcmp(input, "ADD") == 0){ //adding a vertex/node or edge to the graph
      cout << "Adding a vertex or an edge? (VERTEX or EDGE)" << endl;
      cin.get(input, 10);
      cin.ignore(10, '\n');

      if(strcmp(input, "VERTEX") == 0){//adding vertext-> create a new node
	char point;
	cout << "Enter a single character label for your vertex (ex. A, B, C)" << endl;
	cin >> point;

	//create the vertex
	Node* newVertex = new Node();
	newVertex->setPoint(point);
	
	//add new vertex to point list
	pointList.push_back(newVertex);
       
	
      }else if(strcmp(input, "EDGE") == 0){//adding edge-> enter two nodes to connect
	char point1;
	char point2;
	cout << "Enter the start point:" << endl;
	cin >> point1;
	cout << "Enter the end point:" << endl;
	cin >> point2;

	//check that first and second points are in the graph
	Node* node1 = NULL;
	Node* node2 = NULL;
	vector<Node*>::iterator ptr;
	for(ptr = pointList.begin(); ptr < pointList.end(); ptr++){
	  if((*ptr)->getPoint() == point1){
	    node1 = *ptr;
	  }else if((*ptr)->getPoint() == point2){
	    node2 = *ptr;
	  }
	}

	//add connection and distance between two nodes
	if(node1 != NULL &&
	   node2 != NULL){//both points exist
	  int weight;
	  cout << "Enter the distance between the points:" << endl;
	  cin >> weight;

	  //add connection
	  node1->addConnection(node2);
	  node2->addConnection(node1);

	  //add weight
	  node1->addWeight(weight);
	  node2->addWeight(weight);
	  
	  
	  
	}
	
    
      }

      
      //Quiting program
    }else if(strcmp(input, "QUIT") == 0){ //exit program
      running = false;
    }
    

  }
  

  return 0;
}
