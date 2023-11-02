#include<bits/stdc++.h>
using namespace::std;

const int N = 100 + 5;

int n;
char s[N];

bool palindrome(int l, int r){
	int len = r - l + 1;
	for(int i = 0; i < len - i - 1; i++){
		if(s[l + i] != s[r - i]) return false;
	}
	return true;
}

int main(){
	scanf("%s", s + 1);
	n = strlen(s + 1);
	puts(palindrome(1, n) and palindrome(1, (n - 1) / 2) and palindrome((n + 3) / 2, n) ? "Yes" : "No");
	return 0;
}
