INTRODUCTION
This blog has been created with the main intention of documenting my progress, notes, and learnings throughout the Eklavya project. The project is named NovaPi and focuses on developing a bare-metal operating system for the Raspberry Pi, complete with HDMI support and a simple Pong game built from the ground up. Specifically, we are working with the Raspberry Pi 4B model. The notes will be organized according to the tasks assigned during different stages of the project. Kindly disregard any grammatical or spelling mistakes you might come across.

PROJECT DESCRIPTION
The goal of this project is to build a bare-metal OS along with a hardware abstraction layer tailored for the Raspberry Pi 4B. The operating system will support essential functionalities such as communication protocols, interrupt handling, and HDMI output. Once these foundations are in place, the ultimate objective is to develop a basic Pong game that runs using the HDMI capabilities provided by our custom kernel.

TASK 1: Building a Kernel Image and Implementing Mini-UART Output
Let’s begin with a simple explanation of this task. I’ll describe the core concepts in an easy-to-understand way and use plain language throughout.

Kernel: This is the heart of any operating system. It connects the software with the hardware, essentially managing all operations—like starting applications or handling files.

Kernel Image: A compiled binary version of the kernel, ready to be loaded into memory and executed by the processor. It's what the system boots with.

Bare-Metal OS: Software that operates directly on the hardware without relying on an underlying OS layer.

In this task, we aim to create a kernel image for the Raspberry Pi that uses the mini-UART interface to output a basic message. This message is the classic "Hello World"—a standard first program in most learning journeys.

For reference, I used the GitHub repository raspberry-pi-os. The content in that repository is split into lessons, and my task aligns with Lesson 1.1: Introducing RPi OS / bare-metal “Hello, World!”. However, the provided code targets the Raspberry Pi 3B, so a few adjustments are needed for compatibility with Raspberry Pi 4B. These changes are minimal and will be discussed in detail later.

Since I initially copied the code from that repository, my main goal for this task was to thoroughly understand it and run it using QEMU, a virtual emulator for hardware platforms. As QEMU does not currently support Raspberry Pi 4B, I executed the code for the 3B model instead, and it worked successfully.

You can find my updated code in the moksh branch of the NovaPi repository. The code is primarily written in C and ARM assembly, reflecting the ARMv8 architecture used by the Raspberry Pi's processor.



Task 2:


SPI Overview
SPI (Serial Peripheral Interface) is a 3-wire synchronous serial protocol used for high-speed communication between a master and one or more slaves.

Wire roles:

MOSI: Master Out Slave In

MISO: Master In Slave Out

SCLK: Serial Clock

CS: Chip Select (active low by default)

Modes supported:

Standard SPI (3-wire)

Bidirectional SPI (2-wire, single data line)

LoSSI (Low-Speed Serial Interface) — similar to SPI but with 9-bit command/data.

 SPI Modes
1. Standard SPI Master Mode
Uses MOSI, MISO, SCLK lines.

Data is exchanged one byte at a time.

Configurable clock polarity (CPOL) and phase (CPHA).

2. Bidirectional SPI Mode
Uses a single bidirectional data line (MIMO).

Set SPI_REN bit (Read Enable) to switch from writing to reading.

For reads, write dummy data to trigger a read cycle.

3. LoSSI Mode
9-bit transfers: 1 bit for command/data flag + 8-bit payload.

MSB = 0 → Command

MSB = 1 → Parameter

Supports special read commands:

Byte Read: 0x0a – 0x0f, 0xda – 0xdc

24-bit Read: 0x04

32-bit Read: 0x09

 Important Registers and Bits
 CS Register (Control/Status) @ Offset 0x00
TA (bit 7): Transfer Active → Set to start transmission

DONE (bit 16): Set when transfer finishes

TXD / RXD: TX FIFO has space / RX FIFO has data

CSPOL, CSPOL0–2: Chip select polarity (active low = 0)

CPOL / CPHA: Clock polarity/phase

DMAEN: Enable DMA operation

LEN: Enable LoSSI mode

REN: Enable Read in bidirectional mode

CS [1:0]: Select slave (0, 1, 2)

 FIFO Register @ Offset 0x04
Write to send data (TX FIFO), Read to receive (RX FIFO)

In DMA: first write can configure SPIDLEN and control bits

 CLK Register @ Offset 0x08
CDIV (15:0): Clock Divider

SCLK = Core Clock / CDIV

Must be even. 0 = divide by 65536.

 DLEN Register @ Offset 0x0c
LEN (15:0): Number of bytes to transfer (used in DMA only)

 LTOH Register @ Offset 0x10
TOH (3:0): Output hold delay (LoSSI only)

 DC Register @ Offset 0x14
Controls DMA request/panic thresholds for FIFO servicing

 Software Operation Modes
Polled Mode
Set control bits: CS, CPOL, CPHA, then set TA = 1

Poll TXD to write & RXD to read

Wait for DONE = 1

Clear TA = 0

Interrupt Mode
Set INTR (interrupt on RXR), INTD (on DONE)

Set TA = 1

On interrupt:

If DONE is set, write or finish

If RXR is set, read FIFO, then continue writing

DMA Mode
Set DMAEN, ADCS (optional auto chip select)

Use two DMA channels:

One for TX (write to FIFO)

One for RX (read from FIFO)

First TX write: [TransferLength << 16] | [control bits]

Activate both DMA channels

On RX DMA interrupt, transfer is complete

 SPI Behavior Notes
SPI always sends and receives simultaneously—even if one side’s data is "junk".

Clock is only active during byte transfers.

In DMA mode, CS lines assert/de-assert automatically unless controlled manually:

Assert: ≥3 core clocks before transfer

De-assert: ≥1 clock after last clock pulse

