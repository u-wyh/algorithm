#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int len[MAXN];
int fa[MAXN];
map<int,int>nxt[MAXN];

int lst=1;
int tot=1;
long long ans=0;

// 后缀自动机扩展函数：向自动机中添加一个字符
void extend(int c){
    int cur=++tot;
    // 新状态的长度是上一个状态长度+1  初始出现次数为1
    len[cur]=len[lst]+1;

    // 从上一个状态开始，沿着后缀链接向上遍历
    int p=lst;
    while(p&&!nxt[p].count(c)){
        // 为没有字符c转移的状态添加转移到cur
        nxt[p][c]=cur;
        p=fa[p];
    }

    // 情况1：没有找到有字符c转移的状态  也就是说这个字符是第一次出现
    if(p==0){
        // 直接挂到根节点上
        fa[cur]=1;
    }
    else{
        // 找到状态p在字符c上的转移状态q
        int q=nxt[p][c];

        // 情况2：q的长度正好是p的长度+1 直接将cur的后缀链接指向q
        if(len[p]+1==len[q]){
            fa[cur]=q;
        }
        else{
            int nq=++tot;
            len[nq]=len[p]+1;
            
            nxt[nq]=nxt[q];
            // 设置nq的后缀链接为q的后缀链接，并更新q和cur的后缀链接
            fa[nq]=fa[q],fa[q]=nq,fa[cur]=nq;

            // 将原本指向q的转移重定向到nq
            while(p&&nxt[p][c]==q){
                nxt[p][c]=nq;
                p=fa[p];
            }
        }
    }
    ans+=len[cur]-len[fa[cur]];
    lst=cur;
}

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
    int n=read();
    for(int i=1;i<=n;i++){
        int x=read();
        extend(x);
        cout<<ans<<endl;
    }
    return 0;
}