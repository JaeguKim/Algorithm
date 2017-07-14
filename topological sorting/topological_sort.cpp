#include <iostream>
#include <fstream>
#include <string>
#include "adjList.h"

#define WHITE -1
#define GRAY 0
#define BLACK 1
#define MAX_VERTEX 100

using namespace std;

void DFS_visit(int u, int *color, int * p, LinkedList _adjList[],LinkedList &output)
{
    color[u] = GRAY;
    for (Node * temp = _adjList[u].getRoot()->head; temp != NULL; temp = temp->next)
    {
        if (color[temp->vertex] == WHITE)
        {
            p[temp->vertex] = u;
            DFS_visit(temp->vertex, color, p, _adjList,output);
        }
    }
    color[u] = BLACK;
    output.createPreNode(u);
}

void Topological_sort(int V_num, int *color, int *p, LinkedList _adjList[], LinkedList &output)
{
    for (int u = 1; u <= V_num; u++)
    {
        color[u] = WHITE;
        p[u] = NULL;
    }
    for (int u = 1; u <= V_num; u++)
    {
        if (color[u] == WHITE)
            DFS_visit(u, color, p, _adjList,output);
    }
}

int main(void)
{
    ifstream fin;
    string input;
    cin >> input;
    if(fin.fail())
        cout << "File failed to open." << endl;
    cout << "Enter Input File Name : ";
    fin.open(input);
    
    int V_num, E_num;
    LinkedList output;
    
    fin >> V_num >> E_num;
    
    int color[MAX_VERTEX], p[MAX_VERTEX];
    LinkedList _adjList[MAX_VERTEX];
    
    int input_v1, input_v2;
    for (int i = 0; i < E_num; i++)
    {
        fin >> input_v1 >> input_v2;
        _adjList[input_v1].createNode(input_v2);
    }
    
    Topological_sort(V_num, color, p, _adjList,output);
    
    for (Node * temp = output.getRoot()->head; temp != NULL; temp = temp->next)
    {
        cout << temp->vertex << " ";
    }
    cout << endl;
    
}


