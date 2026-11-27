// https://www.luogu.com.cn/problem/P4421
// 题意：N 个用户各有一个密码字符串，当输入串包含某用户密码作为连续子串时可登录该用户
// 求有多少对不同用户的有序对 (i, j) 使得用第 i 个用户的密码可登录第 j 个用户。
// 数据范围：1 <= N <= 20000，每个密码由 1..10 个小写英文字母组成。
#include<bits/stdc++.h>
// 算法标签：字符串、枚举
using namespace std;

map<string,int>cnt;
map<string,int>ok;
int n;
string str[20005];

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>str[i];
    }
    //cout<<endl;
    for(int i=1;i<=n;i++){
        //cout<<i<<':'<<endl;
        for(int j=1;j<=str[i].length();j++){
            for(int k=0;k+j<=str[i].length();k++){
                string s1=str[i].substr(k,j);
                if(ok[s1]!=i){
                    //cout<<s1<<endl;
                    cnt[s1]++;
                    ok[s1]=i;
                }
            }
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        ans+=cnt[str[i]];
    }
    ans-=n;
    cout<<ans<<endl;
    return 0;
}
