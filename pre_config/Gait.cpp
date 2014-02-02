#include "Gait.h"

Gait::Gait(Limb& LimbA, Limb& LimbB, Limb& LimbC, Limb& LimbD, Limb& LimbE, Limb& LimbF) {
  mLimbA = &LimbA;
  mLimbB = &LimbB;
  mLimbC = &LimbC;
  mLimbD = &LimbD;
  mLimbE = &LimbE;
  mLimbF = &LimbF;
}

int Gait::walk(directions directn) {
   switch(directn)  {
      case FORWARD:
        mLimbA->walk(BACKWARD, LEFT, FORWARD);
        mLimbB->walk(FORWARD, LEFT, FORWARD);
        mLimbC->walk(BACKWARD, LEFT, FORWARD);
        
        mLimbD->walk(FORWARD, RIGHT, FORWARD);
        mLimbE->walk(BACKWARD, RIGHT, FORWARD);
        mLimbF->walk(FORWARD, RIGHT, FORWARD);
        break;
        
      case BACKWARD:
        mLimbA->walk(BACKWARD, LEFT, BACKWARD);
        mLimbB->walk(FORWARD, LEFT, BACKWARD);
        mLimbC->walk(BACKWARD, LEFT, BACKWARD);
        
        mLimbD->walk(FORWARD, RIGHT, BACKWARD);
        mLimbE->walk(BACKWARD, RIGHT, BACKWARD);
        mLimbF->walk(FORWARD, RIGHT, BACKWARD);
        break;
   }
}

