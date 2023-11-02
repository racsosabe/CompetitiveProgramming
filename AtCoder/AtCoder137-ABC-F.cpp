#include<bits/stdc++.h>
using namespace::std;

/*
	Author: Racsó Galván

	Idea:

	- Notice that interpolation also works modulo a prime, so we can just apply polynomial interpolation,

	  however, Lagrange is O(n^3), so Newton's Finite Difference method was used


	  to achieve O(n^2).

	- Notice that the final computation of the answer needs us to compute x * (x - 1) * (x - 2) * ... * (x - i)

	  for each i and this seems like O(n^3) but it's actually O(n^2) because we will be

	  multiplying a polynomial with length 2 each time, which gives us a complexity of O(i) for each i.

	- Complexity: O(n^2)

*/

const int N = 2999 + 5;

int n;
int a[N];
int inv[N];
int ans[N];
int memo[N][N];

vector<int> singleton(int x) {
	return {x ? n - x : 0, 1};
}

void add_to_answer(vector<int> &poly, int c) {
	for(int i = 0; i < poly.size(); i++) {
		int to_add = poly[i] * c % n;
		ans[i] += to_add;
		if(ans[i] >= n) ans[i] -= n;
	}
}

void init(int p) {
	inv[1] = 1;
	for(int i = 2; i < p; i++) inv[i] = (p - p / i) * inv[p % i] % p;
}

vector<int> multiply(vector<int> a, vector<int> b) {
	vector<int> res(a.size() + b.size(), 0);
	for(int i = 0; i < a.size(); i++) {
		for(int j = 0; j < b.size(); j++) {
			res[i + j] += a[i] * b[j] % n;
			if(res[i + j] >= n) res[i + j] -= n;
		}
	}
	while(res.back() == 0 and res.size() > 1) res.pop_back();
	return res;
}

void interpolate() {
	for(int i = 0; i < n; i++) memo[i][0] = a[i];
	for(int l = 1; l < n; l++) {
		for(int i = 0; i + l < n; i++) {
			memo[i][l] = (memo[i + 1][l - 1] + n - memo[i][l - 1]) * inv[l] % n;
		}
	}
	vector<int> poly = {1};
	for(int i = 0; i < n; i++) {
		add_to_answer(poly, memo[0][i]);
		poly = multiply(poly, singleton(i));
	}
}

int main() {
	scanf("%d", &n);
	init(n);
	for(int i = 0; i < n; i++) scanf("%d", a + i);
	interpolate();
	for(int i = 0; i < n; i++) printf("%d%c", ans[i], " \n"[i + 1 == n]);
	return 0;
}
