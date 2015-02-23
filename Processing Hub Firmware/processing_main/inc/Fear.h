/*
 * Fear.h
 *
 *  Created on: Jan 29, 2015
 *      Author: B-Chan
 */

#ifndef FEAR_H_
#define FEAR_H_

#define kFilteringFactor 0.1

float prevAccelX = 0;
float prevAccelY = 0;
float prevAccelZ = 0;
bool jump = false;

void Jump
{

	jump = false;

	AccelData currAccel; // from

	float accelX = currAccel.x;
	float accelY = currAccel.y;
	float accelZ = currAccel.z;


	 // Subtract the low-pass value from the current value to get a simplified high-pass filter
    accelX = currAccel.x - ( (currAccel.x * kFilteringFactor) + (accelX * (1.0 - kFilteringFactor)) );
    accelY = currAccel.y - ( (currAccel.y * kFilteringFactor) + (accelY * (1.0 - kFilteringFactor)) );
    accelZ = currAccel.z - ( (currAccel.z * kFilteringFactor) + (accelZ * (1.0 - kFilteringFactor)) );

	//get change in acceleration

    float deltaX = (w_self.accelX - prevAccelX);
    float deltaY = (w_self.accelY - prevAccelY);
    float deltaZ = (w_self.accelZ - prevAccelZ);

    if( deltaX < 0)
    	deltaX = deltaX * (-1);

    if( deltaY < 0)
    	deltaX = deltaY * (-1);

    if( deltaZ < 0)
    	deltaZ = deltaZ * (-1);


	 prevAccelX = accelX;
	 prevAccelY = accelY;
	 prevAccelZ = accelZ;

    if ( deltaX > 1 || deltaY > 1 || deltaZ > 1 )
    	jump = true;

}



#endif /* FEAR_H_ */
