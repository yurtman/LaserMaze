const int laser1 = 12;        
const int laser2 = 11;       
const int laser3 = 10;       
const int laser4 = 9;       
const int laser5 = 8;       
const int gate_laser = 7; 

void setup (){
  pinMode(laser1, OUTPUT);
  pinMode(laser2, OUTPUT);
  pinMode(laser3, OUTPUT);
  pinMode(laser4, OUTPUT);
  pinMode(laser5, OUTPUT);
  pinMode(gate_laser, OUTPUT);
}
void loop(){
  
  digitalWrite(laser1, HIGH);
  digitalWrite(laser2, HIGH);
  digitalWrite(laser3, HIGH);
  digitalWrite(laser4, HIGH);
  digitalWrite(laser5, HIGH);
  digitalWrite(gate_laser, HIGH);
  delay(1000);
        
  
}
