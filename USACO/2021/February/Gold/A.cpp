#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;
const int MAX = 1000000 + 5;

int n;
int a[N];
int ac[MAX];

int test(int pos, int val){
	a[pos] -= val;
	int cnt = 0;
	for(int i = 1; i <= n; i++){
		cnt += a[i] / val;
	}
	a[pos] += val;
	return cnt % 2 == 0;
}

long long solve(){
	int res = 0;
	int maximo = *max_element(a + 1, a + n + 1);
	for(int val = 1; val <= maximo; val++){
		for(int i = 1; i <= n; i++){
			if(a[i] < val) continue;
			int r = test(i, val);
			cout << i << " " << val << " " << r << endl;
			res += r;
		}
	}
	return res;
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", a + i);
	printf("%lld\n", solve());
	return 0;
}
