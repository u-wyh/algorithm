// 岛屿数量
// 给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量
// 岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成
// 此外，你可以假设该网格的四条边均被水包围
// 测试链接 : https://leetcode.cn/problems/number-of-islands/
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#define Max 10000

int father[Max],n,m,sets=0,board[Max][Max];

int getindex(int x,int y){
    return x*m+y;
}

void build(){
    for (int a = 0; a < n; a++) {
        for (int b = 0, index1; b < m; b++) {
            if (board[a][b] == 1) {
                index1 = getindex(a, b);
                father[index1] = index1;
                sets++;
            }
        }
    }
    printf("%d\n",sets);
}

int find(int i) {
    if (i != father[i]) {
        father[i] = find(father[i]);
    }
    return father[i];
}

void un(int a,int b,int c,int d){
    int fx = find(getindex(a, b));
    int fy = find(getindex(c, d));
    if (fx != fy) {
        father[fx] = fy;
        sets--;
    }
}

int numIslands() {
    build();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (board[i][j] == 1) {
                if (j > 0 && board[i][j - 1] == 1) {
                    un(i, j, i, j - 1);
                }
                if (i > 0 && board[i - 1][j] == 1) {
                    un(i, j, i - 1, j);
                }
            }
        }
    }
    return sets;
}

int main()
{
    scanf("%d %d",&n,&m);
    //getchar();
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            scanf("%d",&board[i][j]);
            //getchar();
        }
        //scanf("\n");
        //getchar();
    }
    printf("%d\n",numIslands());
    return 0;
}