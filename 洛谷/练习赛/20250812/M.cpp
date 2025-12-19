#include<bits/stdc++.h>
using namespace std;

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

int main()
{
    int T;
    T=read();
    while(T--){
        int n=read();
        if(n<10){
            cout<<1<<endl;
        }
        else{
            cout<<-1<<endl;
        }
    }
    return 0;
}