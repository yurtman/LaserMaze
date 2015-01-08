#include "LaserMaze.h"
#include "Arduino.h"

// CONSTRUCTOR
LaserMaze::LaserMaze(
  int alarm,
  int laser1, int laser2, int laser3, int laser4, int laser5,
  int portallaser,  int prize,  int portaldetector,
  int detector1, int detector2, int detector3, int detector4, int detector5
)
{
    Serial.println("LaserMaze::LaserMaze");
    delay(1000);
    pinMode(alarm, OUTPUT);
    m_alarm = alarm;
    pinMode(laser1, OUTPUT);
    m_laser1 = laser1;
	pinMode(laser2, OUTPUT);
    m_laser2 = laser2;
	pinMode(laser3, OUTPUT);
    m_laser3 = laser3;
	pinMode(laser4, OUTPUT);
    m_laser4 = laser4;
	pinMode(laser5, OUTPUT);
    m_laser5 = laser5;
	pinMode(portallaser, OUTPUT);
    m_portallaser = portallaser;
    pinMode(prize, INPUT);
    m_prize = prize;
    m_portaldetector = portaldetector;
    m_detector1 = detector1;
    m_detector2 = detector2;
    m_detector3 = detector3;
    m_detector4 = detector4;
    m_detector5 = detector5;
    Serial.println("An instance of LaserMaze has been created. Use Start() to run.");
} 

// BEGIN
void LaserMaze::Start() {
    AlignMaze();
}

// ALIGN
void LaserMaze::AlignMaze() {
    while (isaligned == false) {
        digitalWrite(m_portallaser, HIGH);
        digitalWrite(m_laser1, HIGH);
        digitalWrite(m_laser2, HIGH);
        digitalWrite(m_laser3, HIGH);
        digitalWrite(m_laser4, HIGH);
        digitalWrite(m_laser5, HIGH);
        Serial.println("Please direct the lasers onto the detectors and put prize in place when done.");
		
		// when alignment is complete
        if (DetectSteal() == true) {
            delay(5000);
            Serial.println("You have indicated that you are done with alignment. The sensors will now be calibrated.");
            digitalWrite(m_portallaser, LOW);
            digitalWrite(m_laser1, LOW);
            digitalWrite(m_laser2, LOW);
            digitalWrite(m_laser3, LOW);
            digitalWrite(m_laser4, LOW);
            digitalWrite(m_laser5, LOW);
      		isaligned = true;           
            CalibrateMaze();
        };
    };
    Serial.println("The Beams are already aligned.");

}

// GET THRESHOLD
int LaserMaze::GetThreshold(const int laser, const int detector) {
    int h1, h2, h3 = 0;
    int l1, l2, l3 = 1;
	const int t = 50;
	
	// find threshold by turning laser on and off 3 times	
	 digitalWrite(laser, HIGH);
	 delay(t);
	 h1 = analogRead(detector);
	 digitalWrite(laser, LOW);
	 delay(t);
	 l1 = analogRead(detector);
	 digitalWrite(laser, HIGH);
	 delay(t);
	 h2 = analogRead(detector);
	 digitalWrite(laser, LOW);
	 delay(t);
	 l2 = analogRead(detector);
	 digitalWrite(laser, HIGH);
	 delay(t);
	 h3 = analogRead(detector);
	 digitalWrite(laser, LOW);
	 delay(t);
	 l3 = analogRead(detector);
		
	 // return the threshold value
	 int minimum = (l1+l2+l3)/3;
	 int maximum =  (h1+h2+h3)/3;
     int range =  maximum - minimum ;
    return minimum + 0.05*range;
}

