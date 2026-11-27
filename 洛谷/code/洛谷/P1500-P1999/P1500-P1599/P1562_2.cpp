// https://www.luogu.com.cn/problem/P1562
// 题意：输入 N 及 N*N 棋盘，* 表示可放皇后，. 表示不可放。
// 放置 N 个皇后，使每行、每列恰有 1 个，每条对角线至多 1 个。
// 输出合法放置方案的总数。
// 数据范围：
// 0 < N <= 14（棋盘大小）
// 算法标签：深度优先搜索、位运算、状态压缩
#include<bits/stdc++.h>

#define xianzhi ~(now|ld|rd|sta[d])
#define lowbit(pos)  pos&-pos
#define youzuo (ld+p)<<1
#define zuoyou (rd+p)>>1

int n,all,sta[25],ans;

void dfs(int now,int ld,int rd,int d){
    if(now==all){
        ans++;
        return ;
    }
    int pos=all&xianzhi,p;
    while(pos){
        p=lowbit(pos);
        pos-=p;
        dfs(now+p,youzuo,zuoyou,d+1);
    }
}

int main(){
    scanf("%d",&n);
    all=(1<<n)-1;
    char c[20];
    for(int i=1;i<=n;++i){
        scanf("%s",c+1);
        getchar();//消除行末回车
        for(int j=1;j<=n;++j){
            if(c[j]=='.')
                sta[i]|=(1<<(n-j));
        }
    }
    dfs(0,0,0,1);
    printf("%d",ans);
    return 0;
}
