#include "../genutils.cpp"

int main()
{
	seed();
	cout<<rand()%24<<" "<<rand()%60<<" "<<rand()%60<<endl;
}

