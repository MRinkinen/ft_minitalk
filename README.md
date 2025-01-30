# minitalk

Minitalk is a 42-school project that implements a simple communication system between two processes using the `SIGUSR1` and `SIGUSR2` signals.

## Project Description
This project consists of two programs:
- **Server**: Listens for incoming messages and prints them.
- **Client**: Sends messages to the server one bit at a time using the `SIGUSR1` and `SIGUSR2` signals.


##  Usage Instructions
### 1️ Compile the program
```sh
make
```

###  Start the server
```sh
./server
```
The program prints the process ID (PID), which is needed for sending messages.

###  Send a message using the client
```sh
./client <PID> "Message to the minitalk server!"
```
Replace `<PID>` with the number printed by the server.

## Additional Information
- Messages are sent as bits, where `SIGUSR1` represents bit 0 and `SIGUSR2` represents bit 1.
- The server reconstructs the bits back into characters and prints them to the screen.
