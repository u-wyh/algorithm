#include<bits/stdc++.h>
using namespace std;
#define MN 605

int add[MN][26],fail[MN],state[MN],nod,ans[MN*(1<<12|1)],fa[MN*(1<<12|1)],n,cnt,tot;
//add:Trie树中的地址(address)
bool vis[MN][1<<12|1];
char C[MN],ch[51];
queue<int>Q,Q1,Q2;

void getfail(){
    for(int i=0;i<26;++i)
        if(add[0][i])
            Q.push(add[0][i]);
    while(!Q.empty()){
        int x=Q.front();
        Q.pop();
        for(int i=0;i<26;++i)
            if(add[x][i]){
                fail[add[x][i]]=add[fail[x]][i];
                state[add[x][i]]|=state[add[fail[x]][i]];//它的fail指针包含的字符串它也包含
                Q.push(add[x][i]);
                cout<<state[add[x][i]]<<endl;
            }
            else
                add[x][i]=add[fail[x]][i];
    }
}
//AC自动机建fail树

int main()
{
    scanf("%d",&n);
    int now;
    for(int i=1;i<=n;++i){
        scanf("%s",ch);
        now=0;
        int ln=strlen(ch);
        for(int j=0;j<ln;++j){
            if(!add[now][ch[j]-'A'])
                add[now][ch[j]-'A']=++cnt;
            now=add[now][ch[j]-'A'];
        }
        state[now]|=1<<(i-1);//i-1也不会冲突,省一点空间
        cout<<i<<' '<<state[now]<<endl;
        //有重复的,要用|
    }//建trie树
//    for(int i=0;i<now;i++){
//        cout<<state[i]<<' ';
//    }
    getfail();
    Q1.push(0);
    Q2.push(0);
    //Q1:在Trie中的位置
    //Q2:状态压缩,表示当前包含了哪些要求的字符串
    vis[0][0]=1;
    int Ti=0;
    while(!Q1.empty()){
        int now=Q1.front(),St=Q2.front();
        Q1.pop();
        Q2.pop();
        if(St==((1<<n)-1)){
            while(Ti){
                C[++nod]=ans[Ti];
                Ti=fa[Ti];
            }//递归回去求答案
            for(int i=nod;i>0;--i)
                putchar(C[i]+'A');
            return 0;
        }
        for(int i=0;i<26;++i){
            if(!vis[add[now][i]][St|state[add[now][i]]]){
                vis[add[now][i]][St|state[add[now][i]]]=1;
                Q1.push(add[now][i]);
                Q2.push(St|state[add[now][i]]);
                //找出现新的状态
                fa[++tot]=Ti;
                ans[tot]=i;
                //记录当前搜到的字符,同时建1棵关于答案的树,便于最后查询
            }
        }
        ++Ti;//Ti表示当前的搜索到的编号
    }
    return 0;
}
