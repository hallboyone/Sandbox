
//Define a macro to shift bits
#define MASK(x) ((unsigned char)(1<<(x)))


void setup() {
  //Set pin B.5 to be an output (set to 1)
  DDRB |= MASK(5); //DDRB -> Data Dir Register B

  //Sample function
  managePortD();
}

void loop() {
  PORTB |= MASK(5); // Set pin B5 to HIGH
  delay(500);
  PORTB &= ~MASK(5); //Set pin B5 to LOW
  delay(500);
}

void managePortD(){//Pins 0-7
  //Get current port D register values
  uint8_t snapshot = PORTD;
  
  //Set bits 2 and 5
  snapshot = snapshot | (MASK(2)|MASK(5));

  //Clear bits 0, 3, and 7
  snapshot = snapshot & (MASK(0)|MASK(3)|MASK(7));
  
  //If bit 4 is high, then envert bit 1 
  if(snapshot & MASK(4)){
    snapshot = snapshot ^ MASK(1);
  }

  PORTD = snapshot;
}
