//This project creates a graph of nodes.
//You can add edges and vertexs that are connected by weights.
//This program can calculate the shortest path between two nodes and
//display the path and the distance traveled.
//Author: Paige Wiley
//Date: 06-05-23

#include <iostream>
#include <iterator>
#include <vector>
#include <limits.h>
#include <cstring>
#include "Node.h"

using namespace std;

void printMatrix(vector<Node*> pointList);
void findShortest(Node* source, Node* endpt, vector<Node*> pointList);

int main(){
  bool running = true;
  vector<Node*> pointList; //contains nodes present in graph

  while(running){
    char input[10];
    cout << "Enter a command (ADD, PRINT, DELETE, TRAVEL, QUIT)" << endl;
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

        int index = 0;
	vector<Node*>::iterator ptr;
	for(ptr = pointList.begin(); ptr < pointList.end(); ptr++){
	  if((*ptr)->getPoint() == name){
	    deleting = (*ptr);
            pointList.erase(pointList.begin() + index);
	  }else{
            ++index;
          }
	}

	if(deleting != NULL){
          //remove a connection from each node in remaining points
          vector<Node*>::iterator ptr;
          for(ptr = pointList.begin(); ptr < pointList.end(); ptr++){
	     (*ptr)->deleteConnection(deleting);
          }
        }else{
          cout << "No point found." << endl;
        }
	
      }else if(strcmp(input, "EDGE") == 0){
        char name1;
        Node* point1 = NULL;
        char name2;
        Node* point2 = NULL;
        cout << "Enter the first Vertex" << endl;
        cin >> name1;
        cin.ignore(5, '\n');
        cout << "Enter the second Vertex" << endl;
        cin >> name2;
        cin.ignore(5, '\n');
     
        vector<Node*>::iterator ptr;
        for(ptr = pointList.begin(); ptr < pointList.end(); ptr++){
           if((*ptr)->getPoint() == name1){
             point1 = (*ptr);
           }else if((*ptr)->getPoint() == name2){
             point2 = (*ptr);
           }
        }

        if(point1 != NULL &&
           point2 != NULL){//both given points exist
          point1->deleteConnection(point2);
          point2->deleteConnection(point1);
        }
      }
    }else if(strcmp(input, "TRAVEL") == 0){//finding the shortest path
      Node* source = NULL;
      char sourceName;
      Node* endpt = NULL;
      char endName;
      cout << "Enter the source point" << endl;
      cin >> sourceName;
      cin.ignore(5, '\n');

      cout << "Enter the end point" << endl;
      cin >> endName;
      cin.ignore(5, '\n');

      vector<Node*>::iterator ptr;
      for(ptr = pointList.begin(); ptr < pointList.end(); ptr++){
	if((*ptr)->getPoint() == sourceName){
	  source = (*ptr);
	}else if((*ptr)->getPoint() == endName){
	  endpt = (*ptr);
	}
      }
      if(source != NULL &&
	 endpt != NULL){
	//find the shortest path from source to all other vertexes.
	findShortest(source, endpt, pointList);
      }else{
	cout << "No known vertex in graph" << endl;
      }

    }
  }
  return 0;
}


/*
 *
 */
void findShortest(Node* source, Node* endpt, vector<Node*> pointList){
  vector<Node*> visited;
  visited.push_back(source);
  vector<Node*> unvisited;
  vector<Node*> path;
  
  
  //set all nodes to a distance of 0 (this is infinity) and assign unvisited
  source->setDistance(0);
  vector<Node*>::iterator ptr;
  for(ptr = pointList.begin(); ptr < pointList.end(); ptr++){
    if((*ptr) != source){
      cout << "point " << (*ptr)->getPoint() << endl;
      (*ptr)->setDistance(INT_MAX);
      unvisited.push_back((*ptr));
    }
  }

  Node* current = source;
  while(unvisited.empty() == false){//while unvisited is not empty
    if(current != source){
      current = unvisited[0];
    }
    cout << "current: " << current->getPoint() << endl;
    vector<Node*> connectList;
    connectList = current->getConnection();
    vector<Node*>::iterator ptr;
    for(ptr = connectList.begin(); ptr < connectList.end(); ptr++){
      //set the distance
      cout << "connectino: " << (*ptr)->getPoint() << endl;
      if(current->getWeight((*ptr)) + current->getDistance() < (*ptr)->getDistance()){
	(*ptr)->setDistance(current->getDistance() + current->getWeight((*ptr)));
	(*ptr)->setPrevious(current);
      }
      cout << "point's weight " << (*ptr)->getDistance() << endl;
    }

    
    
    if(current != source){
      //remove from unvisited and move to visited
      visited.push_back(current);
      vector<Node*>::iterator ptr;
      int index = 0;
      for(ptr = unvisited.begin(); ptr < unvisited.end(); ptr++){
	if((*ptr) == current){
	  unvisited.erase(unvisited.begin() + index);
	}
	index++;
      }
    }else{
      current = unvisited[0];
    }
    
  }
  source->setDistance(0);

  if(endpt->getDistance() == INT_MAX){
    cout << "No connection between points" << endl;
  }else{
    current = endpt;
    while(current->getPrevious() != NULL){
      path.insert(path.begin(), current);
      if(current->getPrevious() != NULL){
	current = current->getPrevious();
      }else{
	current = NULL;
      }
    }
    path.insert(path.begin(), source);
    cout << "Distance: " << endpt->getDistance() << endl;

    //print out the path:
    vector<Node*>::iterator pa;
    cout << "Path: ";
    for(pa = path.begin(); pa < path.end(); pa++){
      cout << (*pa)->getPoint() << " ";
    }
    
    cout << " " << endl;

  }

  
  
  //reset all points to infinity:
  vector<Node*>::iterator i;
  for(i = pointList.begin(); i < pointList.end(); i++){
    (*i)->setDistance(INT_MAX);
  }
 
  
  

  
  
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
