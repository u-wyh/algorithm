#include<stdio.h>
#define Max 105

int n,m;
int nums[Max][Max];

void dfs(int i, int j) {
    if (i < 0 || i == n || j < 0 || j == m || nums[i][j] != 1) {
        return;
    }
    nums[i][j] = 0;
    dfs(i - 1, j);
    dfs(i + 1, j);
    dfs(i, j - 1);
    dfs(i, j + 1);
    dfs(i - 1, j - 1);
    dfs(i + 1, j - 1);
    dfs(i - 1, j + 1);
    dfs(i + 1, j + 1);
}

int main()
{
    scanf("%d %d",&n,&m);
    getchar();
    char s[m];
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            scanf("%c",&s[j]);
            if(s[j]=='W')
                nums[i][j]=1;
            else
                nums[i][j]=0;
        }
        getchar();
    }
    int islands = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (nums[i][j] == 1) {
                islands++;
                dfs(i, j);
            }
        }
    }
    printf("%d\n",islands);
    return 0;
}

