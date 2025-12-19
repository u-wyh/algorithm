#include<bits/stdc++.h>
using namespace std;
#define int long long

int n,k;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

bool check(){
    if(k>2e9){
        return true;
    }
    return (k*(k+1))/2>n;
}

signed main()
{
    int T;
    T=read();
    while(T--){
        cin>>n>>k;
        if(n<=k){
            cout<<"OC"<<endl;
        }
        else if(!check()){
            if(k%2){
                cout<<"OC"<<endl;
            }
            else{
                cout<<"KP"<<endl;
            }
        }
        else{
            if(k%2){
                cout<<"OC"<<endl;
            }
            else{
                cout<<"KP"<<endl;
            }
        }
    }
    return 0;
}