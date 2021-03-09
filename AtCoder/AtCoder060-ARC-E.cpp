#include<bits/stdc++.h>
using namespace::std;

/*
	Author: Racso Galvan

	Idea:

	- LCA problem.

	- Just notice that is never suboptimal to go to the rightmost hotel that you can

	  in one move.

	- So, we can compute a function nxt(i) that gives us the optimal hotel to arrive.

	  We can compute it using binary search or two pointers approach.

	- Now, we just want to go the furthest to the right such that our rightmost

	  possible hotel is >= target hotel. (Let's just consider that a < b)

	- We can just consider a Directed Graph using edges (nxt(i), i) and basically

	  we will want to know the distance between a and it's lowest ancestor v

	  such that v >= b. Thus, we will compute the sparse table for querying the

	  ancestor at a distance 2^k in O(1). We will solve the queries in O(logn).

	- Complexity: O((n + q)logn)

*/

const int N = 100000 + 5;
const int LOG = 20;

int n;
int L;
int q;
int x[N];
int h[N];
int nxt[N];
int ST[N][LOG];
vector<int> G[N];

void computeLCA(int u, int p){
	ST[u][0] = p;
	for(int d = 1; 1 << d <= h[u]; d++){
		ST[u][d] = ST[p][0];
		p = ST[p][d];
	}
}

void DFS(int u, int p = n){
	computeLCA(u, p);
	for(int v : G[u]){
		h[v] = h[u] + 1;
		DFS(v, u);
	}
}

void preprocess(){
	int suma = 0;
	int R = 0;
	for(int i = 0; i + 1 < n; i++){
		while(R + 1 < n and suma + x[R + 1] - x[R] <= L){
			suma += x[R + 1] - x[R];
			R += 1;
		}
		suma -= x[i + 1] - x[i];
		nxt[i] = R;
	}
	for(int i = 0; i + 1 < n; i++){
		G[nxt[i]].emplace_back(i);
	}
	DFS(n - 1);
}

int solve(int u, int v){
	int res = 0;
	for(int i = LOG - 1; i >= 0; i--){
		if(ST[u][i] < v and (1 << i) <= h[u]){
			u = ST[u][i];
			res += (1 << i);
		}
	}
	return res + 1;
}

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++) scanf("%d", &x[i]);
	scanf("%d %d", &L, &q);
	preprocess();
	for(int i = 0; i < q; i++){
		int l, r;
		scanf("%d %d", &l, &r);
		l--; r--;
		if(l > r) swap(l, r);
		printf("%d\n", solve(l, r));
	}
	return 0;
}
