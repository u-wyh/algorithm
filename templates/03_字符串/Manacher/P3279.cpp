// https://www.luogu.com.cn/problem/P3279
// 这道题相当于是Manacher算法的逆过程  直接给出回文长度
// 我们主要借助的是回文半径是回文长度加一
// 收集所有一定相同的位置  和  一定不相同的位置
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m;
// 真实的回文长度
int p[MAXN<<1];
// 回文半径
int f[MAXN<<1];

// 并查集  用于收集字符一定相同的位置
int fa[MAXN];

// 用于收集一定不同的字符 
int head[MAXN];
int nxt[MAXN<<2];
int to[MAXN<<2];
int cnt=1;

// 联通块的代表
int id[MAXN];

bool ok[27];

void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        fa[fx]=fy;
    }
}

int main()
{
    scanf("%d",&n);
    // 读入真实回文长度数组  注意读入时的顺序
    for(int i=2;i<=2*n;i+=2){
        scanf("%d",&p[i]);
    }
    for(int i=3;i<2*n;i+=2){
        scanf("%d",&p[i]);
    }
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }

    int mid=0,r=0;
    m=2*n;
    for(int i=2;i<=m;i++){
        // len是回文半径
        int len=(r>i)?min(f[2*mid-i],r-i):1;
        
        while(len-1<p[i]){
            // 回文半径的长度应该是真实回文长度+1
            len++;
            if((i-len+1)%2==0){
                // 对称的字母一样
                int lt=(i-len+1)/2;
                int rt=(i+len-1)/2;
                if(lt<1||rt>n){
                    break;
                }
                un(lt,rt);
            }
        }

        // 这两个字母一定不一样  而且他们肯定是字母  不是空格
        int lt=(i-len)/2;
        int rt=(i+len)/2;
        if(lt>=1&&lt<=n&&rt>=1&&rt<=n){
            addedge(lt,rt);
            addedge(rt,lt);
        }

        f[i]=len;

        if(i+len>r){
            r=i+len;
            mid=i;
        }
    }

    for(int i=1;i<=n;i++){
        int root=find(i);
        if(id[root]==0){
            for(int j=1;j<=26;j++){
                ok[j]=true;
            }
            // 注意这里 应该是查询和i不能是一个颜色的位置  不是和root不同颜色的位置
            // 因为root可能在i的后面
            // 这里其实是一个贪心算法  就是前面出现的越小越好
            for(int ei=head[i];ei;ei=nxt[ei]){
                int v=find(to[ei]);
                ok[id[v]]=false;
            }
            for(int j=1;j<=26;j++){
                if(ok[j]){
                    id[root]=j;
                    break;
                }
            }
        }
        cout<<char('a'+id[root]-1);
    }
    return 0;
}