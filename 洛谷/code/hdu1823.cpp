#include<bits/stdc++.h>
using namespace std;
const int MAXN = 101;
const int MAXM = 1001;
const int MINX = 100;
const int MAXX = 200;
const int MINY = 0;
const int MAXY = 1000;

int tree[MAXN<<2][MAXM<<2];

void innerbuild(int l,int r,int xi,int i){
    tree[xi][i]=-1;
    if(l<r){
        int mid=(l+r)>>1;
        innerbuild(l,mid,xi,i<<1);
        innerbuild(mid+1,r,xi,i<<1|1);
    }
}

void innerupdate(int jobi,int jobv,int l,int r,int xi,int i){
    if(l==r){
        tree[xi][i]=max(tree[xi][i],jobv);
    }
    else{
        int mid=(l+r)>>1;
        if(jobi<=mid){
            innerupdate(jobi,jobv,l,mid,xi,i<<1);
        }
        else{
            innerupdate(jobi,jobv,mid+1,r,xi,i<<1|1);
        }
        tree[xi][i]=max(tree[xi][i<<1],tree[xi][i<<1|1]);
    }
}

int innerquery(int jobl,int jobr,int l,int r,int xi,int i){
    if(jobl<=l&&r<=jobr){
        return tree[xi][i];
    }
    else{
        int mid=(l+r)>>1;
        int ans=-1;
        if(jobl<=mid){
            ans=max(ans,innerquery(jobl,jobr,l,mid,xi,i<<1));
        }
        if(jobr>mid){
            ans=max(ans,innerquery(jobl,jobr,mid+1,r,xi,i<<1|1));
        }
        return ans;
    }
}

void outerbuild(int l,int r,int i){
    innerbuild(MINY,MAXY,i,1);
    if(l<r){
        int mid=(l+r)>>1;
        outerbuild(l,mid,i<<1);
        outerbuild(mid+1,r,i<<1|1);
    }
}

void outerupdate(int jobx,int joby,int jobv,int l,int r,int i){
    innerupdate(joby,jobv,MINY,MAXY,i,1);
    if(l<r){
        int mid=(l+r)>>1;
        if(jobx<=mid){
            outerupdate(jobx,joby,jobv,l,mid,i<<1);
        }
        else{
            outerupdate(jobx,joby,jobv,mid+1,r,i<<1|1);
        }
    }
}

int outerquery(int jobxl,int jobxr,int jobyl,int jobyr,int l,int r,int i){
    if(jobxl<=l&&r<=jobxr){
        return innerquery(jobyl,jobyr,MINY,MAXY,i,1);
    }
    else{
        int mid=(l+r)>>1;
        int ans=-1;
        if(jobxl<=mid){
            ans=max(ans,outerquery(jobxl,jobxr,jobyl,jobyr,l,mid,i<<1));
        }
        if(jobxr>mid){
            ans=max(ans,outerquery(jobxl,jobxr,jobyl,jobyr,mid+1,r,i<<1|1));
        }
        return ans;
    }
}

int main()
{
    int q;
    scanf("%d",&q);
    while(q){
        outerbuild(MINX,MAXX,1);
        for(int i=1;i<=q;i++){
            char op;
            scanf(" %c",&op);
            if(op=='I'){
                int a;
                double b,c;
                scanf("%d %lf %lf",&a,&b,&c);
                outerupdate(a,(int)(b*10),(int)(c*10),MINX,MAXX,1);
            }
            else {
                int a,b;
                double c,d;
                scanf("%d %d %lf %lf",&a,&b,&c,&d);
                if(a>b){
                    swap(a,b);
                }
                if(c>d){
                    swap(c,d);
                }
                int ans=outerquery(a,b,(int)(c*10),(int)(d*10),MINX,MAXX,1);
                if(ans==-1){
                    printf("-1\n");
                }
                else{
                    printf("%.1lf\n",ans/10.0);
                }
            }
        }
        scanf("%d",&q);
    }
    return 0;
}