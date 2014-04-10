#include<iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;
    int x = 1;
    while (n) x *= n--;
    cout << x << endl;
}