// GET RANGE
int LaserMaze::GetRange(const int laser, const int detector) {
	int h1, h2, h3 = 0;
	int l1, l2, l3 = 1;
	const int t = 50;
	
	// find range by turning laser on and off 3 times	
	digitalWrite(laser, HIGH);
	delay(t);
	h1 = analogRead(detector);
	digitalWrite(laser, LOW);
	delay(t);
	l1 = analogRead(detector);
	digitalWrite(laser, HIGH);
	delay(t);
	h2 = analogRead(detector);
	digitalWrite(laser, LOW);
	delay(t);
	l2 = analogRead(detector);
	digitalWrite(laser, HIGH);
	delay(t);
	h3 = analogRead(detector);
	digitalWrite(laser, LOW);
	delay(t);
	l3 = analogRead(detector);
	
	// return the range value
	int minimum = (l1+l2+l3)/3;
	int maximum =  (h1+h2+h3)/3;
    return maximum - minimum;
}

// PRINT CALIBRATION VALUES
void LaserMaze::PrintCalibrationValues() {
    Serial.print("Gate Range: \t \t");
    Serial.print(m_portalrange);
    Serial.print("\t Gate Threshold: \t");
    Serial.println(m_portalthreshold);
    Serial.print("Detector 1 Range: \t");
    Serial.print(m_range1);
    Serial.print("\t Detector1 Threshold: \t");
    Serial.println(m_threshold1);
    Serial.print("Detector 2 Range: \t");
    Serial.print(m_range2);
    Serial.print("\t Detector2 Threshold: \t");
    Serial.println(m_threshold2);
    Serial.print("Detector 3 Range: \t");
    Serial.print(m_range3);
    Serial.print("\t Detector3 Threshold: \t");
    Serial.println(m_threshold3);
    Serial.print("Detector 4 Range: \t");
    Serial.print(m_range4);
    Serial.print("\t Detector4 Threshold: \t");
    Serial.println(m_threshold4);
    Serial.print("Detector 5 Range: \t");
    Serial.print(m_range5);
    Serial.print("\t Detector5 Threshold: \t");
    Serial.println(m_threshold5);
}

// CALIBRATE
void LaserMaze::CalibrateMaze() {
    Serial.println("Calibration in progress...   ");
    // store the threshold values of each detector
    m_portalthreshold = GetThreshold(m_portallaser, m_portaldetector);
    m_threshold1 = GetThreshold(m_laser1, m_detector1);
    m_threshold2 = GetThreshold(m_laser2, m_detector2);
    m_threshold3 = GetThreshold(m_laser3, m_detector3);
    m_threshold4 = GetThreshold(m_laser4, m_detector4);
    m_threshold5 = GetThreshold(m_laser5, m_detector5);
    // store the range values of each detector
    m_portalrange = GetRange(m_portallaser, m_portaldetector);
    m_range1 = GetRange(m_laser1, m_detector1);
    m_range2 = GetRange(m_laser2, m_detector2);
    m_range3 = GetRange(m_laser3, m_detector3);
    m_range4 = GetRange(m_laser4, m_detector4);
    m_range5 = GetRange(m_laser5, m_detector5);
    Serial.println("Calibration process completed!");

	// print the thresholds and ranges
    PrintCalibrationValues();
    iscalibrated = true;
    ResetMaze();
}


// RESETMAZE
void LaserMaze::ResetMaze() {
    // make sure prize is in place
    if(digitalRead(m_prize) == LOW) {
        Serial.println("Please put the prize back");
        delay(5000);
    }
    Serial.println("The Maze has been reset!");
	isplaying = false;
	isstealing = false;
    iswinner = false;
    isactive = false;
    CheckAlignment();
	if(isaligned && iscalibrated) {
        ActivateMaze();
    }
    else {
        Serial.println("The game cannot be reset because it is not aligned and calibrated.");
        AlignMaze();
    };
}

// START TIMER
void LaserMaze::TimerStart() {
    m_StartTime =   millis();
}

// STOP TIMER
void LaserMaze::TimerStop() {
    m_ElapsedTime =   millis() - m_StartTime;
    Serial.print( (int)(m_ElapsedTime / 1000L));     // divide by 1000 to convert to seconds - then cast to an int to print
    Serial.print(".");                             // print decimal point
    // use modulo operator to get fractional part of time
    int fractional = (int)(m_ElapsedTime % 1000L);
    if (fractional == 0)
        Serial.print("000");
    // add three zero's
    else if (fractional < 10)   // if fractional < 10 the 0 is ignored giving a wrong time, so add the zeros
        Serial.print("00");
    // add two zeros
    else if (fractional < 100)
        Serial.print("0");          // add one zero
        Serial.print(fractional);  // print fractional part of time
    Serial.println(" seconds");
}

