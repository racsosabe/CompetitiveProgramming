#include<bits/stdc++.h>
using namespace::std;

int n;

bool prime(int x){
	for(int i = 2; i * i <= x; i++){
		if(x % i == 0) return false;
	}
	return true;
}

int main(){
	scanf("%d", &n);
	while(not prime(n)) n += 1;
	printf("%d\n", n);
	return 0;
}
