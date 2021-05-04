#include<bits/stdc++.h>
using namespace::std;

const int K = 64;
const int N = 100000 + 5;

int n;
long long a[N];

int dim(){
	vector<long long> basis;
	for(int i = 0; i < n; i++){
		long long rep = a[i];
		for(auto x : basis) rep = min(rep, rep ^ x);
		if(rep){
			basis.emplace_back(rep);
		}
	}
	return basis.size();
}

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%lld", a + i);
	}
	printf("%lld\n", (1LL << dim()) - n);
	return 0;
}