// ACTIVATE ( !!! game mode !!! )
void LaserMaze::ActivateMaze() {
    isactive = true;
    Serial.println("Maze is active! LETS PLAY!");
    // turn all lasers ON
    digitalWrite(m_portallaser, HIGH);
    digitalWrite(m_laser1, HIGH);
    digitalWrite(m_laser2, HIGH);
    digitalWrite(m_laser3, HIGH);
    digitalWrite(m_laser4, HIGH);
    digitalWrite(m_laser5, HIGH);
    delay(3000);
    // if portal trip is detected game starts
    while(isactive) {
        if(analogRead(m_portaldetector) < m_portalthreshold) {
            // start timer
            Serial.println("START TIMER");
            TimerStart();
            isplaying = true;
            while (isplaying) {
                // sound alarm if beam is tripped
                if (DetectTrip()) {
                    Alarm();
                    ResetMaze();
                };
                // if exit is reached with the prize, declare a winner
                if (DetectSteal() && (analogRead(m_portaldetector) < m_portalthreshold)) {
                    // stop timer
                    Serial.println("STOP TIMER");
                    Serial.println("You win! Your time is: ");
                    TimerStop();
                    delay(500);
                    iswinner = true;
                    ResetMaze();
                }
            };
        };
    }


	
}

// m_DETECT TRIP
boolean LaserMaze::DetectTrip() {
  if(analogRead(m_detector1) < m_threshold1) {return true;}
  if(analogRead(m_detector2) < m_threshold2) {return true;}
  if(analogRead(m_detector3) < m_threshold3) {return true;}
  if(analogRead(m_detector4) < m_threshold4) {return true;}
  //if(analogRead(m_detector5) < m_threshold5) {return true;}
  else return false;
}

// DETECT STEAL
boolean LaserMaze::DetectSteal() {
    if(digitalRead(m_prize) == LOW) {
        Serial.println("Great! now get to the exit");
        isstealing = true;
        return true;
    }
    else return false;
}

// ALARM
void LaserMaze::Alarm() {
    digitalWrite(m_alarm, HIGH);
    Serial.println("Someone has been detected in the maze! INTRUDER ALERT!!!");
    // blink the lasers for effect
    for(int i = 0; i != 6; ++i) {
        digitalWrite(m_portallaser, HIGH);
        digitalWrite(m_laser1, HIGH);
        digitalWrite(m_laser2, HIGH);
        digitalWrite(m_laser3, HIGH);
        digitalWrite(m_laser4, HIGH);
        digitalWrite(m_laser5, HIGH);
        delay(500);
        digitalWrite(m_portallaser, LOW);
        digitalWrite(m_laser1, LOW);
        digitalWrite(m_laser2, LOW);
        digitalWrite(m_laser3, LOW);
        digitalWrite(m_laser4, LOW);
        digitalWrite(m_laser5, LOW);
        delay(500);
        if(i == 5) {Serial.println("Alarm sequence complete...");}
    };
    digitalWrite(m_alarm, LOW);
}

// UPDATE HIGHSCORES
void LaserMaze::UpdateHighscore() {
    // see which place
    if (m_ElapsedTime > 3);
}

// PRINT HIGHSCORES
void LaserMaze::PrintHighscore() {

}

void LaserMaze::CheckAlignment() {
    // if all is OK continue
    Serial.println("Checking alingment");
    if(m_portalthreshold, m_threshold1, m_threshold2, m_threshold3, m_threshold4 >= 100) {
        isaligned = true;
        iscalibrated = true;
        ActivateMaze();
    }
    // if one of the detector ranges is == 0
    else {
    Serial.println("One or more lasers are not aligned correctly, please check the alignment again!");
    isaligned = false;
    AlignMaze();
    };
}
