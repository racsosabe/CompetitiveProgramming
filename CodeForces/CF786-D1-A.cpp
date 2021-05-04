#include<bits/stdc++.h>
using namespace::std;

const int N = 7000 + 5;

int n;
int deg[2][N];
int memo[2][N];
vector<int> v[2];

void solve(int turn, int pos){
	int prv = turn ^ 1;
	for(auto x : v[prv]){
		int last = (pos + n - x) % n;
		if(memo[prv][last]) continue;
		if(memo[turn][pos] == 1){
			deg[prv][last] -= 1;
			if(deg[prv][last] == 0){
				memo[prv][last] = 2;
				solve(prv, last);
			}
		}
		else{
			memo[prv][last] = 1;
			solve(prv, last);
		}
	}
}

int main(){
	scanf("%d", &n);
	for(int i = 0; i < 2; i++){
		int q;
		scanf("%d", &q);
		for(int j = 0; j < q; j++){
			int x;
			scanf("%d", &x);
			v[i].emplace_back(x);
		}
		for(int j = 0; j < n; j++) deg[i][j] = q;
	}
	memo[0][0] = memo[1][0] = 2;
	solve(0, 0);
	solve(1, 0);
	for(int i = 0; i < 2; i++){
		for(int j = 1; j < n; j++){
			int val = memo[i][j];
			if(!val) printf("Loop");
			else printf("%s", memo[i][j] == 1 ? "Win" : "Lose");
			putchar(" \n"[j + 1 == n]);
		}
	}
	return 0;
}
