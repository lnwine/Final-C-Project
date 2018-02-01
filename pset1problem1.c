#include <stdio.h>

struct ManSet
{
	int N;
	int M;
};

void main()
{
	struct ManSet ManSetInput;
	int n;
	int m;
	printf("Please input an integer value:");
	scanf("%d", &n);
	printf("Please input another integer value:")
	scanf("%d", &m);
	ManSetInput.N = n;
	ManSetInput.M = m;
}