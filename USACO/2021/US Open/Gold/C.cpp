#include<bits/stdc++.h>
using namespace::std;

const int MOD = 1000000000 + 7;
const int N = 40 + 5;

int add(int a, int b){
	return (a + b) % MOD;
}

int mul(int a, int b){
	return (1ll * a * b) % MOD;
}

int n;
int x[N];
int y[N];
int f[N];

int toLeft(int a, int b, int c){
	return (x[b] - x[a]) * (y[c] - y[b]) >= (y[b] - y[a]) * (x[c] - x[b]);
}

int toLeft(int a, int b, int c, int d){
	return (x[b] - x[a]) * (y[d] - y[c]) >= (y[b] - y[a]) * (x[d] - x[c]);
}

int test(int a, int b, int c){
	if(!toLeft(a, b, c)) swap(b, c);
	cerr << "Testing: " << endl;
	cerr << x[a] << " " << y[a] << " - " << x[b] << " " << y[b] <<  " - " << x[c] << " " << y[c] << endl;
	cerr << a << " " << b << " " << c << endl;
	for(int i = 1; i <= n; i++){
		if(i == a or i == b or i == c) continue;
		int cntInt = toLeft(a, b, i) + toLeft(b, c, i) + toLeft(c, a, i);
		if(cntInt == 3) continue;
		if(toLeft(a, c, a, i) and toLeft(b, i, b, c)) continue;
		if(toLeft(c, b, c, i) and toLeft(a, i, a, b)) continue;
		if(toLeft(b, a, b, i) and toLeft(c, i, c, a)) continue;
		cerr << x[i] << " " << y[i] << endl;
		cerr << "Invalid" << endl;
		return 0;
	}
	cerr << "Valid" << endl;
	return f[n - 3];
}

int solve(){
	int ans = 0;
	int cnt = 0;
	int cnt2 = 0;
	for(int i = 1; i <= n; i++){
		for(int j = i + 1; j <= n; j++){
			for(int k = j + 1; k <= n; k++){
				cnt += 1;
				if(test(i, j, k)) cnt2 += 1;
				ans = add(ans, mul(6, test(i, j, k)));
			}
		}
	}
	cerr << cnt << " " << cnt2 << endl;
	return ans;	
}

void init(){
	f[0] = 1;
	for(int i = 1; i < N; i++) f[i] = mul(f[i - 1], i);
}

int main(){
	init();
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d %d", x + i, y + i);
	}
	printf("%d\n", solve());
	return 0;
}
