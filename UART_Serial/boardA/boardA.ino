#define LED_FLASH_INTERVAL 500
#define RED_LED 2
#define GREEN_LED 3

void setup() {
  // opens serial port, set data rate to 9600 bps
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  Serial1.begin(9600);
  Serial.begin(9600); 
}

void led_on(int turn)
{
  switch (turn) {
    case 0:
      digitalWrite(RED_LED, HIGH);
      digitalWrite(GREEN_LED, LOW);
      break;
    case 1:
      digitalWrite(RED_LED, LOW);
      digitalWrite(GREEN_LED, HIGH);
      break;
    default:
      break;
  }
}

void led_off()
{
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
}

void loop() {
  static char *buf = NULL;
  static int  length = 0;
  int incoming_byte; 

  static unsigned long last_time_led;
  static bool toggle_on = false;
  static int turn = 0; 

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
    }
  }

  if (length > 0) {
    if(strcmp(buf, "ON\n") == 0) {
      last_time_led = millis();
      led_on(turn);
      turn = (turn+1)%2;
      Serial.print("LED ON\n");
      Serial1.print("LED ON\n");
      toggle_on = true;
    } else if(strcmp(buf, "OFF\n") == 0) {
      led_off();
      Serial.print("LED OFF\n");
      Serial1.print("LED OFF\n");
      toggle_on = false;
    } else {
      Serial.print(buf);
    }
    free(buf);
    buf = NULL;
    length = 0;
  }

  if(toggle_on && millis()-last_time_led >= LED_FLASH_INTERVAL) {
    last_time_led = millis();
    led_on(turn);
    turn = (turn+1)%2;
  }
}
