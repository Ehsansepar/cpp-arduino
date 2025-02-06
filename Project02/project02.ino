const int ledRouge = 2;  // LED rouge
const int ledOrange = 3; // LED orange
const int ledVert = 4;   // LED vert
const int boutonSOS = 5; // Bouton SOS

bool sosActif = false;
unsigned long dernierClignotement = 0;
bool etatClignotement = false;
unsigned long debutAppui = 0;
int dernierEtat = 0;

void setup()
{
    pinMode(ledRouge, OUTPUT);
    pinMode(ledOrange, OUTPUT);
    pinMode(ledVert, OUTPUT);
    pinMode(boutonSOS, INPUT_PULLUP);
    Serial.begin(9600);

    digitalWrite(ledRouge, LOW);
    digitalWrite(ledOrange, LOW);
    digitalWrite(ledVert, LOW);
}

void loop()
{
    // Lecture du bouton
    bool boutonAppuye = (digitalRead(boutonSOS) == LOW);

    // Premier appui sur le bouton - active le SOS
    if (boutonAppuye && !sosActif && debutAppui == 0)
    {
        sosActif = true;
        debutAppui = millis();
        // Sauvegarder l'état
        if (digitalRead(ledRouge) == HIGH)
            dernierEtat = 0;
        if (digitalRead(ledOrange) == HIGH)
            dernierEtat = 1;
        if (digitalRead(ledVert) == HIGH)
            dernierEtat = 2;
    }

    // Si le bouton est maintenu appuyé et que le mode SOS est actif
    if (boutonAppuye && sosActif)
    {
        if ((millis() - debutAppui) >= 5000)
        {
            // Désactiver le mode SOS
            sosActif = false;

            // Restaurer l'état précédent - version simple
            digitalWrite(ledRouge, LOW);
            digitalWrite(ledOrange, LOW);
            digitalWrite(ledVert, LOW);

            if (dernierEtat == 0)
            {
                digitalWrite(ledRouge, HIGH);
            }
            if (dernierEtat == 1)
            {
                digitalWrite(ledOrange, HIGH);
            }
            if (dernierEtat == 2)
            {
                digitalWrite(ledVert, HIGH);
            }
        }
    }

    // Si le bouton est relâché, réinitialiser le compteur
    if (!boutonAppuye)
    {
        debutAppui = 0;
    }

    // Gestion des messages série
    if (Serial.available() > 0)
    {
        String message = Serial.readStringUntil('\n');
        message.trim();
        Serial.println("Message recu : " + message);

        if (!sosActif)
        {
            if (message == "meduse" || message == "tempete" || message == "requin")
            {
                digitalWrite(ledRouge, HIGH);
                digitalWrite(ledOrange, LOW);
                digitalWrite(ledVert, LOW);
                dernierEtat = 0;
            }
            else if (message == "vague")
            {
                digitalWrite(ledRouge, LOW);
                digitalWrite(ledOrange, HIGH);
                digitalWrite(ledVert, LOW);
                dernierEtat = 1;
            }
            else if (message == "surveillant" || message == "calme")
            {
                digitalWrite(ledRouge, LOW);
                digitalWrite(ledOrange, LOW);
                digitalWrite(ledVert, HIGH);
                dernierEtat = 2;
            }
        }
    }

    // Gestion du clignotement en mode SOS
    if (sosActif)
    {
        if (millis() - dernierClignotement >= 500)
        {
            etatClignotement = !etatClignotement;
            digitalWrite(ledRouge, etatClignotement);
            digitalWrite(ledOrange, LOW);
            digitalWrite(ledVert, LOW);
            dernierClignotement = millis();
        }
    }
}