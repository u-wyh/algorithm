// https://www.luogu.com.cn/problem/P4752
// 题意：多组数据，A 由 N 个正整数相乘，B 由 M 个正整数相乘（保证 b 中每个数出现次数不超过 a 中次数），判断 A/B 是否为质数。
// 数据范围：1 <= T <= 10，1 <= N <= 10^5，sum N <= 10^5，0 <= M <= N，1 <= a_i, b_i <= 10^12。
#include<bits/stdc++.h>
using namespace std;

int n,m,cnt;
map<long long,int>M;
long long nums[100005];

bool check(long long num){
    for(int i=2;i<=sqrt(num);i++){
        if(num%i==0){
            return false;
        }
    }
    return true;
}

int main()
{
    int T;
    cin>>T;
    while(T--){
        cin>>n>>m;
        int a,b,cnt1=0,cnt2=0;
        for(int i=1;i<=n;i++){
            cin>>a;
            if(a==1){
                cnt1++;
            }
            else{
                M[a]++;
                nums[++cnt]=a;
            }
        }
        for(int i=1;i<=m;i++){
            cin>>b;
            if(b==1){
                cnt2++;
            }else{
                M[b]--;
            }
        }
        if((n-cnt1)-(m-cnt2)>1){
            cout<<"NO"<<endl;
        }else if((n-cnt1)-(m-cnt2)==1){
            for(int i=1;i<=cnt;i++){
                if(M[nums[i]]==1){
                    if(check(nums[i])){
                        cout<<"YES"<<endl;
                    }else{
                        cout<<"NO"<<endl;
                    }
                    break;
                }
            }
        }else{
            cout<<"NO"<<endl;
        }
        M.clear();
        cnt=0;
    }
    return 0;
}
