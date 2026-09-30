#include <Servo.h>

Servo myServo;
const int SERVO_PIN = 9;

int currentAngle = 90;   // текущее положение (старт — по центру)
const int STEP_DELAY = 15; // мс между шагами — скорость плавности

void setup() {
  Serial.begin(9600);
  myServo.attach(SERVO_PIN);
  myServo.write(currentAngle);

  Serial.println("=== Servo control ===");
  Serial.println("Enter angle (0-180):");
  Serial.print("Current angle: ");
  Serial.println(currentAngle);
}

void loop() {
  // Ждём ввод в Serial
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();   // убираем пробелы и \r

    // Пустой ввод — игнорируем
    if (input.length() == 0) return;

    // Проверка: только цифры (число)
    bool isNumber = true;
    for (int i = 0; i < input.length(); i++) {
      if (!isDigit(input[i])) {
        isNumber = false;
        break;
      }
    }

    if (!isNumber) {
      Serial.print("Error: '");
      Serial.print(input);
      Serial.println("' is not a number. Enter 0-180.");
      return;
    }

    int angle = input.toInt();

    // Проверка диапазона
    if (angle < 0 || angle > 180) {
      Serial.print("Error: angle ");
      Serial.print(angle);
      Serial.println(" out of range (0-180).");
      return;
    }

    // Если угол совпадает с текущим — ничего не делаем
    if (angle == currentAngle) {
      Serial.print("Angle already ");
      Serial.println(currentAngle);
      return;
    }

    // Плавный поворот
    Serial.print("Moving to ");
    Serial.print(angle);
    Serial.println(" degrees...");

    if (angle > currentAngle) {
      for (int a = currentAngle; a <= angle; a++) {
        myServo.write(a);
        delay(STEP_DELAY);
      }
    } else {
      for (int a = currentAngle; a >= angle; a--) {
        myServo.write(a);
        delay(STEP_DELAY);
      }
    }

    currentAngle = angle;
    Serial.print("Done. Current angle: ");
    Serial.println(currentAngle);
    Serial.println("Enter new angle (0-180):");
  }
}
