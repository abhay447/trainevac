#include <iostream>
#include "math.h"
#define VeloCoeff   0.08824453
#define StableCoeff -0.38086628
#define DistCoeff    0.03996966
using namespace std;

float getAttractionMagnitude(Pedestrian myPed)
{
	float targetDistance = pow(pow((myPed.px-myPed.tx),2) + pow((myPed.py-myPed.ty),2),0.5f)/100;
	float accelPerp      = fabs(myPed.ax*(myPed.ty-myPed.py) - myPed.ay*(myPed.tx-myPed.px))/(pow(pow((myPed.tx-myPed.px),2)+pow((myPed.ty-myPed.py),2),0.5f)*100);
	float speedAlong     = fabs(myPed.ax*(myPed.ty-myPed.py) - myPed.ay*(myPed.tx-myPed.px))/(pow(pow((myPed.tx-myPed.px),2)+pow((myPed.ty-myPed.py),2),0.5f)*100);
	float force          = VeloCoeff*exp(-speedAlong) + StableCoeff*exp(-accelPerp) + DistCoeff*exp(-exp(-targetDistance));
	return 70*force;
}

void selectTarget(Pedestrian &myPed){
    if (myPed.px<=227.8f){
        if(myPed.py>152.0f){
            myPed.tx = 180.0f;
            myPed.ty = 344.0f;                        
        }
        else{
            myPed.tx = 180.0f;
            myPed.ty = -40.0f;                                
        }
    }
    else if (myPed.px>=1854.6f){
        if(myPed.py>152.0f){
            myPed.tx = 1890.0f;
            myPed.ty = 344.0f;                        
        }
        else{
            myPed.tx = 1890.0f;
            myPed.ty = -40.0f;                                
        }
    }
    
    else if(myPed.px<=1040.8f){
        if(myPed.py<105.2f&&myPed.py>148.8f){
            myPed.tx = 220.0f;
            myPed.ty = 152.0f;            
        }
        else{
            myPed.tx = myPed.px-100.0f;
            myPed.ty = 128.0f;            
        }
    }
    else if (myPed.px>1040.8f){
        if(myPed.py<105.2f&&myPed.py>148.8){
            myPed.tx = 1856.0f;
            myPed.ty = 152.0f;            
        }
        else{
            myPed.tx = myPed.px+100.0f;
            myPed.ty = 128.0f;            
        }
    }
    return;
}
