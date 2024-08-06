#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#define PREAMBLE_LENGTH 4
#define MAX_MESSAGE_LENGTH 256 // maximum message length including data
#define CRC8_POLY 0x07

const uint8_t PREAMBLE[PREAMBLE_LENGTH] = {0x01, 0x02, 0x03, 0x04};

// Function to check the preamble
bool check_preamble(uint8_t* data) {
    for (int i = 0; i < PREAMBLE_LENGTH; i++) {
        if (data[i] != PREAMBLE[i]) {
            return false;
        }
    }
    return true;
}

// Function to get the message length
uint8_t get_message_length(uint8_t* data) {
    return data[PREAMBLE_LENGTH];
}

// Function to get the source address
uint8_t get_source_address(uint8_t* data) {
    return data[PREAMBLE_LENGTH + 1];
}

// Function to get the destination address
uint8_t get_destination_address(uint8_t* data) {
    return data[PREAMBLE_LENGTH + 2];
}

// Function to get the message data
void get_message_data(uint8_t* data, uint8_t* message_data, uint8_t length) {
    for (int i = 0; i < length; i++) {
        message_data[i] = data[PREAMBLE_LENGTH + 3 + i];
    }
}

// Function to calculate CRC-8
uint8_t get_crc8(uint8_t* data, uint8_t length) {
    uint8_t crc = 0;
    for (int i = 0; i < length; i++) {
        crc ^= data[i];
        for (int j = 0; j < 8; j++) {
            if (crc & 0x80) // Check the most significant bit
                crc = (crc << 1) ^ CRC8_POLY;
            else
                crc <<= 1;
        }
    }
    return crc;
}

// Function to check CRC-8
bool check_crc8(uint8_t* data, uint8_t length) {
    uint8_t crc = get_crc8(data, length - 1); // excluding the last byte which is the CRC itself
    return crc == data[length - 1];
}

// Function to process the received message
void process_message(uint8_t* data) {
    if (!check_preamble(data)) {
        printf("Invalid preamble.\n");
        return;
    }

    uint8_t message_length = get_message_length(data);
    uint8_t source_address = get_source_address(data);
    uint8_t destination_address = get_destination_address(data);

    uint8_t message_data[MAX_MESSAGE_LENGTH];
    get_message_data(data, message_data, message_length);

    // Message length excluding the CRC byte
    uint8_t crc_length = PREAMBLE_LENGTH + 3 + message_length + 1; // including the CRC byte

    if (!check_crc8(data, crc_length)) {
        printf("CRC error.\n");
        return;
    }

    // Further message processing
    printf("Message received successfully:\n");
    printf("Source Address: %02X\n", source_address);
    printf("Destination Address: %02X\n", destination_address);
    printf("Data: ");
    for (int i = 0; i < message_length; i++) {
        printf("%02X ", message_data[i]);
    }
    printf("\n");
}

// Function to simulate data reception
bool receive_data(uint8_t* buffer, uint8_t* length) {
    // Simulate data reception, replace this with actual code
    // For example, fill the buffer with fixed data.
    buffer[0] = 0x01;
    buffer[1] = 0x02;
    buffer[2] = 0x03;
    buffer[3] = 0x04;
    buffer[4] = 0x05; // Message length
    buffer[5] = 0x11; // Source address
    buffer[6] = 0x22; // Destination address
    buffer[7] = 0x39; // Data
    buffer[8] = 0x44;
    buffer[9] = 0x55;
    buffer[10] = 0x66;
    buffer[11] = 0x77;
    buffer[12] = 0xC1; // CRC

    *length = 13; // Total message length (including preamble, length, addresses, data, and CRC)
    return true;
}

int main() {
    uint8_t buffer[MAX_MESSAGE_LENGTH];
    uint8_t length;

    // Simulate data reception with a time limit
    time_t start_time = time(NULL);

    while (time(NULL) - start_time < 1) { // Maximum message reception time is 1 second
        if (receive_data(buffer, &length)) {
            process_message(buffer);
            break;
        }
    }

    return 0;
}