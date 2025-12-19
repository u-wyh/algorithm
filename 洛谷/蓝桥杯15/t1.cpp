#include <bits/stdc++.h>
using namespace std;
const int size = 5;
int a[10][10],cnt = 0;

bool check(){
	int cnt_1 = 0,cnt_2 = 0;
	for (int i = 1; i <= size; i++) 
		for (int j = 1; j <= size; j++) {
			if (a[i][j] == 1) cnt_1++;
			if (a[i][j] == 2) cnt_2++;
		}
	if (cnt_1 - cnt_2 != 1) 
        return true;
	for (int i = 1; i <= size; i++) {
		bool flag = true;
		for (int j = 1; j <= size; j++) {
			if (a[i][j] != a[i][1]) {
				flag = false;
				break;
			}
		}
		if (flag) return true;
	}
	for (int i = 1; i <= size; i++) {
		bool flag = true;
		for (int j = 1; j <= size; j++) {
			if (a[j][i] != a[1][i]) {
				flag = false;
				break;
			}
		}
		if (flag) return true;
	}
	bool flag = true;
	for (int i = 1; i <= size; i++) {
		if (a[i][i] != a[1][1]) {
			flag = false;
			break;
		}
	}
	if (flag) return true;
	flag = true;
	for (int i = 5,j = 1; i >= 1 && j <= size; i--,j++) {
		if (a[i][j] != a[size][1]) {
			flag = false;
			break;
		}
	}
	if (flag) return true;
	else return false;
}

void dfs(int x,int y){
	if (y == size + 1) {
		dfs(x + 1,1);
		return;
	}
	if (x == size + 1) {
		if (!check()) cnt++;
		return;
	}
	a[x][y] = 1;
	dfs(x,y + 1);
	a[x][y] = 0;
	a[x][y] = 2;
	dfs(x,y + 1);
	a[x][y] = 0;
	return;
}

int main()
{
	// dfs(1,1);
	// printf("%d",cnt);
    cout<<3126376;
	return 0;
}