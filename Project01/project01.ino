int bouton = 3;
int led = 2;
int mode = 0;
bool boutonActif = true;
unsigned long timer = 0;


void setup() {
  pinMode(bouton, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
// Gerer uniquement le bouton et changer de mode

  if(digitalRead(bouton) == 0 && boutonActif) {
    boutonActif = false;
    mode = (mode + 1)%3;
    Serial.println(mode);
  }
  
// 2- allumé
  if(digitalRead (bouton) == 1 && !boutonActif) {
    boutonActif = true;
    delay(100);
  }
  if(mode == 0) digitalWrite(led, LOW); 
  else if(mode == 1) {

    if(millis() - timer >= 1000 ) {
      int statutLed = digitalRead(led);
      int newStatutLed = !statutLed;
      digitalWrite(led, newStatutLed);
      timer = millis();
    }
  }
  else digitalWrite(led, HIGH); 
}
