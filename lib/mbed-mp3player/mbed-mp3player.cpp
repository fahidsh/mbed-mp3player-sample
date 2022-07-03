#include "mbed-mp3player.h"

// Commands are available at: https://wiki.dfrobot.com/DFPlayer_Mini_SKU_DFR0299

MbedDFPlayer::MbedDFPlayer(PinName txPin, PinName rxPin) : mp3_player(txPin, rxPin) {
    mp3_player.set_baud(9600);
    mp3_player.set_format(8, BufferedSerial::None, 1);
    // pause the playback, if something was playing
    execute_command(0x0E);
}




void MbedDFPlayer::play() {
    _is_playing = true;
    execute_command(0x0D /* play: 0xD*/);
}
void MbedDFPlayer::play(int track) {
    _is_playing = true;
    execute_command(0x03 /* play: 0xD*/, track /* arg_low: tracknumber*/);
}
void MbedDFPlayer::pause() {
    _is_playing = false;
    execute_command(0x0E /* pause: 0xE*/);
}
bool MbedDFPlayer::is_playing() {
    return _is_playing;
}
void MbedDFPlayer::next() {
    execute_command(0x01 /* next: 0x1*/);
}
void MbedDFPlayer::previous() {
    execute_command(0x02 /* previous: 0x2*/);
}

/*


void MbedDFPlayer::stop();


int MbedDFPlayer::set_volume(int volume);
int MbedDFPlayer::increase_volume();
int MbedDFPlayer::decrease_volume();
*/

/**
 * ****************************************************************
 * * The real Deal, dirty code follows...
 * ****************************************************************
 */


void MbedDFPlayer::execute_command(char cmd) {
    memcpy(send_buffer, base_command, 10);
    send_buffer[CMD_IDX::CMD] = cmd;
    send_buffer[CMD_IDX::ACK] = request_acknowledgement;// ? 0x01 : 0x00;
    send_buffer[CMD_IDX::ARG_HIGH] = 0x00;
    send_buffer[CMD_IDX::ARG_LOW] = 0x00;
    execute_command(send_buffer);
}

void MbedDFPlayer::make_command(char cmd, char arg_high, char arg_low) {
    memcpy(send_buffer, base_command, 10);
    send_buffer[CMD_IDX::CMD] = cmd;
    send_buffer[CMD_IDX::ACK] = request_acknowledgement;// ? 0x01 : 0x00;
    send_buffer[CMD_IDX::ARG_HIGH] = arg_high;
    send_buffer[CMD_IDX::ARG_LOW] = arg_low;
    execute_command(send_buffer);
}
void MbedDFPlayer::execute_command(char cmd, char arg_low) {
    memcpy(send_buffer, base_command, 10);
    send_buffer[CMD_IDX::CMD] = cmd;
    send_buffer[CMD_IDX::ACK] = request_acknowledgement;// ? 0x01 : 0x00;
    send_buffer[CMD_IDX::ARG_HIGH] = 0x00;
    send_buffer[CMD_IDX::ARG_LOW] = arg_low;
    execute_command(send_buffer);
}

/**
 * @brief sends the command to the mp3-player serial interface
 * 
 * @param cmd char pointer to command array
 */
void MbedDFPlayer::execute_command(char *cmd) {
    fill_checksum(cmd);
    mp3_player.write(cmd, 10);
}


/**
 * @brief fills the checksum of the command into the command array
 * two byte checksum is added to index 7 and 8 of the command array
 * 
 * @param cmd char pointer to command array
 */
void MbedDFPlayer::fill_checksum(char *cmd) {
    // fill checksum HighByte[7] and LowByte[8]
    uint16_t checksum = get_checksum(cmd);
    cmd[CMD_IDX::CHECKSUM_HIGH] = get_high_byte(checksum);
    cmd[CMD_IDX::CHECKSUM_LOW] = get_low_byte(checksum);
}

/**
 * @brief calcutes and returns the checksum of the mp3-player command
 * 
 * @param cmd an array containing the command (10 elements) to be checksummed
 * @return uint16_t calculated checksum as uint16_t
 */
uint16_t MbedDFPlayer::get_checksum (const char *cmd) {
    uint16_t sum = 0;
    // we want to get the sum of byte 2 to byte 7 (Index: 1 to 6)
    // can also be done by loop, but let's do it with array
    sum =   cmd[CMD_IDX::VERSION_BYTE] + 
            cmd[CMD_IDX::LENGTH_BYTE] + 
            cmd[CMD_IDX::CMD] + 
            cmd[CMD_IDX::ACK] + 
            cmd[CMD_IDX::ARG_HIGH] + 
            cmd[CMD_IDX::ARG_LOW];
    return -sum;
}

/**
 * @brief Extracts the 8 bits from left side side of 16 bit int, into 8 bit int 
 * @moreinfo https://www.arduino.cc/reference/en/language/functions/bits-and-bytes/highbyte/
 * @param data 16-bit int
 * @return uint8_t 8-bit from left
 */
uint8_t MbedDFPlayer::get_high_byte (uint16_t data) {
    return (data >> 8) & 0xFF;
}
/**
 * @brief Extracts the 8 bits from right side side of 16 bit int, into 8 bit int 
 * @moreinfo https://www.arduino.cc/reference/en/language/functions/bits-and-bytes/lowbyte/
 * @param data 16-bit int
 * @return uint8_t 8-bit from right
 */
uint8_t MbedDFPlayer::get_low_byte (uint16_t data) {
    return data & 0xFF;
}

