const int pinR = 9;
const int pinG = 10;
const int pinB = 11;

const int sensorSolo = A0;

const int buzzer = 6;      
const int releBomba = 7;   

bool modoSimulacao = false; // AGORA O SENSOR SERÁ USADO

int lerUmidadeReal() {
  long soma = 0;

  // Lê 10 vezes para evitar erro
  for (int i = 0; i < 10; i++) {
    soma += analogRead(sensorSolo);
    delay(5);
  }

  return soma / 10; // média
}

// SENSOR SIMULA CASO A SIMULAÇÃO ESTEJA ON
int lerUmidade() {
  if (modoSimulacao) return random(0, 1024);
  else return lerUmidadeReal();
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
    // SOLO SECO
    setColor(255, 0, 0);
    tone(buzzer, 1000);
    digitalWrite(releBomba, HIGH);
    Serial.println("Solo seco! Buzzer e Irrigação ON");
    delay(1000);
    setColor(0, 0, 0);
    delay(1000);
  }
  else if (umidade < 700) {
    // SOLO OK
    setColor(0, 255, 0);
    noTone(buzzer);
    digitalWrite(releBomba, LOW);
    Serial.println("Solo OK! Sistema OFF");
    delay(1000);
    setColor(0, 0, 0);
    delay(1000);
  }
  else {
    // SOLO MUITO ÚMIDO
    setColor(255, 255, 0);
    noTone(buzzer);
    digitalWrite(releBomba, LOW);
    Serial.println("Solo úmido demais! Sistema OFF");
    delay(1000);
    setColor(0, 0, 0);
    delay(1000);
  }
}
