#include "LaserMaze.h"

// laser pins                // detector pins
const int laser1 = 12;       const int detector1 = A1;  
const int laser2 = 11;       const int detector2 = A2;
const int laser3 = 10;       const int detector3 = A3;
const int laser4 = 9;        const int detector4 = A4;
const int laser5 = 8;        const int detector5 = A5; 

const int gate_laser = 8;    const int gate_detector = A0;

// other pins
const int alarm = 13;
const int prize = 7;

// Constructor

LaserMaze maze = LaserMaze(alarm, laser1, laser2, laser3, laser4, laser5, gate_laser, prize, gate_detector, detector1, detector2, detector3, detector4, detector5);

void setup() {
  Serial.begin(9600);
}

void loop() {
  maze.Start();    
}
