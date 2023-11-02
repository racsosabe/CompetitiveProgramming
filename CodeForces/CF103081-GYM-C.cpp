#include<bits/stdc++.h>
using namespace::std;

const int N = 1000 + 5;

int n;
int X;
int Y;
int par[N];
int sizes[N];
double x[N];
double y[N];
double Ly[N];
double Ry[N];
double Lx[N];
double Rx[N];

int get(int x){
	return par[x] == x ? x : par[x] = get(par[x]);
}

void join(int a, int b){
	a = get(a);
	b = get(b);
	if(a == b) return;
	if(sizes[a] > sizes[b]) swap(a, b);
	par[a] = b;
	sizes[b] += sizes[a];
	Lx[b] = min(Lx[b], Lx[a]);
	Ly[b] = min(Ly[b], Ly[a]);
	Rx[b] = max(Rx[b], Rx[a]);
	Ry[b] = max(Ry[b], Ry[a]);
}

bool can(double d){
	for(int i = 0; i < n; i++){
		par[i] = i;
		sizes[i] = 1;
		Lx[i] = max(0.0, x[i] - d);
		Rx[i] = min(1.0 * X, x[i] + d);
		Ly[i] = max(0.0, y[i] - d);
		Ry[i] = min(1.0 * Y, y[i] + d);
	}
	for(int i = 0; i < n; i++){
		for(int j = i + 1; j < n; j++){
			if(4 * d * d >= (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j])){
				join(i, j);
			}
		}
	}
	for(int i = 0; i < n; i++){
		if(Lx[i] < 1e-10 and X - Rx[i] < 1e-10) return false;
		if(Ly[i] < 1e-10 and Y - Ry[i] < 1e-10) return false;
		if(Lx[i] < 1e-10 and Ly[i] < 1e-10) return false;
		if(X - Rx[i] < 1e-10 and Y - Ry[i] < 1e-10) return false;
	}
	return true;
}

int main(){
	scanf("%d %d", &X, &Y);
	scanf("%d", &n);
	for(int i = 0; i < n; i++) scanf("%lf %lf", x + i, y + i);
	double lo = 0, hi = min(X, Y);
	for(int i = 0; i < 38; i++){
		double mi = (lo + hi) / 2.0;
		if(can(mi)) lo = mi;
		else hi = mi;
	}
	printf("%.10lf\n", lo);
	return 0;
}
