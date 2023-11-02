#include<bits/stdc++.h>
using namespace::std;

const int N = 10 + 5;

int n;
int cnt;
int last;
int x[N];
int y[N];
char ans[N];
bool vis[10];
char s[N][5];

bool check(){
	for(int i = 0; i < n; i++){
		int bulls = 0;
		int cows = 0;
		for(int j = 0; j < 4; j++){
			if(s[i][j] == ans[j]) bulls += 1;
			else if(vis[s[i][j] - '0']) cows += 1;
		}
		if(bulls != x[i] or cows != y[i]) return false;
	}
	return true;
}

void backtracking(int pos, int val){
	if(pos == 4){
		if(check()){
			cnt += 1;
			last = val;
		}
		return;
	}
	for(int i = 0; i < 10; i++){
		if(vis[i]) continue;
		vis[i] = true;
		ans[pos] = '0' + i;
		backtracking(pos + 1, 10 * val + i);
		vis[i] = false;
	}
}

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%s %d %d", s[i], &x[i], &y[i]);
	}
	backtracking(0, 0);
	if(cnt == 0){
		puts("Incorrect data");
		return 0;
	}
	if(cnt > 1) puts("Need more data");
	else printf("%04d\n", last);
	return 0;
}
