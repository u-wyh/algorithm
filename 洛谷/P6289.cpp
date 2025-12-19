//这道题的思想是很美妙的
//我们要求的是最终所有字符串合在一起的结构最少的节点数量
//首先考虑简单情况  我们可以知道  如果是将两条链合并在一起
//那么就是 两条链的长度和 - 合并后的公共前缀
//要使这个公共前缀尽可能的大  这样节点才会少
//那么我们在考虑多条链合并  不管怎么说 多条链合并一定可以看成两条链合并
//这两条链肯定是他的子串  那么我们可以枚举他们是有那两条链最终合并过来的
//答案一定在其中
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int n;
char s[MAXN];
int sum[20][26];
int cnt[1<<16];
int f[1<<16];

int compute(int sta){
    for(int i=0;i<26;i++){
        sum[n+1][i]=INT_MAX;
    }
    for(int i=0;i<n;i++){
        if(sta&(1<<i)){
            for(int j=0;j<26;j++){
                sum[n+1][j]=min(sum[n+1][j],sum[i][j]);
            }
        }
    }
    int ans=0;
    for(int i=0;i<26;i++){
        ans+=sum[n+1][i];
    }
    return ans;
}

int main()
{
    cin>>n;
    for(int i=0;i<(1<<n);i++){
        f[i]=1e9;
    }
    for(int i=0;i<n;i++){
        scanf("%s",s);
        int len=strlen(s);
        for(int j=0;j<len;j++){
            sum[i][s[j]-'a']++;
        }
        f[1<<i]=len;
    }
    for(int i=1;i<(1<<n);i++){
        cnt[i]=compute(i);
    }
    for(int i=1;i<(1<<n);i++){
        for(int j=i;j;j=i&(j-1)){
            f[i]=min(f[j]+f[i-j]-cnt[i],f[i]);
        }
    }
    cout<<f[(1<<n)-1]+1;
    return 0;
}
