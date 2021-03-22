#include<bits/stdc++.h>
using namespace::std;

/*
	Author: Racso Galvan
	
	Idea: 
		- Nice DP problem.

		- First, let's notice that the optimal solution will be an interval
		  of restaurants and there's actually no need to turn backwards.

		- Now, it only reduces to the following:

		  Ans = max_{i < j}(C(i,j))

		  where we can get the cost function in O(m) with a Sparse table for each ticket.

		- Observation: Just realize that if we denote max(L, R) as the maximum

		  of the elements in an subarray v[L...R], then:

		  max(a, d) + max(b, c) <= max(a, c) + max(b, d) with a <= b <= c <= d

		  However, this implies that:

		  C(a, d) + C(b, c) <= C(a, c) + C(b, d) with a <= b <= c <= d

		  This is sufficient to apply Divide and Conquer Optimization for the problem

		- Complexity: O(mnlogn)
*/

const int N = 5000 + 5;
const int M = 200 + 5;
const int LOG = 18;

int n;
int m;
int b[M][N];
long long a[N];
int ST[M][N][LOG];
long long memo[N];

void build(){
	for(int id = 1; id <= m; id++){
		for(int i = 1; i <= n; i++) ST[id][i][0] = b[id][i];
		for(int d = 1; 1 << d <= n; d++){
			int dis = 1 << (d - 1);
			for(int i = 1; i + 2 * dis - 1 <= n; i++){
				ST[id][i][d] = max(ST[id][i][d - 1], ST[id][i + dis][d - 1]);
			}
		}
	}
}

int getMax(int id, int l, int r){
	int d = r - l + 1;
	int k = 31 - __builtin_clz(d);
	int dis = 1 << k;
	return max(ST[id][l][k], ST[id][r - dis + 1][k]);
}

long long C(int l, int r){
	long long res = 0;
	for(int i = 1; i <= m; i++){
		res += getMax(i, l, r);
	}
	return res - a[r] + a[l];
}

void solve(int L, int R, int optL, int optR){
	if(L > R) return;
	int mi = (L + R) / 2;
	int bestMid = -1;
	long long bestAns = LLONG_MIN;
	for(int i = max(mi, optL); i <= optR; i++){
		long long cand = C(mi, i);
		if(bestAns < cand){
			bestAns = cand;
			bestMid = i;
		}
	}
	memo[mi] = bestAns;
	solve(L, mi - 1, optL, bestMid);
	solve(mi + 1, R, bestMid, optR);
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 2; i <= n; i++){
		scanf("%lld", a + i);
		a[i] += a[i - 1];
	}
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			scanf("%d", &b[j][i]);
		}
	}
	build();
	solve(1, n, 1, n);
	printf("%lld\n", *max_element(memo + 1, memo + n + 1));
	return 0;
}
