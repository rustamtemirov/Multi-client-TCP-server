# Line-Reversing Server

## Description
TCP server that receives line-delimited input from client, then reverses and sends back the input line. Server supports line lengths of at least 4 GiB and can server multiple clients simultaneously. 

## Installation

Use `make` command to compile the server or client sides.

Server:
```bash
make -f MakeFile server
```

Client:
```bash
make -f MakeFile client
```

## Usage

To run either server or client.

Server:
```bash
./server
```
Client:
```bash
./client
```
To remove the executable files:
```bash
make -f MakeFile clean
```

## Roadmap
There are some other features like authentication, menu, admin are expected to be added in the future.
