import time
import globals
from RPLCD.i2c import CharLCD
from datetime import date, datetime


lcd = CharLCD(i2c_expander='PCF8574', address=0x3f, port=1,
        cols=20, dotsize=8,
        charmap='A02',
        auto_linebreaks=True,
        backlight_enabled=True)

def display_registered():
    lcd.clear()
    # ID_number = upload.ID_number
    print(globals.ID_number)
    lcd.write_string('Welcome! ')
    lcd.write_string(globals.ID_number)
    time.sleep(2)
    
def display_default():
    # print(globals.state)
    if globals.state != 'default':
        lcd.clear()
        globals.state = 'default'
        lcd.write_string(datetime.now().strftime('%H:%M:%S'))
        lcd.crlf()
        lcd.write_string('Press the button andscan the ID card')
    else:
        lcd.cursor_pos = (0,0)
        lcd.write_string(datetime.now().strftime('%H:%M:%S'))
        
def display_unregistered():
    lcd.clear()
    lcd.write_string('Unregistered!\n\rPlease contact the \n\radmin')
    time.sleep(2)

#default: 時間:先按按鈕 再刷卡 
#刷完:  1. 學號 歡迎
#       2.(fail) you haven't register, plz contact to the  admin