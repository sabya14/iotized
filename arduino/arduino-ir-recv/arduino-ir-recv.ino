#define sprint Serial.print
#define sprintln Serial.println
#include <IRremote.h>

#define IR_RCVR_PIN 2
IRrecv ir_receiver(IR_RCVR_PIN);

void setup() {
  Serial.begin(9600);
  ir_receiver.enableIRIn(); // Start the receiver
}

void loop() {
  sprintln("Press a key");
  recieve();
  delay(2000);
}

int c = 1;
void recieve() {
  if (ir_receiver.decode()) {
    irparams_struct *results = ir_receiver.decodedIRData.rawDataPtr;
    sprintln(ir_receiver.decodedIRData.decodedRawData);
    int count = results->rawlen;
    c++;
    sprintln(count);
    for (int i = 1; i < count; i++) {
      sprint((unsigned int)results->rawbuf[i]);
      sprint(",");
    }
    sprintln(" ");
    
    sprintln("Received key");
    ir_receiver.resume(); // Receive the next value
    
  }
}
