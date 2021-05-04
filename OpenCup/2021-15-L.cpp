#include<bits/stdc++.h>
using namespace::std;

/*
	Grand Prix of China - Problem L "Square"

	Author: Racso Galvan

	- Notice that the assignment of the prime factors for each t_i are independent, so we

	  can focus on solving the problem for a prime p.

	- Obviously, we would want the exponent of p to be as small as possible.

	- Consider the square-free factors only, that is all the p^e will transform to

	  p^(e mod 2), that will make a sequence of 1s and 0s in the exponents.

	- Since we want all the consecutive pairs to be a perfect square, we need

	  that both of them are equal (both 1 or 0). Now, by a chaining reaction,

	  all the exponents of the considered prime must be equal (that is, the final sequence must be
	  
	  composed by only 1s or only 0s).

	- Now, we can change the exponent a position i by making the exponent of t_i 1,

	  otherwise leave it as 0.

	- Thus, our only possibilities are to change all 1s to 0 or change all 0s to 1, which will be

	  the number of positions that have p^(e mod 2) = p or the complement positions.

	- We can process the number of positions with p^(e mod 2) = p for all positions in O(n log MAX)

	  given that we have an augmented sieve.

	- After getting the minimum possible exponent, use fast exponentiation to 

	  update the answer in O(logn).

	- Complexity: O(n(logMAX + logn))
*/

const int MOD = 1000000000 + 7;
const int MAX = 1000000 + 5;
const int N = 100000 + 5;

int n;
int v[N];
int pf[MAX];
int cnt[MAX];
vector<int> primos;
bool composite[MAX];

int mul(int a, int b){
	return (1ll * a * b) % MOD;
}

int pow_mod(int a, int b){
	int r = 1;
	while(b > 0){
		if(b & 1) r = mul(r, a);
		a = mul(a, a);
		b >>= 1;
	}
	return r;
}

void init(){
	for(int i = 2; i < MAX; i++){
		if(not composite[i]){
			pf[i] = i;
			primos.emplace_back(i);
		}
		for(int p : primos){
			if(i * p >= MAX) break;
			composite[i * p] = true;
			pf[i * p] = min(pf[i], p);
			if(i % p == 0) break;
		}
	}
}

void factorize(int x, int i){
	while(x != 1){
		int f = pf[x];
		int e = 0;
		while(x % f == 0){
			e ^= 1;
			x /= f;
		}
		if(e) cnt[f] += 1;
	}
}

int get(int x){
	return min(n - cnt[x], cnt[x]);
}

int solve(){
	int ans = 1;
	for(int i = 1; i < MAX; i++){
		ans = mul(ans, pow_mod(i, get(i)));
	}
	return ans;
}

int main(){
	init();
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d", &v[i]);
		factorize(v[i], i);
	}
	printf("%d\n", solve());
	return 0;
}
