
#include <iostream>
#include <fstream>
#include <vector>
#include<iterator>
#include<stdlib.h>
#include<list>
#include<bits/stdc++.h>

//Use CODE::BLOCKS 16.01 ide, for compiling.

using namespace:: std;
//globally declared variable
int vertex = 5;
vector<int>adjList[1000];
vector<int>::iterator ptr;
void printPath(int , int , bool[] ,int[] , int&);
ofstream myfile;
bool pathAvailable = false;


/*Adding to adjList*/
void addEdge(int u,int v){
adjList[u].push_back(v);
adjList[v].push_back(u);
}
/*Creating adjList*/
void createGraph(int vertex){
 for(int i =0;i<vertex;i++){
    cout<<" \nAdjacency List of Vertex " << i << " is ";
    for (ptr = adjList[i].begin(); ptr < adjList[i].end(); ptr++)
        cout<<" -> "<<*ptr;
    }
 }
 /*To initalize visited as false*/
  void verticesNotVisited(bool visited[],int vertex)
  {

     for(int i=0;i<vertex;i++){
        visited[i]=false;
     }
  }


/*To find a path between two vertex*/
//Check if there is a path and also inputs the path in a text file
 void isPath(int v, int w)
{

    bool *visited = new bool[vertex];
    int *path = new int[vertex];
    int path_index = 0;
    verticesNotVisited(visited,vertex);
    printPath(v, w, visited, path, path_index);

    }



void printPath(int str, int des, bool visited[],
                              int path[], int &path_index)
{

    visited[str] = true;
    path[path_index] = str;
    path_index++;
    if (str == des)
    {
            pathAvailable = true;
            myfile.open ("Graph path holder.txt");//Output Everything to Graph path holder
            myfile<<"The path found is ";
            for (int i = 0; i<path_index; i++){
               cout << path[i]<<" ";
               myfile<<path[i];

    }
        cout << endl;
    }
    else
    {
         vector<int>::iterator j;
        for (j = adjList[str].begin(); j != adjList[str].end(); ++j)
            if (!visited[*j])
                printPath(*j, des, visited, path, path_index);
    }

}
//To go through each vertex of a graph
void check( int v, vector<bool> &visited)
{
	visited[v] = true;
	vector<int>::iterator i;
	for (i = adjList[v].begin(); i != adjList[v].end(); ++i)
	{
		if (!visited[*i])
			check(*i, visited);
	}
}
// check if graph is strongly connected or not
bool isConnected(int vertex)
{
	// do for every vertex
	for (int i = 0; i < vertex; i++)
	{

		vector<bool> visited(vertex);

		check( i, visited);
		if (find(visited.begin(), visited.end(), false)
				!= visited.end())
			return false;//If it does not find the adjacent vertex return false
	}
	return true;

}

/*Implementing BFS starting from vertex i*/
void BFS(int i)
{
    bool *visited = new bool[vertex];
 verticesNotVisited(visited,vertex);
 queue<int>q;
 visited[i]=true;
 q.push(i);
 vector<int>::iterator ptr;
 myfile<<"\nFollowing is Breadth First Traversal : ";
  while(!q.empty())
    {
        i = q.front();
        cout << i <<" ";
          myfile<<i;

        q.pop();
      for (ptr = adjList[i].begin(); ptr != adjList[i].end(); ++ptr)
        {
            if (!visited[*ptr])
            {
                visited[*ptr] = true;
                q.push(*ptr);
          }
        }
    }

}
/*Implementing DFS starting from vertex i*/
void DFS(int i)
{
  bool *visited = new bool[vertex];
 verticesNotVisited(visited,vertex);
    stack<int> u;
    u.push(i);
    myfile<<"\nFollowing is Depth First Traversal : ";
      while (!u.empty())
    {
        i = u.top();
        u.pop();
        if (!visited[i])
        {

            cout << i << " ";
            myfile<<i;
            visited[i] = true;
        }
        vector<int>::iterator ptr;
        for ( ptr = adjList[i].begin(); ptr != adjList[i].end(); ++ptr)
            if (!visited[*ptr])
                u.push(*ptr);

    }

}

int main(){
//add edges
   addEdge(0, 1);
    addEdge(1,2);
    addEdge(2, 3);
   
   createGraph(vertex);
   cout<<"\nEnter the vertices to find path ";
   myfile<<"\nEnter the vertices to find path ";
   int v;
   int w;
  cin>>v>>w;
        cout <<"Following is a paths from " << v
         << " to " << w << ": ";
      isPath(v,w);
      //to check if there is a path
    if(pathAvailable==true){
        myfile<<"\nThere is a path";
    }
    else{
        myfile<<"\nThere is no path";
    }
     if(pathAvailable==true){
        cout<<"There is a path";
    }
    else{
        cout<<"There is no path";
    }
        int startBFS;
        cout<<"\nEnter the start vertex for BFS ";
         myfile<<"\nEnter the start vertex for BFS ";
        cin>>startBFS;
        myfile<<startBFS;
         cout <<"Following is Breadth First Traversal ";
         BFS(startBFS);
         int startDFS;
        cout<<"\nEnter the start vertex for DFS ";
        myfile<<"\nEnter the start vertex for DFS ";
         cin>>startDFS;
         myfile<<startDFS;
         cout << "Following is Depth First Traversal : ";
         DFS(startDFS);
          if (isConnected(vertex))
		cout<< "\nGraph is Strongly Connected";
	     else
		cout << "\nGraph is not Strongly Connected";

          if (isConnected(vertex))
		myfile<< "\nGraph is Strongly Connected";
	     else
		myfile << "\nGraph is not Strongly Connected";

     return 0;
}

