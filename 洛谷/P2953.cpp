#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int sg[MAXN];
int maxx,minn;
bool appear[2];

void func(int x){
    minn=9,maxx=0;
    while(x){
        int k=x%10;
        maxx=max(k,maxx);
        if(k!=0)
            minn=min(k,minn);
        x/=10;
    }
}

void build(){
    for(int i=10;i<=1000000;i++){
        func(i);
        appear[0]=appear[1]=false;
        if(minn!=0)
            appear[sg[i-minn]]=true;
        appear[sg[i-maxx]]=true;
        if(appear[0]){
            sg[i]=1;
        }
        else{
            sg[i]=0;
        }
    }
}

int main()
{
    int T;
    cin>>T;
    for(int i=1;i<=9;i++){
        sg[i]=1;
    }
    build();
    for(int i=1;i<1000;i++){
        cout<<setw(4)<<i<<": "<<sg[i]<<"    ";
        if(i%20==0){
            cout<<endl;
        }
    }
    while(T--){
        int n;
        cin>>n;
        if(sg[n]){
            cout<<"YES"<<endl;
        }
        else{
            cout<<"NO"<<endl;
        }
    }
    return 0;
}
