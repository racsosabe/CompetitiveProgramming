#include<bits/stdc++.h>
using namespace::std;

const int N = 300000 + 5;

int n;
int m;
int a[N];
int b[N];

int solve(){
	if(accumulate(a, a + n, 0LL) != accumulate(b, b + m, 0LL)) return -1;
	int ans = 0;
	int posA = 0, posB = 0;
	long long sumA = 0, sumB = 0;
	while(posA < n and posB < m){
		if(sumA < sumB or sumA == 0){
			sumA += a[posA];
			posA++;
		}
		else if(sumA > sumB){
			sumB += b[posB];
			posB++;
		}
		else{
			ans++;
			sumA = 0;
			sumB = 0;
		}
	}
	return ans + 1;
}

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++) scanf("%d", a + i);
	scanf("%d", &m);
	for(int i = 0; i < m; i++) scanf("%d", b + i);
	printf("%d\n", solve());
	return 0;
}
