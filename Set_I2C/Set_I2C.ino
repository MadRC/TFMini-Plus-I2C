/* File Name: TFMP_example.ino
 * Developer: Bud Ryerson
 * Inception: 29 JAN 2019
 * Last work: 16 MAR 2020
 *
 * Description: Arduino sketch to test the Benewake TFMini Plus
 * time-of-flight Lidar ranging sensor using the TFMPlus library.
 *
 * Default settings for the TFMini Plus are a 115200 serial baud rate
 * and a 100Hz measurement frame rate. The device will begin returning
 * measurement data right away:
 *   Distance in centimeters,
 *   Signal strength in arbitrary units,
 *   and an encoded number for Temperature in degrees centigrade.
   **********************     IMPORTANT    ************************
   ****  Changed name of 'buildCommand()' to 'sendCommand()'.  ****
   ****************************************************************
 * Use the 'sendCommand' to send commands and return a status code.
 * Commands are selected from the library's list of defined commands.
 * Parameters can be entered directly (115200, 250, etc) but for
 * safety, they should be chosen from the library's defined lists.
 *
 */

#include <TFMPlus.h>  // Include TFMini Plus Library v1.3.4
TFMPlus tfmP;         // Create a TFMini Plus object

#include "printf.h"   // May not work corrrectly with Intel devices

//#include <SoftwareSerial.h>       // alternative software serial library
//SoftwareSerial mySerial(10, 11);  // Choose the correct RX, TX Pins

uint16_t tfDist;       // Distance measurement in centimeters (default)
uint16_t tfFlux;       // Luminous flux or intensity of return signal
uint16_t tfTemp;       // Temperature in degrees Centigrade (coded)
uint16_t loopCount;    // Loop counter (1-20)

/*  - - - - -  A few useful Lidar commands    - - - - - */

// Try three times to get the firmware version number
// which is saved as 'tfmp.version', a three byte array.



void factoryReset()
{
    printf( "Lidar factory reset ");
    if( tfmP.sendCommand( RESTORE_FACTORY_SETTINGS, 0))
    {
        printf( "passed.\r\n");
    }
    else
    {
        printf( "failed.");
        tfmP.printStatus( false);
    }
}

void firmwareVersion()
{
    for( uint8_t fvi = 1; fvi < 4; ++fvi)
    {
        if( tfmP.sendCommand( SET_I2C_MODE, 0))
        {
            // If successful, display the version number...
            printf( "Complete");      // and brreak out of loop.
        }
        else
        {
            // If not successful, display the attempt number
            // and the error: HEADER, CHERCKSUM, SERIAL, tec.
            printf( "failed. "); // Display error message...
          
        }
        delay(100);  // Wait to try again
    }
}


/*  - - -   End of useful Lidar commands   - - - -   */

void setup()
{
    Serial.begin( 115200);   // Intialize terminal serial port
    delay(20);               // Give port time to initalize
    printf_begin();          // Initialize printf.
    printf("\r\nTFMPlus Library Example - 07JUN2019\r\n");  // say 'hello'

    Serial.begin( 115200);  // Initialize TFMPLus device serial port.
    delay(20);               // Give port time to initalize
    tfmP.begin( &Serial);   // Initialize device library object and...
                             // pass device serial port to the object.
  delay(3000);            // And wait for half a second.

    // Send commands to device during setup.
  //factoryReset();     // reset to default settings
    firmwareVersion();  // get firmware version



    // Initialize the variables for this example
    loopCount = 0;         // Reset loop counter.
    tfDist = 0;            // Clear device data variables.
    tfFlux = 0;
    tfTemp = 0;

    delay(500);            // And wait for half a second.
}

// Use the 'getData' function to pass back device data.
void loop()
{
        // Delay to match the 100Hz data frame rate.
}
