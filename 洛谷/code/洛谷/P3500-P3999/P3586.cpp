// https://www.luogu.com.cn/problem/P3586
// 题意：初始有长度为 n 的全 0 序列，输入 n 和操作数 m，
// 以及 m 个操作。
// U k a 将第 k 个数改为 a；
// Z c s 询问能否独立地进行 s 次「选 c 个正数各减 1」的操作。
// 对每个 Z 询问输出一行 TAK 或 NIE。
// 数据范围：1 <= n, m <= 10^6，1 <= k, c <= n，
// 0 <= a <= 10^9，1 <= s <= 10^9。
// 算法标签：树状数组、离散化、离线处理
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e6+5;

int n,q,m=1,cnt;
int nums[MAXN];
char op[MAXN];
int a[MAXN],b[MAXN];
int arr[MAXN];
int tree1[MAXN];
long long tree2[MAXN];

inline int lowbit(int x){
    return x&-x;
}

void add1(int x,int v){
    while(x<=m){
        tree1[x]+=v;
        x+=lowbit(x);
    }
}

int query1(int x){
    int ans=0;
    while(x){
        ans+=tree1[x];
        x-=lowbit(x);
    }
    return ans;
}

void add2(int x,int v){
    while(x<=m){
        tree2[x]+=v;
        x+=lowbit(x);
    }
}

long long query2(int x){
    long long ans=0;
    while(x){
        ans+=tree2[x];
        x-=lowbit(x);
    }
    return ans;
}

int find(int val){
    int l=1,r=m,ans=m+1;
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

signed main()
{
    cin>>n>>q;
    for(int i=1;i<=q;i++){
        cin>>op[i]>>a[i]>>b[i];
        if(op[i]=='U'){
            arr[++cnt]=b[i];
        }
    }
    arr[++cnt]=0;
    sort(arr+1,arr+cnt+1);
    for(int i=2;i<=cnt;i++){
        if(arr[i]!=arr[i-1]){
            arr[++m]=arr[i];
        }
    }
    add1(1,n);
    for(int i=1;i<=q;i++){
        if(op[i]=='U'){
            int v=find(nums[a[i]]);
            add1(v,-1);
            add2(v,-nums[a[i]]);
            nums[a[i]]=b[i];
            v=find(b[i]);
            add1(v,1);
            add2(v,b[i]);
        }
        else{
            long long need=a[i]*b[i];
            int v=find(b[i]);
            need-=query2(v-1);
            need-=b[i]*(n-query1(v-1));
            if(need>0){
                cout<<"NIE"<<endl;
            }
            else{
                cout<<"TAK"<<endl;
            }
        }
    }
    return 0;
}