# CRC8-Message-Processor

## Overview
This repository contains a C program for processing messages with CRC-8 validation. The program includes functions for checking the preamble, extracting message length, source and destination addresses, and validating the CRC-8 checksum.

## Features
- **Preamble Check**: Ensures the message starts with the correct preamble.
- **Message Length Extraction**: Retrieves the length of the message.
- **Address Extraction**: Retrieves the source and destination addresses.
- **CRC-8 Calculation and Validation**: Computes and validates the CRC-8 checksum for data integrity.

## Files
- `main.c`: The main program file containing all functions and the main loop.
- `Makefile`: A makefile for compiling the program.

## Usage
1. Clone the repository:
   ```sh
   git git@github.com:roboeggs/CRC8-Message-Processor.git
   cd CRC8-Message-Processor
   ```
2. Compile the program using make:
    ```sh
    make
    ```

3. Run the program:
    ```sh
    ./crc8_processor
    ```
## Dependencies
Standard C libraries: stdint.h, stdbool.h, stdio.h, time.h
## License
This project is licensed under the MIT License - see the LICENSE file for details.