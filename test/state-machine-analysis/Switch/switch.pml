/*
 * SPIN Model checker for the high level design of the project - Flashing Jacket.
 * Although many details of the state machine are left out in this 
 * implementation, it still gives us confidence of our model.
 */

// Outputs of the gesture detector
mtype = {GESTURE, NONGESTURE};

// Outputs of the switch detector
mtype = {SWITCH, NONSWITCH};

// State definitions
mtype = {BIKE, MUSIC};

// communication channel
chan gesture_channel = [0] of {mtype};
chan switch_channel = [0] of {mtype};

// State machine variables
mtype state = BIKE;
mtype gesture = NONGESTURE;
mtype swit = NONSWITCH;

/*
 * Use non-deterministic semantic to simulate the Outputs of both the gesture detector and the switch detector.
 * Put them in the same process to represent the fact that they are actually generated from the same data.
 * And nested if statement specifies that only when it is a gesture does switch signal make sense.
 */ 

inline environment() {
  atomic {
    if
      :: gesture_channel ! NONGESTURE;
      :: gesture_channel ! GESTURE ->
        if
          :: switch_channel ! SWITCH;
          :: switch_channel ! NONSWITCH;
        fi
    fi;
  }
}

/*
 * Model the switch function of Flashing Jacket.
 */
active proctype Switch() {
  do
    :: atomic {
      environment();
      gesture_channel ? gesture ->
        if
          :: gesture == GESTURE ->
            switch_channel ? swit ->
              if
                :: swit == NONSWITCH -> skip;
                :: swit == SWITCH ->
                  if
                    :: state == BIKE -> state = MUSIC;
                    :: state == MUSIC -> state = BIKE;
                  fi
              fi
          :: else -> skip;
        fi;
    }
  od;
}


/*
 * LTL properties specify that once the switch signal is detected, the state machine
 * will transition to the other mode.
 */
ltl p1 { []( (gesture == GESTURE && swit == SWITCH && state == BIKE)  -> X(state == MUSIC) ) }
ltl p2 { []( (gesture == GESTURE && swit == SWITCH && state == MUSIC) -> X(state == BIKE) ) }