#include<bits/stdc++.h>
using namespace::std;

/*
	Author: Racso Galvan

	Idea:

	- Hashing & Observation problem

	- Notice that the only case in which the answer is greater than 2 is when 

	  all the characters are equal (therefore, the answer will be n 1).

	- Now, the answer is 1 if s is not periodic (therefore, the answer will be 1 1)

	- Else, we can always choose s[0:0] and s[1:(n-1)] as good strings in our 

	  partition, so we only need to check which prefixes and suffixes are good

	  to get the number of ways.

	- We can compute the goodness of a string using hashing and iterating over all

	  the divisors of its length.

	- Complexity: O(nlogn).

*/

const int MOD = 1000000000 + 9;
const int N = 500000 + 5;
const int B = 311;

int mul(int a, int b){
	return (1ll * a * b) % MOD;
}

int pow_mod(int a, int b){
	int r = 1;
	while(b > 0){
		if(b & 1) r = (1ll * r * a) % MOD;
		a = (1ll * a * a) % MOD;
		b >>= 1;
	}
	return r;
}

int n;
int z[N];
char s[N];
int pot[N];
int hsh[N];
int poti[N];
bool prefix[N];
bool suffix[N];
vector<int> D[N];

void init(){
	pot[0] = 1;
	for(int i = 1; i <= n; i++) pot[i] = (1ll * B * pot[i - 1]) % MOD;
	poti[n] = pow_mod(pot[n], MOD - 2);
	for(int i = n - 1; i >= 0; i--) poti[i] = (1ll * B * poti[i + 1]) % MOD;
	for(int i = 1; i <= n; i++){
		hsh[i] = (hsh[i - 1] + mul(pot[i], s[i - 1] - 'a' + 1)) % MOD;
	}
	for(int i = 1; i <= n; i++){
		for(int j = i << 1; j <= n; j += i){
			D[j].emplace_back(i);
		}
	}

}

bool equal(){
	for(int i = 1; i < n; i++){
		if(s[i] != s[0]) return false;
	}
	return true;
}

int period(){
	for(int i = 0; i < n; i++) z[i] = 0;
	int l = 0, r = 0;
	for(int i = 1; i < n; i++){
		z[i] = min(r - i + 1, z[i - l]);
		if(z[i] < 0) z[i] += 1;
		while(i + z[i] < n and s[z[i]] == s[i + z[i]]) z[i] += 1;
		if(r < i + z[i] - 1){
			l = i;
			r = i + z[i] - 1;
		}
	}
	for(int i = 1; i < n; i++){
		if(n % i == 0 and z[i] + i == n) return i;
	}
	return n;
}

int get(int l, int r){
	return mul(poti[l], (hsh[r] - hsh[l - 1] + MOD) % MOD);
}

int solve(){
	init();
	for(int i = 1; i <= n; i++){
		prefix[i] = true;
		for(int d : D[i]){
			if(get(1, i - d) == get(d + 1, i)){
				prefix[i] = false;
				break;
			}
		}
		suffix[i] = true;
		int len = n - i + 1;
		for(int d : D[len]){
			if(get(i, i + len - d - 1) == get(i + d, n)){
				suffix[i] = false;
				break;
			}
		}
	}
	int ans = 0;
	for(int i = 1; i < n; i++){
		if(prefix[i] and suffix[i + 1]) ans += 1;
	}
	return ans;
}

int main(){
	scanf("%s", s);
	n = strlen(s);
	if(equal()) printf("%d\n1\n", n);
	else if(period() == n) puts("1\n1");
	else{
		printf("2\n%d\n", solve());
	}
	return 0;
}
