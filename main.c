#include <stdio.h>
#include <math.h>
#include "NUC100Series.h"
#include "GPIO.h"
#include "SYS.h"
#include "SYS_init.h"
#include "LCD.h"
#include "Scankey.h"
#include "Draw2D.h"

#define  PI 3.14159265

int8_t key;
int8_t x,y,i,j,a,b;
int8_t score;
char text[16];


void init_PWM0(void)
{
	PWM_ConfigOutputChannel(PWM0, PWM_CH0, 50,  3); // 0.544ms = ~3% duty_cycle
	PWM_EnableOutput(PWM0, PWM_CH_0_MASK);
	PWM_Start(PWM0, PWM_CH_0_MASK);
}

void init_PWM1(void)
{
	PWM_ConfigOutputChannel(PWM0, PWM_CH1, 50,  3); // 0.544ms = ~3% duty_cycle
	PWM_EnableOutput(PWM0, PWM_CH_1_MASK);
	PWM_Start(PWM0, PWM_CH_1_MASK);
}

void init_PWM2(void)
{
	PWM_ConfigOutputChannel(PWM0, PWM_CH2, 50,  3); // 0.544ms = ~3% duty_cycle
	PWM_EnableOutput(PWM0, PWM_CH_2_MASK);
	PWM_Start(PWM0, PWM_CH_2_MASK);
}

void init_PWM3(void)
{
	PWM_ConfigOutputChannel(PWM0, PWM_CH3, 50,  3); // 0.544ms = ~3% duty_cycle
	PWM_EnableOutput(PWM0, PWM_CH_3_MASK);
	PWM_Start(PWM0, PWM_CH_3_MASK);
}

void right (void)
{
	clear_LCD();
	draw_Circle(32,32,30,FG_COLOR, BG_COLOR);	 // draw a circle
	x=65; y=33; printS_5x7(x,y,"YOU'RE RIGHT");		
	CLK_SysTickLongDelay(1500000);
	score=score+10;
}

void wrong (void)
{
	clear_LCD();
	draw_Triangle(0,63,32,0,64,63,FG_COLOR, BG_COLOR);// draw a triangle
	x=65; y=33; printS_5x7(x,y,"YOU'RE WRONG");
	CLK_SysTickLongDelay(1500000);
}

void win (void)
{
	clear_LCD();
	print_Line (1,"CONGRATULATIONS");
	print_Line (2,"    YOU WIN");	
	for (j=0; j<4; j++) 
		{
      PB11=0;
			CLK_SysTickDelay(500000);	
			PB11=1;	
			CLK_SysTickDelay(500000);	
		}
	CLK_SysTickLongDelay(1500000);
	clear_LCD();
	print_Line(0, "   TAKE  YOUR");
	print_Line(2, "    PRESENT!");
	CLK_SysTickLongDelay(1500000);
}

void lose (void)
{
		clear_LCD();
	  print_Line (1,"     SORRY");
		print_Line (2,"    YOU LOSE");	
		for (j=0; j<1; j++) 
		{
      PB11=0;
			CLK_SysTickLongDelay(1500000);	
			PB11=1;	
			CLK_SysTickLongDelay(1500000);	
		}
	CLK_SysTickLongDelay(1500000);
	clear_LCD();
	print_Line(0, "    SEE YOU");
	print_Line(2, "   NEXT TIME!");
	CLK_SysTickLongDelay(1500000);
}

void result (void)
{
	clear_LCD();
	sprintf(text,"YOUR SCORE: %3d",score);	
	print_Line(1, text);
  CLK_SysTickLongDelay(1500000);
}

void level_1 (void)
{   
	for (i=1;i<4;++i)
	{
		switch (i)
		{
		case 1:
			clear_LCD();
			OpenKeyPad();
			score=0;
			print_Line(0, "      2 + 5");
			print_Line(1, "   A.3 B.7 C.8");
			print_Line(2, "     ANSWER");
				while (1)
					{
						key=ScanKey();
							if (key==7)
							{	  
								print_Line(3, "        A");			
								CLK_SysTickLongDelay(1500000);
								wrong();
								break;
							}
							else if (key==8)
							{
								print_Line(3, "        B");			
								CLK_SysTickLongDelay(1500000);
								right();
								break;
							}
							else if (key==9)
							{
								print_Line(3, "        C");			
								CLK_SysTickLongDelay(1500000);
								wrong();
								break;
							}
					}
				break;	
		case 2:
			clear_LCD();
			OpenKeyPad();
			print_Line(0, "      5 + 1");
			print_Line(1, "   A.6 B.7 C.4");
			print_Line(2, "     ANSWER");
				while (1)
					{
						key=ScanKey();
							if (key==7)
							{	  
								print_Line(3, "        A");			
								CLK_SysTickLongDelay(1500000);
								right();
								break;
							}
							else if (key==8)
							{
								print_Line(3, "        B");			
								CLK_SysTickLongDelay(1500000);
								wrong();
								break;
							}
							else if (key==9)
							{
								print_Line(3, "        C");			
								CLK_SysTickLongDelay(1500000);
								wrong();
								break;
							}
					}
			break;
		case 3:
			clear_LCD();
			OpenKeyPad();
			print_Line(0, "      2 + 3");
			print_Line(1, "   A.7 B.5 C.2");
			print_Line(2, "     ANSWER");
				while (1)
					{
						key=ScanKey();
							if (key==7)
							{	  
								print_Line(3, "        A");			
								CLK_SysTickLongDelay(1500000);
								wrong();
								break;
							}
							else if (key==8)
							{
								print_Line(3, "        B");			
								CLK_SysTickLongDelay(1500000);
								right();
								break;
							}
							else if (key==9)
							{
								print_Line(3, "        C");			
								CLK_SysTickLongDelay(1500000);
								wrong();
								break;
							}
					}
				break;					
			}
	}
	result();
	if (score==30)
	{
		win();
		init_PWM0();
		PWM_ConfigOutputChannel(PWM0, PWM_CH0, 50,  13);
		clear_LCD();
	}
	else
	{
		lose();
		clear_LCD();
	}
}

