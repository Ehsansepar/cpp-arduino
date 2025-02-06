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
}
