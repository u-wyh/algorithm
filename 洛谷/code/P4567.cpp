#include<bits/stdc++.h>
using namespace std;
const int MAXN = (1<<21)+1e4;

int n;
int it;

int head;
int cnt;
int ls[MAXN];
int rs[MAXN];
int sz[MAXN];
char key[MAXN];
bool rev[MAXN];
double priority[MAXN];

int newnode(char c){
    ++cnt;
    key[cnt]=c;
    sz[cnt]=1;
    priority[cnt]=(double)rand()/RAND_MAX;
    return cnt;
}

void up(int i) {
    sz[i] = sz[ls[i]] + sz[rs[i]] + 1;
}

void down(int i) {
    if (rev[i]) {
        swap(ls[i], rs[i]);
        rev[ls[i]] ^= 1;
        rev[rs[i]] ^= 1;
        rev[i] = false;
    }
}

void split(int l, int r, int i, int rank) {
    if (i == 0) {
        rs[l] = ls[r] = 0;
    } else {
        down(i);
        if (sz[ls[i]] + 1 <= rank) {
            rs[l] = i;
            split(i, r, rs[i], rank - sz[ls[i]] - 1);
        } else {
            ls[r] = i;
            split(l, i, ls[i], rank);
        }
        up(i);
    }
}

int merge(int l, int r) {
    if (l == 0 || r == 0) {
        return l + r;
    }
    if (priority[l] >= priority[r]) {
        down(l);//下发懒信息
        rs[l] = merge(rs[l], r);
        up(l);
        return l;
    } else {
        down(r);
        ls[r] = merge(l, ls[r]);
        up(r);
        return r;
    }
}

char getrank(int rk){
    int u=head;
    while(u){
        down(u);
        if(sz[ls[u]]+1==rk){
            return key[u];
        }
        else if(sz[ls[u]]+1<rk){
            rk-=sz[ls[u]]+1;
            u=rs[u];
        }
        else{
            u=ls[u];
        }
    }
    return '\0'; // Return null character if not found
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;
    it=0;
    while(n--){
        string s;
        cin>>s;
        // cout<<' '<<s<<endl;
        if(s[0]=='M'){
            cin>>it;
        }
        else if(s[0]=='P'){
            it--;
        }
        else if(s[0]=='N'){
            it++;
        }
        else if(s[0]=='G'){
            char c=getrank(it+1);
            if(c=='\n'){
                cout<<endl;
            }
            else{
                cout<<c<<endl;
            }
        }
        else{
            int k;
            cin>>k;
            if(s[0]=='I'){
                cin.get();
                split(0,0,head,it);
                int l=rs[0];
                int r=ls[0];
                getline(cin,s);
                // cout<<"    888"<<s<<endl;
                for(int i=1;i<=k;i++){
                    l=merge(l,newnode(s[i-1]));
                }
                head=merge(l,r);
            }
            else if(s[0]=='D'){
                split(0,0,head,it+k);
                int lm=rs[0];
                int r=ls[0];
                split(0,0,lm,it);
                head=merge(rs[0],r);
            }
            else{
                split(0,0,head,it+k);
                int lm=rs[0];
                int r=ls[0];
                split(0,0,lm,it);
                rev[ls[0]]^=1;
                head=merge(merge(rs[0],ls[0]),r);
            }
        }
    }
    return 0;
}