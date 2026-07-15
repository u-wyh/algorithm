#include<bits/stdc++.h>
using namespace std;

int n,m,q;
int xsum[100005],ysum[100005];

void xup(int i) {
    xsum[i] = xsum[i << 1] + xsum[i << 1 | 1];
}

void xUpdate(int jobl, int l, int r, int i) {
    if (l==r) {
        xsum[i]^=1;
    } else {
        int mid = (l + r) >> 1;
        if (jobl <= mid) {
            xUpdate(jobl, l, mid, i << 1);
        }else {
            xUpdate(jobl, mid + 1, r, i << 1 | 1);
        }
        xup(i);
    }
}

int xquery(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return xsum[i];
    }
    int mid = (l + r) >> 1;
    int ans = 0;
    if (jobl <= mid) {
        ans += xquery(jobl, jobr, l, mid, i << 1);
    }
    if (jobr > mid) {
        ans += xquery(jobl, jobr, mid + 1, r, i << 1 | 1);
    }
    return ans;
}

void yup(int i) {
    ysum[i] = ysum[i << 1] + ysum[i << 1 | 1];
}

void yUpdate(int jobl, int l, int r, int i) {
    if (l==r) {
        ysum[i]^=1;
    } else {
        int mid = (l + r) >> 1;
        if (jobl <= mid) {
            yUpdate(jobl, l, mid, i << 1);
        }else {
            yUpdate(jobl, mid + 1, r, i << 1 | 1);
        }
        yup(i);
    }
}

int yquery(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return ysum[i];
    }
    int mid = (l + r) >> 1;
    int ans = 0;
    if (jobl <= mid) {
        ans += yquery(jobl, jobr, l, mid, i << 1);
    }
    if (jobr > mid) {
        ans += yquery(jobl, jobr, mid + 1, r, i << 1 | 1);
    }
    return ans;
}

int main()
{
    cin>>n>>m>>q;
    for(int i=1;i<=q;i++){
        int op,x,y,x1,y1;
        cin>>op;
        if(op==1){
            cin>>x>>y;
            xUpdate(x,1,n,1);
            yUpdate(y,1,n,1);
        }else{
            cin>>x>>y>>x1>>y1;
            cout<<xquery(x,x1,1,n,1)*(y1-y+1)+yquery(y,y1,1,n,1)*(x1-x+1)-2*xquery(x,x1,1,n,1)*yquery(y,y1,1,n,1)<<endl;
        }
    }
    return 0;
}
