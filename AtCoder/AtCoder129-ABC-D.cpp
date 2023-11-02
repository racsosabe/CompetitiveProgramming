#include<bits/stdc++.h>
using namespace::std;

const int N = 2000 + 5;

int n;
int m;
char s[N][N];

int solveTwoPointers(){
	vector< vector<int> > vertical(n + 1, vector<int>(m + 1, 0));
	for(int j = 1; j <= m; j++){
		int L = 1, R = 1;
		while(L <= n){
			while(L <= n and s[L][j] == '#') L += 1;
			if(L > n) break;
			R = L;
			while(R <= n and s[R][j] != '#') R += 1;
			int len = R - L;
			for(int i = L; i < R; i++){
				vertical[i][j] = len;
			}
			L = R;
		}
	}
	int ans = 0;
	for(int i = 1; i <= n; i++){
		int L = 1, R = 1;
		while(L <= m){
			while(L <= m and s[i][L] == '#') L += 1;
			if(L > m) break;
			R = L;
			while(R <= m and s[i][R] != '#') R += 1;
			int len = R - L;
			for(int j = L; j < R; j++){
				int cur = len + vertical[i][j] - 1;
				ans = max(ans, cur);
			}
			L = R;
		}
	}
	return ans;
}

int solveDP(){
	vector< vector<int> > L(n + 2, vector<int>(m + 2, 0)), R(n + 2, vector<int>(m + 2, 0)), U(n + 2, vector<int>(m + 2, 0)), D(n + 2, vector<int>(m + 2, 0));
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			if(s[i][j] == '#') continue;
			L[i][j] = 1 + L[i][j - 1];
			U[i][j] = 1 + U[i - 1][j];
		}
	}
	for(int i = n; i >= 1; i--){
		for(int j = m; j >= 1; j--){
			if(s[i][j] == '#') continue;
			R[i][j] = 1 + R[i][j + 1];
			D[i][j] = 1 + D[i + 1][j];
		}
	}
	int ans = 0;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			if(s[i][j] == '#') continue;
			int cur = L[i][j] + R[i][j] + D[i][j] + U[i][j] - 3;
			ans = max(ans, cur);
		}
	}
	return ans;
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++){
		scanf("%s", s[i] + 1);
	}
	printf("%d\n", solveTwoPointers());
	return 0;
}
