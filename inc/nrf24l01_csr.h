#ifndef INC_NRF24L01_CSR_H_
#define INC_NRF24L01_CSR_H_

// CONFIG Register Masks
#define MASK_RX_DR_MASK      0x40  // 0b01000000
#define MASK_TX_DS_MASK      0x20  // 0b00100000
#define MASK_MAX_RT_MASK     0x10  // 0b00010000
#define EN_CRC_MASK          0x08  // 0b00001000
#define CRCO_MASK            0x04  // 0b00000100
#define PWR_UP_MASK          0x02  // 0b00000010
#define PRIM_RX_MASK         0x01  // 0b00000001

// EN_AA Register Masks (Enable Auto Acknowledgment)
#define ENAA_P5_MASK         0x20  // 0b00100000
#define ENAA_P4_MASK         0x10  // 0b00010000
#define ENAA_P3_MASK         0x08  // 0b00001000
#define ENAA_P2_MASK         0x04  // 0b00000100
#define ENAA_P1_MASK         0x02  // 0b00000010
#define ENAA_P0_MASK         0x01  // 0b00000001

// EN_RXADDR Register Masks (Enable RX Addresses)
#define ERX_P5_MASK          0x20  // 0b00100000
#define ERX_P4_MASK          0x10  // 0b00010000
#define ERX_P3_MASK          0x08  // 0b00001000
#define ERX_P2_MASK          0x04  // 0b00000100
#define ERX_P1_MASK          0x02  // 0b00000010
#define ERX_P0_MASK          0x01  // 0b00000001

// SETUP_AW Register Masks (Address Width)
#define AW_MASK              0x03  // 0b00000011 (2 bits)

// SETUP_RETR Register Masks (Automatic Retransmission)
#define ARD_MASK             0xF0  // 0b11110000 (4 bits)
#define ARC_MASK             0x0F  // 0b00001111 (4 bits)

// RF_CH Register Masks (RF Channel)
#define RF_CH_MASK           0x7F  // 0b01111111 (7 bits)

// RF_SETUP Register Masks (RF Setup)
#define CONT_WAVE_MASK       0x80  // 0b10000000
#define RF_DR_LOW_MASK       0x20  // 0b00100000
#define PLL_LOCK_MASK        0x10  // 0b00010000
#define RF_DR_HIGH_MASK      0x08  // 0b00001000
#define RF_PWR_MASK          0x06  // 0b00000110 (2 bits)

// STATUS Register Masks
#define RX_DR_MASK           0x40  // 0b01000000
#define TX_DS_MASK           0x20  // 0b00100000
#define MAX_RT_MASK          0x10  // 0b00010000
#define RX_P_NO_MASK         0x0E  // 0b00001110 (3 bits)
#define TX_FULL_MASK         0x01  // 0b00000001

// OBSERVE_TX Register Masks
#define PLOS_CNT_MASK        0xF0  // 0b11110000 (4 bits)
#define ARC_CNT_MASK         0x0F  // 0b00001111 (4 bits)

// FIFO_STATUS Register Masks
#define TX_REUSE_MASK        0x40  // 0b01000000
#define FIFO_FULL_MASK       0x20  // 0b00100000
#define TX_EMPTY_MASK        0x10  // 0b00010000
#define RX_FULL_MASK         0x02  // 0b00000010
#define RX_EMPTY_MASK        0x01  // 0b00000001

// DYNPD Register Masks (Dynamic Payload)
#define DPL_P5_MASK          0x20  // 0b00100000
#define DPL_P4_MASK          0x10  // 0b00010000
#define DPL_P3_MASK          0x08  // 0b00001000
#define DPL_P2_MASK          0x04  // 0b00000100
#define DPL_P1_MASK          0x02  // 0b00000010
#define DPL_P0_MASK          0x01  // 0b00000001

// FEATURE Register Masks
#define EN_DPL_MASK          0x04  // 0b00000100
#define EN_ACK_PAY_MASK      0x02  // 0b00000010
#define EN_DYN_ACK_MASK      0x01  // 0b00000001



