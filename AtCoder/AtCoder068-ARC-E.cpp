#include<bits/stdc++.h>
using namespace::std;

/*
	Author: Racso Galvan

	Idea:

	- Data structures problem.

	- Notice that if we fix a d, instead of knowing how many intervals are visited,

	  we can compute the number of intervals that are not visited ever by d.


	- Thus, for each d we can count the number of intervals contained in [x + 1, x + d - 1]

	  for each d | x. Just not forget to consider the last interval [x + 1, m]

	  for x = floor(m / d) * d.

	- Since we are going to analyze the divisors of each d, the sum of positions

	  is O(nlogn), and if we do a sweep over all r values and update a fenwick

	  tree with the l positions of the intervals processed so far, we just need

	  to take the intervals in the corresponding range in O(logn).

	- Complexity: O(mlog^2m + n)

*/

const int N = 100000 + 5;

int n;
int m;
int ft[N];
int ans[N];
queue<int> Q[N];
vector<int> D[N];

void update(int pos, int val){
	pos++;
	while(pos <= m + 1){
		ft[pos] += val;
		pos += (-pos) & pos;
	}
}

int getSum(int pos){
	pos++;
	int res = 0;
	while(pos > 0){
		res += ft[pos];
		pos &= pos - 1;
	}
	return res;
}

void download(int pos){
	while(!Q[pos].empty()){
		update(Q[pos].front(), 1);
		Q[pos].pop();
	}
}

void solve(){
	for(int i = 1; i <= m; i++) ans[i] = n;
	int cnt = 0;
	for(int r = 1; r <= m; r++){
		for(int d : D[r]){
			ans[d] -= cnt - getSum(r - d);
		}
		cnt += Q[r].size();
		download(r);
	}
	for(int i = 1; i <= m; i++){
		ans[i] -= cnt - getSum(m - m % i);
	}
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++){
		int l, r;
		scanf("%d %d", &l, &r);
		Q[r].emplace(l);
	}
	for(int i = 1; i <= m; i++){
		for(int j = i; j <= m; j += i){
			D[j].emplace_back(i);
		}
	}
	solve();
	for(int i = 1; i <= m; i++){
		printf("%d\n", ans[i]);
	}
	return 0;
}
