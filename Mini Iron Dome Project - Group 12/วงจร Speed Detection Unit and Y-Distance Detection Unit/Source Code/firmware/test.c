#include <usbdrv.h>
#include <string.h>

#define RQ_SET_LED    0
#define RQ_GET_SWITCH 1
#define RQ_GET_LIGHT  2
//const char* trigPin = "PIN_PC0";
//const char* echoPin = "PIN_PC1";
#define LOW 0
#define HIGH 1
int duration;
int distance;

//////////////////////////////////////////////////////////////////////
usbMsgLen_t usbFunctionSetup(uint8_t data[8])
{
  usbRequest_t *rq = (usbRequest_t*)data;
  static uint8_t switch_state;

if (rq->bRequest == RQ_GET_SWITCH)
  {
    digitalWrite(PIN_PC0, LOW);
    delayMicroseconds(2);
    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
    digitalWrite(0, HIGH);
    delayMicroseconds(10);
    digitalWrite(0, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(1, HIGH);
    // Calculating the distance
    distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
    
    /* point usbMsgPtr to the data to be returned to host */
    usbMsgPtr = (uint8_t*) &distance;
    
    /* return the number of bytes of data to be returned to host */
    return sizeof(distance);
    
  }

  return 0;   /* nothing to do; return no data back to host */
}

//////////////////////////////////////////////////////////////////////
void setup()
{

    //pinMode(PIN_PC2,OUTPUT);
    //pinMode(PIN_PC3,INPUT_PULLUP);
    //pinMode(PIN_PC4,INPUT);
    //pinMode(PIN_PD3,OUTPUT);
    pinMode(PIN_PC0, OUTPUT); // Sets the trigPin as an Output
    pinMode(PIN_PC1, INPUT); // Sets the echoPin as an Input

    usbInit();

    /* enforce re-enumeration of USB devices */
    usbDeviceDisconnect();
    delay(300);
    usbDeviceConnect();
}


void loop()
{
  usbPoll();
}

