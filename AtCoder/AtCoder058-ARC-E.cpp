#include<bits/stdc++.h>
using namespace::std;

const int N = 40 + 5;
const int MOD = 1000000000 + 7;

int n;
int a[4];
int C[N];
int Q[10][10];
bool vis[N][10][4];
int memo[N][10][4];

void preprocess(){
	Q[0][0] = 1;
	for(int i = 1; i <= 7; i++){
		for(int j = 1; j <= i; j++){
			for(int k = 1; k <= i; k++){
				Q[i][j] += Q[i - k][j - 1];
				if(Q[i][j] >= MOD) Q[i][j] -= MOD;
			}
		}
	}

}

int solve(){
	
}

int main(){
	scanf("%d", &n);
	for(int i = 0; i < 3; i++) scanf("%d", a + i);
	preprocess();
	printf("%d\n", solve());
	return 0;
}
