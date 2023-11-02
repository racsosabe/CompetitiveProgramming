#include<bits/stdc++.h>
using namespace::std;

const int N = 2000 + 5;

int gcd(int a, int b){
	while(b){
		a %= b;
		swap(a, b);
	}
	return a;
}

int n;
int a[N];

int solve(){
	map<int, int> G;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j * j <= a[i]; j++){
			if(a[i] % j == 0){
				if(G.count(j)) G[j] = gcd(G[j], a[i]);
				else G[j] = a[i];
				if(G.count(a[i] / j)) G[a[i] / j] = gcd(G[a[i] / j], a[i]);
				else G[a[i] / j] = a[i];
			}
		}
	}
	int ans = 0;
	int mini = *min_element(a + 1, a + n + 1);
	for(auto e : G){
		if(e.first < mini and e.second == e.first) ans++;
	}
	return ans + 1;
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", a + i);
	printf("%d\n", solve());
	return 0;
}
