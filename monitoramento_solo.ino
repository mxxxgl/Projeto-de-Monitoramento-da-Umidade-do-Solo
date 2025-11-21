const int pinR = 9;
const int pinG = 10;
const int pinB = 11;

const int sensorSolo = A0;

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
    
    setColor(255, 0, 0); 
    delay(500); 

    setColor(0, 0, 0); 
    delay(500); 
  }
  else if (umidade >= 300 && umidade < 700) {
    
    setColor(255, 255, 0); 
    delay(500); 

    setColor(0, 0, 0); 
    delay(500); 
  }
  else {
    
    setColor(0, 255, 0); 
    delay(500); 

    setColor(0, 0, 0); 
    delay(500); 
  }
}
