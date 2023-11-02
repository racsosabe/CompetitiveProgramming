#include<bits/stdc++.h>
using namespace::std;

const int N = 500000 + 5;

int n;
pair<int, int> v[N];

bool check(double t){
	
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d %d", &v[i].first, &v[i].second);
	sort(v + 1, v + n + 1);
	double lo = 0, hi = 2e9;
	for(int i = 0; i < 50; i++){
		double mi = (lo + hi) / 2.0;
		if(check(mi)) hi = mi;
		else lo = mi;
	}
	if(!check(lo)) puts("-1");
	else printf("%.10lf\n", lo);
	return 0;
}
