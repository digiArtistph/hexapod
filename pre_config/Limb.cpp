#include "Limb.h"

Limb::Limb(Servo& svHip, Servo& svUprLimb, Servo& svLwrLimb){
  // initializes some data members
  cntr = 0.0;
  cntrB = 0.0;
  projY = 5; // Note: this is the of the limb's angle (forward)
  projYB = -5; // Note: this is the of the limb's angle (backward)
  
  // Settings: 12:0.2||ok; 11:0.2-.25||much ok
  length = 10;
  
  mSvHip = svHip;
  mSvUprLimb = svUprLimb;
  mSvLwrLimb = svLwrLimb;
  
  // instantiates the Inverser Kinematics class
  ikLeg = Inversekinematics();
  
  // sets the orietation priority of the leg
  revDirectionFrontPrior = revFORWARD;
  revDirectionBackPrior = revBACKWARD;
  raiseLegOffsetForward = 0.0;
  raiseLegOffsetBackward = 0.0;
  
  // speed
  pace = 0.125; 
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
  (side == RIGHT) ? mSvUprLimb.write(getAbsoluteAngle((int)ikLeg.getUpperLimb() - raiseLegOffsetForward, RIGHT)) : mSvUprLimb.write(getAbsoluteAngle((int)ikLeg.getUpperLimb() - raiseLegOffsetForward, LEFT));
  (side == RIGHT) ? mSvLwrLimb.write(getAbsoluteAngle((int)ikLeg.getLowerLimb(), RIGHT)) : mSvLwrLimb.write(getAbsoluteAngle((int)ikLeg.getLowerLimb(), LEFT));
//  Serial.print(" cntr: ");
//  Serial.println(cntr); 
//  Serial.print("Gamma: ");
//  Serial.print((int)ikLeg.getHip());
//  Serial.print(" Direction: ");
//  Serial.println(revDirectionFrontPrior);
//  delay(500);
  if(revDirectionFrontPrior == revFORWARD) {
    cntr = cntr + pace;
    if(cntr > projY)
      revDirectionFrontPrior = revBACKWARD;
    // raise leg    
    raiseLegOffsetForward = RAISEOFFSET_Y;
  } else {
    cntr = cntr - pace;
    if(cntr < 0) revDirectionFrontPrior = revFORWARD;
    
    // down leg
    raiseLegOffsetForward = 0.0;
  }
}

void Limb::walkBackward(sides side){
  // walks backward
  ikLeg.move(cntrB, length);

  (side == RIGHT) ? mSvHip.write(getAbsoluteAngle((int)ikLeg.getHip(), RIGHT)) : mSvHip.write(getAbsoluteAngle((int)ikLeg.getHip(), LEFT));
  (side == RIGHT) ? mSvUprLimb.write(getAbsoluteAngle((int)ikLeg.getUpperLimb() - raiseLegOffsetBackward, RIGHT)) : mSvUprLimb.write(getAbsoluteAngle((int)ikLeg.getUpperLimb() - raiseLegOffsetBackward, LEFT));
  (side == RIGHT) ? mSvLwrLimb.write(getAbsoluteAngle((int)ikLeg.getLowerLimb(), RIGHT)) : mSvLwrLimb.write(getAbsoluteAngle((int)ikLeg.getLowerLimb(), LEFT));
//  Serial.print(" cntrB: ");
//  Serial.println(cntrB); 
//  Serial.print("Gamma: ");
//  Serial.print((int)ikLeg.getHip());
//  Serial.print(" Direction: ");
//  Serial.println(revDirectionBackPrior);
  
  if(revDirectionBackPrior == revBACKWARD) {
    cntrB = cntrB - pace;
    if(cntrB < projYB)
      revDirectionBackPrior = revFORWARD;
      raiseLegOffsetBackward = 0;
  } else {
    cntrB = cntrB + pace;
    if(cntrB > 0) 
      revDirectionBackPrior = revBACKWARD;
      
    raiseLegOffsetBackward = RAISEOFFSET_Y;
  }
  
}

void Limb::setPace(double newVal) {
  pace = newVal; 
}

double Limb::getPace() {
  return pace; 
}



