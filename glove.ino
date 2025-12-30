#include <Wire.h>  
#include <LiquidCrystal_I2C.h>  
#include <Adafruit_MPU6050.h>  
#include <Adafruit_Sensor.h>  

#define BUZZER_PIN 9
#define BUTTON_PIN 2  // Tambah button buat trigger
const int flexPins[5] = {A0, A1, A2, A3, A4};
LiquidCrystal_I2C lcd(0x27, 16, 2);

String kataNames[2] = {"Halo", "Dadah"};
int kataReference[2][5] = {
  {398, 375, 405, 386, 417},  // Halo: Jari lurus, wave cepat
  {620, 600, 630, 650, 610}   // Dadah: Jari tekuk sedikit, wave lambat
  // bisa ditambahkan disini buat kata" yang dibutuhkan / bisa connect ke dataset yang didapatkan nnti
};
int kataCount = 2;

// Base class Sensor (abstrak, inheritance)
class Sensor {
protected:
  int pin;
public:
  Sensor(int p) : pin(p) {}
  virtual int readData() = 0;  // Polymorphism
};

// FlexSensor inherit dari Sensor
class FlexSensor : public Sensor {
public:
  FlexSensor(int p) : Sensor(p) {}
  int readData() override {
    int raw = analogRead(pin);
    return raw;  // Bisa tambah filter: average 3 reads
  }
};

// IMUSensor buat detect wave (dinamis)
class IMUSensor {
private:
  Adafruit_MPU6050 mpu;
  float prevZ = 0.0;
public:
  void init() {
    if (!mpu.begin()) { while(1) delay(10); }  // Error handle
    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  }
  float readAccelZ() {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    return a.acceleration.z;
  }
  bool isWaving() {  // Detect goyang: Perubahan accel > threshold
    float currentZ = readAccelZ();
    float delta = abs(currentZ - prevZ);
    prevZ = currentZ;
    return delta > 2.0;  // Sesuaikan threshold dari test
  }
};

// GestureRecognizer (encapsulate matching)
class GestureRecognizer {
private:
  FlexSensor* flexes[5];
  IMUSensor* imu;
public:
  GestureRecognizer(FlexSensor* f[], IMUSensor* i) {
    for (int j = 0; j < 5; j++) flexes[j] = f[j];
    imu = i;
  }
  String recognize() {
    int vals[5];
    for (int i = 0; i < 5; i++) vals[i] = flexes[i]->readData();
    bool waving = imu->isWaving();

    int bestIdx = -1;
    int minDist = 99999;
    for (int i = 0; i < kataCount; i++) {
      int dist = 0;
      for (int j = 0; j < 5; j++) dist += abs(vals[j] - kataReference[i][j]);
      if (dist < minDist) { minDist = dist; bestIdx = i; }
    }

    if (bestIdx != -1 && minDist < 50 && waving) {  // Tambah check waving
      return kataNames[bestIdx];
    }
    return "Tidak dikenal";
  }
};

// Output class
class Output {
public:
  void init() {
    lcd.init(); lcd.backlight();
    pinMode(BUZZER_PIN, OUTPUT);
  }
  void display(String text) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(text);
    tone(BUZZER_PIN, 1000, 50);  // Beep
  }
};

// Global objects
FlexSensor* flexSensors[5];
IMUSensor imu;
GestureRecognizer recognizer(flexSensors, &imu);
Output output;

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  for (int i = 0; i < 5; i++) flexSensors[i] = new FlexSensor(flexPins[i]);

  imu.init();
  output.init();

  lcd.setCursor(0, 0); lcd.print("Tes Glove BISINDO");
  Serial.println("Ready. Tekan button buat deteksi.");
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) {  // Trigger button
    String gesture = recognizer.recognize();
    output.display(gesture);
    Serial.println("Detected: " + gesture);
    delay(1000);  // Debounce
  }
  delay(100);
}