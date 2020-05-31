#include <stdio.h>
#include <LPC214X.H>

extern "C" void init_serial(void);

unsigned long del = 0;

/*Timer 1 interrupt executes each 10 ms */
__irq void tc1 (void) {
	printf("qu");
	T0IR = 1;
	VICVectAddr = 0;
	if (del < 100)
		del++;
	else
		del = 0;
}

void wait (void)  {
	while (del < 100)
	{
		printf("%d %d %d\n", int(T0TC), int(T0MR0), int(del));
	}
}

/* Setup the Timer Counter 1 interrupt */
void init_timer (void)  {
	printf("hi");
	T0MR0 = 20;                          // 10mSec = 150000-1 counts
  T0MCR = 3;                               // Interrupt and Reset on MR0
	T0PR = 150000;
  T0TCR = 1;                               // Timer0 Enable
	VICVectAddr0 = (unsigned long)tc1;       // set interrupt vector in 0
  VICVectCntl0 = 0x20 | 4;                 // use it for Timer 0 Interrupt
  VICIntEnable = 0x00000010; 
	printf("HI");
}

int main(void)
{
	int cnt = 0;
	init_serial();
	init_timer();

	while (1)
	{
		
		if (cnt == 3)
		{
			T0TCR = 0;
			printf(" timer 1 has been stoped.\n");
			break;
		}
		wait();
		printf(" timer 1 interupt burst %d times.\n", ++cnt);
	}
	while(1);
}
