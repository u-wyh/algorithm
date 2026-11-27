// https://www.luogu.com.cn/problem/P1162
// 题意：给一个 n × n 的 01 方阵。如果某个 0 只走上下左右的其他 0 时到不了方阵边界，就把它改成 2。输出涂完后的方阵。
// 数据范围：1 ≤ n ≤ 30，只有一个闭合圈，圈内至少有一个 0 且圈内的 0 连通。
// 算法标签：深度优先搜索

#include<stdio.h>
#define Max 35

int n;
int nums[Max][Max];

void dfs(int i, int j) {
    if (i < 0 || i == n || j < 0 || j == n || nums[i][j] != 0) {
        return;
    }
    nums[i][j]=3;
    dfs(i-1,j);
    dfs(i,j-1);
    dfs(i+1,j);
    dfs(i,j+1);
}

int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%d",&nums[i][j]);
        }
    }
    for(int i=0;i<n;i++){
        if(nums[0][i]==0){
            dfs(0,i);
        }
        if(nums[n-1][i]==0){
            dfs(n-1,i);
        }
    }
    for(int i=1;i<n-1;i++){
        if(nums[i][0]==0){
            dfs(i,0);
        }
        if(nums[i][n-1]==0){
            dfs(i,n-1);
        }
    }
    /*
    printf("-----------------------------\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("%d ",nums[i][j]);
        }
        printf("\n");
    }
    printf("------------------------------\n");
    */
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(nums[i][j]==0)
                nums[i][j]=2;
            else if(nums[i][j]==3)
                nums[i][j]=0;
        }
        //printf("\n");
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("%d ",nums[i][j]);
        }
        printf("\n");
    }
    return 0;
}
