#include<bits/stdc++.h>
using namespace std;
struct dlx{
    int row,col;
	int left,right,up,down;
}node[3000]; int cntd=0;
int row[750],ans[100],cnt[350],dp[10][10];
void initnode(int m){
	for(int i=0;i<=m;i++){
		node[i].left=i-1; node[i].right=i+1;
		node[i].up=i; node[i].down=i;
	}
	memset(row,0,sizeof row);
	memset(cnt,0,sizeof cnt);
	node[0].left=m; node[m].right=0; cntd=m;
}
void add(int p,int q){
    ++cntd; cnt[q]++;
	node[cntd].row=p; node[cntd].col=q;
	node[cntd].up=node[q].up; node[cntd].down=q;
	node[node[q].up].down=cntd; node[q].up=cntd;
	if(row[p]==0){
	    row[p]=cntd;
		node[cntd].left=cntd;
		node[cntd].right=cntd;
	} else{
		node[cntd].left=node[row[p]].left;
		node[cntd].right=row[p];
		node[node[cntd].left].right=cntd;
		node[node[cntd].right].left=cntd;
	}
}
void remove(int p){
	for(int i=node[p].down;i!=p;i=node[i].down){
		for(int j=node[i].right;j!=i;j=node[j].right){
			node[node[j].up].down=node[j].down;
			node[node[j].down].up=node[j].up;
			cnt[node[j].col]--;
		}
	}
	node[node[p].right].left=node[p].left;
	node[node[p].left].right=node[p].right;
}
void resume(int p){
	node[node[p].right].left=p;
	node[node[p].left].right=p;
	for(int i=node[p].down;i!=p;i=node[i].down){
		for(int j=node[i].right;j!=i;j=node[j].right){
			node[node[j].up].down=j;
			node[node[j].down].up=j;
			cnt[node[j].col]++;
		}
	}
}
bool dfs(int dep){
	if(node[0].right==0){
		for(int i=1;i<dep;i++){
			int p=(ans[i]-1)/9/9+1,q=(ans[i]-1)/9%9+1;
			int d=(ans[i]-1)%9+1; dp[p][q]=d;
		}
		return 1;
	}
	int p=node[0].right;
	for(int i=node[0].right;i!=0;i=node[i].right){
		if(cnt[i]<cnt[p]) p=i;
	}
	remove(p);
	for(int i=node[p].down;i!=p;i=node[i].down){
		ans[dep]=node[i].row;
		for(int j=node[i].right;j!=i;j=node[j].right){
			remove(node[j].col);
		} if(dfs(dep+1)) return 1;
		for(int j=node[i].right;j!=i;j=node[j].right){
			resume(node[j].col);
		}
	}
	resume(p); return 0;
}
int main(){
    int t;scanf("%d",&t);
    while(t--){
		cntd=0; initnode(324);
    	for(int i=1;i<=9;i++){
    		for(int j=1;j<=9;j++){
    			char ch;cin>>ch;
    			int p=ch^48;
    			for(int k=1;k<=9;k++){
    				if(p!=k&&p!=0) continue;
    				int p1=81*0+9*(i-1)+j; add(81*(i-1)+9*(j-1)+k,p1);
    				int p2=81*1+9*(i-1)+k; add(81*(i-1)+9*(j-1)+k,p2);
    				int p3=81*2+9*(j-1)+k; add(81*(i-1)+9*(j-1)+k,p3);
    				int n=3*((i-1)/3)+(j-1)/3+1;
    				int p4=81*3+9*(n-1)+k; add(81*(i-1)+9*(j-1)+k,p4);
    			}
    		}
    	}
    	dfs(1);
    	for(int i=1;i<=9;i++){
    		for(int j=1;j<=9;j++) printf("%d",dp[i][j]);
    		printf("\n");
    	}
    }
	return 0;
}
