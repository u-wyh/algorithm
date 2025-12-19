// https://www.luogu.com.cn/problem/P6086   
// 时间复杂度为O(n)
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e6+5;

int n,op;
int d[MAXN];
int nums[MAXN];
int ans[MAXN];
bool vis[MAXN];

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
    n=read(),op=read();
    if(op==1){
        for(int i=1;i<n;i++){
            nums[i]=read();
            d[nums[i]]++,d[i]++;
        }
        //这里采用的是线性做法  找到第一个度数为1的节点p
        //然后找到他的父亲节点  这个父亲节点一定是答案  然后如果父亲小于叶子  那么父亲就是叶子
        //因为此时叶子已经是最小的了  父亲还要更小 那么父亲就是叶子  否则p自增找到最小的
        //这有一个特性  父亲节点在那时一定不会是度数为1的  他肯定存在父亲  否则他就是n  可是n的编号一定是最大的
        int p;
        for(int i=1;i<=n;i++){
            if(d[i]==1){
                p=i;
                break;
            }
        }
        int tot=0;
        int leaf=p;
        while(tot<n-2){
            int f=nums[leaf];
            ans[++tot]=f;
            d[f]--;
            if(d[f]==1&&f<p){
                leaf=f;
            }
            else{
                p++;
                while(d[p]!=1){
                    p++;
                }
                leaf=p;
            }
        }
        long long res=0;
        for(int i=1;i<=n-2;i++){
            res=(res^(1ll*i*ans[i]));
        }
        cout<<res<<endl;
    }
    else{
        for(int i=1;i<=n;i++){
            d[i]=1;
        }
        for(int i=1;i<=n-2;i++){
            nums[i]=read();
            d[nums[i]]++;
        }
        int p=1;
        for(int i=1;i<=n;i++){
            if(d[i]==1){
                p=i;
                break;
            }
        }
        int tot=0;
        int leaf=p;
        while(tot<n-2){
            int f=nums[++tot];
            ans[leaf]=f;
            d[f]--;
            if(d[f]==1&&f<p){
                leaf=f;
            }
            else{
                p++;
                while(d[p]!=1){
                    p++;
                }
                leaf=p;
            }
        }
        ans[leaf]=n;
        long long res=0;
        for(int i=1;i<=n-1;i++){
            res=(res^(1ll*i*ans[i]));
        }
        cout<<res<<endl;
    }
    return 0;
}