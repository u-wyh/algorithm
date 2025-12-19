#include<bits/stdc++.h>
using namespace std;

int n,m;
vector<vector<int>>vec;
vector<vector<int>>dp;

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
    cin>>n>>m;
    return 0;
}