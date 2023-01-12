#include <usbdrv.h>
#include <string.h>
#include <Servo.h>

#define RQ_GET_SENSOR 1
//const char* trigPin = "PIN_PC0";
//const char* echoPin = "PIN_PC1";
int duration=0;
int distance=0;
Servo myServo;

usbMsgLen_t usbFunctionSetup(uint8_t data[8])
{
  usbRequest_t *rq = (usbRequest_t*)data;
  static uint8_t switch_state;

if (rq->bRequest == RQ_GET_SENSOR)
  {
    digitalWrite(PIN_PC0, LOW);
    delayMicroseconds(2);
    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
    digitalWrite(PIN_PC0, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_PC0, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(PIN_PC1, HIGH);
    // Calculating the distance
    distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
    
    /* point usbMsgPtr to the data to be returned to host */
    usbMsgPtr = (uint8_t*) &distance;
    
    /* return the number of bytes of data to be returned to host */
    return sizeof(distance);
    
  }

  return 0;   /* nothing to do; return no data back to host */
}


void setup()
{

    pinMode(PIN_PC0, OUTPUT); // Sets the trigPin as an Output
    pinMode(PIN_PC1, INPUT); // Sets the echoPin as an Input
    myServo.attach(PIN_PC2);
    usbInit();

    /* enforce re-enumeration of USB devices */
    usbDeviceDisconnect();
    delay(300);
    usbDeviceConnect();
}


void loop()
{
  for(int i=15;i<=165;i++)
  {  
  myServo.write(i);
  delay(30);
  usbPoll();
  }
  for(int i=165;i>15;i--)
  {  
  myServo.write(i);
  delay(30);
  usbPoll();
  }
}