void level_2 (void)
{
	for (i=1;i<4;++i)
	{
		switch (i)
		{
		case 1:
			clear_LCD();
			OpenKeyPad();
			score=0;
			print_Line(0, "      7 - 3");
			print_Line(1, "  A.10 B.5 C.4");
			print_Line(2, "     ANSWER");
				while (1)
					{
						key=ScanKey();
							if (key==7)
							{	  
								print_Line(3, "        A");			
								CLK_SysTickLongDelay(1500000);
								wrong();
								break;
							}
							else if (key==8)
							{
								print_Line(3, "        B");			
								CLK_SysTickLongDelay(1500000);
								wrong();
								break;
							}
							else if (key==9)
							{
								print_Line(3, "        C");			
								CLK_SysTickLongDelay(1500000);
								right();
								break;
							}
					}
				break;	
		case 2:
			clear_LCD();
			OpenKeyPad();
			print_Line(0, "     10 - 7");
			print_Line(1, "   A.7 B.3 C.5");
			print_Line(2, "     ANSWER");
				while (1)
					{
						key=ScanKey();
							if (key==7)
							{	  
								print_Line(3, "        A");			
								CLK_SysTickLongDelay(1500000);
								wrong();
								break;
							}
							else if (key==8)
							{
								print_Line(3, "        B");			
								CLK_SysTickLongDelay(1500000);
								right();
								break;
							}
							else if (key==9)
							{
								print_Line(3, "        C");			
								CLK_SysTickLongDelay(1500000);
								wrong();
								break;
							}
					}
			break;
		case 3:
			clear_LCD();
			OpenKeyPad();
			print_Line(0, "      4 - 1");
			print_Line(1, "   A.3 B.2 C.5");
			print_Line(2, "     ANSWER");
				while (1)
					{
						key=ScanKey();
							if (key==7)
							{	  
								print_Line(3, "        A");			
								CLK_SysTickLongDelay(1500000);
								right();
								break;
							}
							else if (key==8)
							{
								print_Line(3, "        B");			
								CLK_SysTickLongDelay(1500000);
								wrong();
								break;
							}
							else if (key==9)
							{
								print_Line(3, "        C");			
								CLK_SysTickLongDelay(1500000);
								wrong();
								break;
							}
					}
				break;					
			}
	}
	result();
	if (score==30)
	{
		win();
		init_PWM1();
		PWM_ConfigOutputChannel(PWM0, PWM_CH1, 50,  13);
		clear_LCD();
	}
	else
	{
		lose();
		clear_LCD();
	}
}

