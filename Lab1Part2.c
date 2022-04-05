//#include "address_map_arm.h"
/* Your first program*/

//volatile int DELAY_LENGTH;


// base addresses for LEDs and switches
// I don't want to include a header file to maximize
// compatibility with the simulator
#define LED_BASE 0xFF200000
#define SW_BASE  0xFF200040
#define segment 0xFF200020
	
volatile int DELAY_LENGTH; // volatile so it survives compilation

//We use these pointers to reference the memory addresses of switches and the seven segment display
volatile unsigned int* const sw_ptr = ( unsigned int* )SW_BASE;
volatile unsigned int* const sg_ptr = ( unsigned int* )segment;
	
//Show hex equivalent of value on the seven segments
//Array of values -> corresponding LED segments in binary
void DisplayHex(int value)
{

	//Here I map the index of the array value(hex_code[0] ~example) to the binary value which will turn on that digit on the 7 segment display
	//Each bit in the byte corresponds to a segment, so the sum of these values will "equal" the number
    char hex_code[16] = {0x3f,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x7,0x7F,0x67,0x77,0X7C,0X39,0X5E,0x79,0x71};

	//Set the segment display to the hexadecimal sum whose value will map to the hex value on the display
	*(sg_ptr) = hex_code[value];
	
}

//Read from slide switch bank
int ReadSwitches(void)
{
		//Return the value from the switch bank
		return *sw_ptr;
	
}

int main(void) {



	//Code from template to blink the seven segment display
    volatile int delay_count; 

	//State variable to determine where the program is at currently
	volatile int status;
	
	//We set a length of delay which is linked to frequency of blinking
	DELAY_LENGTH = 700000;
	status = 0;
	
	//Constantly loop
    while (1) 
	{
		//Flip the status of the state
		if (status == 0)
		{
			status = 1;

			//Display the Hex value that is read as binaryfrom the switches 
			//Switches 0011 would map to 3 on the display
			DisplayHex(ReadSwitches());
			
		}
		else
		{
			status = 0;
			//Set the seven segment dispaly to off to provide blinking
			*(sg_ptr) = 0;
		}
        for (delay_count = DELAY_LENGTH; delay_count != 0; --delay_count)
            ; // delay loop
    }
}
