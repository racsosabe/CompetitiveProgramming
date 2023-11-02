#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;
const int MOD = 1000000000 + 7;

int n;
int l;
int memo[N];

int main(){
	scanf("%d %d", &n, &l);
	memo[0] = 1;
	for(int i = 1; i <= n; i++){
		memo[i] = memo[i - 1];
		if(i >= l) memo[i] += memo[i - l];
		if(memo[i] >= MOD) memo[i] -= MOD;
	}
	printf("%d\n", memo[n]);
	return 0;
}
