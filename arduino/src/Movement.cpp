/*

 Copyright (C) 2017 Eric van Dijken <eric@team-moki.nl>

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.

*/

#include "Movement.h"

//
// Forward
//
void Movement::Compute(Rov &R) {

//
// Thruster 1
//
    if ((R.T1.current != R.T1.target) && R.T1.once == false) {
        if (R.T1.step == 1) {
            R.T1.current = R.T1.target;
            R.T1.once = true;
        } else {
            R.T1.step--;
            if (R.T1.current > R.T1.target) {
                R.T1.current = R.T1.target - (R.T1.target - R.T1.current)/R.T1.step;
            } else {
                R.T1.current = R.T1.target + (R.T1.target - R.T1.current)/R.T1.step;
            }
        }
    }
//
// Thruster 2
//
    if ((R.T2.current != R.T2.target) && R.T2.once == false) {
        if (R.T2.step == 1) {
            R.T2.current = R.T2.target;
            R.T2.once = true;
        } else {
            R.T2.step--;
            if (R.T2.current > R.T2.target) {
                R.T2.current = R.T2.target - (R.T2.target - R.T2.current)/R.T2.step;
            } else {
                R.T2.current = R.T2.target + (R.T2.target - R.T2.current)/R.T2.step;
            }
        }
    }
//
// Thruster 3
//
    if ((R.T3.current != R.T3.target) && R.T3.once == false) {
        if (R.T3.step == 1) {
            R.T3.current = R.T3.target;
            R.T3.once = true;
        } else {
            R.T3.step--;
            if (R.T3.current > R.T3.target) {
                R.T3.current = R.T3.target - (R.T3.target - R.T3.current)/R.T3.step;
            } else {
                R.T3.current = R.T3.target + (R.T3.target - R.T3.current)/R.T3.step;
            }
        }
    }
//
// Thruster 4
//
    if ((R.T4.current != R.T4.target) && R.T4.once == false) {
        if (R.T4.step == 1) {
            R.T4.current = R.T4.target;
            R.T4.once = true;
        } else {
            R.T4.step--;
            if (R.T4.current > R.T4.target) {
                R.T4.current = R.T4.target - (R.T4.target - R.T4.current)/R.T4.step;
            } else {
                R.T4.current = R.T4.target + (R.T4.target - R.T4.current)/R.T4.step;
            }
        }
    }
//
// Thruster 5
//
    if ((R.T5.current != R.T5.target) && R.T5.once == false) {
        if (R.T5.step == 1) {
            R.T5.current = R.T5.target;
            R.T5.once = true;
        } else {
            R.T5.step--;
            if (R.T5.current > R.T5.target) {
                R.T5.current = R.T5.target - (R.T5.target - R.T5.current)/R.T5.step;
            } else {
                R.T5.current = R.T5.target + (R.T5.target - R.T5.current)/R.T5.step;
            }
        }
    }
//
// Thruster 6
//
    if ((R.T6.current != R.T6.target) && R.T6.once == false) {
        if (R.T6.step == 1) {
            R.T6.current = R.T6.target;
            R.T6.once = true;
        } else {
            R.T6.step--;
            if (R.T6.current > R.T6.target) {
                R.T6.current = R.T6.target - (R.T6.target - R.T6.current)/R.T6.step;
            } else {
                R.T6.current = R.T6.target + (R.T6.target - R.T6.current)/R.T6.step;
            }
        }
    }
}


//
// Run 
//
void Movement::Run(Rov &R, int DIRECTION, int POWER) {

//
// Thruster 1
//
    if (DIRECTION & THRUSTER1_DIR) {
        if (DIRECTION & THRUSTER1_REVERSE) {
            R.T1.target = THRUSTER1_NEUTRAL-(4 * POWER);
        } else {
            R.T1.target = THRUSTER1_NEUTRAL+(4 * POWER);
        }
        R.T1.once = false;
        R.T1.step = MOVEMENT_STEPS;
    }
//
// Thruster 2
//
    if (DIRECTION & THRUSTER2_DIR) {
        if (DIRECTION & THRUSTER2_REVERSE) {
            R.T2.target = THRUSTER2_NEUTRAL-(4 * POWER);
        } else {
            R.T2.target = THRUSTER2_NEUTRAL+(4 * POWER);
        }
        R.T2.once = false;
        R.T2.step = MOVEMENT_STEPS;
    }
//
// Thruster 3
//
    if (DIRECTION & THRUSTER3_DIR) {
        if (DIRECTION & THRUSTER3_REVERSE) {
            R.T3.target = THRUSTER3_NEUTRAL-(4 * POWER);
        } else {
            R.T3.target = THRUSTER3_NEUTRAL+(4 * POWER);
        }
        R.T3.once = false;
        R.T3.step = MOVEMENT_STEPS;
    }
//
// Thruster 4
//
    if (DIRECTION & THRUSTER4_DIR) {
        if (DIRECTION & THRUSTER4_REVERSE) {
            R.T4.target = THRUSTER4_NEUTRAL-(4 * POWER);
        } else {
            R.T4.target = THRUSTER4_NEUTRAL+(4 * POWER);
        }
        R.T4.once = false;
        R.T4.step = MOVEMENT_STEPS;
    }
//
// Thruster 5
//
    if (DIRECTION & THRUSTER5_DIR) {
        if (DIRECTION & THRUSTER5_REVERSE) {
            R.T5.target = THRUSTER5_NEUTRAL-(4 * POWER);
        } else {
            R.T5.target = THRUSTER5_NEUTRAL+(4 * POWER);
        }
        R.T5.once = false;
        R.T5.step = MOVEMENT_STEPS;
    }
//
// Thruster 6
//
    if (DIRECTION & THRUSTER6_DIR) {
        if (DIRECTION & THRUSTER6_REVERSE) {
            R.T6.target = THRUSTER6_NEUTRAL-(4 * POWER);
        } else {
            R.T6.target = THRUSTER6_NEUTRAL+(4 * POWER);
        }
        R.T6.once = false;
        R.T6.step = MOVEMENT_STEPS;
    }

    Compute(R);

    Thruster::Loop(R);
}

