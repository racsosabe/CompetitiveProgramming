#include<bits/stdc++.h>
using namespace::std;

const int N = 100 + 5;

int n;
int m;
char a[N];
char b[N];
int memo[N][N];

int main(){
	scanf("%s", a + 1);
	scanf("%s", b + 1);
	n = strlen(a + 1);
	m = strlen(b + 1);
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			if(a[i] == b[j]){
				memo[i][j] = 1 + memo[i - 1][j - 1];
			}
			else{
				memo[i][j] = max(memo[i - 1][j], memo[i][j - 1]);
			}
		}
	}
	vector<int> A, B;
	int x = n, y = m;
	while(x >= 1 and y >= 1){
		if(a[x] == b[y]){
			A.emplace_back(x);
			B.emplace_back(y);
			x -= 1;
			y -= 1;
		}
		else{
			if(memo[x - 1][y] > memo[x][y - 1]) x -= 1;
			else y -= 1;
		}
	}
	reverse(A.begin(), A.end());
	reverse(B.begin(), B.end());
	printf("%d\n", memo[n][m]);
	for(int i = 0; i < A.size(); i++){
		printf("%d%c", A[i], " \n"[i + 1 == A.size()]);
	}
	for(int i = 0; i < B.size(); i++){
		printf("%d%c", B[i], " \n"[i + 1 == B.size()]);
	}
	return 0;
}
