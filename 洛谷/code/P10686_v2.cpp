#include<bits/stdc++.h>//万能头
using namespace std;
const int N=5e6+10;

struct T{
	int a,b,c;
}t[N];

int n,m,fa[N],ans1,ans2,ansnum;//ans1是裁判，ans2是轮数，ansnum是统计裁判的个数

inline void init(){//初始化并查集
	for(int i=1;i<=3*n;i++)	fa[i]=i;
}

inline int find(int x){//查询
	return x==fa[x]?x:fa[x]=find(fa[x]);
}

inline void noin(int x,int y){//合并
	fa[find(x)]=find(y);
}

int main(){
	while(cin>>n){
		cin>>m;
		ans1=0,ans2=0,ansnum=0;
		init();
		if(m==0){	printf("Player 0 can be determined to be the judge after 0 lines\n");continue;}//特判一下
		for(int i=1;i<=m;i++){
			char s;
			cin>>t[i].a>>s>>t[i].b;
			t[i].a++,t[i].b++;//去掉小朋友为0的情况
			if(s=='>') t[i].c=1;
			if(s=='=') t[i].c=2;
			if(s=='<'){//统一 成'>'
				t[i].c=1;
				swap(t[i].a,t[i].b);
			}
		}
		for(int i=1;i<=n;i++){//枚举裁判
			int flag=1;//记录是否存在裁判
			init();//初始化
			for(int j=1;j<=m;j++){
				if(t[j].a==i||t[j].b==i)	continue;
				if(t[j].c==2){//平局
//					if(t[j].a==t[j].b)	continue;//要不要都一样的(*/ω＼*)
					if((find(t[j].a)==find(t[j].b+n))||(find(t[j].a+n)==find(t[j].b))){
						flag=0;//没有裁判
						ans2=max(ans2,j);break;//记录轮数
					}
					noin(t[j].a,t[j].b);
					noin(t[j].a+n,t[j].b+n);
					noin(t[j].a+2*n,t[j].b+2*n);
				}
				if(t[j].c==1){//'>'的情况(已处理过'<'的情况了)
					if((find(t[j].a)==find(t[j].b))||(find(t[j].a)==find(t[j].b+n))){
						flag=0;//没有裁判
						ans2=max(ans2,j);break;//记录轮数
					}
					noin(t[j].a,t[j].b+2*n);
					noin(t[j].a+n,t[j].b);
					noin(t[j].a+2*n,t[j].b+n);
				}
			}
			if(flag==1) ansnum++,ans1=i;//存在裁判，就记录答案
		//	cout<<ansnum<<'\n';
		}
		if(ansnum==1)	printf("Player %d can be determined to be the judge after %d lines\n",ans1-1,ans2);//因为我们最开始把小朋友多加了 1，所以此时还原减 1
		else if(ansnum>1)	printf("Can not determine\n");//存在多个裁判
		else	printf("Impossible\n");//找不到裁判
	}
	return 0;
}
