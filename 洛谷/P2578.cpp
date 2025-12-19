#include<bits/stdc++.h>

bool hsh[100000000];

int Zip(int xx[]){ // 将一个表示矩阵的数组转化为一个表示状态的数组
	int Ans = 0;
	for(int i = 1; i <= 8; i++){
		Ans *= 10;
		Ans += xx[i];
	}
	return Ans;
}

struct Point{
	int Step;
	int Sit[10];
    int Last;
}q[1000010];
int qf = 1, qe = 1;

void Dfs(int Cur){
    if(Cur != 1)
        Dfs(q[Cur].Last);
    printf("%d %d %d\n%d %d %d\n%d %d %d\n\n", q[Cur].Sit[1], q[Cur].Sit[2], q[Cur].Sit[3], q[Cur].Sit[4], q[Cur].Sit[5], q[Cur].Sit[6], q[Cur].Sit[7], q[Cur].Sit[8], q[Cur].Sit[9]);
}
int main(){
	char s;
	q[1].Step = 0;
	for(int i = 1; i <= 9; i++){
        scanf("%d", &q[1].Sit[i]);
	}
	while(qf <= qe){
    	if(Zip(q[qf].Sit) == 1234567){
			printf("%d\n", q[qf].Step);
            Dfs(qf);
			return 0;
		}
		Point Prev = q[qf];
        q[++qe] = Prev;
        q[qe].Last = qf;
        q[qe].Step++;
        std::swap(q[qe].Sit[7], q[qe].Sit[4]);
        std::swap(q[qe].Sit[8], q[qe].Sit[7]);
        std::swap(q[qe].Sit[9], q[qe].Sit[8]);
        std::swap(q[qe].Sit[6], q[qe].Sit[9]);
        std::swap(q[qe].Sit[3], q[qe].Sit[6]);
        std::swap(q[qe].Sit[2], q[qe].Sit[3]);
        std::swap(q[qe].Sit[1], q[qe].Sit[2]);
        int kkk = Zip(q[qe].Sit);
        if(hsh[kkk])
            qe--;
        hsh[kkk] = true;

        q[++qe] = Prev;
        q[qe].Last = qf;
        q[qe].Step++;
        std::swap(q[qe].Sit[6], q[qe].Sit[5]);
        std::swap(q[qe].Sit[5], q[qe].Sit[4]);
        kkk = Zip(q[qe].Sit);
        if(hsh[kkk])
            qe--;
        hsh[kkk] = true;
        
        qf++;
	}
    printf("-1");
}