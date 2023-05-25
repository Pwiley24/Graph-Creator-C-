#include <iostream>
#include <vector>
#include <cstring>
#include "Node.h"

using namespace std;

void printMatrix(vector<Node*> pointList);

int main(){
  bool running = true;
  vector<Node*> pointList; //contains nodes present in graph

  while(running){
    char input[10];
    cout << "Enter a command (ADD, PRINT, QUIT)" << endl;
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
	cin.ignore(5, '\n');

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
	cin.ignore(5, '\n');
	
	cout << "Enter the end point:" << endl;
	cin >> point2;
	cin.ignore(5, '\n');

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
	  cin.ignore(5, '\n');

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

      //printing the matrix table
    }else if(strcmp(input, "PRINT") == 0){
      printMatrix(pointList);


      //Deleting an edge/vertex:
    }else if(strcmp(input, "DELETE") == 0){
      cout << "Deleting a VERTEX or an EDGE?" << endl;
      cin.get(input, 10);
      cin.ignore(10, '\n');

      if(strcmp(input, "VERTEX") == 0){
	Node* deleting = NULL;
	char name;
	cout << "Enter the Vertex to delete:" << endl;
	cin >> name;
	cin.ignore(5, '\n');

	vector<Node*>::iterator ptr;
	for(ptr = pointList.begin(); ptr < pointList.end(); ptr++){
	  if((*ptr)->getValue() == name){
	    deleting = (*ptr);
	  }
	}

	if(deleting != NULL){
	  deleteVertex();//start here
	}
	
      }else if(strcmp(input, "EDGE") == 0){
	deleteEdge();
      }
    }
    

  }
  

  return 0;
}


/*
 * Prints a row and column of the points from the pointList vector.
 * Then prints the weight between each point.
 * EX)
 *   A B C
 * A 0 3 0
 * B 3 0 2 
 * C 0 2 0
 */
void printMatrix(vector<Node*> pointList){
  
  //print out the row of points:
  vector<Node*>::iterator ptr;
  cout << "  ";
  for(ptr = pointList.begin(); ptr < pointList.end(); ptr++){
    cout << (*ptr)->getPoint() << " ";
  }
  cout << " " << endl;
  //print out columns with weights starting with a point:

  vector<Node*>::iterator i;
  int index = 1;
  for(i = pointList.begin(); i < pointList.end(); i++){
    cout << (*i)->getPoint() << " ";
    for(int x = 0; x < pointList.size(); x++){
      Node* endPoint = pointList[x];

      if(endPoint == (*i)){
	cout << "0 ";
      }else if((*i)->getWeight(endPoint) != 0){
	cout << (*i)->getWeight(endPoint) << " ";
      }else{
	cout << "0 ";
      }
    }
    cout << " " << endl;
  }
    
    
  
}
