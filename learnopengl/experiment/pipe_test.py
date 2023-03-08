import sys

def main():
    print("python called")
    # Read the message from the C++ program
    message = sys.stdin.readline().strip()
    print("Received message from C++:", message)

    # Send a message back to the C++ program
    print("Hello from Python")
    sys.stdout.flush()

if __name__ == '__main__':
    main()
