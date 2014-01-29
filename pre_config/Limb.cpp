#include "Limb.h"

Limb::Limb(Servo& svHip, Servo& svUprLimb, Servo& svLwrLimb){
  // initializes some data members
  cntr = 0.0;
  cntrB = 0.0;
  projY = 5; // Note: this is the of the limb's angle (forward)
  projYB = -5; // Note: this is the of the limb's angle (backward)

  length = 13;
  
  mSvHip = svHip;
  mSvUprLimb = svUprLimb;
  mSvLwrLimb = svLwrLimb;
  
  // instantiates the Inverser Kinematics class
  ikLeg = Inversekinematics();
  
  // sets the orietation priority of the leg
  revDirectionFrontPrior = revFORWARD;
  revDirectionBackPrior = revBACKWARD;
  
  // speed
  pace = 0.25; 
}

void Limb::walk(directions directn, sides side) {
  switch(directn) {
     case FORWARD:
         walkForward(side);
         break;
     case BACKWARD:
         walkBackward(side);
         break;
     default:
          FORWARD; 
  }
}

void Limb::walkForward(sides side) {
  // walks forward
  ikLeg.move(cntr, length);
  
  (side == RIGHT) ? mSvHip.write(getAbsoluteAngle((int)ikLeg.getHip(), RIGHT)) : mSvHip.write(getAbsoluteAngle((int)ikLeg.getHip(), LEFT));
  (side == RIGHT) ? mSvUprLimb.write(getAbsoluteAngle((int)ikLeg.getUpperLimb(), RIGHT)) : mSvUprLimb.write(getAbsoluteAngle((int)ikLeg.getUpperLimb(), LEFT));
  (side == RIGHT) ? mSvLwrLimb.write(getAbsoluteAngle((int)ikLeg.getLowerLimb(), RIGHT)) : mSvLwrLimb.write(getAbsoluteAngle((int)ikLeg.getLowerLimb(), LEFT));
  Serial.print(" cntr: ");
  Serial.println(cntr); 
  Serial.print("Gamma: ");
  Serial.print((int)ikLeg.getHip());
  Serial.print(" Direction: ");
  Serial.println(revDirectionFrontPrior);
//  delay(500);
  if(revDirectionFrontPrior == revFORWARD) {
    cntr = cntr + pace;
    if(cntr > projY)
      revDirectionFrontPrior = revBACKWARD;
  } else {
    cntr = cntr - pace;
    if(cntr < 0) revDirectionFrontPrior = revFORWARD;
  }
}

void Limb::walkBackward(sides side){
  // walks backward
  ikLeg.move(cntrB, length);

  (side == RIGHT) ? mSvHip.write(getAbsoluteAngle((int)ikLeg.getHip(), RIGHT)) : mSvHip.write(getAbsoluteAngle((int)ikLeg.getHip(), LEFT));
  (side == RIGHT) ? mSvUprLimb.write(getAbsoluteAngle((int)ikLeg.getUpperLimb(), RIGHT)) : mSvUprLimb.write(getAbsoluteAngle((int)ikLeg.getUpperLimb(), LEFT));
  (side == RIGHT) ? mSvLwrLimb.write(getAbsoluteAngle((int)ikLeg.getLowerLimb(), RIGHT)) : mSvLwrLimb.write(getAbsoluteAngle((int)ikLeg.getLowerLimb(), LEFT));
  Serial.print(" cntrB: ");
  Serial.println(cntrB); 
  Serial.print("Gamma: ");
  Serial.print((int)ikLeg.getHip());
  Serial.print(" Direction: ");
  Serial.println(revDirectionBackPrior);
  
  if(revDirectionBackPrior == revBACKWARD) {
    cntrB = cntrB - pace;
    if(cntrB < projYB)
      revDirectionBackPrior = revFORWARD;
  } else {
    cntrB = cntrB + pace;
    if(cntrB > 0) 
      revDirectionBackPrior = revBACKWARD;
  }
  
}

void Limb::setPace(double newVal) {
  pace = newVal; 
}

double Limb::getPace() {
  return pace; 
}


