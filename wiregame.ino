
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define WIRE 12    //WIRE that user holds
#define RESET_B 13  //RESET Button
#define END 11      //The sensor at the end of the game


LiquidCrystal_I2C lcd(0x27,20,4);


int score = 0;
int state = 0;      //1 if the STICK touch the WIRE, use to prevent the score from increasing due to prolong contact
void setup() {
  // put your setup code here, to run once:
  pinMode(WIRE, INPUT);
  pinMode(RESET_B, INPUT_PULLUP);
  pinMode(END, INPUT);
  Serial.begin(9600);
  digitalWrite(WIRE, 0);
  digitalWrite(RESET_B, 0);
  digitalWrite(END, 0);

  lcd.init();
  lcd.backlight();
  displayScore(0);
}

void displayScore(int score){
  String s="Touched: ";
  s=s+score;
  lcd.setCursor(0,0);
  lcd.clear();
  lcd.print(s);
}

void loop() {
  // put your main code here, to run repeatedly:
  int wire = digitalRead(WIRE);
  int end_reached = digitalRead(END);
  int reset_triggered = digitalRead(13);
  Serial.println(wire);

  if(wire == HIGH && state == 0){ //If touch the wire
    score = score + 1;
    state = 1;
    displayScore(score);
  }else if (wire==HIGH && state ==1){
    tone(8, 262, 10);
  }else if (wire == LOW){
    state = 0;
  }

  if(reset_triggered){
    score = 0;
    displayScore(score);
  }

  /*
  Serial.print("Score ");
  Serial.print(score);
  Serial.print(" State: ");
  Serial.print(state);
  Serial.print(" End:");
  Serial.println(end_reached);
  */
}
