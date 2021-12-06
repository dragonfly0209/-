
// PIC18F4550 Configuration Bit Settings

// 'C' source line config statements

#include <p18F4550.h>
#include <delays.h>
#include <usart.h>
#include <stdio.h>
#include "MFRC522.h"

// CONFIG1L
#pragma config PLLDIV = 4       // PLL Prescaler Selection bits (Divide by 4 (16 MHz oscillator input))
#pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
#pragma config USBDIV = 2       // USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes from the 96 MHz PLL divided by 2)

// CONFIG1H
#pragma config FOSC = HSPLL_HS  // Oscillator Selection bits (HS oscillator, PLL enabled (HSPLL))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = OFF        // Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
#pragma config BORV = 3         // Brown-out Reset Voltage bits (Minimum setting 2.05V)
#pragma config VREGEN = OFF     // USB Voltage Regulator Enable bit (USB voltage regulator disabled)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = ON      // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = ON      // PORTB A/D Enable bit (PORTB<4:0> pins are configured as analog input channels on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = OFF     // Stack Full/Underflow Reset Enable bit (Stack full/underflow will not cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config ICPRT = OFF      // Dedicated In-Circuit Debug/Programming Port (ICPORT) Enable bit (ICPORT disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) is not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) is not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) is not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) is not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) is not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) is not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) is not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) is not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) is not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM is not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) is not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) is not protected from table reads executed in other blocks)

// --------IO pin Definition for LEDs and Buzzer--------------
#define LED1            LATCbits.LATC1
#define LED2            LATAbits.LATA2
#define LED3            LATAbits.LATA3

// --------Variables Declaration for MFRC522------------   
Uid uid;
MIFARE_Key key;

// --------Function Declaration for Task--------------
void Start(void);
void Update(void);
void dump_byte_array(byte *buffer, byte bufferSize);

void high_isr(void);
/*
* For PIC18 devices the high interrupt vector is found at
* 00000008h. The following code will branch to the
* high_interrupt_service_routine function to handle
* interrupts that occur at the high vector.
*/
#pragma code high_vector=0x08
void interrupt_at_high_vector(void)
{
_asm GOTO high_isr _endasm
}
#pragma code /* return to the default code section */
#pragma interrupt high_isr
void high_isr (void)
{
    if (PIR1bits.RCIF) {
        ReadUSART();
    }
}

void main () 
{
    // *********** User Code Area #Begin 0 *********** //

    // *********** User Code Area #End 0 *********** //    
    
    Start();
    
    // *********** User Code Area #Begin 1 *********** //

    // *********** User Code Area #End 1 *********** // 
    while (1) 
    {
        // *********** User Code Area #Begin 2 *********** //
        
        // *********** User Code Area #End 2 *********** //
        
        Update();
        
        // *********** User Code Area #Begin 4 *********** //
        
        // *********** User Code Area #End 4 *********** //
    }
}

void Start(void) {
    byte i;
    // VREF- source = VSS
    // VREF+ source = VDD
    // AN1 ~ AN0 are analog.
    ADCON1 = 0b00001101;
        
    // RA5 for MFRC522_CS
    // RA3 for LED3
    // RA2 for LED2
    TRISA = 0b11010011;
    LATA = 0xFF;
    // RB5 for MFRC522_RST
    // RB4 for MFRC522_IRQ
    TRISB = 0b11010000;
    LATB = 0xFF;
    // RC7 for RX
    // RC6 for TX
    // RC1 for LED1
    TRISC = 0b10111001;
    LATC = 0xFF;
    
    TRISD = 0b00000000;
    LATD = 0xFF;
    // RE2 for MISO
    // RE1 for MOSI
    // RE0 for SCK
    TRISE = 0b100;
    LATE = 0b111;
    
    LED1 = 0; LED2 = 0; LED3 = 0; 
    
    
    OpenUSART(  USART_TX_INT_OFF &
                USART_RX_INT_ON &
                USART_ASYNCH_MODE &
                USART_EIGHT_BIT &
                USART_CONT_RX &
                USART_BRGH_HIGH,
                77 ); //48M / 16 / (77 + 1) = 38462
    
    RCONbits.IPEN = 1;
    INTCONbits.GIEH = 1;
    INTCONbits.GIEL = 1;
    
    // Peripherals Initialization.
    PCD_Init();
    PCD_DumpVersionToSerial();
    
    // Prepare the key (used both as key A and as key B)
    // using FFFFFFFFFFFFh which is the default at chip delivery from the factory
    for (i = 0; i < 6; i++) {
        key.keyByte[i] = 0xFF;
    }
       
    printf("Scan a MIFARE Classic PICC to demonstrate read and write.\r\n");
    printf("Using key (for A and B): ");
    dump_byte_array(key.keyByte, MF_KEY_SIZE);
    printf("\r\n");
    
    printf("BEWARE: Data will be written to the PICC, in sector #1\r\n");
}

