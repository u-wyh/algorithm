#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 80005;
const int INF = 1e18;
const int MOD = 1e6;

int n;
long long ans;
int sz1,sz2;
int cnt[2];
int head[2];
int ls[MAXN][2];
int rs[MAXN][2];
double priority[MAXN][2];
int size[MAXN][2];
int key[MAXN][2];

void up(int i,int op) {
    size[i][op] = size[ls[i][op]][op] + size[rs[i][op]][op] + 1;
}

void split(int l, int r, int i, int num,int op) {
    if (i == 0) {
        rs[l][op] = ls[r][op] = 0;
    } else {
        if (key[i][op] <= num) {
            rs[l][op] = i;
            split(i, r, rs[i][op], num,op);
        } else {
            ls[r][op] = i;
            split(l, i, ls[i][op], num,op);
        }
        up(i,op);
    }
}

int merge(int l, int r,int op) {
    if (l == 0 || r == 0) {
        return l + r;
    }
    if (priority[l][op] >= priority[r][op]) {
        rs[l][op] = merge(rs[l][op], r,op);
        up(l,op);
        return l;
    } else {
        ls[r][op] = merge(l, ls[r][op],op);
        up(r,op);
        return r;
    }
}

//没有词频压缩  直接就是新增节点
void add(int num,int op) {
    split(0, 0, head[op], num,op);
    key[++cnt[op]][op] = num;
    size[cnt[op]][op] = 1;
    priority[cnt[op]][op] = (double)rand() / RAND_MAX;
    head[op] = merge(merge(rs[0][op], cnt[op],op), ls[0][op],op);
}

//删除节点的时候 是将树按照num分裂  然后将<=num 的按照 num-1 分裂
//将那么 >num-1 的树头结点一定是num  只要将这个节点忽略就是删除节点
void remove(int num,int op) {
    split(0, 0, head[op], num,op);
    int lm = rs[0][op];
    int r = ls[0][op];
    split(0, 0, lm, num - 1,op);
    int l = rs[0][op];
    int m = ls[0][op];
    head[op] = merge(merge(l, merge(ls[m][op], rs[m][op],op),op), r,op);
}

int pre(int i, int num,int op) {
    if (i == 0) {
        return -INF;
    }
    if (key[i][op] > num) {
        return pre(ls[i][op], num,op);
    } else {
        return max(key[i][op], pre(rs[i][op], num,op));
    }
}

int pre(int num,int op) {
    return pre(head[op], num,op);
}

int post(int i, int num,int op) {
    if (i == 0) {
        return INF;
    }
    if (key[i][op] < num) {
        return post(rs[i][op], num,op);
    } else {
        return min(key[i][op], post(ls[i][op], num,op));
    }
}

int post(int num,int op) {
    return post(head[op], num,op);
}

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        int op,v;
        cin>>op>>v;
        if(op==0&&sz2>0){
            sz2--;
            int a=pre(v,1);
            int b=post(v,1);
            if((v-a)<=(b-v)){
                ans+=(v-a);
                remove(a,1);
            }
            else{
                ans+=(b-v);
                remove(b,1);
            }
        }
        else if(op==0){
            sz1++;
            add(v,0);
        }
        else if(op==1&&sz1>0){
            sz1--;
            int a=pre(v,0);
            int b=post(v,0);
            if((v-a)<=(b-v)){
                ans+=(v-a);
                remove(a,0);
            }
            else{
                ans+=(b-v);
                remove(b,0);
            }
        }
        else{
            sz2++;
            add(v,1);
        }
        ans%=MOD;
    }
    cout<<(ans%MOD);
    return 0;
}