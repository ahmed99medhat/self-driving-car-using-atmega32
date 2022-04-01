/*
* Interfacing_Module_D22.c
*
* Created: 2/15/2022 12:10:23 PM
* Author : User
*/

#include "main.h"

	volatile uint16_t distance_front_the_ultra=0;//variable to get the distance of object front the ultrasonic
	

int main(void)
{
	LCD_Initialization();
	ServoMotor_Initialization();
	Motor_Initialization();
	LCD_Clear();
	Ultrasonic_Init();
	while (1)
	{
		
		distance_front_the_ultra=Ultrasonic();//to get the distance of object front the ultrasonic
		LCD_Clear();
		ServoMotor_Rotate(Angle_0);
		LCD_Write_String((uint8_t*)"distance: ");
		LCD_Write_Number(distance_front_the_ultra);
		LCD_Location(2,2);
		_delay_ms(250);
		 		if(distance_front_the_ultra>=35)
		 		{
		 			Motor_Start(Motor1, Motor_CW);
		 			Motor_Start(Motor2, Motor_CW);//move forward
					 LCD_Clear();
		 			LCD_Write_String((uint8_t*)"forward");
		 			_delay_ms(150);
		 		}
				 else if (distance_front_the_ultra<35)
						{
							ServoMotor_Rotate(Angle_P90);//rotate the servo 90 degree to the right
							distance_front_the_ultra=Ultrasonic();//to get new value after rotation
							                    if(distance_front_the_ultra>35)
							                    {
													 LCD_Clear();
													 LCD_Write_String((uint8_t*)"right");
								                       Motor_Start(Motor1,Motor_CW);//move right
													    _delay_ms(150);//////////////////////////////////////////////////////////////
								                       ServoMotor_Rotate(Angle_0);//to return to the initial position
				
				
							                     }
												  else if (distance_front_the_ultra<35)
												   {
													   ServoMotor_Rotate(Angle_N90);//to rotate servo 90 degree to the left
												 	   distance_front_the_ultra=Ultrasonic();//to get new value after rotation
												 	  if (distance_front_the_ultra>35)
												 	  {
												 		   LCD_Clear();
												 		   LCD_Write_String((uint8_t*)"left");
												 		  Motor_Start(Motor1,Motor_CW);//move left
												 		    _delay_ms(1500);//////////////////////////////////////////////////////////////
												 		  ServoMotor_Rotate(Angle_0);//to return to the initial position
												 	
												 	  }
													  else if (distance_front_the_ultra<35)
													   {
														    LCD_Clear();
														    LCD_Write_String((uint8_t*)"The car rotates 180 degrees");
														   Motor_Start(Motor1, Motor_CW);
														   Motor_Start(Motor2, Motor_CCW);//car rotate 180 degrees 
														   _delay_ms(200);
														    Motor_Stop(Motor1);
														    Motor_Stop(Motor2);//stop
														    ServoMotor_Rotate(Angle_0);//to return to the initial position
														    
													    }
														
												   }
						}
	}
return 0;
}