// CONFIG Register Masks
#define MASK_RX_DR  6  // Mask interrupt caused by RX_DR
#define MASK_TX_DS  5  // Mask interrupt caused by TX_DS
#define MASK_MAX_RT 4  // Mask interrupt caused by MAX_RT
#define EN_CRC      3  // Enable CRC
#define CRCO        2  // CRC encoding scheme (0: 1 byte, 1: 2 bytes)
#define PWR_UP      1  // Power up/down
#define PRIM_RX     0  // RX/TX mode (0: TX, 1: RX)

// EN_AA Register Masks (Enable Auto Acknowledgment)
#define ENAA_P5     5  // Enable auto acknowledgment for data pipe 5
#define ENAA_P4     4  // Enable auto acknowledgment for data pipe 4
#define ENAA_P3     3  // Enable auto acknowledgment for data pipe 3
#define ENAA_P2     2  // Enable auto acknowledgment for data pipe 2
#define ENAA_P1     1  // Enable auto acknowledgment for data pipe 1
#define ENAA_P0     0  // Enable auto acknowledgment for data pipe 0

// EN_RXADDR Register Masks (Enable RX Addresses)
#define ERX_P5      5  // Enable data pipe 5
#define ERX_P4      4  // Enable data pipe 4
#define ERX_P3      3  // Enable data pipe 3
#define ERX_P2      2  // Enable data pipe 2
#define ERX_P1      1  // Enable data pipe 1
#define ERX_P0      0  // Enable data pipe 0

// SETUP_AW Register Masks (Address Width)
#define AW          0  // Address width (00: illegal, 01: 3 bytes, 10: 4 bytes, 11: 5 bytes)

// SETUP_RETR Register Masks (Automatic Retransmission)
#define ARD         4  // Auto retransmit delay (0000: 250us, 1111: 4000us)
#define ARC         0  // Auto retransmit count (0000: disable, 1111: 15 retries)

// RF_CH Register Masks (RF Channel)
#define RF_CH       0  // RF channel frequency (0-125)

// RF_SETUP Register Masks (RF Setup)
#define CONT_WAVE   7  // Continuous carrier transmit
#define RF_DR_LOW   5  // Data rate low bit
#define PLL_LOCK    4  // PLL lock (read-only)
#define RF_DR_HIGH  3  // Data rate high bit
#define RF_PWR      1  // RF output power (00: -18dBm, 01: -12dBm, 10: -6dBm, 11: 0dBm)

// STATUS Register Masks
#define RX_DR       6  // Data ready RX FIFO interrupt
#define TX_DS       5  // Data sent TX FIFO interrupt
#define MAX_RT      4  // Maximum retries interrupt
#define RX_P_NO     1  // Data pipe number for the payload available in RX FIFO
#define TX_FULL     0  // TX FIFO full flag

// OBSERVE_TX Register Masks
#define PLOS_CNT    4  // Packet loss counter
#define ARC_CNT     0  // Retransmit counter

// FIFO_STATUS Register Masks
#define TX_REUSE    6  // Reuse last transmitted payload
#define FIFO_FULL   5  // TX FIFO full
#define TX_EMPTY    4  // TX FIFO empty
#define RX_FULL     1  // RX FIFO full
#define RX_EMPTY    0  // RX FIFO empty

// DYNPD Register Masks (Dynamic Payload)
#define DPL_P5      5  // Enable dynamic payload for data pipe 5
#define DPL_P4      4  // Enable dynamic payload for data pipe 4
#define DPL_P3      3  // Enable dynamic payload for data pipe 3
#define DPL_P2      2  // Enable dynamic payload for data pipe 2
#define DPL_P1      1  // Enable dynamic payload for data pipe 1
#define DPL_P0      0  // Enable dynamic payload for data pipe 0

// FEATURE Register Masks
#define EN_DPL      2  // Enable dynamic payload length
#define EN_ACK_PAY  1  // Enable payload with ACK
#define EN_DYN_ACK  0  // Enable W_TX_PAYLOAD_NOACK command



#endif /* INC_NRF24L01_CSR_H_ */
