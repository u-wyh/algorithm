#include<bits/stdc++.h>

using namespace std;

#define MAX 1000000+5

queue<int>Q;
int d[MAX];
int n;

int main()
{
    scanf("%d",&n);
    Q.push(1);
    d[1]=0;
    while(!Q.empty()){
        int tmp=Q.front();
        Q.pop();
        for(int i=1;i<=3;i++){
            int k;
            if(i==1) k=-1;
            if(i==2) k=1;
            if(i==3) k=tmp;
            int x=tmp+k;
            if(x<1||x>n||d[x]!=0){
                continue;
            }
            Q.push(x);
            d[x]=d[tmp]+1;
            if(x==n){
                printf("%d\n",d[x]);
                return 0;
            }
        }
    }
    return 0;
}
