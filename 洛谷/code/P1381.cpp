#include<bits/stdc++.h>
using namespace std;
const int MAXM = 1e5+5;
const int BASE = 499;

int n,m,need;
map<long long,int>ques;
map<long long,int>sum;
long long word[MAXM];

// 计算一个字符串的哈希值
long long hashString(const string& str) {
    if (str.empty()) {
        return 0;
    }
    int n = str.length();
    long long ans = str[0] - 'a' + 1;
    for (int j = 1; j < n; ++j) {
        ans = ans * BASE + str[j] - 'a' + 1;
    }
    return ans;
}

bool check(int limit){
    int t=0;
    for(int i=1;i<=limit;i++){
        if(++sum[word[i]]==ques[word[i]]){
            t++;
            if(t==need){
                for(int j=1;j<=i;j++){
                    sum[word[j]]=0;
                }
                return true;
            }
        }
    }
    for(int i=limit+1;i<=m;i++){
        if(sum[word[i-limit]]==ques[word[i-limit]]){
            t--;
        }
        sum[word[i-limit]]--;
        if(++sum[word[i]]==ques[word[i]]){
            t++;
            if(t==need){
                for(int j=1;j<=i;j++){
                    sum[word[j]]=0;
                }
                return true;
            }
        }
    }
    for(int i=1;i<=m;i++){
        sum[word[i]]=0;
    }
    return false;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        string s;
        cin>>s;
        long long val=hashString(s);
        ques[val]++;
    }
    cin>>m;
    for(int i=1;i<=m;i++){
        string s;
        cin>>s;
        word[i]=hashString(s);
    }
    int debt=n;
    for(int i=1;i<=m;i++){
        if(++sum[word[i]]==ques[word[i]]){
            debt--;
        }
    }
    for(int i=1;i<=m;i++){
        sum[word[i]]=0;
    }
    need=n-debt;
    cout<<need<<endl;
    if(need==0){
        cout<<0<<endl;
        return 0;
    }
    int l=need,r=m,ans=m;
    while(l<=r){
        int mid=(l+r)/2;
        if(check(mid)){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    cout<<ans<<endl;
    return 0;
}
