#include <avr/io.h>
#include <avr/interrupt.h>  /* for sei() */
#include <util/delay.h>     /* for _delay_ms() */
#include <avr/pgmspace.h>   /* required by usbdrv.h */

#include "peri.h"
#include "usbdrv.h"

#define A_DETECT() ((PINC & (1<<PC3)) == 0)
#define B_DETECT() ((PINC & (1<<PC4)) == 0)
#define ECHO_DETECT() ((PINC & (1<<PC5)) == 0)

#define RQ_SET_BEEP		0
#define RQ_GET_DETECT		1
#define RQ_SET_ECHO		2
#define RQ_GET_ECHO		3

// pin 0 output beep
// pin 1 output us
// pin 3,4 input ir
// pin 5 input us


/* ------------------------------------------------------------------------- */
/* ----------------------------- USB interface ----------------------------- */
/* ------------------------------------------------------------------------- */
usbMsgLen_t usbFunctionSetup(uint8_t data[8])
{
    usbRequest_t *rq = (void *)data;

    static uint8_t a_state;  
    static uint8_t b_state;  
    static uint8_t echo_state;  

    if (rq->bRequest == RQ_SET_BEEP)
    {
        uint8_t beep_state = rq->wValue.bytes[0];
        set_led(0, beep_state);
        return 0;
    }
    else if (rq->bRequest == RQ_GET_DETECT)
    {
        //  uint8_t led_state = rq->wValue.bytes[0];
        //  uint8_t led_no  = rq->wIndex.bytes[0];
        //  set_led(led_no, led_state);
	uint8_t detect_no = rq->wIndex.bytes[0];
	if(!detect_no){
		a_state = A_DETECT();
		usbMsgPtr = &a_state;
	}
	else{
		b_state = B_DETECT();
		usbMsgPtr = &b_state;
	}
        return 1;
    }
    else if (rq->bRequest == RQ_GET_ECHO)
    {
        echo_state = 0;
	set_led(1,0);
	_delay_us(2);
	set_led(1,1);
	_delay_us(10);
	set_led(1,0);
	while(!ECHO_DETECT()){
            echo_state++;
	    _delay_us(1);
	}
	while(!ECHO_DETECT()){
	}
	_delay_ms(1);
	usbMsgPtr = &echo_state;
	return 1;
    }

    /* default for not implemented requests: return no data back to host */
    return 0;
}

/* ------------------------------------------------------------------------- */
int main(void)
{
    init_peri();

    usbInit();

    /* enforce re-enumeration, do this while interrupts are disabled! */
    usbDeviceDisconnect();
    _delay_ms(300);
    usbDeviceConnect();

    /* enable global interrupts */
    sei();

    /* main event loop */
    for(;;)
    {
        usbPoll();
    }

    return 0;
}

/* ------------------------------------------------------------------------- */
