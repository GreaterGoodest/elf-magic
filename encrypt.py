#!/usr/bin/env python3
import sys

def crypt(binary: str, start: int, stop: int):
    """Encrypts the provided binary from start address to stop address"""
    print(f"Encrypting {binary} from address {start} to address {stop}")
    size = stop - start                 #size of space to be encrypted
    with open(binary, 'rb+') as f:
        f.seek(start)                   #move file pointer to start address
        data = bytearray(f.read(size))  #read in data to be encrypted
        for i in range(len(data)):      #encrypt data using single byte xor
            data[i] = data[i] ^ 0xFA
        data = bytes(data)              #convert back to bytes for writing to binary

        f.seek(start)                   #return to start address
        f.write(data)                   #replace data with encrypted version


if __name__ == "__main__":
    if len(sys.argv) < 4:
        print("Usage: ./crypt [binary] [start address] [stop address]")
        sys.exit(1)

    binary = sys.argv[1]                #binary file name
    try:
        start = int(sys.argv[2])        #encryption start address
    except ValueError:
        start = int(sys.argv[2], 16)

    try:
        stop = int(sys.argv[3])         #encryption end address
    except ValueError:
        stop = int(sys.argv[3], 16)

    crypt(binary, start, stop)
