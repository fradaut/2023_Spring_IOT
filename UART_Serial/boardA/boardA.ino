void setup() {
  // opens serial port, set data rate to 9600 bps
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  static char buf[200];
  static int  length = 0;
  buf[length] = '\0';
  int incoming_byte; 

  if(Serial.available() > 0) {
    incoming_byte = Serial.read();
    buf[length++] = incoming_byte;
    if(incoming_byte == '\n') { 
      buf[length] = '\0';
      Serial.print(buf);
      Serial1.write(buf);
      length = 0;
    }
  }
  
  if (Serial1.available() > 0) {
    incoming_byte = Serial1.read();
    buf[length++] = incoming_byte;
    if(incoming_byte == '\n') {
      buf[length] = '\0';
      Serial.print(buf);
      length = 0;
    }
  }
}
