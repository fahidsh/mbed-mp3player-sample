# Mbed (DF) Mp3 Player

[-] Language: C++<br>
[-] Platform: mbed OS 6<br>
[-] License: MIT<br>
[-] Author: [Fahid Shehzad](https://github.com/fahidsh)<br>
[-] Source: [GitHub](https://github.com/fahidsh/mbed-mp3player)<br>
[-] IDE/Software: Platform.io<br>
[-] Last Update: 03.07.2022

During our Technical Project, a fellow to use the  [DFPlayer Mini MP3 Player, for Arduino](https://www.dfrobot.com/product-1121.html), there are many examples and libraries available for this MP3 Player.

But we had to use the [`mbed OS`](https://mbed.org/) to control it. 

There are not a lot of libraries or examples available for this MP3 Player in conjunction with `mbed OS`. There is one mbed library available for this MP3 Player [here](https://os.mbed.com/users/kysiki/code/DFPlayerMini/), but it uses lagacy `Serial Port` API, which is not supported by `mbed OS 6`. When I tried to use this library, I kept getting errors/unexpected results, so I decided to write my own library. Of course the above mentioned library was still a very good reference. But I still needed to search around and get help from other resources, resources worth mentioning (for me) were: 
1. [`Documentation`](https://wiki.dfrobot.com/DFPlayer_Mini_SKU_DFR0299)
2. [`Video from Ralph S Bacon`](https://www.youtube.com/watch?v=TjomLQs0KgY)
3. [`Github from RalphBacon`](https://github.com/RalphBacon/MP3-Player-DFPlayer)
4. [`DFPlayerMini by yuto kamo`](https://os.mbed.com/users/kysiki/code/DFPlayerMini/)

Especially the video and Github repo from RalphBacon was very helpful. Because he is using the player without the Arduino library.

With the help of the above mentioned resources and some headache, I was able to get the mp3-player working.

## Usage
import the library to your project and include the `.h` file in your project.

```cpp
#include "mbed.h"
#include "mbed-mp3player.h"
MbedDFPlayer mp3_player(PC_10, PC_11); // tx, rx
```
and you can start using the functions in your project.

```cpp
// play a track
void mp3_player.play();

// play a specific track 
void mp3_player.play(1); // int value

// pause the track
void mp3_player.pause();

// next track
void mp3_player.next();

// previous track
void mp3_player.previous();

// get the status if currently playing or not
bool mp3_player.is_playing();
```
## Limitations
I have tried to keep this library as simple as possible, so that it can be extended by someone in the future to offer more functions and features of MFPlayer. But as of now, I have kept it limited to necessary functions that are needed by my colleague for his project. Due to time constraints, I have not added the functions that are not required.

I had the mp3-player module this weekend to get it workding with `mbed OS 6`, which it is working fine, I will be returning it back and possibly won't work any further on it. Everyone is welcome to fork/copy it and add more functions to it. Maybe leave a link here as well so other people searching may also find your good work.

### What functions are not available right now?
- selecting and playing from specific folders
- using differet equalizers
- repeating the track
- standby/normal mode

`the above listed functions can easily be added with just a few lines of code each. What however still needs a work is the functionality to get information from the mp3 player.`

## Verion History
### v0.1.0: 03.07.2022 - Initial Release
Play/Play-Specific/Pause/Next/Previous are working. But in my opinion, now it is much easier to extend it from here.