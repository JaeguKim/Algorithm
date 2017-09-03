#include <cstdio>
#include <vector>
using namespace std;
int adj[1001][1001];
int visit[1001];

void dfs(int cur,int N){
    visit[cur] = 1;
    for (int i=1;i<=N;i++)
    {
        if (adj[cur][i] != 0 && visit[i] == 0){
            dfs(i,N);
        }
    }
}

int main(void){
    int N,M;
    scanf("%d%d",&N,&M);
    
    for (int i=0;i<M;i++){
        int from,to;
        scanf("%d%d",&from,&to);
        adj[from][to] = 1;
        adj[to][from] = 1;
    }
    int cnt=0;
    for (int i=1; i<=N;i++){
        if (visit[i] == 0){
            dfs(i,N);
            cnt++;
        }
    }
    printf("%d",cnt);
}
