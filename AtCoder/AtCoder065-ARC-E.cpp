#include<bits/stdc++.h>
using namespace::std;

/*
	Author: Racso Galvan

	Idea:

	- Rotate the plane 45 degrees, the new coordinates will be (x / sqrt(2) - y / sqrt(2), x / sqrt(2) + y / sqrt(2)), but we can ignore the sqrt(2) by multiplying

	  everything by it, the distances relations won't be affected.

	- Then, we need the maximum of the differences between x and y of two points

	  to be equal to D (according to the new coordinates, D = max(abs(x[a] - x[b]), abs(y[a] - y[b])))

	- If we consider that the maximum is abs(x[i] - x[j]), furthermore that x[i] < x[j]

	  so x[j] = x[i] + D, we need that abs(y[i] - y[j]) <= D, so we can sort

	  points by X and then by Y to get all those ranges.

	  Obviously, the pairs that hold this will be connected (compass will be able 
	  
	  to use them as extreme points), so we can use DSU to mantain the sets.

	  After solving that for X, we can swap X and Y coordinates and apply the same

	  algorithm to find the pairs with maximum equal to abs(y[i] - y[j]).

	- Now, we just need to count the number of edges in the component of a and b.

	  We can use DSU to join quickly the components.

	- Then, to count the number of edges, we can use two pointers in the component of

	  a and b and then swap coordinates. However, to avoid double count of the

	  pairs with abs(x[i] - x[j]) = abs(y[i] - y[j]) = D, the first counting should

	  be <= D and the second one <= D - 1.

	- Complexity: O(nlogn)
*/

const int N = 100000 + 5;

int n;
int a;
int b;
int D;
int m;
int x[N];
int y[N];
int par[N];
int sizes[N];

int get(int x){
	return par[x] == x ? x : par[x] = get(par[x]);
}

void join(int u, int v){
	u = get(u);
	v = get(v);
	if(u == v) return;
	if(sizes[u] > sizes[v]) swap(u, v);
	par[u] = v;
	sizes[v] += sizes[u];
}

void getComp(){
	vector<int> p(n);
	iota(p.begin(), p.end(), 0);
	sort(p.begin(), p.end(), [&] (int i, int j){
		if(x[i] == x[j]) return y[i] < y[j];
		return x[i] < x[j];
	});
	int L = 0, R = 0;
	int pos = 0;
	for(int i = 0; i < n; i++){
		while(pos < n and x[p[pos]] < x[p[i]] + D) pos++;
		if(pos < n and x[p[pos]] == x[p[i]] + D){
			while(pos < n and x[p[pos]] == x[p[i]] + D and y[p[pos]] < y[p[i]] - D) pos++;
			if(pos < n and x[p[pos]] == x[p[i]] + D){
				while(pos < n and x[p[pos]] == x[p[i]] + D and y[p[pos]] <= y[p[i]] + D){
					join(p[i], p[pos]);
					pos++;
				}
			}
		}
		pos--;
		L = R;
	}
}

long long f(int dif){
	vector<int> p(m);
	iota(p.begin(), p.end(), 0);
	sort(p.begin(), p.end(), [&] (int i, int j){
		if(x[i] == x[j]) return y[i] < y[j];
		return x[i] < x[j];
	});
	long long res = 0;
	int l = 0, r = 0;
	int pos = 0;
	for(int i = 0; i < m; i++){
		while(l < m and x[p[l]] < x[p[i]] + D) l++;
		while(r < m and x[p[r]] < x[p[i]] + D) r++;
		if(l < m and x[p[i]] + D == x[p[l]]){
			while(l < m and x[p[i]] + D == x[p[l]] and y[p[l]] < y[p[i]] - D + dif) l++;
			while(r < m and x[p[i]] + D == x[p[r]] and y[p[r]] <= y[p[i]] + D - dif) r++;
			res += r - l;
		}
	}
	return res;
}

long long solve(){
	long long res = f(0);
	for(int i = 0; i < m; i++){
		swap(x[i], y[i]);
	}
	res += f(1);
	return res;
}

int main(){
	scanf("%d %d %d", &n, &a, &b);
	a--; b--;
	for(int i = 0; i < n; i++){
		int X, Y;
		scanf("%d %d", &X, &Y);
		x[i] = X + Y;
		y[i] = X - Y;
		par[i] = i;
		sizes[i] = 1;
	}
	D = max(abs(x[a] - x[b]), abs(y[a] - y[b]));
	getComp();
	for(int i = 0; i < n; i++){
		swap(x[i], y[i]);
	}
	getComp();
	a = get(a);
	for(int i = 0; i < n; i++){
		if(get(i) == a){
			x[m] = x[i];
			y[m] = y[i];
			m += 1;
		}
	}
	printf("%lld\n", solve());
	return 0;
}
