void setup() {
  // opens serial port, set data rate to 9600 bps
  Serial1.begin(9600);
  Serial.begin(9600); 
}

void loop() {
  static char *buf = NULL;
  static int  length = 0;
  int incoming_byte; 

  while(Serial.available() > 0) {
    incoming_byte = Serial.read();
    buf = (char*)realloc(buf, length + 1);
    buf[length++] = incoming_byte;
    if(incoming_byte == '\n') { 
      buf[length] = '\0';
      Serial.print(buf);
      Serial1.print(buf);
      free(buf);
      buf = NULL;
      length = 0;
    }
  }

  while(Serial1.available() > 0) {
    incoming_byte = Serial1.read();
    buf = (char*)realloc(buf, length + 1);
    buf[length++] = incoming_byte;
    if(incoming_byte == '\n') {
      buf[length] = '\0';
      Serial.print(buf);
      free(buf);
      buf = NULL;
      length = 0;
    }
  }
}
