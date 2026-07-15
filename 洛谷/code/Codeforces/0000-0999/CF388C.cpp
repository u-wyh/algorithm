#include<bits/stdc++.h>
using namespace std;

int n;
int a,b;
int top;
int nums[105];

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

bool cmp(int a,int b){
    return a>b;
}

int main()
{
    n=read();
    while(n--){
        int t;
        t=read();
        for(int i=1;i<=t/2;i++){
            a+=read();
        }
        if(t%2==1){
            nums[++top]=read();
        }
        for(int i=1;i<=t/2;i++){
            b+=read();
        }
    }
    sort(nums+1,nums+top+1,cmp);
    for(int i=1;i<=top;i+=2){
        a+=nums[i];
    }
    for(int i=2;i<=top;i+=2){
        b+=nums[i];
    }
    printf("%d %d",a,b);
    return 0;
}