//
// Forward
//
void Movement::Forward(Rov &R) {
    Run(R, MOVEMENT_FORWARD, R.Power);
}
void Movement::Forward(Rov &R, int Power) {
    Run(R, MOVEMENT_FORWARD, Power);
}

//
// Reverse
//
void Movement::Reverse(Rov &R) {
    Run(R, MOVEMENT_REVERSE, R.Power);
}
void Movement::Reverse(Rov &R, int Power) {
    Run(R, MOVEMENT_REVERSE, Power);
}

//
// Right
//
void Movement::Right(Rov &R) {
    Run(R, MOVEMENT_RIGHT, R.Power);
}
void Movement::Right(Rov &R, int Power) {
    Run(R, MOVEMENT_RIGHT, Power);
}

//
// Left
//
void Movement::Left(Rov &R) {
    Run(R, MOVEMENT_LEFT, R.Power);
}
void Movement::Left(Rov &R, int Power) {
    Run(R, MOVEMENT_LEFT, Power);
}

//
// Up
//
void Movement::Up(Rov &R) {
    Run(R, MOVEMENT_UP, R.Power);
}
void Movement::Up(Rov &R, int Power) {
    Run(R, MOVEMENT_UP, Power);
}

//
// Dive
//
void Movement::Dive(Rov &R) {
    Run(R, MOVEMENT_DIVE, R.Power);
}
void Movement::Dive(Rov &R, int Power) {
    Run(R, MOVEMENT_DIVE, Power);
}

//
// Strafe_Right
//
void Movement::Strafe_Right(Rov &R) {
    Run(R, MOVEMENT_STRAFE_RIGHT, R.Power);
}
void Movement::Strafe_Right(Rov &R, int Power) {
    Run(R, MOVEMENT_STRAFE_RIGHT, Power);
}

//
// Strafe_Left
//
void Movement::Strafe_Left(Rov &R) {
    Run(R, MOVEMENT_STRAFE_LEFT, R.Power);
}
void Movement::Strafe_Left(Rov &R, int Power) {
    Run(R, MOVEMENT_STRAFE_LEFT, Power);
}

//
// Roll_Right
//
void Movement::Roll_Right(Rov &R) {
    Run(R, MOVEMENT_ROLL_RIGHT, R.Power);
}
void Movement::Roll_Right(Rov &R, int Power) {
    Run(R, MOVEMENT_ROLL_RIGHT, Power);
}

//
// Roll_Left
//
void Movement::Roll_Left(Rov &R) {
    Run(R, MOVEMENT_ROLL_LEFT, R.Power);
}
void Movement::Roll_Left(Rov &R, int Power) {
    Run(R, MOVEMENT_ROLL_LEFT, Power);
}

//
// Movement::Stop
// 
void Movement::Stop(Rov &R)
{
#if defined THRUSTER1_PWM
    R.T1.current = THRUSTER1_NEUTRAL;
    R.T1.target = THRUSTER1_NEUTRAL;
#endif
#if defined THRUSTER2_PWM
    R.T2.current = THRUSTER2_NEUTRAL;
    R.T2.target = THRUSTER2_NEUTRAL;
#endif
#if defined THRUSTER3_PWM
    R.T3.current = THRUSTER3_NEUTRAL;
    R.T3.target = THRUSTER3_NEUTRAL;
#endif
#if defined THRUSTER4_PWM
    R.T4.current = THRUSTER4_NEUTRAL;
    R.T4.target = THRUSTER4_NEUTRAL;
#endif
#if defined THRUSTER5_PWM
    R.T5.current = THRUSTER5_NEUTRAL;
    R.T5.target = THRUSTER5_NEUTRAL;
#endif
#if defined THRUSTER6_PWM
    R.T6.current = THRUSTER6_NEUTRAL;
    R.T6.target = THRUSTER6_NEUTRAL;
#endif

    Thruster::Loop(R);
}

//
// Movement::Setup
//
void Movement::Setup(Rov &R)
{
    R.Power = 0;

#if defined THRUSTER1_PWM
    R.T1.current = THRUSTER1_NEUTRAL;
    R.T1.target = THRUSTER1_NEUTRAL;
#endif
#if defined THRUSTER2_PWM
    R.T2.current = THRUSTER2_NEUTRAL;
    R.T2.target = THRUSTER2_NEUTRAL;
#endif
#if defined THRUSTER3_PWM
    R.T3.current = THRUSTER3_NEUTRAL;
    R.T3.target = THRUSTER3_NEUTRAL;
#endif
#if defined THRUSTER4_PWM
    R.T4.current = THRUSTER4_NEUTRAL;
    R.T4.target = THRUSTER4_NEUTRAL;
#endif
#if defined THRUSTER5_PWM
    R.T5.current = THRUSTER5_NEUTRAL;
    R.T5.target = THRUSTER5_NEUTRAL;
#endif
#if defined THRUSTER6_PWM
    R.T6.current = THRUSTER6_NEUTRAL;
    R.T6.target = THRUSTER6_NEUTRAL;
#endif

    Thruster::Loop(R);
}
