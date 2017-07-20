#include <iostream>
#include <fstream>

using namespace std;

int parent[500];
int v1[500];
int v2[500];
int e[500];

void simpleUnion(int i, int j)
//Replace the disjoint sets with roots i and j, i! = j with //their union
{
   parent[ i ] = j;
}

int simpleFind(int i)
//find the root of the tree containing element i.
{
   while( parent[ i ] >= 0 ) i = parent[ i ];
   return i;
}

void weightedUnion(int i, int j)
//Union sets with roots i and j, i ¡Á j, using the weighting rule.
//parent[ i ] = - count[ i ] and parent[ j ] = - count[ j ].
{ 
   int temp = parent[ i ] + parent[ j ];
   if( parent[ i ] > parent[ j ] ){ // i has fewer nodes
   parent[ i ] = j;
   parent[ j ] = temp;
	}
   else{ // j has fewer nodes (or i and j have the same number of nodes)
   parent[ j ] = i;
   parent[ i ] = temp;
	}
}

int main(void)
{
	int _vertex;
	int _edge;

	ifstream inFile("input2.txt");
	inFile >> _vertex;
	inFile >> _edge;

	for (int i = 1; i<=_vertex; i++)
	{
		parent[i] = -1;
	}

	int input_vertex1;
	int input_vertex2;
	int input_edge;
	int p,q;
	int add_cnt = 0;
	while (1)
	{
		inFile >> input_vertex1;
		inFile >> input_vertex2;
		inFile >> input_edge;
		p = simpleFind(input_vertex1);
		q = simpleFind(input_vertex2);
		if (p != q)
		{
			weightedUnion(p,q);
			v1[add_cnt] = input_vertex1;
			v2[add_cnt] = input_vertex2;
			e[add_cnt] = input_edge;
			add_cnt++;
		}

		if (add_cnt == _vertex-1)
			break;
	}

	for (int i = 0; i<add_cnt; i++)
	{
		cout << v1[i] << " ";
		cout << v2[i] << " ";
		cout << e[i] << " ";
		cout << endl;
	}
}
	
//}Procedural kruskal(n, m: integers; E :set_of_edges; var F : set_of_edges);
//Var  i,  j : index;
//      p, q : set_pointer;
//        e   : edge
//{ sort m edges of E;
//  F=¨ª;
//  initial(n);    //Initialize n disjoint sets.//
//  repeat
//       e=next edge;
//       (i, j ) =e;
//       p=find(i);
//       q=find(j);
//      if  p¡Áq then {merge (p, q); add e to F; } 
//  until  |F|=n-1;
//}
//