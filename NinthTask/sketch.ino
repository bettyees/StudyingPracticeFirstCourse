const int PHOTO_PIN   = A0;
const int LED_GREEN   = 8;
const int LED_RED     = 9;
const int THRESHOLD   = 512;
const unsigned long OPEN_TIME = 2000;  // мс

void setup() {
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  Serial.begin(9600);

  // По умолчанию дверь закрыта — горит красный
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_GREEN, LOW);
  Serial.println("Door initialized: CLOSED");
}

void loop() {
  int light = analogRead(PHOTO_PIN);
  Serial.print("Light level: ");
  Serial.println(light);

  // Если света много (человек близко) — открываем
  if (light > THRESHOLD) {
    Serial.println("Event: person detected, DOOR OPENING");
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, HIGH);

    // Ждём OPEN_TIME, каждые 100 мс проверяем — не ушёл ли человек
    unsigned long start = millis();
    while (millis() - start < OPEN_TIME) {
      delay(100);
      light = analogRead(PHOTO_PIN);
      if (light > THRESHOLD) {
        // человек всё ещё рядом — продлеваем
        start = millis();
      }
    }

    // Проверка после истечения времени
    light = analogRead(PHOTO_PIN);
    if (light > THRESHOLD) {
      Serial.println("Event: person still here, door stays OPEN");
      // остаёмся открытыми — цикл loop сам повторит проверку
    } else {
      Serial.println("Event: person left, DOOR CLOSING");
      digitalWrite(LED_GREEN, LOW);
      digitalWrite(LED_RED, HIGH);
    }
  }

  delay(200);
}
