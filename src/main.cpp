#include "mbed.h"
#include "mbed-mp3player.h"

static BufferedSerial pc_serial(USBTX, USBRX, MbedDFPlayer::BAUD_RATE);
MbedDFPlayer mp3_player(PC_10, PC_11);

// MF-Shield Tasters
InterruptIn taster1(PA_1, PullDown);
InterruptIn taster2(PA_4, PullDown);
InterruptIn taster3(PB_0, PullDown);

enum COMMAND {
    NONE,
    PLAY_PAUSE,
    NEXT,
    PREV,
};
COMMAND next_command = NONE;

// functions
void play_pause();
void play_next();
void play_previous();
void set_play_pause();
void set_next();
void set_previous();
void control_center();

int main() {
    pc_serial.set_format(8, BufferedSerial::None, 1);
    pc_serial.write("MP3 Player Program Started\r\n", 28);
    
    // MF-Shield Tasten als Interrupts aktivieren
    taster1.rise(&set_previous);
    taster1.enable_irq();
    taster2.rise(&set_play_pause);
    taster2.enable_irq();
    taster3.rise(&set_next);
    taster3.enable_irq();

    Ticker control_center_ticker;
    control_center_ticker.attach(&control_center, 100ms); 

    while(true) {

    }
}

void set_play_pause() {
    next_command = PLAY_PAUSE;
}
void set_next() {
    next_command = NEXT;
}
void set_previous() {
    next_command = PREV;
}

void control_center() {
    switch(next_command) {
        case PLAY_PAUSE:
            play_pause();
            break;
        case NEXT:
            play_next();
            break;
        case PREV:
            play_previous();
            break;
        default:
            break;
    }
    next_command = NONE;
}

void play_pause() {
    if(mp3_player.is_playing()) {
        pc_serial.write("Pause\r\n", 7);
        mp3_player.pause();
    } else {
        pc_serial.write("Play\r\n", 6);
        mp3_player.play();
    }
}
void play_next() {
    pc_serial.write("Next\r\n", 6);
    mp3_player.next();
}
void play_previous() {
    pc_serial.write("Track at index 1\r\n", 10);
    mp3_player.play(1);
}
