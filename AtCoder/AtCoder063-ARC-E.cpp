#include<bits/stdc++.h>
using namespace::std;

/*
	Author: Racso Galvan

	Idea:

	- DFS and math problem.

	- Notice that if we can ensure that there is a valid answer, we can greedily

	  assign the values using a fixed-value node as root.

	- Thus, we can set a fixed-value node as root and get 3 properties per node:

	  1) Minimum possible value (L)
	  2) Maximum possible value (R)
	  3) Parity of the height (h)


	- First, if L[u] > R[u] for some u, then there is no answer.

	- Also, we can see that if h[u] doens't match with the parity of the fixed value of u

	  (The k nodes given), then there is no answer.

	- If we have an answer, we can just greedily assign from the root to its neighbors

	  using a DFS adding 1 if the lowest value of v is lower than the assigned value

	  of u and taking 1 otherwise.
	
	- Complexity: O(n)
*/

const int N = 100000 + 5;

int n;
int k;
int h[N];
int L[N];
int R[N];
int ans[N];
vector<int> G[N];

void DFS(int u, int p = -1){
	for(int v : G[u]){
		if(v == p) continue;
		h[v] = h[u] ^ 1;
		L[v] = max(L[v], L[u] - 1);
		R[v] = min(R[v], R[u] + 1);
		DFS(v, u);
		L[u] = max(L[u], L[v] - 1);
		R[u] = min(R[u], R[v] + 1);
	}
}

bool DFS2(int u, int p = -1){
	if(L[u] > R[u] or (L[u] == R[u] and h[u] != (L[u] & 1))) return false;
	for(int v : G[u]){
		if(v == p) continue;
		ans[v] = ans[u] + (L[v] < ans[u] ? -1 : 1);
		if(not DFS2(v, u)) return false;
	}
	return true;
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i < n; i++){
		int u, v;
		scanf("%d %d", &u, &v);
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	for(int i = 1; i <= n; i++){
		L[i] = -1e9;
		R[i] = 1e9;
	}
	scanf("%d", &k);
	int root = 1;
	for(int i = 1; i <= k; i++){
		int u, v;
		scanf("%d %d", &u, &v);
		L[u] = R[u] = ans[u] = v;
		root = u;
	}
	h[root] = L[root] & 1;
	DFS(root);
	if(DFS2(root)){
		puts("Yes");
		for(int i = 1; i <= n; i++){
			printf("%d\n", ans[i]);
		}
	}
	else puts("No");
	return 0;
}
