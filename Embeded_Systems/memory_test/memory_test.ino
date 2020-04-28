
volatile int x;
volatile uint8_t sensor_data[1000];

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  sensor_data[x++] = x;
}
