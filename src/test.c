#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "ax12a.h"
#include "leg.h"

#define STEP 1.0

int get_leg_num(void)
{
    char buffer[10];
    printf("enter a leg number (0-5) : ");
    scanf(" %s", buffer);
    return atoi(buffer);
}

int main(void)
{
    char portName[] = "/dev/ttyUSB0";
    char buffer[20];
    int i, motorID, retval;
    float degree, speed;
    
    openPort(portName);
    
    printf("Please choose a method to test: \n\t1. turnMotor\n\t2. moveLeg\n\t3. moveLeg (with number keys\n");
    scanf(" %s", buffer);
    int choice = atoi(buffer);
    if(choice == 1)
    {
        while(1)
        {
            printf("Enter a motor ID number (0 - 253 or q to quit): ");
            scanf(" %s", buffer);
            
            if(buffer[0] == 'q')
            {
                break;
            }
            
            motorID = atoi(buffer);
            
            printf("Enter a goal position (0 - 300 or q to quit): ");
            scanf(" %s", buffer);
            
            if(buffer[0] == 'q')
            {
                break;
            }
            
            degree = atof(buffer);
            
            printf("Enter a speed (0 - ?? or q to quit): ");
            scanf(" %s", buffer);
            
            if(buffer[0] == 'q')
            {
                break;
            }
            
            speed = atof(buffer);
            
            retval = turnMotor(motorID, degree, speed);
            
            if(retval != 0)
            {
                printf("Error: %i\n", retval);
            }
            else
            {
                printf("Success!!!\n");
            }
        }
    }
    else if(choice == 2)
    {
        float x,y,z;
        
        while(1)
        {
            int leg_num = get_leg_num();
            printf("enter a point, x : ");
            scanf(" %s", buffer);
            x = atoi(buffer);
            printf("enter a point, y : ");
            scanf(" %s", buffer);
            y = atoi(buffer);
            printf("enter a point, z : ");
            scanf(" %s", buffer);
            z = atoi(buffer);
            
            move_leg(leg_num, x, y, z);
        }
        
        
    }
    else if(choice == 3)
    {
        struct position pos;
        float x,y,z;
        int leg_num = get_leg_num();
        /*printf("enter a starting point, x : ");
        scanf(" %s", buffer);
        x = atoi(buffer);
        printf("enter a starting point, y : ");
        scanf(" %s", buffer);
        y = atoi(buffer);
        printf("enter a starting point, z : ");
        scanf(" %s", buffer);
        z = atoi(buffer);*/
        x=0;
        y=20;
        z=0;
        
        move_leg(leg_num, x, y, z);
        
        printf("Use the number keys to move the leg along the x, y, and z axes\n");
        
        while(1)
        {
            printf("\n1. decrease x\n2. increase x\n3. decrease y\n4. increase y\n5. decrease z\n6. increase z\n");
            char c = getchar();
            printf("%c\n", c);
            
            if (c == '1')
                x=x-STEP;
            else if (c == '2')
                x=x+STEP;
            else if (c == '3')
                y=y-STEP;
            else if (c == '4')
                y=y+STEP;
            else if (c == '5')
                z=z-STEP;
            else if (c == '6')
                z=z+STEP;
            
            move_leg(leg_num, x, y, z);
        }
    }
    else if(choice == 4)
    {
        float step = 1;
        float x,y,z;
        x=0;
        y=20;
        z=0;
        int leg_num = get_leg_num();
        move_leg(leg_num,x,y,z);
        sleep(1);
        int boundary = 19;
        float time = 0.1;
        for (x = 0; x < boundary; x+=step)
        {
            move_leg(leg_num, x, y, z);
            //sleep(time);
        }
        while(1)
        {
            for (x = boundary; x > -boundary; x-=step)
            {
                move_leg(leg_num, x, y, z);
                //sleep(time);
            }
            for (x = -boundary; x < boundary; x+=step)
            {
                move_leg(leg_num, x, y, z);
                //sleep(time);
            }
        }
    }
    else if(choice == 5)
    {
        float step = 3;
        float x,y,z;
        x=0;
        y=15;
        z=1;
        //move_leg(1,x,y,z);
        //sleep(1);
        int boundary = 7;
        float time = 0.001;
        for (x = 0; x < boundary; x+=step)
        {
            move_leg(1, x, y, z);
            move_leg(3, x, y, z);
            move_leg(5, x, y, z);
            //sleep(time);
        }
        while(1)
        {
            for (x = boundary; x > -boundary; x-=step)
            {
                move_leg(1, x, y, z);
                move_leg(3, x, y, z);
                move_leg(5, x, y, z);
                //sleep(time);
            }
            for (x = -boundary; x < boundary; x+=step)
            {
                move_leg(1, x, y, z);
                move_leg(3, x, y, z);
                move_leg(5, x, y, z);
                //sleep(time);
            }
        }
    }
    else if(choice == 6)
    {
        float step = 3;
        float x,y,z;
        x=0;
        y=15;
        z=1;
        //move_leg(1,x,y,z);
	move_leg(1, x, y, z);
        move_leg(4, x, y, z);
        //move_leg(0, x, y, z);
        sleep(1);
        int boundary = 15;
        float time = 0.001;
        for (x = 0; x < boundary; x+=step)
        {
            move_leg(1, x, y, z);
            move_leg(4, x, y, z);
            //move_leg(5, x, y, z);
            //sleep(time);
        }
        while(1)
        {
            for (x = boundary; x > -boundary; x-=step)
            {
                move_leg(1, x, y, z);
                move_leg(4, x, y, z);
                //move_leg(5, x, y, z);
                //sleep(time);
            }
            for (x = -boundary; x < boundary; x+=step)
            {
                move_leg(1, x, y, z);
                move_leg(4, x, y, z);
                //move_leg(5, x, y, z);
                //sleep(time);
            }
        }
    }
    else
    {
        printf("That is not a valid choice, program terminating.");
    }
    
    closePort();
    
    return 0;
}