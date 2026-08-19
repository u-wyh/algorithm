#include<bits/stdc++.h>
using namespace std;

const int MAXN = 2e5+5;

int n;
long long m;

char s[MAXN];
int a[MAXN];

void solve(){
    scanf("%d%lld",&n,&m);
    scanf("%s",s+1);

    int l=0,r=0;
    int fixedOpen=0;

    // 找到连续的 ? 区间，同时统计已经确定的左括号数量
    for(int i=1;i<=n;i++){
        if(s[i]=='?'){
            if(!l){
                l=i;
            }
            r=i;
        }
        else if(s[i]=='('){
            fixedOpen++;
        }
    }

    // 没有 ?，题目保证答案存在，直接输出
    if(!l){
        printf("%s\n",s+1);
        return;
    }

    int len=r-l+1;

    // 合法括号串总共有 n/2 个左括号
    int x=n/2-fixedOpen;

    // ? 区间中的右括号数量
    int y=len-x;

    long long pre=0;
    int bal=0;

    // 计算固定前缀的贡献，以及进入 ? 区间时的深度
    for(int i=1;i<l;i++){
        if(s[i]=='('){
            bal++;
        }
        else{
            pre+=bal;
            bal--;
        }
    }

    int start=bal;

    // ? 区间结束后的深度是固定的
    int finish=start+x-y;

    long long suf=0;
    bal=finish;

    // 计算固定后缀的贡献
    for(int i=r+1;i<=n;i++){
        if(s[i]=='('){
            bal++;
        }
        else{
            suf+=bal;
            bal--;
        }
    }

    // ? 区间需要提供的贡献
    long long target=m-pre-suf;

    // a[i] 表示第 i 个右括号前已经出现了多少个左括号
    long long sum=0;

    for(int i=1;i<=y;i++){
        // 保证第 i 个右括号出现时栈非空
        a[i]=max(0,i-start);
        sum+=a[i];
    }

    // 不考虑 a[i] 时，所有右括号本身的基础贡献
    long long base=1LL*y*start-1LL*y*(y-1)/2;

    // 还需要让 sum(a[i]) 增加多少
    long long need=target-base-sum;

    // 从后往前增加 a[i]，保证 a[] 仍然单调不降
    for(int i=y;i>=1;i--){
        int lim;

        if(i==y){
            lim=x;
        }
        else{
            lim=a[i+1];
        }

        long long can=lim-a[i];
        long long add=min(need,can);

        a[i]+=add;
        need-=add;
    }

    int pos=l;
    int opened=0;

    // 根据 a[] 还原 ? 区间
    for(int i=1;i<=y;i++){
        while(opened<a[i]){
            s[pos++]='(';
            opened++;
        }

        s[pos++]=')';
    }

    // 补上还没有放置的左括号
    while(opened<x){
        s[pos++]='(';
        opened++;
    }

    printf("%s\n",s+1);
}

int main(){
    int T;
    scanf("%d",&T);

    while(T--){
        solve();
    }

    return 0;
}