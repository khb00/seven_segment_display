#include <stdio.h>
#include <stdlib.h>


//This function acts in place of a switch
//Output is 0, off, or 1, on
int fpgaswitch (){
    int inputInteger = 2;
    char inputString[101];

    while(inputInteger != 0 && inputInteger != 1){//Should continue looping until gets a valid input, which is integer value 0 or 1
        printf("Enter an integer: ");
        gets(inputString);//reads the input as a string
        inputInteger = atoi(inputString);//turns string into integer value
        if (inputInteger != 0 && inputInteger != 1){//if input is not 0 or 1.
            printf("An input of %s is invalid\n", inputString);
            inputInteger = 2; //Reset input back to 2 until input is valid
            }
        }
    return inputInteger;//Should return either 0 or 1
}


//Input is the decimal number that needs to be displayed
//Output is binary number that corresponds the segments of the display
int seven_segment_display(const int input_number){
    int seven_segment;

    //input_number is the number that will be displayed.
    //Segment on is 0 and segment off is 1
    switch (input_number){
        case 0:
            seven_segment = 0b01000000;
            break;

        case 1:
            seven_segment = 0b01111001;
            break;

        case 2:
            seven_segment = 0b00100100;
            break;

        case 3:
            seven_segment = 0b00110000;
            break;

        case 4:
            seven_segment = 0b00011001;
            break;

        case 5:
            seven_segment = 0b00010010;
            break;

        case 6:
            seven_segment = 0b00000010;
            break;

        case 7:
            seven_segment = 0b01111000;
            break;

        case 8:
            seven_segment = 0b00000000;
            break;

        case 9:
            seven_segment = 0b00011000;
            break;

        default:
            seven_segment = 0b00000110;
    }
    return seven_segment;
}

int main(){
    int count;
    int display_23;
    int display_45;
    int display_01;
    int ALT_LWFPGA_SWITCH_BASE = 0x00000000;
    int ALT_LWFPGA_HEXA_BASE = 0x00000000;
    int ALT_LWFPGA_HEXB_BASE = 0x00000000;

    while(1){//Should be continuously read the switches and output new values

        ALT_LWFPGA_SWITCH_BASE = 0x00000000;
        //This loop just acts as the 9 switches
        //First loop is MSB and switch 9
        //Last loop is LSB and switch 0
        for( count = 0; count < 10; count = count + 1 ){
            ALT_LWFPGA_SWITCH_BASE <<= 1;
            ALT_LWFPGA_SWITCH_BASE = ALT_LWFPGA_SWITCH_BASE + fpgaswitch();//Add 0 or 1 to last LSB of SWITCH_BASE
        }

        display_23 = ALT_LWFPGA_SWITCH_BASE % 32;//Take the 5 LSBs as switches 4 to 0
        display_45 = ALT_LWFPGA_SWITCH_BASE / 32;//Take the 5 MSBs as switches 9 to 5
        display_01 = display_45 + display_23;

        //Display of MSB is the tens and the display of the LSB is the unit
        ALT_LWFPGA_HEXA_BASE = ALT_LWFPGA_HEXA_BASE + seven_segment_display(display_23 / 10);//Display 3
        ALT_LWFPGA_HEXA_BASE <<= 8;
        ALT_LWFPGA_HEXA_BASE = ALT_LWFPGA_HEXA_BASE + seven_segment_display(display_23 % 10);//Display 2
        ALT_LWFPGA_HEXA_BASE <<= 8;
        ALT_LWFPGA_HEXA_BASE = ALT_LWFPGA_HEXA_BASE + seven_segment_display(display_01 / 10);//Display 1
        ALT_LWFPGA_HEXA_BASE <<= 8;
        ALT_LWFPGA_HEXA_BASE = ALT_LWFPGA_HEXA_BASE + seven_segment_display(display_01 % 10);//Display 0

        ALT_LWFPGA_HEXB_BASE = ALT_LWFPGA_HEXB_BASE + seven_segment_display(display_45 / 10);//Display 5
        ALT_LWFPGA_HEXB_BASE <<= 8;
        ALT_LWFPGA_HEXB_BASE = ALT_LWFPGA_HEXB_BASE + seven_segment_display(display_45 % 10);//Display 4
    }
}
