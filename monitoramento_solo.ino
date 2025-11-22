const int pinR = 9;
const int pinG = 10;
const int pinB = 11;

const int sensorSolo = A0;

const int buzzer = 6; // <<--- BUZZER ADICIONADO

bool modoSimulacao = true; 

void setColor(int R, int G, int B) {
  analogWrite(pinR, R); 
  analogWrite(pinG, G);
  analogWrite(pinB, B);
}

void setup() {
  Serial.begin(9600);

  pinMode(pinR, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(sensorSolo, INPUT); 
  
  pinMode(buzzer, OUTPUT); // <<--- CONFIGURA O BUZZER

  randomSeed(analogRead(A5)); 
}

int lerUmidade() {
  if (modoSimulacao) {
    return random(0, 1024);
  } 
  else {
    return analogRead(sensorSolo);
  }
}

void loop() {
  int umidade = lerUmidade();

  Serial.print("Umidade lida: ");
  Serial.println(umidade);

  if (umidade < 300) {
    // SOLO SECO
    setColor(255, 0, 0); 
    tone(buzzer, 1000); // <<--- LIGA O BUZZER
    Serial.println("BUZZER ATIVO 🔔");
    delay(500);

    setColor(0, 0, 0); 
    delay(500); 
  }
  else if (umidade >= 300 && umidade < 700) {
    // UMIDADE MEDIA
    setColor(255, 255, 0);
    noTone(buzzer); // <<--- DESLIGA O BUZZER
    Serial.println("BUZZER DESLIGADO 🚫");
    delay(500);

    setColor(0, 0, 0);
    delay(500); 
  }
  else {
    // SOLO ÚMIDO
    setColor(0, 255, 0);
    noTone(buzzer); // <<--- DESLIGA O BUZZER
    Serial.println("BUZZER DESLIGADO 🚫");
    delay(500);

    setColor(0, 0, 0); 
    delay(500); 
  }
}
