#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n;
int arr[MAXN];
int tmp[MAXN];
int f[MAXN];
int g[MAXN];

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

int compute(int *arr){
    for(int i=1;i<=n;i++){
        f[i]=g[i]=arr[i];
    }
    for(int i=2;i<=n;i++){
        f[i]=(f[i-1]>0)?(f[i-1]+arr[i]):arr[i];
    }
    for(int i=n-1;i>=1;i--){
        g[i]=(g[i+1]>0)?(g[i+1]+arr[i]):arr[i];
    }
    for(int i=2;i<=n;i++){
        f[i]=max(f[i],f[i-1]);
    }
    for(int i=n-1;i>=1;i--){
        g[i]=max(g[i],g[i+1]);
    }
    // for(int i=1;i<=n;i++){
    //     cout<<f[i]<<' ';
    // }
    // cout<<endl;
    // for(int i=1;i<=n;i++){
    //     cout<<g[i]<<' ';
    // }
    // cout<<endl;
    int ans=INT_MIN;
    for(int i=1;i<n;i++){
        ans=max(ans,f[i]+g[i+1]);
    }
    return ans;
}

int main()
{
    n=read();
    int sum=0;
    for(int i=1;i<=n;i++){
        arr[i]=read();
        sum+=arr[i];
        tmp[i]=-arr[i];
    }
    int ans1=compute(arr);
    int ans2=compute(tmp);
    if((ans2+sum)!=0){//这里相当于特判全是负数的情况
        cout<<max(ans1,sum+ans2);
    }
    else{
        cout<<ans1<<endl;
    }
    return 0;
}