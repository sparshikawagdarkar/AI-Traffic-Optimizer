import os
import time

print("--- Python Traffic Optimizer Brain Online ---")

# Ensure clean start by clearing old action files
if os.path.exists("action.txt"):
    os.remove("action.txt")

for second in range(1, 21):
    queue_length = 0
    
    # 1. WAIT for C++ to write the state file
    print(f"[Second {second}] Python waiting for C++ update...", end="\r")
    while not os.path.exists("state.txt"):
        time.sleep(0.05) # Tiny pause to prevent CPU melting
        
    # Read the state
    try:
        with open("state.txt", "r") as infile:
            content = infile.read().strip()
            if content.isdigit():
                queue_length = int(content)
    except IOError:
        pass # Handle occasional file access collision
        
    # Remove state.txt so Python knows it has processed this frame
    try:
        os.remove("state.txt")
    except:
        pass

    print(f"[Second {second}] Python saw Queue Length: {queue_length}")
    
    # 2. Optimization Logic
    if queue_length >= 2:
        action = "GREEN"
        print("  -> Optimization Alert: Queue too long! Forcing GREEN.")
    else:
        action = "RED"
        print("  -> Road clear or light traffic. Keeping RED.")
        
    # 3. Write action back to C++
    with open("action.txt", "w") as outfile:
        outfile.write(action + "\n")

print("--- Python Optimization Loop Ended ---")