void Update(void) 
{
    // --------Variables Declaration Begin------------  
    PICC_Type piccType;
    // In this sample we use the second sector,
    // that is: sector #1, covering block #4 up to and including block #7
    byte sector         = 1;
    byte blockAddr      = 4;
    byte dataBlock[]    = {
        '0', '0', '0', '0',
        '0', 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00 
    };
    byte trailerBlock   = 7;
    StatusCode status;
    byte buffer[18];
    byte size = sizeof(buffer);
    byte count;
    byte i;
    
    // --------Variables Declaration End------------  
    
    // Look for new cards
	if ( ! PICC_IsNewCardPresent()) {
		return;
	}
    
    // Select one of the cards
	if ( ! PICC_ReadCardSerial(&uid)) {
		return;
	}
   
    
//    // Dump debug info about the card; PICC_HaltA() is automatically called
//	PICC_DumpToSerial(&uid);
    
    // Show some details of the PICC (that is: the tag/card)
    printf("Card UID: ");
    dump_byte_array(uid.uidByte, uid.size);
    printf("\r\n");
    printf("PICC type: ");
    piccType = PICC_GetType(uid.sak);
	printf(PICC_GetTypeName(piccType));
    printf("\r\n");
    
    // Check for compatibility
    if (    piccType != PICC_TYPE_MIFARE_MINI
        &&  piccType != PICC_TYPE_MIFARE_1K
        &&  piccType != PICC_TYPE_MIFARE_4K) {
        printf("This sample only works with MIFARE Classic cards.\r\n");
        return;
    }
    
    // In this sample we use the second sector,
    // that is: sector #1, covering block #4 up to and including block #7
    
    // Authenticate using key A
    printf("Authenticating using key A...\r\n");
    status = (StatusCode) PCD_Authenticate(PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &uid);
    if (status != STATUS_OK) {
        printf("PCD_Authenticate() failed: ");
        printf(GetStatusCodeName(status));
        printf("\r\n");
        return;
    }
    
    // Show the whole sector as it currently is
    printf("Current data in sector:\r\n");
    PICC_DumpMifareClassicSectorToSerial(&uid, &key, sector);
    printf("\r\n");
    
    
    // *********** User Code Area #Begin 3 *********** //
    //    Hint 1 : Pointer dataBlock is very important 
    //    Hint 2 : Pointer buffer is very important 
     
    //    dataBlock[0] = 'E' is E-cash
    //    dataBlock[0] = 'I' is E-item
    //    
    //    dataBlock[1] : cost 10^3
    //    dataBlock[2] : cost 10^2
    //    dataBlock[3] : cost 10^1
    //    dataBlock[4] : cost 10^0 

    
    
    // Read data from the block
    printf("Reading data from block %02X ...\r\n", blockAddr);
    status = (StatusCode) MIFARE_Read(blockAddr, buffer, &size);
    if (status != STATUS_OK) {
        printf("MIFARE_Read() failed: ");
        printf(GetStatusCodeName(status));
        printf("\r\n");
    }
    printf("Data in block %02X:\r\n", blockAddr);
    dump_byte_array(buffer, 16);
    printf("\r\n\r\n");

    
    
    
    // Write data to the block
    printf("Writing data into block %02X ...\r\n", blockAddr);;
    dump_byte_array(dataBlock, 16);
    printf("\r\n");
    status = (StatusCode) MIFARE_Write(blockAddr, dataBlock, 16);
    if (status != STATUS_OK) {
        printf("MIFARE_Write() failed: ");
        printf(GetStatusCodeName(status));
        printf("\r\n");
    }
    printf("\r\n");        
    
    LED1 = 1; LED2 = 1; LED3 = 1; 
     
    // *********** User Code Area #End 3 *********** //
    
    // Dump the sector data
    printf("Current data in sector:\r\n");
    PICC_DumpMifareClassicSectorToSerial(&uid, &key, sector);
    printf("\r\n");
    
    // Halt PICC
    PICC_HaltA();
    // Stop encryption on PCD
    PCD_StopCrypto1();
}

/**
 * Helper routine to dump a byte array as hex values to Serial.
 */
void dump_byte_array(byte *buffer, byte bufferSize) {
    byte i;
    for (i = 0; i < bufferSize; i++) {
        printf("%02X ", buffer[i]);
    }
}