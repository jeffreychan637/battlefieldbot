COMMANDS = ["fire", "retrieve", "stop"]

def send_command(command):
    print("Command Sent: %s" % command)
    #send command to PSOC
    #send command to GUI

def main():
    while True:
        command = raw_input("Enter Command: ")
        if command == "f":
            send_command("fire")
        elif command == "r":
            send_command("retrieve")
        elif command == "s":
            send_command("stop")

if __name__ == '__main__': main()
