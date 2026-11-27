#include<bits/stdc++.h>
using namespace std;

const int MAXN = 5e5+5;

int n;
int p[MAXN];

struct node{
    int mn,mx;
    int sz;
    long long d1,d2;     // 主对角线、副对角线全部亮的时间
};

node st[MAXN];
int topn;

node merge_node(node L,node R,int tp){
    node now;

    now.mn=min(L.mn,R.mn);
    now.mx=max(L.mx,R.mx);
    now.sz=L.sz+R.sz;

    if(tp==1){
        // 正接，L 在左上，R 在右下
        // 大块主对角线由两块主对角线直接拼成
        now.d1=max(L.d1,R.d1);

        // 从主对角线向另一条对角线扩散
        now.d2=now.d1+now.sz-1;
    }
    else{
        // 反接，L 在右上，R 在左下
        // 大块副对角线由两块副对角线直接拼成
        now.d2=max(L.d2,R.d2);

        // 从副对角线向另一条对角线扩散
        now.d1=now.d2+now.sz-1;
    }

    return now;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;

    for(int i=1;i<=n;i++){
        cin>>p[i];
    }

    for(int i=1;i<=n;i++){
        node now;

        now.mn=now.mx=p[i];
        now.sz=1;
        now.d1=now.d2=0;

        st[++topn]=now;

        while(topn>=2){
            node L=st[topn-1];
            node R=st[topn];

            int tp=0;

            if(L.mx+1==R.mn){
                tp=1;
            }
            else if(R.mx+1==L.mn){
                tp=-1;
            }
            else{
                break;
            }

            topn-=2;
            st[++topn]=merge_node(L,R,tp);
        }
    }

    if(topn!=1){
        cout<<-1<<'\n';
        return 0;
    }

    cout<<max(st[1].d1,st[1].d2)<<'\n';

    return 0;
}