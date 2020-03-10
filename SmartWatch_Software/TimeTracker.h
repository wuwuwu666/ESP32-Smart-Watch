boolean correctTime = false;

void printLocalTime() ;
void updateTime (uint64_t elapsedTime);
void beginTimedSleep (unsigned long tm0);

String getInternetTime() {
  //connect to WiFi
  int wifiCounter = 0;


  //i need these values to be strings so some extra code is required
  WiFi.mode(WIFI_STA);
  char ssid0[60];
  char password0[60];
  ssid.toCharArray(ssid0, ssid.length() + 1);
  password.toCharArray(password0, password.length() + 1);

#ifdef DEBUG
  Serial.println("Connecting to " + ssid);
#endif

  WiFi.begin(ssid0, password0);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
#ifdef DEBUG
    Serial.print(".");
#endif
    if (++wifiCounter > 30) {
#ifdef DEBUG
      Serial.println("COULD NOT CONNECT TO WIFI ");
#endif
      break;
    }
  }
#ifdef DEBUG
  if  (WiFi.status() == WL_CONNECTED) {
    Serial.println(" CONNECTED");
  }
#endif
  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  delay(1000);
  printLocalTime();
  unsigned long tm0 = micros();
  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
  //  bootCount++;
  //  beginTimedSleep (tm0);
  return "00:00:00AM";
}

void printLocalTime() {
  time(&now);
  timeinfo = localtime (&now);
#ifdef DEBUG
  Serial.printf ("%s\n", asctime(timeinfo));
#endif
  delay(2); // 26 bytes @ 115200 baud is less than 2 ms
}

void updateTime (uint64_t elapsedTime) { // elapsedTime in us
  if (elapsedTime == 0) Mics += micros();
  else Mics += elapsedTime;
  if (Mics > 1000000) {
    Mics = Mics % 1000000;
    now += Mics / 1000000;
  }
}

void beginTimedSleep (unsigned long tm0) {
  updateTime (SleepTime - (micros() - tm0));
  esp_sleep_enable_timer_wakeup(SleepTime - (micros() - tm0));
  esp_deep_sleep_start();
}


void drawDate(int x, int y, int textSize) {

}

void drawDateCentered(int y, int textSize) {

}

void drawTime(int x, int y, int textSize)
{
  time(&now);
  timeinfo = localtime (&now);
  String t = asctime(timeinfo);
 
}
