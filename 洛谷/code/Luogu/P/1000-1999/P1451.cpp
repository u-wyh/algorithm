#include<bits/stdc++.h>
using namespace std;
#define Max 1000

int n,m;
int nums[Max][Max];
char s[Max];

void dfs(int i, int j) {
    if (i < 0 || i == n || j < 0 || j == m || nums[i][j] ==0) {
        return;
    }
    // board[i][j] = '1'
    nums[i][j] = 0;
    dfs(i - 1, j);
    dfs(i + 1, j);
    dfs(i, j - 1);
    dfs(i, j + 1);
}

int main()
{
    cin>>n>>m;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            cin>>s[j];
            nums[i][j]=s[j]-'0';
        }
    }
    int islands = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (nums[i][j] != 0) {
                islands++;
                dfs(i, j);
            }
        }
    }
    printf("%d\n",islands);
    return 0;
}
