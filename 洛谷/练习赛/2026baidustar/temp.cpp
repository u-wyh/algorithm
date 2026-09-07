#include<bits/stdc++.h>
using namespace std;

const int MAXN = 2e5+5;

int n,m,k,len;
long long a[MAXN],num[MAXN];
vector<int> pos[MAXN];

set<int> zero;
multiset<int> small,big;

long long sum;
int lim;

void balance(){
    while((int)big.size()>lim){
        int x=*big.begin();
        sum-=x;
        big.erase(big.begin());
        small.insert(x);
    }

    while((int)big.size()<lim&&!small.empty()){
        auto it=prev(small.end());
        int x=*it;
        small.erase(it);
        big.insert(x);
        sum+=x;
    }

    while(!small.empty()&&!big.empty()){
        int x=*prev(small.end());
        int y=*big.begin();

        if(x<=y){
            break;
        }

        small.erase(prev(small.end()));
        big.erase(big.begin());

        small.insert(y);
        big.insert(x);

        sum+=x-y;
    }
}

void addBlock(int x){
    if(x<=0){
        return;
    }

    small.insert(x);
    balance();
}

void delBlock(int x){
    if(x<=0){
        return;
    }

    auto it=big.find(x);

    if(it!=big.end()){
        sum-=x;
        big.erase(it);
    }
    else{
        it=small.find(x);
        small.erase(it);
    }

    balance();
}

void join(int p){
    auto it=zero.find(p);

    int l=*prev(it);
    int r=*next(it);

    delBlock(p-l-1);
    delBlock(r-p-1);

    addBlock(r-l-1);

    zero.erase(it);
}

void del(int p){
    auto it=zero.lower_bound(p);

    int r=*it;
    int l=*prev(it);

    delBlock(r-l-1);

    addBlock(p-l-1);
    addBlock(r-p-1);

    zero.insert(p);
}

void solve(){
    cin>>n>>m>>k;

    for(int i=1;i<=n;i++){
        pos[i].clear();
    }

    for(int i=1;i<=n;i++){
        cin>>a[i];
        num[i]=a[i];
    }

    sort(num+1,num+n+1);

    len=0;

    for(int i=1;i<=n;i++){
        if(i==1||num[i]!=num[i-1]){
            num[++len]=num[i];
        }
    }

    for(int i=1;i<=n;i++){
        int id=lower_bound(num+1,num+len+1,a[i])-num;
        pos[id].push_back(i);
    }

    zero.clear();
    small.clear();
    big.clear();

    for(int i=0;i<=n+1;i++){
        zero.insert(i);
    }

    lim=min(n,m+1);
    sum=0;

    long long ans=LLONG_MAX;

    int r=0;

    for(int l=1;l<=len;l++){

        while(r<len&&sum<k){
            r++;

            for(int p:pos[r]){
                join(p);
            }
        }

        if(sum>=k){
            ans=min(ans,num[r]-num[l]);
        }

        for(int p:pos[l]){
            del(p);
        }
    }

    cout<<ans<<"\n";
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin>>T;

    while(T--){
        solve();
    }

    return 0;
}