from practicum import McuBoard

RQ_GET_SENSOR = 1

####################################
class PeriBoard(McuBoard):

    ################################
    def setLed(self, led_no, led_val):
        '''
        Set status of LED led_no on peripheral board to led_val
        '''
        return

    ################################
    def setLedValue(self, value):
        '''
        Display value's 3 LSBs on peripheral board's LEDs
        '''
        return

    ################################
    def getSwitch(self):
        '''
        Return a boolean value indicating whether the switch on the peripheral
        board is currently pressed
        '''
        return

    ################################
    def getLight(self):
        '''
        Return the current reading of light sensor on peripheral board
        '''
        return
