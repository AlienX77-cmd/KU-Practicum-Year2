ชื่อโครงงาน: Mini Iron Dome
จัดทำโดย: กลุ่มที่ 12 Operation Overlord
(วงจรแถม) Radar X-Distance Detection Unit

6310503286 นายณกรณ์ ศรีพันธุ์
6310503316 นายณัฐภัทร ตัณฑ์สุรัตน์
6310503502 นายภัคพล นารถธนะรุ่ง
6310505688 นายกิตติภัค วิบูลเสถียร

โครงงานนี้เป็นส่วนหนึ่งของรายวิชา 01204223 Practicum for Computer Engineering ภาคปลาย ปีการศึกษา 2564 ภาควิชาวิศวกรรมคอมพิวเตอร์ คณะวิศวกรรมศาสตร์
================================================================================================================
อุปกรณ์
1.Servo Motor model SG90 x1
2.Ultrasonic Sensor model HC-SR04 x1
3.RasberryPi x1
4.Ribbon Cable x1
5.Jumper x7
6.Practicum Board (NodeMCU ATmega328p) x1
7.Breadboard x1
8.PC x1
================================================================================================================
รายละเอียดไฟล์
1) Folder Source Code:
	1.ino = ไฟล์ arduino ที่ใช่ควบคุม servo motor ให้หมุน 0-180 องศา และ คำนวณค่าที่ได้จาก ultrasonic sensor ให้กลายเป็นระยะทาง
	main.py = ไฟล์คำสั่งให้ตัว usb ส่งค่าระยะห่างที่ได้จาก ultrasonic sensor
	practicum.py = ไฟล์ฟังก์ชันต่างๆที่ใช้รับหรือส่งค่าจาก usb
2) Folder รูปวงจร -> แสดงรูปภาพวงจรในหลายๆมุม
3) Folder รูปสมาชิก -> แสดงรูปภาพสมาชิกกลุ่ม
4) File Schematic.png -> ผังวงจร
5) File license.txt   -> ไฟล์แสดงข้อมูลลิขสิทธิ์ 
6) File practicum-v3.zip -> sch practicum board

รายการ library
	library arduino
	<Servo.h> = library ของอุปกรณ์ servo motor
================================================================================================================
