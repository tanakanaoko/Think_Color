import processing.serial.*;
import java.awt.*;
import java.awt.event.*;

int linefeed = 10;
Serial myPort;
int inByte0, inByte1, inByte2;
int recv_data; 
int low_g, high_g;
String readString;

int r, g, b;
int white_red;
int white_blue;
int white_green;
int black_red;
int black_blue;
int black_green;
int cr, cg, cb;

void keyPressed() {
  if (key == 'w') {
    white_red = r;
    white_green = g;
    white_blue = b;
  } else if (key == 'b') {
    black_red = r;
    black_green = g;
    black_blue = b;
  }
}

void setup() {

  size(500, 500);
  myPort = new Serial(this, "/dev/cu.wchusbserial14320", 9600);
  myPort.bufferUntil(linefeed);
  delay(3000);
}

int i = 0;
void serialEvent(Serial p) {
  //print("serialEvent is called:");
  //println(i);
  i++;
  readString  = p.readString();
  //println(i + ":" + readString);
  //if(myPort.available() > 2){
  //}
}

float Kr = 1.0; 
float Kg = 1.0;
float Kb = 1.0;
int calib_r() {
  return (int)( Kr * map(r, white_red, black_red, 255, 0) );
}

int calib_g() {
  return (int)(Kg * map(g, white_green, black_green, 255, 0));
}

int calib_b() {
  return (int)(Kb *map(b, white_blue, black_blue, 255, 0));
}

void draw() {
  int indx = readString.indexOf(',');
  String rstr = readString.substring(0, indx);
  String remainder = readString.substring(indx+1);
  print("R:" + rstr);
  r = Integer.parseInt(rstr);

  indx = remainder.indexOf(',');
  String gstr = remainder.substring(0, indx);
  remainder = remainder.substring(indx+1);
  print("G:" + gstr);
  g = Integer.parseInt(gstr);

  String bstr = remainder.trim();
  println("B:" + bstr);
  b = Integer.parseInt(bstr);

  cr = calib_r();
  cg = calib_g();
  cb = calib_b();
  background(255);
  noStroke();
  fill(cr, cg, cb);
  rect(100, 100, 300, 300);

  if (cr>215 && cg>180) { 
    textSize(30);
    fill(0);
    text("SPRING", 50, 50);
  } else if (cr>215 && cg<180) {
    textSize(30);
    fill(0);
    text("SUMMER", 50, 50);
  } else if (cr<215 && cg>180) {
    textSize(30);
    fill(0);
    text("AUTUMN", 50, 50);
  } else {
    textSize(30);
    fill(0);
    text("WINTER", 50, 50);
  }
}