#include<bits/stdc++.h>
using namespace::std;

int n;
string s[] = {"Sheldon", "Leonard", "Penny", "Rajesh", "Howard"};

int main(){
	scanf("%d", &n);
	n -= 1;
	int k = 1;
	while(5 * k <= n){
		n -= 5 * k;
		k <<= 1;
	}
	printf("%s\n", s[n / k].c_str());
	return 0;
}
