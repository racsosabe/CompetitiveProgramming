#include<bits/stdc++.h>
using namespace::std;

int gcd(int a, int b){
	while(b){
		a %= b;
		swap(a, b);
	}
	return a;
}

int a;
int b;
int k;

int get(int x){
	int res = 0;
	for(int i = 2; i * i <= x; i++){
		if(x % i == 0){
			while(x % i == 0){
				res += 1;
				x /= i;
			}
		}
	}
	if(x > 1) res += 1;
	return res;
}

int solve(){
	int mcd = gcd(a, b);
	int max_moves_a = get(a / mcd);
	int max_moves_b = get(b / mcd);
	int max_extra = get(mcd);
	if(k > max_moves_a + max_moves_b + 2 * max_extra) return false;
	if(k < (a != mcd) + (b != mcd)) return false;
	if(k == 1) return (a == mcd and b != mcd) or (a != mcd and b == mcd);
	return true;
}

int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%d %d %d", &a, &b, &k);
		puts(solve() ? "YES" : "NO");
	}
	return 0;
}
