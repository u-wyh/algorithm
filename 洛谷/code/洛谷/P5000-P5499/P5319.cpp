// https://www.luogu.com.cn/problem/P5319
// 题意：给定长为 n、由数字 '0'~'9' 和 '.' 组成的串 T，
// 以及 m 个数字串咒语 (S_i, V_i)；将 '.' 替换为数字 0~9。
// 若修复串中咒语共出现 c 次（不同位置重复算），
// 最终神力值为 (prod V_i)^(1/c)（c=0 时为 1），
// 输出使神力值最大的任一修复串。
// 数据范围：
// 1 <= n, m,
// s <= 1501（s = sum |S_i|，所有 S_i 互不相同），
// 1 <= V_i <= 10^9。
// 算法标签：AC自动机、分数规划、动态规划
#include<bits/stdc++.h>
using namespace std;
const double eps = 1e-8;
const int INF = 1e9;
const int MAXN = 1600;

int n,m;
char s[MAXN];
char t[MAXN];

char ans[MAXN];

int trie[MAXN][10];
int fail[MAXN];
double val[MAXN];
double sum[MAXN];
int cnt;

// 记录的是当前来到了i位置匹配到自动机上的j  最大权值是多少
double f[MAXN][MAXN];
// 这个是用于回溯的  状态转移
int g[MAXN][MAXN];
char h[MAXN][MAXN];

void insert(double v){
    int cur=0;
    int len=strlen(t+1);
    for(int i=1;i<=len;i++){
        char ch=t[i];
        int path=ch-'0';
        if(trie[cur][path]==0){
            trie[cur][path]=++cnt;
        }
        cur=trie[cur][path];
    }
    val[cur]+=v;
    sum[cur]++;
}

void setfail(){
    queue<int>q;
    for(int i=0;i<10;i++){
        if(trie[0][i]){
            q.push(trie[0][i]);
        }
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        val[u]+=val[fail[u]];
        sum[u]+=sum[fail[u]];
        for(int i=0;i<10;i++){
            if(trie[u][i]==0){
                trie[u][i]=trie[fail[u]][i];
            }
            else{
                fail[trie[u][i]]=trie[fail[u]][i];
                q.push(trie[u][i]);
            }
        }
    }
}

bool check(double limit){
    // 分数规划  算出在这个条件下的有效val
    for(int i=0;i<=cnt;i++){
        val[i]-=sum[i]*limit;
    }

    for(int i=0;i<=n;i++){
        for(int j=0;j<=cnt;j++){
            f[i][j]=-1e100;
        }
    }
    f[0][0]=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<=cnt;j++){
            if(f[i][j]<-1e99){
                continue;
            }
            // 设置可填字符范围
            char st='0',en='9';
            if(s[i+1]!='.'){
                st=s[i+1];
                en=s[i+1];
            }
            for(char c=st;c<=en;c++){
                int jj=trie[j][c-'0'];
                double v=f[i][j]+val[jj];
                if(v>f[i+1][jj]){
                    f[i+1][jj]=v;
                    // 记录好转移路径 方便最后回溯
                    g[i+1][jj]=j;
                    h[i+1][jj]=c;
                }
            }
        }
    }

    // 复原val数组
    for(int i=0;i<=cnt;i++){
        val[i]+=sum[i]*limit;
    }

    for(int i=0;i<=cnt;i++){
        if(f[n][i]>0){
            return true;
        }
    }
    return false;
}

// 回溯 得到字符数组
void compute(){
    int cur=0;
    for(int i=1;i<=cnt;i++){
        if(f[n][i]>f[n][cur]){
            cur=i;
        }
    }
    for(int i=n;i>=1;i--){
        ans[i]=h[i][cur];
        cur=g[i][cur];
    }
}

int main()
{
    scanf("%d %d",&n,&m);
    scanf("%s",s+1);
    for(int i=1;i<=m;i++){
        int val;
        scanf("%s %d",t+1,&val);
        insert(log(val));
    }
    setfail();

    double l=0,r=log(INF),res=0;
    while(r-l>eps){
        double mid=(l+r)/2;
        if(check(mid)){
            res=mid;
            l=mid+eps;
        }
        else{
            r=mid-eps;
        }
    }
    check(res);
    compute();
    printf("%s",ans+1);
    return 0;
}