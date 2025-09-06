# Learning operating system development using Linux kernel and Raspberry Pi

The repository deals with creating a bare-metal operating system and hardware abstraction layer for Raspberry Pi 4B. The operating system will implement basic communication protocols, interrupt  controllers and ultimately HDMI support. Using these as the base this project will aim at creating a simple pong game using the HDMI Support of our kernel. This is still work in progress.

### *TASKS*

1. UART IMPLEMENTATION (BOTH PL011 AND MINI-UART)
2. CHANGING EL STATUS FROM 2 TO 1
3. INTERRUPT AND SYSTEM-TIMER
4. SPI (Serial Peripheral Interface)
5. I2C DRIVER
6. MAILBOX AND VIDEO VIA HDMI(WORK IN PROGRESS)
7. DMA (WORK IN PROGRESS)
8. PING-PONG GAME (TO BE DONE)

HOW TO START ON THIS PROJECT :
1. Clone the repository in your computer
2. Use command
```bash
     make clean && make
     ```
3. REQUIREMENTS : A MICRO SD CARD , and using RPI IMAGER flah the raspberry pi 64 os on it.
4. AFTER MAKE A 'kernel8.img' will be generated copy this and the 'config.txt' files in sd card and you are ready to start on this project.

HAPPY CODING !!!!!