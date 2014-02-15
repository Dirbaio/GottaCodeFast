#include <iostream>
#include <vector>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

void seed()
{
	int seed;
	int fd = open("/dev/urandom", O_RDONLY);
	read(fd, &seed, sizeof(seed));
	close(fd);
	srand(seed); 
}


