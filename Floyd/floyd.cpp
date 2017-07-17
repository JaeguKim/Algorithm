//
//  floyd.cpp
//  algo
//
//  Created by 김재구 on 2017. 7. 17..
//  Copyright © 2017년 김재구. All rights reserved.
//

#include <iostream>
#include <vector>
#include <stack>
#define MAX 987654321
#define NIL -1
using namespace std;

vector<vector<pair<int,int>>> D_P;
stack<int> P;

int main(){
    int n,m,x;
    scanf("%d %d %d", &n,&m,&x);
    D_P.resize(n+1);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            D_P[i].push_back(make_pair(MAX,NIL));
            if (i == j) D_P[i][j].first = 0;
        }
    }
    for (int i = 0; i < m; i++){
        int u,v,w;
        scanf("%d %d %d", &u,&v,&w);
        D_P[u-1][v-1].first = w;
        D_P[u-1][v-1].second = u-1;
    }
    
    printf("****Before Table****\n");
    printf("table D\n");
    for (int i = 0; i<n; i++){
        for (int j = 0; j < n; j++){
            printf(D_P[i][j].first == MAX ? "INF\t" : "%d\t", D_P[i][j].first);
        }
        printf("\n");
    }
    printf("table P\n");
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            printf(D_P[i][j].second == NIL ? "\NIL\t" : "%d\t", D_P[i][j].second+1);
        }
        printf("\n");
    }
    
    for (int k = 0; k < n; k++){
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                if (D_P[i][j].first > D_P[i][k].first + D_P[k][j].first)
                {
                    D_P[i][j].first = D_P[i][k].first + D_P[k][j].first;
                    D_P[i][j].second = D_P[k][j].second;
                }
            }
            
        }
    }
    
    printf("****After Table****\n");
    printf("table D\n");
    for (int i = 0; i<n; i++){
        for (int j = 0; j < n; j++){
            printf(D_P[i][j].first == MAX ? "INF\t" : "%d\t", D_P[i][j].first);
        }
        printf("\n");
    }
    printf("table P\n");
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            printf(D_P[i][j].second == NIL ? "NIL\t" : "%d\t", D_P[i][j].second+1);
        }
        printf("\n");
    }
    
    printf("\n");
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (D_P[i][j].second == NIL) continue;
            printf("%d부터 %d까지 경로 : ",i+1, j+1);
            int prev = j;
            P.push(j+1);
            while (i != D_P[i][prev].second){
                prev = D_P[i][prev].second;
                P.push(prev+1);
            }
            printf("%d",i+1);
            while (!P.empty()){
                printf("-%d",P.top());
                P.pop();
            }
            printf("\n");
        }
    }
    
    int max = 0;
    for (int i = 0; i < n; i++){
        if (i == x-1) continue;
        int time = D_P[i][x-1].first + D_P[x-1][i].first;
        if (time > max)
            max = time;
    }
}
