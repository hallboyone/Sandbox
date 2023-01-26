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

difficulty_scaler = 1
if len(sys.argv) > 1:
    difficulty_scaler = float(sys.argv[1])

override_chars = ['1', 'z', '0', 'm']
type_speed = [500, 1000, 1500, 2000, 2500, 3000, 3500]
min_char_num = [80, 160, 240, 400, 500, 700, 800]
max_char_num = [400, 800, 1200, 2000, 2500, 3250, 4000]
wait_time = [2, 1.75, 1.75, 1.5, 1.25, 1.125, 1]
rand_char_set = string.ascii_uppercase + string.ascii_lowercase + "\n"
term_str= (Fore.GREEN+"\033[1msecurity@GLBC-Mainfraim"+Style.RESET_ALL
           +":\033[1m"+Fore.BLUE+"~ $ "+Style.RESET_ALL)

os.system('cls' if os.name == 'nt' else 'clear')
while True:
    while True:
        # Wait for user input
        usr_input = input(term_str)
        if usr_input.endswith("exit"):
            exit()
        elif usr_input.endswith("sys.start"):
            break
        elif usr_input.endswith("clear"):
            os.system('cls' if os.name == 'nt' else 'clear')
        elif usr_input.endswith("deaddrop"):
            print("[This may help you break a code later. Memorize it and then type 'clear']\n\n" +
                  "Let us hold fast the confession of our faith without wavering,\n" +
                  "for he who promised is faithful.\n"+
                  "                                            Heb 10:23 (ESV)")
        else:
            print("Unknown command. Type 'sys.start' to begin or 'clear' to clear screen.")

    # Print opening text
    print(term_str, end="")
    sys.stdout.flush()
    time.sleep(0.5)
    type_text("sys.transfer surveillance all 2h \n", 100)
    time.sleep(0.5)
    print("Retrieving...")
    time.sleep(0.5)
    print(Fore.BLACK + Back.RED + "ACCESS DENIED - Unauthorized User" + Style.RESET_ALL)
    
    # Override 7 times
    for j in range(7):
        # Generate random amounts of random text
        num_chars = random.randint(min_char_num[j], max_char_num[j])
        type_text(''.join(random.choices(rand_char_set, k=num_chars)), type_speed[j])
        
        if j==4:
            # Share hint for cryptex puzzle
            type_text("\nAeTdosnAdnn Enter \033[1mdeaddrop"+Style.RESET_ALL +
                      " for an important message Adnnads foSn", type_speed[j])
        
        # Get override variables
        override_char = random.choice(override_chars)
        right_key_pressed = False
        wrong_key_pressed = False
        
        # Print override message to terminal
        print(Fore.RED + "\nOverride security "+ str(j+1) + "/7 (press "
              + override_char + ")" + Style.RESET_ALL + " ", end="")
        sys.stdout.flush()

        # Wait for user input
        start_time = time.time()
        while time.time() - start_time < difficulty_scaler * wait_time[j]:
            time.sleep(0.01)
            if wrong_key_pressed or right_key_pressed:
                # Keystroke sensed. No need to wait longer
                break
            
            # Look for pressed keys.
            for c in string.ascii_lowercase + string.digits:
                if keyboard.is_pressed(c):
                    if c == override_char:
                        print(Fore.BLACK + Back.GREEN + "override successfull" + Style.RESET_ALL)
                        right_key_pressed = True
                    else:
                        print(Fore.BLACK + Back.RED+ "invalid override key\n" + Style.RESET_ALL)
                        wrong_key_pressed = True
                    break
                
        # Right key not pressed fast enough. Game over, restart for loop
        if not right_key_pressed:
            print(Fore.BLACK + Back.RED + "Threat eleminated. System locked." + Style.RESET_ALL)
            break

    # For loop ended with right key pressed ==> Game is won!
    if right_key_pressed:
        print(Fore.GREEN + "Download complete. Ending process..." + Style.RESET_ALL)

    time.sleep(2)
