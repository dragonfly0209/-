#include <p18F4550.h>
#include <delays.h>
#include <stdio.h>
#include <string.h>
#include "Day1_Test_Input.h"

void USB_Init(byte * buffer)
{
    byte cmdBuffer[4] = {0xaa,0xaa,0xaa,0xaa};
    
	memcpy(buffer , &cmdBuffer[0] , 4);
}

