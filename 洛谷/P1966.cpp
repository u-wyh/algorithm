#include<bits/stdc++.h>
using namespace std;
const int mod = 99999997;

int n;
int a[100005],b[100005],c[100005],d[100005],A[100005],B[100005];
int father[100005],Size[100005],Stack[100005];

void build(int n){
    for(int i=1;i<=n;i++){
        father[i]=i;
        Size[i]=1;
    }
}

int find(int i){
    int sz=0;
    while(i!=father[i]){
        Stack[sz++]=i;
        i=father[i];
    }
    while(sz>0){
        father[Stack[--sz]]=i;
    }
    return i;
}

void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        if(Size[fx]>=Size[fy]){
            Size[fx]+=Size[fy];
            father[fy]=fx;
        }else{
            Size[fy]+=Size[fx];
            father[fx]=fy;
        }
    }
}


int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        A[i]=a[i];
    }
    for(int i=1;i<=n;i++){
        cin>>b[i];
        B[i]=b[i];
    }
    sort(A+1,A+n+1);
    sort(B+1,B+n+1);
    for(int i=1;i<=n;i++){
        c[i]=lower_bound(A+1,A+n+1,a[i])-A;
        printf("%3d",c[i]);
    }
    cout<<endl;
    for(int i=1;i<=n;i++){
        d[i]=lower_bound(B+1,B+n+1,b[i])-B;
        printf("%3d",d[i]);
    }
    cout<<endl;
    build(n);
    for(int i=1;i<=n;i++){
        if(c[i]!=d[i]){
            un(c[i],d[i]);
        }
    }
    int cnt=0;
    for(int i=1;i<=n;i++){
        if(Size[c[i]]!=1&&father[c[i]]==c[i]){
            cnt=(cnt+(Size[c[i]]-1)%mod)%mod;
        }
    }
    cout<<cnt;
    return 0;
}
