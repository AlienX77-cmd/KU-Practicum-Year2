import time
import usb
from practicum import find_mcu_boards, McuBoard
device = find_mcu_boards()
mcu = McuBoard(device[0])
while(1):
	cm = mcu.usb_read(request=1,length=1)
	print("distance "+str(cm[0])+" cm")
	time.sleep(0.1)
