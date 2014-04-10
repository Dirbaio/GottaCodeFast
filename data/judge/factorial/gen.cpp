#include "../genutils.cpp"

int main()
{
    const int n = 12;
	seed();
    cout<<rand()%(n+1)<<endl;
}

