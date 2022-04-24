//#define Serial1 Serial1USB
int state = -1;
float timeNow;
float oldTime; 
float stateTime;
float timeSec;

void setup() {
  // put your setup code here, to run once:
  Serial1.begin(115200);
}

void loop() {
  timeNow = millis();
  if(timeNow - oldTime >= 66.67){
    oldTime = timeNow;
    timeSec = timeNow / 1000;
    Serial1.print("ROTATLM"); // prefix
    Serial1.print(random(-1000, 1000) * 0.01, 2);                 Serial1.print(",");
    Serial1.print(random(-1000, 1000) * 0.01, 2);                 Serial1.print(",");
    Serial1.print(random(-1000, 1000) * 0.01, 2);                 Serial1.print(",");
    Serial1.print(random(970, 990) * 0.01, 2);               Serial1.print(",");
    Serial1.print(random(-1000, 1000) * 0.001, 2);               Serial1.print(",");
    Serial1.print(random(-1000, 1000) * 0.001, 2);               Serial1.print(",");
    Serial1.print(random(-1000, 1000) * 0.001, 2);                Serial1.print(",");
    Serial1.print(random(-1000, 1000) * 0.001, 2);                Serial1.print(",");
    Serial1.print(random(-1000, 1000) * 0.001, 2);                Serial1.print(",");
    Serial1.print(random(-1000, 1000) * 0.001, 2);              Serial1.print(",");
    Serial1.print(random(-1000, 1000) * 0.001, 2);             Serial1.print(",");
    Serial1.print(random(-2550, 2550) * 0.1, 2);               Serial1.print(",");
    Serial1.print(random(8300, 8600) * 0.001, 2);        Serial1.print(",");
    Serial1.print(state);              Serial1.print(",");
    Serial1.print(1);              Serial1.print(",");
    Serial1.print(1);       Serial1.print(",");
    Serial1.print(timeSec, 3);             Serial1.print(",");
    Serial1.print(timeSec, 3);         Serial1.print(",");
    Serial1.print(random(101200, 101400) * 0.01, 3);              Serial1.print(",");
    Serial1.print(random(240, 260) * 0.01, 2);               Serial1.print(",");
    Serial1.print(random(340, 360) * 0.01, 2);              Serial1.print(",");
    Serial1.print(random(13, 14));                  Serial1.print(",");
    Serial1.print(random(496956,496996)*0.0001 , 4);              Serial1.print(",");
    Serial1.println(random(1128451,1128751)*0.0001, 4);
  }

  if(timeNow - stateTime >= 1000){
    stateTime = timeNow;
    state++;
    if(state == 10){
      state = 0;
    }   
  }

}
