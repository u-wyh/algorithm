#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e3+5;
const int MAXM = 1<<11;

int n;
int val[MAXN][MAXN];
int tmp[MAXN][MAXN];
// vector<int>vec[MAXM];
set<int>st;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            cin>>val[i][j];
            val[j][i]=val[i][j];
            // vec[i][val[i][j]].push_back(j);
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i!=j){
                tmp[i][j]=val[i][j]^j;
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            int v=(i-1)*n+j;
            if(val[i][j]==(i^j))
                st.insert(v);
        }
    }
    for(int i=1;i<=n;i++){
        if((int)st.size()==n-1){
            break;
        }
        // vector<int>vec[MAXM];
        // for(int j=1;j<=n;j++){
        //     vec[val[i][j]].push_back(j);
        // }
        vector<int>del;
        for(auto edge:st){
            int u=(edge-1)/n+1;
            int v=(edge-1)%n+1;
            if(tmp[i][v]!=val[i][u]&&tmp[i][u]!=val[i][v]){
                del.push_back(edge);
            }
        }
        for(auto val:del){
            st.erase(val);
        }
    }
    for(auto v:st){
        cout<<((v-1)/n+1)<<' '<<((v-1)%n+1)<<endl;
    }
    return 0;
}