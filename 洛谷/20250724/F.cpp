#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 3e5+5;

int n,k,c;
int ans=0;
int nums[MAXN];
priority_queue<int,vector<int>,greater<int>>heap;//小根堆

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

signed main()
{
    n=read(),k=read(),c=read();
    for(int i=1;i<=n;i++){
        nums[i]=read();
    }
    if(k==0){
        cout<<0<<endl;
        return 0;
    }
    for(int i=1;i<=k;i++){
        ans+=nums[i];
        heap.push(nums[i]+(k-i+1)*c);
    }
    for(int i=k+1;i<=n;i++){
        nums[i]-=(i-k-1)*c;
        int u=heap.top();
        if(nums[i]<u){
            continue;
        }
        else{
            ans+=(nums[i]-u);
            heap.pop();
            heap.push(nums[i]);
        }
    }
    cout<<ans<<endl;
    return 0;
}