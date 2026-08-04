#include<bits/stdc++.h>
using namespace std;
const int MAXV = 1e5+5;
const int MAXH = 170;
const int B = 650;
const int INF = 0x3f3f3f3f;

int n,m,lastans;

// posVal[i]：位置i当前所属的内部集合编号
int posVal[MAXV];

// belong[x]：题目中的值x当前对应哪个内部集合
int belong[MAXV];

// cnt[x]：内部集合x的总大小
int cnt[MAXV];

// 小集合保存全部位置，大集合只保存重构后的新增位置
int head[MAXV];
int tail[MAXV];
int listSize[MAXV];
int nxt[MAXV];

// bigId[x]：大集合x对应的距离表编号
int bigId[MAXV];
int bigCnt;
int dista[MAXH][MAXV];

inline int read(){
    int x=0;
    char ch=getchar();

    while(ch<'0'||ch>'9')
        ch=getchar();

    while(ch>='0'&&ch<='9'){
        x=x*10+ch-'0';
        ch=getchar();
    }

    return x;
}

inline void addPos(int x,int pos){
    if(!head[x]){
        head[x]=tail[x]=pos;
    }
    else{
        nxt[tail[x]]=pos;
        tail[x]=pos;
    }

    listSize[x]++;
}

// 重新计算大集合x到所有集合的最短距离
void rebuildBig(int x,bool firstBuild){
    if(firstBuild)
        bigId[x]=++bigCnt;

    int id=bigId[x];
    memset(dista[id],0x3f,sizeof(dista[id]));

    int last=0;

    for(int i=1;i<=n;i++){
        if(posVal[i]==x)
            last=i;

        if(last)
            dista[id][posVal[i]]=min(dista[id][posVal[i]],i-last);
    }

    last=0;

    for(int i=n;i>=1;i--){
        if(posVal[i]==x)
            last=i;

        if(last)
            dista[id][posVal[i]]=min(dista[id][posVal[i]],last-i);
    }

    head[x]=0;
    tail[x]=0;
    listSize[x]=0;
}

// 合并两个递增的位置链表，结果放入large
void mergeList(int small,int large){
    int p=head[small];
    int q=head[large];

    int newHead=0;
    int newTail=0;

    while(p&&q){
        int u;

        if(p<q){
            u=p;
            p=nxt[p];
        }
        else{
            u=q;
            q=nxt[q];
        }

        if(!newHead){
            newHead=newTail=u;
        }
        else{
            nxt[newTail]=u;
            newTail=u;
        }
    }

    int remain;

    if(p)
        remain=p;
    else
        remain=q;

    while(remain){
        int u=remain;
        remain=nxt[remain];

        if(!newHead){
            newHead=newTail=u;
        }
        else{
            nxt[newTail]=u;
            newTail=u;
        }
    }

    if(newTail)
        nxt[newTail]=0;

    head[large]=newHead;
    tail[large]=newTail;
    listSize[large]+=listSize[small];

    head[small]=0;
    tail[small]=0;
    listSize[small]=0;
}

// small是小集合，修改它保存的全部位置
void relabelList(int small,int large){
    for(int i=head[small];i;i=nxt[i])
        posVal[i]=large;
}

// 全局修改small的集合编号
void relabelAll(int small,int large){
    for(int i=1;i<=n;i++){
        if(posVal[i]==small)
            posVal[i]=large;
    }
}

// small并入large后，更新所有大集合到large的距离
void mergeDistance(int small,int large){
    for(int i=1;i<=bigCnt;i++){
        dista[i][large]=min(
            dista[i][large],
            dista[i][small]
        );
    }
}

void modify(int x,int y){
    int compX=belong[x];
    int compY=belong[y];

    if(compX==0||compX==compY)
        return;

    // y不存在，只需要把compX改名为y
    if(compY==0){
        belong[x]=0;
        belong[y]=compX;
        return;
    }

    // 内部始终把较小集合并入较大集合
    int small=compX;
    int large=compY;

    if(cnt[small]>cnt[large]){
        int tmp=small;
        small=large;
        large=tmp;
    }

    mergeDistance(small,large);

    if(cnt[small]>B){
        // 两个集合都是大集合
        relabelAll(small,large);
        rebuildBig(large,false);
    }
    else if(listSize[small]+listSize[large]<=B){
        // 合并后仍可保存在小链表或缓冲区中
        relabelList(small,large);
        mergeList(small,large);
    }
    else{
        relabelList(small,large);

        bool firstBuild=false;

        if(cnt[large]<=B)
            firstBuild=true;

        rebuildBig(large,firstBuild);
    }

    cnt[large]+=cnt[small];
    cnt[small]=0;

    head[small]=0;
    tail[small]=0;
    listSize[small]=0;

    // 对外只保留值y
    belong[x]=0;
    belong[y]=large;
}

int queryList(int x,int y){
    int p=head[x];
    int q=head[y];
    int ans=INF;

    while(p&&q){
        ans=min(ans,abs(p-q));

        if(p<q)
            p=nxt[p];
        else
            q=nxt[q];
    }

    return ans;
}

int query(int x,int y){
    int compX=belong[x];
    int compY=belong[y];

    if(compX==0||compY==0)
        return INF;

    if(compX==compY)
        return 0;

    int ans=queryList(compX,compY);

    if(cnt[compX]>B){
        ans=min(
            ans,
            dista[bigId[compX]][compY]
        );
    }

    if(cnt[compY]>B){
        ans=min(
            ans,
            dista[bigId[compY]][compX]
        );
    }

    return ans;
}

int main(){
    n=read();
    m=read();

    for(int i=1;i<=n;i++){
        int x=read();

        posVal[i]=x;
        belong[x]=x;
        cnt[x]++;

        addPos(x,i);
    }

    for(int x=1;x<MAXV;x++){
        if(cnt[x]>B)
            rebuildBig(x,true);
    }

    while(m--){
        int op=read();
        int x=read()^lastans;
        int y=read()^lastans;

        if(op==1){
            modify(x,y);
        }
        else{
            int ans=query(x,y);

            if(ans==INF){
                puts("Ikaros");
                lastans=0;
            }
            else{
                printf("%d\n",ans);
                lastans=ans;
            }
        }
    }

    return 0;
}