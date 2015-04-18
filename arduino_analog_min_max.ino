/**
 * Find the minimum and maximum values read from analog in.
 * This may be used to find min max values from joysticks.
 */

int timeFrame = 20000;
bool done = false;

struct AnalogInput {
  int pin;
  int min;
  int max;
};

int inputAmount = 6;
AnalogInput a0 = {A0, 1023, 0};
AnalogInput a1 = {A1, 1023, 0};
AnalogInput a2 = {A2, 1023, 0};
AnalogInput a3 = {A3, 1023, 0};
AnalogInput a4 = {A4, 1023, 0};
AnalogInput a5 = {A5, 1023, 0};

AnalogInput* inputs[] = {&a0, &a1, &a2, &a3, &a4, &a5};

void setup() {
  Serial.begin(115200);
  Serial.println("Move your analog inputs to their min and max positions...");
}

void loop() {
  /* find minima and maxima */
  if(!done) {
    for(int i = 0; i < inputAmount; ++i) {
      AnalogInput* in = inputs[i];
      int value = analogRead(in->pin);

      if(value < in->min) in->min = value;
      if(value > in->max) in->max = value;
    }
  }

  /* Print the minima and maxima after timeFrame has passed */
  if(millis() >= timeFrame && !done) {
    done = true;

    Serial.println("Follwoing min/max values where found:");
    for(int i = 0; i < inputAmount; ++i) {
      AnalogInput* in = inputs[i];

      Serial.print("A");
      Serial.print(i);
      Serial.print(": min=");
      Serial.print(in->min);
      Serial.print(", max=");
      Serial.println(in->max);
    }
  }
}
