#!/usr/bin/env python3
import sys

def stomp(binary: str, write_address: int, replacement: str):
    """Overwrites binary with data contained in replacement file
       Starting at write_address 
    """
    replacement_data = None
    with open(replacement, 'rb') as f:
        replacement_data = f.read(0x1000)

    with open(binary, 'rb+') as f:
        f.seek(write_address)
        f.write(replacement_data)

if __name__ == "__main__":
    if len(sys.argv) < 4:
        print("Usage: ./overwrite [binary] [write address] [replacement]")
        sys.exit(1)

    binary = sys.argv[1]

    write_address = sys.argv[2]
    try:
        write_address = int(sys.argv[2])        #encryption start address
    except ValueError:
        write_address = int(sys.argv[2], 16)

    replacement = sys.argv[3] 
    stomp(binary, write_address, replacement)
