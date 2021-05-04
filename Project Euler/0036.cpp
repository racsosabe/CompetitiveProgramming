#include<bits/stdc++.h>
using namespace::std;

bool palindrome(int n, int b){
	vector<int> v;
	while(n > 0){
		v.emplace_back(n % b);
		n /= b;
	}
	for(int i = 0; i < v.size() - 1 - i; i++){
		if(v[i] != v[v.size() - 1 - i]) return false;
	}
	return true;
}

int main(){
	long long ans = 0;
	for(int i = 1; i < 1000000; i++){
		if(palindrome(i, 10) and palindrome(i, 2)) ans += i;
	}
	printf("%lld\n", ans);
	return 0;
}
