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
