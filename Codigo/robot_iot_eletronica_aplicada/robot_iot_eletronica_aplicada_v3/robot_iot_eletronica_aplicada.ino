// Seguidor de linha com curvas agressivas e recuperação inteligente da linha

int PinoSensor1 = 2;
int PinoSensor2 = 3;
int PinoSensor3 = 4;
int PinoSensor4 = 7;
int PinoSensor5 = 8;

int Motor1F = 6;
int Motor1T = 5;
int Motor2F = 10;
int Motor2T = 9;

String ultimaDirecao = "frente"; // "esquerda", "direita", "frente"

void setup() {
  Serial.begin(9600);

  pinMode(PinoSensor1, INPUT);
  pinMode(PinoSensor2, INPUT);
  pinMode(PinoSensor3, INPUT);
  pinMode(PinoSensor4, INPUT);
  pinMode(PinoSensor5, INPUT);

  pinMode(Motor1F, OUTPUT);
  pinMode(Motor1T, OUTPUT);
  pinMode(Motor2F, OUTPUT);
  pinMode(Motor2T, OUTPUT);
}

void loop() {
  int Sensor1 = digitalRead(PinoSensor1);
  int Sensor2 = digitalRead(PinoSensor2);
  int Sensor3 = digitalRead(PinoSensor3);
  int Sensor4 = digitalRead(PinoSensor4);
  int Sensor5 = digitalRead(PinoSensor5);

  Serial.print("S1: "); Serial.print(Sensor1);
  Serial.print(" S2: "); Serial.print(Sensor2);
  Serial.print(" S3: "); Serial.print(Sensor3);
  Serial.print(" S4: "); Serial.print(Sensor4);
  Serial.print(" S5: "); Serial.println(Sensor5);

  // Se todos os sensores estiverem no preto, buscar linha
  if (Sensor1 == LOW && Sensor2 == LOW && Sensor3 == LOW && Sensor4 == LOW && Sensor5 == LOW) {
    buscarLinha();
    return;
  }

  // Movimento normal baseado na leitura dos sensores
  if (Sensor3 == HIGH) {
    moveForward(100);
    ultimaDirecao = "frente";
  } else if (Sensor1 == LOW && Sensor2 == LOW) {
    spinRight(100);
    ultimaDirecao = "direita";
  } else if (Sensor4 == LOW && Sensor5 == LOW) {
    spinLeft(100);
    ultimaDirecao = "esquerda";
  } else if (Sensor1 == LOW && Sensor2 == HIGH) {
    turnRight(80);
    ultimaDirecao = "direita";
  } else if (Sensor4 == HIGH && Sensor5 == LOW) {
    turnLeft(80);
    ultimaDirecao = "esquerda";
  } else if (Sensor2 == LOW && Sensor3 == LOW) {
    turnRight(80);
    ultimaDirecao = "direita";
  } else if (Sensor3 == LOW && Sensor4 == LOW) {
    turnLeft(80);
    ultimaDirecao = "esquerda";
  } else if (Sensor1 == LOW && Sensor5 == HIGH) {
    spinRight(100);
    ultimaDirecao = "direita";
  } else if (Sensor1 == HIGH && Sensor5 == LOW) {
    spinLeft(100);
    ultimaDirecao = "esquerda";
  } else {
    stopMotors();
  }
}

void moveForward(int velocidade) {
  analogWrite(Motor1F, velocidade);
  analogWrite(Motor1T, 0);
  analogWrite(Motor2F, velocidade);
  analogWrite(Motor2T, 0);
}

void turnRight(int velocidade) {
  analogWrite(Motor1F, velocidade);
  analogWrite(Motor1T, 0);
  analogWrite(Motor2F, velocidade / 2);
  analogWrite(Motor2T, 0);
}

void turnLeft(int velocidade) {
  analogWrite(Motor1F, velocidade / 2);
  analogWrite(Motor1T, 0);
  analogWrite(Motor2F, velocidade);
  analogWrite(Motor2T, 0);
}

void spinRight(int velocidade) {
  analogWrite(Motor1F, velocidade);
  analogWrite(Motor1T, 0);
  analogWrite(Motor2F, 0);
  analogWrite(Motor2T, velocidade);
}

void spinLeft(int velocidade) {
  analogWrite(Motor1F, 0);
  analogWrite(Motor1T, velocidade);
  analogWrite(Motor2F, velocidade);
  analogWrite(Motor2T, 0);
}

void stopMotors() {
  analogWrite(Motor1F, 0);
  analogWrite(Motor1T, 0);
  analogWrite(Motor2F, 0);
  analogWrite(Motor2T, 0);
}

void buscarLinha() {
  if (ultimaDirecao == "direita") {
    spinLeft(90);
  } else if (ultimaDirecao == "esquerda") {
    spinRight(90);
  } else {
    spinLeft(80); // tenta uma direção padrão
  }
}
