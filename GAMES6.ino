#define redLed 6
#define redBtn 4
#define yellowLed 9
bool IsLedOn;
int cnt = 0;
int last, curr, cntLedOn,val;
unsigned long randomNum, currTime;
unsigned long lastTime;
unsigned long LastPressTime;

void LedOn() {
  digitalWrite(redLed, HIGH);
  IsLedOn = true;
  cntLedOn++;
}
void LedOff() {
  digitalWrite(redLed, LOW);
  IsLedOn = false;
}
bool IsBtnPressStarted() {

  if ((curr == LOW) && (last == HIGH) && (millis() - LastPressTime > 150)) {
    IsLedOn? cnt++:cnt--;
    cnt= max(0,cnt);
    cnt= min(5,cnt);
    Serial.println(cnt);
    LastPressTime = millis();
    return true;
  }
  return false;
}

void setup() {
  Serial.begin(9600);
  pinMode(redLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(redBtn, INPUT_PULLUP);
  randomSeed(analogRead(A1));
  randomNum = random(1000, 3001);
  val= map(analogRead(A0),0,1023,7,12);

}

void loop() {
  currTime = millis();
  curr = digitalRead(redBtn);
  if (currTime - lastTime >= randomNum && cntLedOn< val) {
    lastTime = currTime;
    IsLedOn? LedOff():LedOn();
    randomNum = random(1000, 3000);
  }
  if(cntLedOn == val){
    Serial.println("game over");
    Serial.print("score:");
    Serial.print(cnt);
    Serial.print("/5");
    cntLedOn++;
    LedOff();
  }
  IsBtnPressStarted();
  last = curr;
  
  int ledValy= map(cnt,0,5,0,255);
  analogWrite(yellowLed, ledValy);

}