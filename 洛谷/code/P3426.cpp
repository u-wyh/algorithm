#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;

int n;
char s[MAXN];
int nxt[MAXN];

int f[MAXN];
int g[MAXN];

// 计算1-based next数组
void calcnext(){
    nxt[1]=0;
    for(int i=2,j=0;i<=n;i++){
        // 当不匹配时，通过next数组回溯
        while(j>0&&s[i]!=s[j+1]){
            j=nxt[j];
        }
        // 如果当前字符匹配，j增加
        if(s[i]==s[j+1]){
            j++;
        }
        // 设置当前位置的next值
        nxt[i]=j;
    }
}

int main()
{
    scanf("%s",s+1);
    n=strlen(s+1);
    calcnext();
    for(int i=1;i<=n;i++){
        f[i]=i;
        int k=nxt[i];
        int candidate=f[k];
        if(g[candidate]>=i-candidate){
            f[i]=candidate;
        }
        g[f[i]]=i;
    }
    cout<<f[n]<<endl;
    return 0;
}