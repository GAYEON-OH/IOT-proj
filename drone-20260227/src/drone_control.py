import tkinter as tk
import serial
import time

'''
#블루투스 연결 설정

COM_PORT = 'COM3' 
BAUD_RATE = 9600

try:
    bt_serial = serial.Serial(COM_PORT, BAUD_RATE, timeout=0.1)
    print(f"[{COM_PORT}] 블루투스 연결 성공")
except:
    print(f"[{COM_PORT}] 연결 실패/ 블루투스 연결, 드론 전원, COM 포트 번호가 맞는지 확인")
    bt_serial = None
    
'''

# 테스트용 더미 시리얼

class DummySerial:
    def __init__(self):
        self.is_open = True
        
    def write(self, data):
        print(f"키: {data.decode()}")

bt_serial = DummySerial()
print("가상 연결 테스트")


active_keys = set()

def key_press(event):
    key = event.keysym.lower()
    active_keys.add(key)

def key_release(event):
    key = event.keysym.lower()
    if key in active_keys:
        active_keys.remove(key)


def send_command():
    if bt_serial and bt_serial.is_open:

        if 'w' in active_keys:
            bt_serial.write(b'W')
            status_var.set("W")
        elif 's' in active_keys:
            bt_serial.write(b'S')
            status_var.set("S")
        elif 'a' in active_keys:
            bt_serial.write(b'A')
            status_var.set("A")
        elif 'd' in active_keys:
            bt_serial.write(b'D')
            status_var.set("D")
        elif 't' in active_keys:
            bt_serial.write(b'T')
            status_var.set("T")
        elif 'g' in active_keys:
            bt_serial.write(b'G')
            status_var.set("G")
        elif 'q' in active_keys:
            bt_serial.write(b'Q')
            status_var.set("Q")
        elif 'e' in active_keys:
            bt_serial.write(b'E')
            status_var.set("E")
        else:
            bt_serial.write(b'X')
            status_var.set("X")

    root.after(50, send_command)


root = tk.Tk()
root.title("드론 컨트롤러")
root.geometry("400x250")
root.configure(bg="white")

\
title_lbl = tk.Label(root, text="WASD: 방향 조정 / T: 이륙 / G: 착륙", fg="gray", bg="white", font=("Arial", 10))
title_lbl.pack(pady=20)

status_var = tk.StringVar()
status_var.set("대기")
status_lbl = tk.Label(root, textvariable=status_var, fg="black", bg="white", font=("Arial", 12))
status_lbl.pack(pady=20)

root.bind('<KeyPress>', key_press)
root.bind('<KeyRelease>', key_release)

send_command()
root.mainloop()