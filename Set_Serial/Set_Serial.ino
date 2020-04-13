#include <TFMPI2C.h>

#include <Wire.h>     // Arduino standard I2C/Two-Wire Library
#include "printf.h"   // Modified by to support Intel based Arduino
                      // devices such as the Galileo. Download from:
                      // https://github.com/spaniakos/AES/blob/master/printf.h

#include <TFMPI2C.h>  // TFMini-Plus I2C Library v0.2.2
TFMPI2C tfmP;         // Create a TFMini-Plus I2C object

void setup()
{
    Wire.begin();            // Initialize two-wire interface
//    Wire.setClock( 400000);  // Set I2C bus speed to 'Fast' if
                               // your Arduino supports 400KHz.
    Serial.begin( 115200);   // Initialize terminal serial port
    printf_begin();          // Initialize printf library.
    delay(20);

    printf( "\r\nTFMPlus I2C Library Example\r\n");  // say 'hello'

    // Send some example commands to the TFMini-Plus
    // - - - - - - - - - - - - - - - - - - - - - - - -
    printf( "Serial Set: ");
    if( tfmP.sendCommand( SET_UART_MODE, 0)) /// sets serial mode to UART, all code after this does not run if sucsesfull. 
    {
        printf( "passed.\r\n");
    }
    else tfmP.printErrorStatus();
    // - - - - - - - - - - - - - - - - - - - - - - - -
    printf( "Firmware version: ");
    if( tfmP.sendCommand( OBTAIN_FIRMWARE_VERSION, 0))
    {
        printf( "%1u.", tfmP.version[ 0]); // print three single numbers
        printf( "%1u.", tfmP.version[ 1]); // each separated by a dot
        printf( "%1u\r\n", tfmP.version[ 2]);
    }
    else tfmP.printErrorStatus();
    // - - - - - - - - - - - - - - - - - - - - - - - -
    printf( "Data-Frame rate: ");
    if( tfmP.sendCommand( SET_FRAME_RATE, FRAME_250))
    {
        printf( "%2uHz.\r\n", FRAME_250);
    }
    else tfmP.printErrorStatus();
    // - - - - - - - - - - - - - - - - - - - - - - - -

    delay(500);            // And wait for half a second.
}

// Initialize variables
uint16_t tfDist = 0;       // Distance to object in centimeters
uint16_t tfFlux = 0;       // Signal strength or quality of return signal
uint16_t tfTemp = 0;       // Internal temperature of Lidar sensor chip

// = = = = = = = = = =  MAIN LOOP  = = = = = = = = = =
void loop()
{
    delay(50);    //  Run loop at approximately 20Hz.

    tfmP.getData( tfDist, tfFlux, tfTemp); // Get a frame of data
    if( tfmP.status == TFMP_READY)         // If no error...
    {
        printf( "Dist:%04ucm ", tfDist);   // display distance,
        printf( "Flux:%05u ",   tfFlux);   // display signal strength/quality,
        printf( "Temp:%2u\°C",  tfTemp);   // display temperature,
        printf( "\r\n");                   // end-of-line.
    }
    else tfmP.printErrorStatus();          // Otherwise, display error. 
}
