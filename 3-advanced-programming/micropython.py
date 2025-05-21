from machine import Pin, Timer
import utime as time

print("Hello Python!")

led = Pin("LED", Pin.OUT)

while True:
    led.toggle()

    time.sleep_ms(1000)