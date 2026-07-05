import time
import os

print("--- Python Traffic Optimizer Brain Online ---")

# Let's run a loop that checks the C++ state file every second
for second in range(1, 21):
    queue_length = 0
    
    # 1. Read the current queue size from the C++ state file
    if os.path.exists("state.txt"):
        with open("state.txt", "r") as infile:
            content = infile.read().strip()
            if content.isdigit():
                queue_length = int(content)
                
    print(f"[Second {second}] Python saw Queue Length: {queue_length}")
    
    # 2. Optimization Logic: 
    # If a traffic queue builds up to 2 or more cars, override and force GREEN.
    # Otherwise, keep it RED to simulate a strict boundary check.
    if queue_length >= 2:
        action = "GREEN"
        print("  -> Optimization Alert: Queue too long! Forcing GREEN.")
    else:
        action = "RED"
        print("  -> Road clear or light traffic. Keeping RED.")
        
    # 3. Write the decision back to the action file for C++ to read
    with open("action.txt", "w") as outfile:
        outfile.write(action + "\n")
        
    time.sleep(1) # Wait 1 second before checking again

print("--- Python Optimization Loop Ended ---")