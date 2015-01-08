import processing.serial.*;
// still need to import
import processing.sound.*
// define myPort of type Serial
Serial myPort; 
color yellow = color(255, 255, 0);
color red    = color(255, 0, 0);
color green  = color(0, 255, 0);
color black  = color(0);
color white  = color(255);

// state box
void box(String text, color colour, int i) {
  int w = 100;
  int h = 50;
  fill(colour);
  rect(x, y, w, h, 20)
  text(text, )
}

// function for game state (aligned, calibrated, active, playing, stealing)
void state() {
  // aligned
  if(isaligned == false) {
    // draw yellow
    stroke(black);
    fill(yellow);
    rect(;  
  }
  else if(calibrating) {
    dd;
  };
}
// function to draw alignment complete button press
// function to draw reset maze button press 
// function to draw alarm sequence

// reset maze button
// moving ghost based on highscore
// display calibration values


// TEXT
text(text, x, y); // bottom left
rect(x, y, w, h, rounding); // top left


void setup() {
  // create canvas
  size(1350, 256);
  // backgrond of colour white
  background(0);
  // 
  noStroke();
  
  fill(255, 0 , 0);
  println(Serial.list());
  myPort = new Serial(this, Serial.list()[0], 9600);
}

    int oy = 0;
    int x = 0;
void draw() {
  while (myPort.available() >0) {
    int ny = myPort.read();
    println(ny);
    
    line(x, oy, x+5, ny);
    oy = ny;
    x=x+5;
    
    if(x == width){
     x = 0;
     background(255); 
    }
  }
 
}
