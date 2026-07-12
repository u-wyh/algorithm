#include<bits/stdc++.h>
using namespace std;
#define int long long

struct node{
    int a,b,c;
};

node start;
node target;

void make_state(node &a){
    int aa=a.a;
    int bb=a.b;
    int cc=a.c;
    a.a=min(aa,min(bb,cc));
    a.c=max(aa,max(bb,cc));
    a.b=(aa+bb+cc)-a.a-a.c;
}

bool check(node a,node b){
    if(a.a==b.a&&a.b==b.b&&a.c==b.c){
        return true;
    }
    return false;
}

pair<node,int> get_root(node a){
    int dep=0;
    while(true){
        int lt=a.b-a.a;
        int rt=a.c-a.b;

        if(lt==rt){
            break;
        }

        if(lt<rt){
            int k=(rt-1)/lt;
            dep+=k;
            a.a+=k*lt;
            a.b+=k*lt;
        }
        else{
            int k=(lt-1)/rt;
            dep+=k;
            a.b-=k*rt;
            a.c-=k*rt;
        }
    }
    return {a,dep};
}

node jump(node a,int step){
    while(step>0){
        int lt=a.b-a.a;
        int rt=a.c-a.b;

        if(lt==rt){
            break ;
        }

        if(lt<rt){
            int k=min(step,(rt-1)/lt);
            step-=k;
            a.a+=k*lt;
            a.b+=k*lt;
        }
        else{
            int k=min(step,(lt-1)/rt);
            step-=k;
            a.b-=k*rt;
            a.c-=k*rt;
        }
    }
    return a;
}

signed main()
{
    cin>>start.a>>start.b>>start.c;
    cin>>target.a>>target.b>>target.c;

    make_state(start);
    make_state(target);

    auto [root1,dep1]=get_root(start);
    auto [root2,dep2]=get_root(target);

    if(!check(root1,root2)){
        cout<<"NO"<<endl;
        return 0;
    }
    cout<<"YES"<<endl;

    int ans=0;

    if(dep1>dep2){
        ans+=dep1-dep2;
        start=jump(start,dep1-dep2);
        dep1=dep2;
    }
    else if(dep2>dep1){
        ans+=dep2-dep1;
        target=jump(target,dep2-dep1);
        dep2=dep1;
    }

    if(check(start,target)){
        cout<<ans<<endl;
        return 0;
    }

    for(int i=62;i>=0;i--){
        int step=1ll<<i;

        if(step>dep1){
            continue;
        }

        node tmp1=jump(start,step);
        node tmp2=jump(target,step);

        if(!check(tmp1,tmp2)){
            start=tmp1;
            target=tmp2;
            dep1-=step;
            dep2-=step;
            ans+=2*step;
        }
    }

    ans+=2;
    cout<<ans<<endl;
    return 0;
}