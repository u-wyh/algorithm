#include<bits/stdc++.h>
using namespace std;
const int MAXK = 1e6+5;
const int MAXN = 1e7+5e6+5;

int n,k;
vector<int>vec;
int sta[MAXN];
int top;

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
    k=read();
    n=read();
    while(n!=0){
        vec.push_back(n);
        n=read();
    }
    n=vec.size();
    for(int i=0;i<n;i++){
        while(top>0&&vec[i]>sta[top-1]&&(top-1+n-i)>=k){
            top--;
        }
        sta[top++]=vec[i];
    }
    for(int i=0;i<k;i++){
        printf("%d\n",sta[i]);
    }
    return 0;
}