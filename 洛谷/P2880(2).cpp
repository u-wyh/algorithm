//对数组进行更新操作，并求最大值
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 50005;

int arr[MAXN];
int Max[MAXN<<2];
int Min[MAXN<<2];
int n,m;

//比较左右两边最大值
void maxup(int i) {
    Max[i] = max(Max[i << 1] ,Max[i << 1 | 1]);
}

void minup(int i) {
    Min[i] = min(Min[i << 1] ,Min[i << 1 | 1]);
}

int maxquery(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return Max[i];
    }
    int mid = (l + r) >> 1;
    int ans = 0;
    if (jobl <= mid) {
        ans =max(ans, maxquery(jobl, jobr, l, mid, i << 1));
    }
    if (jobr > mid) {
        ans =max(ans, maxquery(jobl, jobr, mid + 1, r, i << 1 | 1));
    }
    return ans;
}

int minquery(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return Min[i];
    }
    int mid = (l + r) >> 1;
    int ans = 1e9;
    if (jobl <= mid) {
        ans =min(ans, minquery(jobl, jobr, l, mid, i << 1));
    }
    if (jobr > mid) {
        ans =min(ans, minquery(jobl, jobr, mid + 1, r, i << 1 | 1));
    }
    return ans;
}

void maxbuild(int l, int r, int i) {
    if (l == r) {
        Max[i] = arr[l];
    } else {
        int mid = (l + r) >> 1;
        maxbuild(l, mid, i << 1);
        maxbuild(mid + 1, r, i << 1 | 1);
        maxup(i);
    }
}

void minbuild(int l, int r, int i) {
    if (l == r) {
        Min[i] = arr[l];
    } else {
        int mid = (l + r) >> 1;
        minbuild(l, mid, i << 1);
        minbuild(mid + 1, r, i << 1 | 1);
        minup(i);
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        cin>>arr[i];
    maxbuild(1,n,1);
    minbuild(1,n,1);
    /*
    for(int i=1;i<=13;i++)
        printf("%3d",Max[i]);
    printf("\n");
    for(int i=1;i<=13;i++)
        printf("%3d",Min[i]);
    printf("\n");
    */
    for (int i = 1, jobl, jobr; i <= m; i++) {
        cin>>jobl>>jobr;
        //cout<<maxquery(jobl,jobr,1,n,1)<<' '<<minquery(jobl,jobr,1,n,1)<<' '
        cout<<maxquery(jobl,jobr,1,n,1)-minquery(jobl,jobr,1,n,1)<<endl;
    }
    return 0;
}

