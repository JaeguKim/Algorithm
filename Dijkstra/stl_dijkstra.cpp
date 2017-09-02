#include <cstdio>
#include <queue>
#include <list>
#include <stack>
#define SIZE 20001
#define INF 987654321
using namespace std;

typedef struct Node
{
    int vertex;
    int edge;
    Node(int v,int e):vertex(v),edge(e){}
}Node;

struct cmp{
    bool operator()(Node a, Node b){
        return a.edge > b.edge;
    }
};


list<Node> li[SIZE];
int d[SIZE];
int p[SIZE];
int num_V,num_E;


void dijstra(int n,int start)
{
    priority_queue<Node,vector<Node>,cmp> pq;

    for (int u = 1; u <= num_V; u++)
    { d[u] = INF; }
    
    d[start] = 0;
    p[start] = -1;
    
    pq.push(Node(start,d[start]));
    
    while(!pq.empty())
    {
        struct Node u = pq.top();
        pq.pop();
        if (u.edge > d[u.vertex])
            continue;
       
        list<Node> :: iterator temp;
        for (temp = li[u.vertex].begin(); temp != li[u.vertex].end(); temp++)
        {
            if (d[(*temp).vertex] > (*temp).edge + d[u.vertex])
            {
                p[(*temp).vertex] = u.vertex;
                d[(*temp).vertex] = (*temp).edge + d[u.vertex];
                pq.push(*temp);
            }
        }
    }
}

int main(void)
{
    scanf("%d%d",&num_V,&num_E);
    int temp_V1, temp_V2, tempEdge;
    
    for (int i = 0; i< num_E; i++)
    {
        scanf("%d%d%d",&temp_V1,&temp_V2,&tempEdge);
        li[temp_V1].push_back(Node(temp_V2,tempEdge));
    }
    int start,end;
    scanf("%d%d",&start,&end);
    dijstra(num_V,start);
    printf("%d\n",d[end]);
    stack<int> s;
    s.push(end);
    int temp = p[end];
    while (temp != -1){
        s.push(temp);
        temp = p[temp];
    }
    printf("%d\n",s.size());
    while (!s.empty()){
        printf("%d ",s.top());
        s.pop();
    }
    
    
}
