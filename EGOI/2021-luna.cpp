#include<bits/stdc++.h>
using namespace::std;

const int N = 1000000 + 5;
const int inf = 1e9;

int n;
int m;
int a[N];
int L[N];
int R[N];
int b[N];
int ft[N];
bool close[N];

void update(int pos, int val){
	pos++;
	while(pos <= m + 1){
		ft[pos] += val;
		pos += (-pos) & pos;
	}
}

int getSum(int pos){
	pos++;
	int res = 0;
	while(pos > 0){
		res += ft[pos];
		pos &= pos - 1;
	}
	return res;
}

int query(int l, int r){
	return getSum(r) - getSum(l - 1);
}

long long solve(){
	for(int i = 1; i <= m; i++){
		if(L[a[i]] == 0){
			L[a[i]] = i;
			update(i, 1);
		}
		else{
			close[i] = true;
		}
		R[a[i]] = i;
	}
	long long ans = 0;
	for(int i = 1; i <= m; i++){
		if(close[i]){
			update(L[a[i]], -1);
			ans += query(L[a[i]], i);
		}
	}
	return ans + n;
}

int main(){
	scanf("%d", &n);
	m = n << 1;
	for(int i = 1; i <= m; i++){
		scanf("%d", a + i);
	}
	printf("%lld\n", solve());
	return 0;
}
