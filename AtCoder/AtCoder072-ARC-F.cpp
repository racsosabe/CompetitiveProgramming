#include<bits/stdc++.h>
using namespace::std;

const int N = 500000 + 5;

int n;
int L;
int v[N];
int t[N];
long double maxi[N];
long double mini[N];

int main(){
	scanf("%d %d", &n, &L);
	for(int i = 1; i <= n; i++){
		scanf("%d %d", t + i, v + i);
	}
	mini[1] = maxi[1] = v[1];
	for(int i = 2; i <= n; i++){
		maxi[i] = max(maxi[i - 1] + v[i] * (t[i] - maxi[i - 1]) / L, mini[i - 1] + v[i] * (t[i] - mini[i - 1]) / L);
		mini[i] = min(maxi[i - 1] + v[i] * (t[i] - maxi[i - 1]) / L, mini[i - 1] + v[i] * (t[i] - mini[i - 1]) / L);
	}
	for(int i = 1; i <= n; i++){
		printf("%.10Lf\n", maxi[i]);
	}
	return 0;
}