void level_3 (void)
{
	for (i=1;i<4;++i)
	{
		switch (i)
		{
		case 1:
			clear_LCD();
			OpenKeyPad();
			score=0;
			print_Line(0, "      2 x 3");
			print_Line(1, "   A.6 B.5 C.4");
			print_Line(2, "     ANSWER");
				while (1)
					{
						key=ScanKey();
							if (key==7)
							{	  
								print_Line(3, "        A");			
								CLK_SysTickLongDelay(1500000);
								right();
								break;
							}
							else if (key==8)
							{
								print_Line(3, "        B");			
								CLK_SysTickLongDelay(1500000);
								wrong();
								break;
							}
							else if (key==9)
							{
								print_Line(3, "        C");			
								CLK_SysTickLongDelay(1500000);
								wrong();
								break;
							}
					}
				break;	
		case 2:
			clear_LCD();
			OpenKeyPad();
			print_Line(0, "      3 x 3");
			print_Line(1, "   A.7 B.6 C.9");
			print_Line(2, "     ANSWER");
				while (1)
					{
						key=ScanKey();
							if (key==7)
							{	  
								print_Line(3, "        A");			
								CLK_SysTickLongDelay(1500000);
								wrong();
								break;
							}
							else if (key==8)
							{
								print_Line(3, "        B");			
								CLK_SysTickLongDelay(1500000);
								wrong();
								break;
							}
							else if (key==9)
							{
								print_Line(3, "        C");			
								CLK_SysTickLongDelay(1500000);
								right();
								break;
							}
					}
			break;
		case 3:
			clear_LCD();
			OpenKeyPad();
			print_Line(0, "      4 x 0");
			print_Line(1, "   A.1 B.0 C.4");
			print_Line(2, "     ANSWER");
				while (1)
					{
						key=ScanKey();
							if (key==7)
							{	  
								print_Line(3, "        A");			
								CLK_SysTickLongDelay(1500000);
								wrong();
								break;
							}
							else if (key==8)
							{
								print_Line(3, "        B");			
								CLK_SysTickLongDelay(1500000);
								right();
								break;
							}
							else if (key==9)
							{
								print_Line(3, "        C");			
								CLK_SysTickLongDelay(1500000);
								wrong();
								break;
							}
					}
				break;					
			}
	}
	result();
	if (score==30)
	{
		win();
		init_PWM2();
		PWM_ConfigOutputChannel(PWM0, PWM_CH2, 50,  13);
		clear_LCD();		
	}
	else
	{
		lose();
		clear_LCD();
	}
}

void level_4 (void)
{
	for (i=1;i<4;++i)
	{
		switch (i)
		{
		case 1:
			clear_LCD();
			OpenKeyPad();
			score=0;
			print_Line(0, "      6 : 3");
			print_Line(1, "   A.2 B.12 C.4");
			print_Line(2, "     ANSWER");
				while (1)
					{
						key=ScanKey();
							if (key==7)
							{	  
								print_Line(3, "        A");			
								CLK_SysTickLongDelay(1500000);
								right();
								break;
							}
							else if (key==8)
							{
								print_Line(3, "        B");			
								CLK_SysTickLongDelay(1500000);
								wrong();
								break;
							}
							else if (key==9)
							{
								print_Line(3, "        C");			
								CLK_SysTickLongDelay(1500000);
								wrong();
								break;
							}
					}
				break;	
		case 2:
			clear_LCD();
			OpenKeyPad();
			print_Line(0, "     10 : 2");
			print_Line(1, "  A.5 B.8 C.12");
			print_Line(2, "     ANSWER");
				while (1)
					{
						key=ScanKey();
							if (key==7)
							{	  
								print_Line(3, "        A");			
								CLK_SysTickLongDelay(1500000);
								right();
								break;
							}
							else if (key==8)
							{
								print_Line(3, "        B");			
								CLK_SysTickLongDelay(1500000);
								wrong();
								break;
							}
							else if (key==9)
							{
								print_Line(3, "        C");			
								CLK_SysTickLongDelay(1500000);
								wrong();
								break;
							}
					}
			break;
		case 3:
			clear_LCD();
			OpenKeyPad();
			print_Line(0, "      7 : 7");
			print_Line(1, "  A.49 B.0 C.1");
			print_Line(2, "     ANSWER");
				while (1)
					{
						key=ScanKey();
							if (key==7)
							{	  
								print_Line(3, "        A");			
								CLK_SysTickLongDelay(1500000);
								wrong();
								break;
							}
							else if (key==8)
							{
								print_Line(3, "        B");			
								CLK_SysTickLongDelay(1500000);
								wrong();
								break;
							}
							else if (key==9)
							{
								print_Line(3, "        C");			
								CLK_SysTickLongDelay(1500000);
								right();
								break;
							}
					}
				break;					
			}
	}
	result();
	if (score==30)
	{
		win();
		init_PWM3();
		PWM_ConfigOutputChannel(PWM0, PWM_CH3, 50,  13);
		clear_LCD();
	}
	else
	{
		lose();
		clear_LCD();
	}
}


int32_t main (void)
{
	SYS_Init();

	GPIO_SetMode(PB, BIT11, GPIO_MODE_OUTPUT);
	
init_LCD();
//Init_PWM1();
//Init_PWM2();
clear_LCD();
OpenKeyPad();

	print_Line(0, "    WELCOME!!");
	print_Line(1, "       TO");
	print_Line(2, " MATH  LEARNING");
	print_Line(3, "      BOARD");
  CLK_SysTickLongDelay(1500000);	
  clear_LCD();

	print_Line(0, "  SELECT LEVEL");
	print_Line(1, "1.LVL 1  3.LVL 3");
	print_Line(2, "2.LVL 2  4.LVL 4");
	
	while(1)
		{
			key=ScanKey();
			if (key==1)
			{
				level_1();
				break;
			}
			else if (key==2)
			{
				level_2();
				break;
			}
			else if (key==3)
			{
				level_3();
				break;
			}
			else if (key==4)
			{
				level_4();
				break;
			}
		}
}

