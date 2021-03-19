#include<bits/stdc++.h>
using namespace::std;

/*
	Author: Racso Galvan

	Idea:

	- Strings and combinatorics problem.

	- First, notice that if we fix the period of the string as d (d must divide n)

	  then we will have only d different strings, because in the d-th shift we

	  will get the same original string.

	- Observation 1: The period string must be a palindrome.

	- We can partition all the possible strings by their minimal period, thus we

	  should analyze only D(n) values.

	- Period X is the minimal period if none of its divisors is a period too, so

	  we can compute f(X) and take f(Y) for all Y | X, which are also divisors

	  of n.

	- Notice that f(X) = k^ceil(X / 2), because we will have the first ceil(X / 2)

	  characters fixed and the other ones must reflect them.

	- Now, once we have f(X) for each X | n, we must know how many strings does

	  it contribute with. 

	  If we have an even X, we should notice that if we shift X / 2 characters,

	  our result will be another palindrome string of length n with minimal period

	  X, so we will be counting twice this string, so we only have X / 2 different

	  strings.

	  Otherwise, we won't have repetitions, so we have X different strings.

	- Finally, our expression will be the sum of X * f(X) for all odd X and (X / 2) * f(X) for all even X.

	- Complexity: O(D(n)^2)
*/

const int MOD = 1000000000 + 7;

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

int n;
int k;

vector<int> getDivisors(int x){
	vector<int> v;
	for(int i = 1; i * i <= x; i++){
		if(x % i == 0){
			v.emplace_back(i);
			if(i * i != x) v.emplace_back(x / i);
		}
	}
	sort(v.begin(), v.end());
	return v;
}

int solve(){
	vector<int> d = getDivisors(n);
	vector<int> val(d.size(), 0);
	for(int i = 0; i < d.size(); i++){
		val[i] = pow_mod(k, (d[i] + 1) / 2);
		for(int j = 0; j < i; j++){
			if(d[i] % d[j] == 0){
				val[i] += MOD - val[j];
				if(val[i] >= MOD) val[i] -= MOD;
			}
		}
	}
	int ans = 0;
	for(int i = 0; i < d.size(); i++){
		if(d[i] & 1){
			ans += mul(val[i], d[i]);
		}
		else{
			ans += mul(val[i], d[i] >> 1);
		}
		if(ans >= MOD) ans -= MOD;
	}
	return ans;
}

int main(){
	scanf("%d %d", &n, &k);
	printf("%d\n", solve());
	return 0;
}
