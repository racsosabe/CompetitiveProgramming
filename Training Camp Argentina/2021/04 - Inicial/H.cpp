#include<bits/stdc++.h>
using namespace::std;

const int N = 50000 + 5;

int n;
int x[N];
int y[N];

double solve(){
	vector<int> p(n);
	iota(p.begin(), p.end(), 1);
	sort(p.begin(), p.end(), [&] (int i, int j){
		return x[i] < x[j];
	});
	double minimo = DBL_MAX;
	for(int i = 0; i < n; i++){
		int l = i - 1;
		double here = minimo;
		while(l >= 0 and x[p[i]] - x[p[l]] <= here){
			here = min(here, hypot(x[p[i]] - x[p[l]], y[p[i]] - y[p[l]]));
			l -= 1;
		}
		int r = i + 1;
		while(r < n and x[p[r]] - x[p[i]] <= here){
			here = min(here, hypot(x[p[i]] - x[p[r]], y[p[i]] - y[p[r]]));
			r += 1;
		}
		minimo = min(minimo, here);
	}
	double s_minimo = DBL_MAX;
	for(int i = 0; i < n; i++){
		int l = i - 1;
		double here = s_minimo;
		while(l >= 0 and x[p[i]] - x[p[l]] <= here){
			double cur = hypot(x[p[i]] - x[p[l]], y[p[i]] - y[p[l]]);
			if(cur > minimo) here = min(here, cur);
			l -= 1;
		}
		int r = i + 1;
		while(r < n and x[p[r]] - x[p[i]] <= here){
			double cur = hypot(x[p[i]] - x[p[r]], y[p[i]] - y[p[r]]);
			if(cur > minimo) here = min(here, cur);
			r += 1;
		}
		s_minimo = min(s_minimo, here);
	}
	return s_minimo;
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d %d", x + i, y + i);
	}
	printf("%.10lf\n", solve());
	return 0;
}
