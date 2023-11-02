#include<bits/stdc++.h>
using namespace::std;

const int N = 100 + 5;

int n;
int p;
int q;
int a[N];

int mul(int a, int b){
	return (1ll * a * b) % p;
}

int solve(){
	int ans = 0;
	for(int i1 = 0; i1 < n; i1++){
		for(int i2 = i1 + 1; i2 < n; i2++){
			for(int i3 = i2 + 1; i3 < n; i3++){
				for(int i4 = i3 + 1; i4 < n; i4++){
					for(int i5 = i4 + 1; i5 < n; i5++){
						int val = mul(a[i1], mul(a[i2], mul(a[i3], mul(a[i4], a[i5]))));
						if(val == q) ans += 1;
					}
				}
			}
		}
	}
	return ans;
}

int main(){
	scanf("%d %d %d", &n, &p, &q);
	for(int i = 0; i < n; i++){
		scanf("%d", a + i);
	}
	printf("%d\n", solve());
	return 0;
}
