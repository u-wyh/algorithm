// https://www.luogu.com.cn/problem/P3069
// 题意：输入奶牛数量 N、可移除血统种数上限 K，以及排成一排的每头奶牛血统编号 B(i)。
// 最多选出 K 种不同的血统编号，将队列中属于这些血统的所有奶牛全部赶走（不改变剩余牛的相对顺序）。
// 求赶走后剩余队伍中由相同血统编号构成的连续段最大可能长度。
// 输出一行一个整数，表示最大连续段长度。
// 数据范围：对于 100% 的数据，1 <= N <= 10^5，0 <= B(i) <= 10^9（题面未单独写出 K 的显式范围）。
#include<bits/stdc++.h>
// 算法标签：双指针、离散化
using namespace std;
const int MAXN = 1e5+5;

int temp[MAXN];
int arr[MAXN];
int n,k;
int cnt[MAXN];
map<int,int>m;
int tot=1;
int ans=0;
int kind=0;

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

void build(){
    sort(temp+1,temp+n+1);
    m[temp[1]]=tot;
    for(int i=2;i<=n;i++){
        if(temp[i]!=temp[i-1]){
            m[temp[i]]=++tot;
            temp[tot]=temp[i];
        }
    }
}

int main()
{
    n=read(),k=read();
    k++;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        temp[i]=arr[i];
    }
    build();
    for(int i=1;i<=n;i++){
        arr[i]=m[arr[i]];
        //cout<<arr[i]<<' ';
    }
    cnt[arr[1]]++;
    kind=1;
    ans=1;
    int l=1;
    for(int r=2;r<=n;r++){
        if(cnt[arr[r]]==0){
            kind++;
        }
        cnt[arr[r]]++;
        ans=max(ans,cnt[arr[r]]);
        while(kind>k){
            if(cnt[arr[l]]==1){
                kind--;
            }
            cnt[arr[l++]]--;
        }
    }
    cout<<ans<<endl;
    return 0;
}
