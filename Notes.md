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
















DMA Controller 
1. Overview
The BCM2711 (used in Raspberry Pi 4B) has multiple DMA engines for high-speed data movement without CPU involvement.

Transfers can be:

Memory ↔ Memory

Memory ↔ Peripheral FIFOs

Supports:

AXI bus bursts

Peripheral DREQ pacing

2D stride mode (graphics-friendly)

Chained control blocks

Interrupts on completion or error.

In Circle, DMA is used in many drivers (SPI, USB, networking, etc.), with CPU data cache considerations for performance and correctness.

2. DMA Buffer Requirements (Circle)
Cache Coherency Issue: DMA bypasses CPU caches → stale or dirty data can cause corruption if buffers aren’t properly flushed/invalidated.

Cache Line Size:

Pi 1 / Zero: 32 B

Pi 2–4: 64 B (important for Pi 4B)

Alignment Rules:

Buffer base address must be aligned to cache line size.

Buffer size must be a multiple of cache line size.

Misalignment can corrupt nearby memory.

When Required:

Any buffer passed to DMA-related Circle methods (e.g., CDMAChannel, CSPIMasterDMA, low-level USB transfers, network device direct frame access, mass storage).

Not required for CSocket networking or SD card driver (no DMA).

Defining a DMA Buffer:

Stack: Use

c
Copy
Edit
DMA_BUFFER(unsigned char, MyBuffer, 100);
→ expands to __attribute__((aligned(64))) with padding.

Heap: Normal new or malloc() is already cache-aligned.

Static: Use DMA_BUFFER() macro.

3. DMA Controller Registers (per Channel)
(BCM2711 Peripheral Manual)

CS – Control & Status: Start/Stop, Reset, Interrupt, Error flags.

CONBLK_AD – Physical address of current control block.

TI – Transfer Information:

Peripheral DREQ mapping

Source/Destination increment

Burst length, pacing, 2D stride enable.

SOURCE_AD – Source address.

DEST_AD – Destination address.

TXFR_LEN – Transfer length.

STRIDE – Stride values for 2D transfers.

NEXTCONBK – Pointer to next control block (for chaining).

Debug registers.

4. Control Block Structure
A 32-byte block in memory describing one DMA transfer:

Transfer Information (TI)

Source Address

Destination Address

Transfer Length

Stride (2D mode)

Next Control Block address

Reserved/padding
DMA follows the chain for continuous transfers.

5. Peripheral DREQ Signals
Hardware signals that pace DMA to peripheral readiness.

Examples (BCM2711):

DREQ 6 – SPI0 TX

DREQ 7 – SPI0 RX

DREQ 10 – PWM

DREQ 18 – PCM TX

Prevents FIFO underflow/overflow.

6. AXI Bursts
DMA can group sequential transfers into bursts → improves throughput.

Burst length programmable in TI.

7. Error Handling
Errors flagged in CS:

Read error – bad source access.

Write error – bad destination access.

Halts DMA; requires:

Clear error bits

Possibly reset channel before restart.

8. DMA Variants
Full DMA:

All modes: 2D, bursts, high bandwidth.

DMA Lite:

No 2D mode, smaller transfers, simpler hardware.

DMA4 Engines (BCM2711-specific):

Improved AXI performance

Extended addressing (>4 GB memory)

More channels.

9. Raspberry Pi 4B Specific Differences
Uses BCM2711 DMA architecture with AXI-based bus, higher throughput.

Cache line size: 64 B (affects alignment requirements in Circle).

More DMA channels available than earlier Pis.

Memory map addresses differ slightly from Pi 3 (due to ARMv8 LPAE changes).

DMA4 engines allow access to RAM above 4 GB if using Pi 4 with >4 GB RAM.

Higher system bus speed → burst settings can be more aggressive without saturating peripherals.

10. Practical Programming Tips (Bare-Metal / Circle)
Always cache-align buffers for DMA.

Place control blocks in uncached memory or flush cache before start.

Use NEXTCONBK to chain transfers for large or repeated operations.

Use DREQ pacing for streaming peripherals (UART, SPI, I²S, etc.).

In HDMI/framebuffer work → 2D stride mode saves CPU bandwidth.

Always reset DMA channel and clear interrupts before reuse.

