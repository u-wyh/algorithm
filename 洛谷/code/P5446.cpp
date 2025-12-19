#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e6+55;

char ss[MAXN << 1];//这个数组中间添加了#
char a[MAXN];//原始数组
int p[MAXN << 1];//半径数组
int n;
bool vis[MAXN<<1];
stack<int>st;

void manacherss() {
    n = strlen(a) * 2 + 1;
    for (int i = 0, j = 0; i < n; i++) {
        ss[i] = (i & 1) == 0 ? '#' : a[j++];
    }
}

void manacher() {
    manacherss();
    for (int i = 0, c = 0, r = 0, len; i < n; i++) {//i是此时来到的中心位置
        len = r > i ? min(p[2 * c - i], r - i) : 1;//这个值是基本值  如果包住了  那么基本值就是最终值  否则后续再加
        while (i + len < n && i - len >= 0 && ss[i + len] == ss[i - len]) {
            len++;
            //如果被包住了  那么直接跳出来了
        }
        //此时已经求出了以i为中心的回文半径大小
        if (i + len > r) {
            r = i + len;
            c = i;//c表示的是如今的r是以那个点为中心的右边界
            //如果更新了右边界  那么c就是i  r就是i+len
        }
        p[i] = len-1;
        //得到回文半径
    }
}

int main()
{
    int T;
    cin>>T;
    while(T--){
        scanf("%s",a);
        manacher();
        for(int i=0;i<=n;i++){
            vis[i]=false;
        }
        vis[n-2]=true;
        for(int i=n-2;i>=1;i-=2){
            if(i+p[i]-1==(n-2)){
                //st.push((i+1)/2);
                vis[i]=true;
            }
            else if(i==p[i]&&vis[i+p[i]-1]){
                //st.push((i+1)/2);
                vis[i]=true;
            }
        }
        for(int i=1;i<=n-2;i++){
            if(vis[i]){
                cout<<(i+1)/2<<' ';
            }
        }
        cout<<endl;
    }
    return 0;
}
