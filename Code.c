#include<reg51.h>
sbit rs=P1^0; //Register select pin for LCD
sbit rw=P1^1; //Read/Write pin for LCD
sbit en=P1^2; //Enable pin for LCD

sbit level_25=P3^0; //to indicate 1/4 full
sbit level_50=P3^1; //to indicate half
sbit level_75=P3^2; //to indicate 3/4 full
sbit level_100=P3^3; //to indicate full

sbit motor=P3^7; //to turn on and off motor

void lcdcmd(unsigned char); //function declaration for LCD commands
void lcddisplay(unsigned char); //function declaration for LCD data
void delay(); //function declaration for delay

void display_empty() //function to display empty
{
		lcdcmd(0x38);//declaration of matrix 5x7
		delay();
		lcdcmd(0x01);//clear screen
		delay();
		lcdcmd(0x10);//cursor position and blinking
		delay();
		lcdcmd(0x0c);//dispaly on cursor on
		delay();
		lcdcmd(0x81);//dispaly on cursor on
		delay();
		lcddisplay('E');
		delay();
		lcddisplay('M');
		delay();
		lcddisplay('P');
		delay();
		lcddisplay('T');
		delay();
		lcddisplay('Y');
		delay();
}

void display_full() //function to display full
{
		lcdcmd(0x38);//declaration of matrix 5x7
		delay();
		lcdcmd(0x01);//clear screen
		delay();
		lcdcmd(0x10);//cursor position and blinking
		delay();
		lcdcmd(0x0c);//dispaly on cursor on
		delay();
		lcdcmd(0x81);//dispaly on cursor on
		delay();
		lcddisplay('F');
		delay();
		lcddisplay('U');
		delay();
		lcddisplay('L');
		delay();
		lcddisplay('L');
		delay();
}

void display_three_fourth() //function to dispaly 3/4 full
{
		lcdcmd(0x38);//declaration of matrix 5x7
		delay();
		lcdcmd(0x01);//clear screen
		delay();
		lcdcmd(0x10);//cursor position and blinking
		delay();
		lcdcmd(0x0c);//dispaly on cursor on
		delay();
		lcdcmd(0x81);//dispaly on cursor on
		delay();
		lcddisplay('3');
		delay();
		lcddisplay('/');
		delay();
		lcddisplay('4');
		delay();
	  lcddisplay(' ');
		delay();
		lcddisplay('F');
		delay();
		lcddisplay('U');
		delay();
		lcddisplay('L');
		delay();
		lcddisplay('L');
		delay();
}

void display_half() //function to display half
{
		lcdcmd(0x38);//declaration of matrix 5x7
		delay();
		lcdcmd(0x01);//clear screen
		delay();
		lcdcmd(0x10);//cursor position and blinking
		delay();
		lcdcmd(0x0c);//dispaly on cursor on
		delay();
		lcdcmd(0x81);//dispaly on cursor on
		delay();
		lcddisplay('H');
		delay();
		lcddisplay('A');
		delay();
		lcddisplay('L');
		delay();
		lcddisplay('F');
		delay();
}

void display_one_fourth() //finction to display 1/4 full
{
		lcdcmd(0x38);//declaration of matrix 5x7
		delay();
		lcdcmd(0x01);//clear screen
		delay();
		lcdcmd(0x10);//cursor position and blinking
		delay();
		lcdcmd(0x0c);//dispaly on cursor on
		delay();
		lcdcmd(0x81);//dispaly on cursor on
		delay();
		lcddisplay('1');
		delay();
		lcddisplay('/');
		delay();
		lcddisplay('4');
		delay();
	  lcddisplay(' ');
		delay();
		lcddisplay('F');
		delay();
		lcddisplay('U');
		delay();
		lcddisplay('L');
		delay();
		lcddisplay('L');
		delay();
}

void main()
{
	unsigned char on,off; //variables to keep track of motor on or off
	P2=0x00; //output declaration
	motor=0; //output declaration
	level_25=1;
	level_50=1;
	level_75=1;
	level_100=1;
	while(1)
	{
		if(level_25==1 && level_50==1 && level_75==1 && level_100==1) //if all pins are high then display empty on LCD and turn on motor
		{
			display_empty(); //function calling to display empty on LCD
			off=1;
			on=0;
			if(off==1 && on==0)
			{
				motor=1; //send high pulse to motor to turn it on
			}
		}
		else if(level_25==0 && level_50==1 && level_75==1 && level_100==1) //when first pin is low and all are high then display 1/4 full and keep the state of motor as it is
		{
			display_one_fourth(); //function calling to display 1/4 full on LCD
			if(off==1 && on==0)
			{
				motor=1; //if motor is on keep it on
			}
			if(off==0 && on==1)
			{
				motor=0;  //if motor is off keep it off
			}
		}
		else if(level_25==0 && level_50==0 && level_75==1 && level_100==1) //when first and second pin are low and remainig two are high then display half full and keep the state of motor as it is
		{
			display_half(); //function calling to display half full on LCD
			if(off==1 && on==0)
			{
				motor=1; //if motor is on keep it on
			}
			if(off==0 && on==1)
			{
				motor=0; //if motor is off keep it off
			}
			
		}
		else if(level_25==0 && level_50==0 && level_75==0 && level_100==1) //when only last pin is high and all other low then display 3/4 full and keep the state of motor as it is
		{
			display_three_fourth(); //function calling to display 3/4 full on LCD
			if(off==1 && on==0)
			{
				motor=1; //if motor is off keep it off
			}
			if(off==0 && on==1)
			{
				motor=0; //if motor is off keep it off
			}
		}
		else if(level_25==0 && level_50==0 && level_75==0 && level_100==0) //when all pins are low then display full and stop the motor
		{
			display_full();
			on=1;
			off=0;
			if(off==0 && on==1) 
			{

				motor=0; //stop the motor
			}
		}
		else
		{
			lcdcmd(0x08);//clear screen
			delay();
		}
	}
}

void lcdcmd(unsigned char val) //function definition for LCD commands
{
	P2=val;
	rs=0; //value is considered as command
	rw=0; //write fnction
	//setting enable pin from high to low to interpret successful transmission of command
	en=1;
	delay();
	en=0;
}

void lcddisplay(unsigned char val) //function definition for LCD data
{
	P2=val;
	rs=1; //value is considered as data
	rw=0; //write function
	//setting enable pin from high to low to interpret successful transmission of data
	en=1;
	delay();
	en=0;
}

void delay() //function definition for delay
{
	int i;
	for(i=0;i<12000;i++);
} 