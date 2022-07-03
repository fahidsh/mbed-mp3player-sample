
#ifndef MBED_DF_PLAYER_H
#define MBED_DF_PLAYER_H

#include "mbed.h"

enum CMD_IDX { // this is the index of the command in the mp3_player_command_buffer
    START_BYTE, // Fixed 0x7E
    VERSION_BYTE, // Fixed 0xFF
    LENGTH_BYTE, // Fixed 0x06
    CMD, // Command comes here
    ACK, // Acknowledgement, 0x00 or 0x01
    ARG_HIGH, // Argument high byte, if Argument is more than one byte (>0xFF)
    ARG_LOW, // Argument low byte, when Argument value is <= 0xFF, it is only one byte.
    CHECKSUM_HIGH, // Checksum high byte, calculated by sum of bytes 2 to 6
    CHECKSUM_LOW, // Checksum low byte, calculated by sum of bytes 2 to 6
    END_BYTE // Fixed 0xEF
};

class MbedDFPlayer {
public:
    static const int CMD_LEN = 10;
    static const int BAUD_RATE = 9600;

    MbedDFPlayer(PinName txPin, PinName rxPin);
    void play();
    void play(int track);
    void pause();
    void stop();
    bool is_playing();
    void next();
    void previous();
    int set_volume(int volume);
    int increase_volume();
    int decrease_volume();
    int get_volume();


private:
    BufferedSerial mp3_player;
    const char base_command[10] = {0x7E, 0xFF, 06, 00, 00, 00, 00, 00, 00, 0xEF};
    char send_buffer[10];
    char receive_buffer[10];
    bool request_acknowledgement = false;
    bool _is_playing = false; // true if currently playing music
    uint8_t volume = 30; // volume of the music, 0-30
    uint8_t current_song = 0; // current song number

    void execute_command(char cmd);
    void make_command(char cmd, char arg_high, char arg_low);
    void execute_command(char cmd, char arg_low);
    void execute_command(char *cmd);
    void fill_checksum(char *cmd);
    uint16_t get_checksum (const char *cmd);
    uint8_t get_high_byte (uint16_t data);
    uint8_t get_low_byte (uint16_t data);

};

#endif // MBED_DF_PLAYER_H