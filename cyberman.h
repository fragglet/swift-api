/*
    SPHINX Programming (C) 1994.
    NAME:  CYBERMAN.H--
    DESCRIPTION:  This file supplies complete access to a Logitech CyberMan
                  device via the SWIFT (SenseWare InterFace Technology)
                  device interface standard.  SWIFT functions are provided
                  by Logitech mouse drivers version 6.31 or later.
    LAST MODIFIED:  25 June 1994
    PROCEDURES DEFINED IN THIS FILE:
	: void CYBERMAN_FEEDBACK(byte motor_on_time,byte motor_off_time,
                                 byte duration)
	: byte cyberman_installed()
        : void GET_CYBERMAN()
*/

// these variables are filled by calling GET_CYBERMAN();
int cyberman_xpos=0;  /* x position:  254 values from -8128 to +8064 in
                                    increments of 64 */
int cyberman_ypos=0;  /* y position:  254 values from -8128 to +8064 in
                                    increments of 64 */
int cyberman_zpos=0;        /*  z position:  -8192, 0 or +8191 */
int cyberman_pitchvalue=0;  /* pitch value:  -8192, 0 or +8191 */
int cyberman_rollvalue=0;   /*  roll value:  -8192, 0 or +8191 */
int cyberman_yawvalue=0;    /*   yaw value:  -8192, 0 or +8191 */
word cyberman_buttons=0;  /* bit 0 == Right Button (1 = pressed)
                             bit 1 == Middle Button (1 = pressed)
                             bit 2 == Left Button (1 = pressed)
                             bit 3 == Button 4
                             bit 4 == Button 5
                             bit 5 == Button 6
                             bit 6 == Button 7
                             bits 7-15 == Reserved */



: byte cyberman_installed ()
/* Returns TRUE if a CyberMan and Driver is installed, otherwise it returns
   FALSE.
*/
byte cyber_buf[10];
{
ES = SS;
DX = #cyber_buf;
AX = 0x53C1;
$INT 0x33
IF( AX != 1 )
    return(FALSE);
IF( cyber_buf[0] != 1 )
    return(FALSE);
return(TRUE);
}


: void CYBERMAN_FEEDBACK () /* (byte motor_on_time,byte motor_off_time,
                                   byte duration) */
/*
motor_on_time is motor on time in 5 ms units.
motor_off_time is motor on time in 5 ms units.
duration is length of time of feedback in units of 40 ms.
*/
{
BH = AL;
AX = 0x5330;
$INT 0x33
}


: void GET_CYBERMAN ()
/* Obtains button and location status info of the Cyberman from the driver.
   The results are stored in the 'cyber_' variables.
*/
{
ES = CS;
DX = #cyberman_xpos;
AX = 0x5301;
$INT 0x33
}


/* end of CYBERMAN.H-- */

