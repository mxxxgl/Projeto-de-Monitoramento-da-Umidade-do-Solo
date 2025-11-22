const int pinR = 9;
const int pinG = 10;
const int pinB = 11;

const int sensorSolo = A0;

const int buzzer = 6;      
const int releBomba = 7;   

bool modoSimulacao = true; // true para simular, false para usar sensor real

int lerUmidadeReal() {
  long soma = 0;
  for (int i = 0; i < 10; i++) {
    soma += analogRead(sensorSolo);
    delay(5);
  }
  return soma / 10;
}

int lerUmidade() {
  if (modoSimulacao) {
    int faixa = random(0, 3); // 0 = seco, 1 = ok, 2 = muito úmido
    switch (faixa) {
      case 0: return random(0, 300);      // solo seco
      case 1: return random(300, 700);    // solo ok
      case 2: return random(700, 1024);   // solo muito úmido
    }
  } 
  return lerUmidadeReal();
}

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

  pinMode(buzzer, OUTPUT);
  pinMode(releBomba, OUTPUT);

  noTone(buzzer);
  digitalWrite(releBomba, LOW);
}

void loop() {
  int umidade = lerUmidade();

  Serial.print("Umidade (média): ");
  Serial.println(umidade);

  if (umidade < 300) {
    setColor(255, 0, 0);
    tone(buzzer, 1000);
    digitalWrite(releBomba, HIGH);
    Serial.println("Solo seco! Buzzer e Irrigação ON");
  } 
  else if (umidade < 700) {
    setColor(0, 255, 0);
    noTone(buzzer);
    digitalWrite(releBomba, LOW);
    Serial.println("Solo OK! Sistema OFF");
  } 
  else {
    setColor(255, 255, 0);
    noTone(buzzer);
    digitalWrite(releBomba, LOW);
    Serial.println("Solo úmido demais! Sistema OFF");
  }

  delay(1000);
  setColor(0, 0, 0);
  delay(1000);
}
