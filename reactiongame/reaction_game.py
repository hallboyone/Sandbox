import keyboard
import sys,time,random
import os
import string
from colorama import Fore, Back, Style
import time

def type_text(msg, typing_speed):
    for l in msg:
        sys.stdout.write(l)
        sys.stdout.flush()
        time.sleep(random.random()*10.0/typing_speed)

hack_chars = ['1', 'z', '0', 'm']
type_speed = [500, 1000, 1500, 2000, 2500, 3000, 3500]
min_char_num = [80, 160, 240, 400, 500, 700, 800]
max_char_num = [400, 800, 1200, 2000, 2500, 3250, 4000]
wait_time = [2, 1.75, 1.75, 1.5, 1.25, 1.125, 1]
rand_char_set = string.ascii_uppercase + string.ascii_lowercase + "\n"
terminal_string = Fore.GREEN + "\033[1msecurity@GLBC-Mainfraim" + Style.RESET_ALL + ":\033[1m" + Fore.BLUE + "~ $ " + Style.RESET_ALL


os.system('cls' if os.name == 'nt' else 'clear')
while True:
    while True:
        usr_input = input(terminal_string)
        if usr_input.endswith("exit"):
            exit()
        elif usr_input.endswith("sys.start"):
            break
        print("Unknown command. Type sys.start to begin.")

    print(terminal_string, end="")
    sys.stdout.flush()
    time.sleep(0.5)
    type_text("sys.transfer surveillance all 2h \n", 100)
    time.sleep(0.5)
    print("Retrieving...")
    time.sleep(0.5)
    print(Fore.BLACK + Back.RED + "ACCESS DENIED - Unauthorized User" + Style.RESET_ALL)
    for j in range(7):
        type_text(''.join(random.choices(rand_char_set, k=random.randint(min_char_num[j], max_char_num[j]))), type_speed[j])
        
        hack_char = hack_chars[random.randint(0,3)]

        print(Fore.RED + "\nOverride security "+ str(j+1) + "/7 (press " + hack_char + ")" + Style.RESET_ALL + " ", end="")
        sys.stdout.flush()

        start_time = time.time()
        key_pressed_fast_enough = False
        wrong_key_pressed = False
        while time.time() - start_time < wait_time[j]:
            time.sleep(0.01)
            if wrong_key_pressed:
                break
            for c in string.ascii_lowercase + string.digits:
                if keyboard.is_pressed(c):
                    if c==hack_char:
                        print(Fore.BLACK + Back.GREEN + "override successfull" + Style.RESET_ALL)
                        time.sleep(1)
                        key_pressed_fast_enough = True
                    else:
                        print(Fore.BLACK + Back.RED+ "invalid override key\n" + Style.RESET_ALL)
                        wrong_key_pressed = True
                    break
                
        if not key_pressed_fast_enough:
            print(Fore.BLACK + Back.RED + "Threat eleminated. System locked." + Style.RESET_ALL)
            break

    if key_pressed_fast_enough:
        print(Fore.GREEN + "Download complete. Ending process..." + Style.RESET_ALL)

    time.sleep(0.5)