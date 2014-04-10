#include<iostream>

using namespace std;

const int mod = 1e9+7;
const int maxn = 1e6+2;

int main()
{
	int n;
	cin >> n;
	int a = 1, b = 0;
	for (int i = 0; i < n; ++i) {
		int aux = a;
		a = (aux+b)%mod;
		b = aux;
	}

	cout << b << endl;
}
