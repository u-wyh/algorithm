#include<bits/stdc++.h>
using namespace std;

int T,n,w;
struct node{
    int lt,rt;
    bool friend operator < (const node &a,const node &b){
        return a.rt<b.rt;
    }
}A[200005];

int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&w);
        bool tag=true;
        for(int i=1;i<=n;i++){
            scanf("%d%d",&A[i].lt,&A[i].rt);
            if(A[i].rt-A[i].lt+1<w)tag=false;
        }
        if(!tag){
            puts("No");
            continue;
        }
        if(!w){
            puts("1");
            continue;
        }
        sort(A+1,A+1+n);
        int Max=-1;
        int pos=0;
        for(int i=1;i<=n;i++){
            if(Max<A[i].lt){
                pos++;
                Max=A[i].rt-w+1;
            }
        }
        printf("%d\n",pos);
    }
    return 0;
}
