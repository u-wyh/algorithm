// https://www.luogu.com.cn/problem/P4404
// 题意：初始为空、容量为 M 的缓存依次处理 N 个主存块访问请求，缓存满且未命中时可任选一块换出，求最少的 Cache 缺失次数。
// 数据范围：1 <= M <= N <= 10^5，主存块编号为不超过 10^9 的正整数。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,q,m;
int val[MAXN];
int arr[MAXN];

int lst[MAXN];
int nxt[MAXN];

bool vis[MAXN];
priority_queue<pair<int,int>>heap;

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

int find(int val){
    int l=1,r=m,ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(arr[mid]>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

int main()
{
    n=read(),q=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
        arr[i]=val[i];
    }
    sort(arr+1,arr+n+1);
    m=1;
    for(int i=2;i<=n;i++){
        if(arr[i]!=arr[i-1]){
            arr[++m]=arr[i];
        }
    }
    for(int i=1;i<=n;i++){
        val[i]=find(val[i]);
    }

    for(int i=1;i<=n;i++){
        nxt[i]=n+1;
    }
    for(int i=1;i<=n;i++){
        nxt[lst[val[i]]]=i;
        lst[val[i]]=i;
    }

    int cnt=0,sum=0;
    for(int i=1;i<=n;i++){
        while(!heap.empty()&&!vis[heap.top().second]){
            heap.pop();
        }
        if(vis[val[i]]){
            heap.push({nxt[i],val[i]});
        }
        else{
            ++cnt;
            vis[val[i]]=true;
            if(sum>=q){
                vis[heap.top().second]=false;
                heap.pop();
            }
            else{
                ++sum;
            }
            heap.push({nxt[i],val[i]});
        }
    }
    cout<<cnt<<endl;
    return 0;
}