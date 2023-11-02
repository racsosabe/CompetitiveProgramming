#include<bits/stdc++.h>
using namespace::std;

int n;
int x;
vector<double> p;
vector<double> res;

vector<double> multiply(vector<double> &a, vector<double> &b){
	vector<double> res(2 * max(a.size(), b.size()), 0);
	for(int i = 0; i < a.size(); i++){
		for(int j = 0; j < b.size(); j++){
			res[i ^ j] += a[i] * b[j];
		}
	}
	while(res.back() == 0) res.pop_back();
	return res;
}

void solve(int b){
	res.emplace_back(1);
	while(b > 0){
		if(b & 1) res = multiply(res, p);
		p = multiply(p, p);
		b >>= 1;
	}
}

int main(){
	scanf("%d %d", &n, &x);
	p.resize(x + 1);
	for(int i = 0; i <= x; i++) scanf("%lf", &p[i]);
	solve(n);
	printf("%.10lf\n", 1.0 - res[0]);
	return 0;
}
