#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;
const int n = 100;

int a[N];

unsigned long long r(unsigned long long x){
	x ^= x << 13;
	x ^= x >> 7;
	x ^= x << 17;
	return x;
}

void gen(unsigned long long x){
	for(int i = 1; i <= n; i++) a[i] = i;
	for(int i = 1; i <= n; i++){
		x = r(x);
		cerr << (x % i) + 1 << " ";
		if(i != (x % i) + 1){
			swap(a[i], a[(x % i) + 1]);
		}
	}
	cerr << endl;
}

int main(){
	cerr << (1ULL << 45) << endl;
	gen(1ULL << 45);
	printf("%d\n", n);
	for(int i = 1; i <= n; i++) cout << a[i] << " ";
	cout << endl;
	return 0;
}
