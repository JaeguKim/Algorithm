#include <cstdio>
#include <deque>
using namespace std;

int main(void)
{
    int N;
    scanf("%d",&N);
    deque<pair<int,int>> _deque;
    
    for (int i=0; i<N;i++){
        int M,X;
        int rank = 0;
        scanf("%d %d",&M,&X);
        for (int j=0;j<M;j++)
        {
            int pri;
            scanf("%d",&pri);
            _deque.push_back((make_pair(j,pri)));
        }
        while(1){
            int pri = _deque.front().second;
            bool is_larger = false;
            for (int j=1;j<=_deque.size()-1;j++)
            {
                if (pri < _deque[j].second)
                {
                    is_larger = true;
                    break;
                }
            }
            
            if (is_larger == true){
                pair<int,int>temp = _deque.front();
                _deque.pop_front();
                _deque.push_back(temp);
            }
            else{
                rank++;
                if (X == _deque.front().first)
                {
                    printf("%d\n",rank);
                    _deque.pop_front();
                    _deque.clear();
                    break;
                }
                _deque.pop_front();
            }
        }
    }
    
}
