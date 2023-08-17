import psutil
import serial
import time
import datetime

def get_system_info():
    cpu_percent = psutil.cpu_percent(interval=1)  # Get total CPU usage across all cores
    memory = psutil.virtual_memory()
    used_memory_gb = memory.used / (1024 * 1024 * 1024)  # Convert to GB
    return int(cpu_percent), used_memory_gb  # Convert CPU usage to integer

def is_daytime():
    now = datetime.datetime.now()
    return (now.hour >= 7 and now.hour < 17)  # Between 7:00 and 16:59

def should_turn_on_backlight():
    now = datetime.datetime.now()
    return (now.hour >= 17 or now.hour < 7)  # After 17:00 or before 7:00

# Establish serial communication with NodeMCU
ser = serial.Serial('COM3', 9600)  # Adjust 'COM3' to match your NodeMCU's serial port
time.sleep(2)  # Allow time for the connection to be established

while True:
    cpu_usage, used_ram_gb = get_system_info()
    backlight_signal = "ON" if should_turn_on_backlight() else "OFF"
    lcd_signal = "ON" if is_daytime() else "ON"
    data = f"CPU:{cpu_usage:02d} RAM:{used_ram_gb:.2f} BACKLIGHT:{backlight_signal} LCD:{lcd_signal}\n"
    ser.write(data.encode())
    print(f"Sent: {data.strip()}")

    time.sleep(1)  # Send data every 5 seconds
