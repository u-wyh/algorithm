#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;

int n,k;
int val[MAXN];
int tmp[MAXN];

int compute(int a,int b,int c,int op){
    if(op==0){
        if(a==0||b==0||c==0){
            if(a==1||b==1||c==1){
                if(a==2||b==2||c==2){
                    return 3;
                }
                else{
                    return 2;
                }
            }
            return 1;
        }
        else{
            return 0;
        }
    }
    else{
        int ta=a,tb=b,tc=c;
        a=min(ta,min(tb,tc));
        c=max(ta,max(tb,tc));
        b=ta+tb+tc-a-c;
        return b;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>val[i];
    }

    for(int v=1;v<=k;v++){
        for(int i=1;i<=n;i++){
            tmp[i]=compute(val[i],val[(i-1)==0?n:(i-1)],val[(i+1)==(n+1)?1:(i+1)],0);
        }
        for(int i=1;i<=n;i++){
            val[i]=tmp[i];
            cout<<val[i]<<' ';
        }
        cout<<endl;
    }
    return 0;
}
/*
6 8
4 2 3 1 6 5 7 0
*/