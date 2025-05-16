int PinoSensor1 = 2;  // PINO DIGITAL UTILIZADO PELO SENSOR
int PinoSensor2 = 3;  // PINO DIGITAL UTILIZADO PELO SENSOR
int PinoSensor3 = 4;  // PINO DIGITAL UTILIZADO PELO SENSOR
int PinoSensor4 = 7;  // PINO DIGITAL UTILIZADO PELO SENSOR
int PinoSensor5 = 8;  // PINO DIGITAL UTILIZADO PELO SENSOR

int Motor1F = 6;   // Motor 1 para frente
int Motor1T = 5;   // Motor 1 para trás
int Motor2F = 10;  // Motor 2 para frente
int Motor2T = 9;   // Motor 2 para trás

// Velocidades definidas
int velocidadeFrente = 100;
int curvaSuave = 70;
int curvaModerada = 60;
int curvaRapida = 90;

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

  Serial.print("S1: ");
  Serial.print(Sensor1);
  Serial.print(" S2: ");
  Serial.print(Sensor2);
  Serial.print(" S3: ");
  Serial.print(Sensor3);
  Serial.print(" S4: ");
  Serial.print(Sensor4);
  Serial.print(" S5: ");
  Serial.println(Sensor5);

  // **PARAR NO PRETO**
  if (Sensor1 == LOW && Sensor2 == LOW && Sensor3 == LOW && Sensor4 == LOW && Sensor5 == LOW) {
    stopMotors();
    return;
  }

  // **LINHA RETA**
  if (Sensor3 == HIGH) {
    moveForward(velocidadeFrente);
  }

  // **CURVAS**
  else if (Sensor1 == LOW && Sensor2 == LOW) {
    turnRight(curvaRapida);  // Curva rápida à direita
  } 
  else if (Sensor4 == LOW && Sensor5 == LOW) {
    turnLeft(curvaRapida);   // Curva rápida à esquerda
  } 
  else if (Sensor1 == LOW && Sensor2 == HIGH) {
    turnRight(curvaSuave);   // Curva suave à direita
  } 
  else if (Sensor4 == HIGH && Sensor5 == LOW) {
    turnLeft(curvaSuave);    // Curva suave à esquerda
  } 
  else if (Sensor2 == LOW && Sensor3 == LOW) {
    turnRight(curvaModerada); // Curva moderada à direita
  } 
  else if (Sensor4 == LOW && Sensor3 == LOW) {
    turnLeft(curvaModerada);  // Curva moderada à esquerda
  } 
  else if (Sensor1 == LOW && Sensor5 == HIGH) {
    turnRight(curvaRapida);   // Curva rápida à direita
  } 
  else if (Sensor1 == HIGH && Sensor5 == LOW) {
    turnLeft(curvaRapida);    // Curva rápida à esquerda
  }

  else {
    stopMotors(); // Linha perdida
  }
}

// FUNÇÕES DE CONTROLE DOS MOTORES

void moveForward(int speed) {
  analogWrite(Motor1F, speed);
  analogWrite(Motor1T, 0);
  analogWrite(Motor2F, speed);
  analogWrite(Motor2T, 0);
}

void turnRight(int speed) {
  analogWrite(Motor1F, speed - 10);  // reduzido levemente para suavizar a curva
  analogWrite(Motor1T, 0);
  analogWrite(Motor2F, 0);
  analogWrite(Motor2T, speed);
}

void turnLeft(int speed) {
  analogWrite(Motor1F, 0);
  analogWrite(Motor1T, speed);
  analogWrite(Motor2F, speed - 10);  // reduzido levemente para suavizar a curva
  analogWrite(Motor2T, 0);
}

void stopMotors() {
  analogWrite(Motor1F, 0);
  analogWrite(Motor1T, 0);
  analogWrite(Motor2F, 0);
  analogWrite(Motor2T, 0);
}
