#include <Arduino.h>

const int ledPins[] = {2, 3, 4, 5, 6, 7};          // Пин, к которому подключены светодиоды
const int numLeds = sizeof(ledPins) / sizeof(int); // Количество светодиодов
const int buzzerPin = 9;                           // Пин, к которому подключен звуковой модуль

unsigned long previousMillisLED = 0; // хранения времени последнего включения светодиода.
const long intervalLED = 40;         // интервал времени между включениями светодиода в мсек

unsigned long previousMillisSiren = 0; // хранения времени последнего включения сирены.
const long intervalSiren = 5;          // интервал времени между включениями сирены в мсек

void setup()
{
  for (int i = 0; i < numLeds; i++)
  {
    pinMode(ledPins[i], OUTPUT); // Устанавливаем все светодиоды как выходные
  }
  pinMode(buzzerPin, OUTPUT); // Устанавливаем звуковой модуль как выходной
}

void siren()
{
  unsigned long currentMillis = millis(); // Получаем текущее время в миллисекундах с момента начала работы программы
  if (currentMillis - previousMillisSiren >= intervalSiren)
  {                                      // Если прошло достаточно времени с последнего включения сирены
    previousMillisSiren = currentMillis; // Обновляем время последнего включения сирены

    static int freq = 16;  // Инициализируем переменную freq значением 16
    tone(buzzerPin, freq); // Генерируем звук на текущей частоте на пине буззера

    // Увеличиваем частоту на разное количество, в зависимости от текущего диапазона
    if (freq <= 500)
    {
      freq += 5; // Увеличиваем медленно для низких частот
    }
    else if (freq <= 1500)
    {
      freq += 10; // Увеличиваем средней скорость для средних частот
    }
    else
    {
      freq += 50; // Увеличиваем быстро для высоких частот
    }

    if (freq > 5000)
    {            // Если частота стала больше 5000
      freq = 16; // Сбрасываем ее обратно на 16
    }
  }
}

void ledsvet()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillisLED >= intervalLED)
  {
    previousMillisLED = currentMillis;

    static int ledIndex = 0;
    digitalWrite(ledPins[ledIndex], HIGH); // Включаем светодиод
    delay(10);                             // Ждем 10 мс
    digitalWrite(ledPins[ledIndex], LOW);  // Выключаем светодиод
    delay(10);                             // Ждем 10 мс

    ledIndex++;
    if (ledIndex >= numLeds)
    {
      ledIndex = 0;
    }
  }
}

void loop()
{
  siren();
  ledsvet();
}