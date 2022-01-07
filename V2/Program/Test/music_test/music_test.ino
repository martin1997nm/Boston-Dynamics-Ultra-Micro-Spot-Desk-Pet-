const int PIN = 4;

hw_timer_t* timer = NULL;
bool value = true;
int frequency = 20; // 20 to 20000

void IRAM_ATTR onTimer() {
  value = !value;
  digitalWrite(PIN, value); 
}

void setup() {
    Serial.begin(115200);
    pinMode(PIN, OUTPUT);    // sets the digital pin as output
    setupTimer();
}

void setupTimer() {
    // Use 1st timer of 4  - 1 tick take 1/(80MHZ/80) = 1us so we set divider 80 and count up 
    timer = timerBegin(0, 80, true);//div 80
    timerAttachInterrupt(timer, &onTimer, true);
}

void setFrequency(long frequencyHz){
    timerAlarmDisable(timer);
    timerAlarmWrite(timer, 1000000l / frequencyHz, true);
    timerAlarmEnable(timer);
}

void tone(long frequencyHz, long durationMs){
    setFrequency(frequencyHz);
    delay(durationMs);
}

void loop() {
    Serial.print(frequency); // in hz
    Serial.println(" hz");
    tone(frequency,1000);
    frequency+=100;
    if (frequency>=200000){
      frequency = 20;
    }
}
