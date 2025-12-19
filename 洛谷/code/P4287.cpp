#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;

char ss[MAXN << 1];//这个数组中间添加了#
char a[MAXN];//原始数组
int p[MAXN << 1];//半径数组
int l[MAXN<<1];
int n;

void manacherss() {
    n = strlen(a) * 2 + 1;
    for (int i = 0, j = 0; i < n; i++) {
        ss[i] = (i & 1) == 0 ? '#' : a[j++];
    }
}

void manacher() {
    manacherss();
    for (int i = 0, c = 0, r = 0, len; i < n; i++) {
        len = r > i ? min(p[2 * c - i], r - i) : 1;
        while (i + len < n && i - len >= 0 && ss[i + len] == ss[i - len]) {
            len++;
        }
        if (i + len > r) {
            r = i + len;
            c = i;
        }
        p[i] = len;
    }
}

int main()
{
    scanf("%d %s",&n,a);
    manacher();
    for (int i = 0, j = 0; i < n; i++) {
        while (i + p[i] > j) {
            l[j] = j - i;
            j += 2;//只想遇到#
        }
    }
    // for(int i=0;i<n;i++){
    //     cout<<setw(3)<<i;
    // }
    // cout<<endl;
    // for(int i=0;i<n;i++){
    //     cout<<setw(3)<<p[i];
    // }
    // cout<<endl;
    // for(int i=0;i<n;i++){
    //     cout<<setw(3)<<l[i];
    // }
    // cout<<endl;
    int ans=0;
    for(int i=0;i<n;i+=2){
        if(l[i]%4==0&&l[i]>ans){
            if((p[i-l[i]/2*3]-1)>=l[i]/2){
                ans=l[i];
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}