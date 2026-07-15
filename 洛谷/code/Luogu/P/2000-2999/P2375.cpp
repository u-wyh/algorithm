#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;
const int MOD = 1e9+7;

char s1[MAXN];
int Next[MAXN];
int cnt[MAXN];
long long ans=1;

// 计算next数组
void nextArray(const char *s, int m) {
    if (m == 1) {
        ans=1;
        return ;
    }

    Next[0] = -1;
    cnt[1] = 1;

    int i = 2, cn = 0;
    // i表示当前要求next值的位置
    // cn表示当前要和前一个字符比对的下标
    while (i < m) {
        if (s[i - 1] == s[cn]) {
            Next[i] = ++cn;
            cnt[++i]=cnt[cn]+1;
        } else if (cn > 0) {
            cn = Next[cn];
        } else {
            Next[i++] = 0;
        }
    }
}

int main()
{
    int T;
    cin>>T;
    while(T--){
        scanf("%s",s1);
        memset(cnt,0,sizeof(cnt));
        memset(Next,0,sizeof(Next));
        ans=1;
        int n=strlen(s1);
        cout<<n<<endl;
        nextArray(s1,n);
        for(int i=0;i<=n;i++){
            cout<<cnt[i]<<' ';
        }
        cout<<endl;
//        for(int i=1;i<n;i++){
//            int k=i;
//            while(Next[k]*2>i){
//                k=Next[k];
//            }
//            ans=(ans*(cnt[k]+1))%MOD;
//        }
        cout<<ans<<endl;
    }
    return 0;
}
