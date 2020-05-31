#include <stdio.h>
#include <LPC214X.H>

extern "C" void init_serial(void);

int main(void)
{
	init_serial();
	printf("  Hello, world!\n");
	return 0;
}