/*
 *  nrf24l01_plus.c
 *
 *  Created on: 2021. 7. 20.
 *      Author: mokhwasomssi
 * 
 */


#include "nrf24l01p.h"
#include <stdio.h>

static uint8_t nrf24l01p_addr_width;

static void cs_high()
{
    HAL_GPIO_WritePin(NRF24L01P_SPI_CS_PIN_PORT, NRF24L01P_SPI_CS_PIN_NUMBER, GPIO_PIN_SET);
}

static void cs_low()
{
    HAL_GPIO_WritePin(NRF24L01P_SPI_CS_PIN_PORT, NRF24L01P_SPI_CS_PIN_NUMBER, GPIO_PIN_RESET);
}

static void ce_high()
{
    HAL_GPIO_WritePin(NRF24L01P_CE_PIN_PORT, NRF24L01P_CE_PIN_NUMBER, GPIO_PIN_SET);
}

static void ce_low()
{
    HAL_GPIO_WritePin(NRF24L01P_CE_PIN_PORT, NRF24L01P_CE_PIN_NUMBER, GPIO_PIN_RESET);
}

static uint8_t read_register(uint8_t reg)
{
    uint8_t command = NRF24L01P_CMD_R_REGISTER | reg;
    uint8_t status;
    uint8_t read_val;

    cs_low();
    HAL_SPI_TransmitReceive(NRF24L01P_SPI, &command, &status, 1, 2000);
    HAL_SPI_Receive(NRF24L01P_SPI, &read_val, 1, 2000);
    cs_high();

    return read_val;
}

static uint8_t write_register(uint8_t reg, uint8_t value)
{
    uint8_t command = NRF24L01P_CMD_W_REGISTER | reg;
    uint8_t status;
    uint8_t write_val = value;

    cs_low();
    HAL_SPI_TransmitReceive(NRF24L01P_SPI, &command, &status, 1, 2000);
    HAL_SPI_Transmit(NRF24L01P_SPI, &write_val, 1, 2000);
    cs_high();

    return write_val;
}


/**************************************************************************************/

void nrf24l01p_write_bytes(uint8_t reg, uint8_t* buf, uint8_t size)
{
    uint8_t command = NRF24L01P_CMD_W_REGISTER | reg;
    uint8_t status;

    cs_low();
    HAL_SPI_TransmitReceive(NRF24L01P_SPI, &command, &status, 1, 2000);
    HAL_SPI_Transmit(NRF24L01P_SPI, buf, size, 2000);
    cs_high();
}

uint8_t nrf24l01p_read_bytes(uint8_t reg, uint8_t* buf, uint8_t size)
{
    uint8_t command = NRF24L01P_CMD_R_REGISTER | reg;
    uint8_t status;

    cs_low();
    HAL_SPI_TransmitReceive(NRF24L01P_SPI, &command, &status, 1, 2000);
    HAL_SPI_Receive(NRF24L01P_SPI, buf, size, 2000);
    cs_high();

    return status;
}


/**************************************************************************************/



/* nRF24L01+ Main Functions */
void nrf24l01p_rx_init(channel channel_no, air_data_rate bps)
{
    nrf24l01p_reset();

    nrf24l01p_prx_mode();
    nrf24l01p_power_up();

    nrf24l01p_rx_set_payload_widths( NRF24L01P_REG_RX_PW_P0, NRF24L01P_PAYLOAD_LENGTH);
    nrf24l01p_rx_set_payload_widths( NRF24L01P_REG_RX_PW_P1, NRF24L01P_PAYLOAD_LENGTH);

    nrf24l01p_set_rf_channel(channel_no);
    nrf24l01p_set_rf_air_data_rate(bps);
    nrf24l01p_set_rf_tx_output_power(_0dBm);

    nrf24l01p_set_crc_length(1);
    nrf24l01p_set_address_widths(5);

    nrf24l01p_auto_retransmit_count(3);
    nrf24l01p_auto_retransmit_delay(250);
    
    ce_high();
}

void nrf24l01p_start_listening(nrf_rx_pipe_t pipe_no, uint8_t* address)
{
	// read RX pipe Enable reg
	uint8_t reg_val = read_register(NRF24L01P_REG_EN_RXADDR);
	reg_val |= (0x01U << pipe_no);
	write_register(NRF24L01P_REG_EN_RXADDR, reg_val); // Enable data pipe

	//write address
	uint8_t pipe_reg_addr = NRF24L01P_REG_RX_ADDR_P0 + pipe_no;

	if(pipe_no <= nrf_rx_pipe_1 )
	{
		nrf24l01p_write_bytes( pipe_reg_addr ,address, nrf24l01p_addr_width);
	}
	else //if pipe no. is 2-5 , get only last byte
	{
		uint8_t LSB = address[nrf24l01p_addr_width-1];
		write_register( pipe_reg_addr ,LSB);
	}


}


void nrf24l01p_tx_init(channel channel_no, air_data_rate bps)
{
    nrf24l01p_reset();

    nrf24l01p_ptx_mode();
    nrf24l01p_power_up();

    nrf24l01p_set_rf_channel(channel_no);
    nrf24l01p_set_rf_air_data_rate(bps);
    nrf24l01p_set_rf_tx_output_power(_0dBm);

    write_register(NRF24L01P_REG_EN_AA, 0x01);  // Enable Enhanced ShockBurst on pipe 0

    // Enable RX pipe 0 for receiving acknowledgments
    write_register(NRF24L01P_REG_EN_RXADDR, 0x01); // Enable data pipe 0

    // Set RX payload width for pipe 0 (same as TX payload size)
    write_register(NRF24L01P_REG_RX_PW_P0, 32); // Example: 32-byte payload

    nrf24l01p_set_crc_length(1);
    nrf24l01p_set_address_widths(5);

    nrf24l01p_auto_retransmit_count(3);
    nrf24l01p_auto_retransmit_delay(250);

    ce_high();
}

void nrf24l01p_rx_receive(nrf_rx_packet_t* nrf_rx_packet)
{
    nrf_rx_packet->pipe_no = (NRF24L01P_PIPE_NO_MASK & read_register(NRF24L01P_REG_STATUS)) >> 1;
    nrf24l01p_read_rx_fifo(nrf_rx_packet->rx_data);
    nrf24l01p_clear_rx_dr();

}

void nrf24l01p_tx_transmit(uint8_t* tx_payload)
{
    nrf24l01p_write_tx_fifo(tx_payload);
}

void nrf24l01p_tx_irq()
{
    uint8_t tx_ds = nrf24l01p_get_status();
    tx_ds &= 0x20;

    if(tx_ds)
    {   
        // TX_DS
        nrf24l01p_clear_tx_ds();
    }

    else
    {
        // MAX_RT
        nrf24l01p_clear_max_rt();
    }
}

/* nRF24L01+ Sub Functions */
void nrf24l01p_reset()
{
    // Reset pins
    cs_high();
    ce_low();

    // Reset registers
    write_register(NRF24L01P_REG_CONFIG, 0x08);
    write_register(NRF24L01P_REG_EN_AA, 0x3F);
    write_register(NRF24L01P_REG_EN_RXADDR, 0x03);
    write_register(NRF24L01P_REG_SETUP_AW, 0x03);
    write_register(NRF24L01P_REG_SETUP_RETR, 0x03);
    write_register(NRF24L01P_REG_RF_CH, 0x02);
    write_register(NRF24L01P_REG_RF_SETUP, 0x07);
    write_register(NRF24L01P_REG_STATUS, 0x7E);
    write_register(NRF24L01P_REG_RX_PW_P0, 0x00);
    write_register(NRF24L01P_REG_RX_PW_P0, 0x00);
    write_register(NRF24L01P_REG_RX_PW_P1, 0x00);
    write_register(NRF24L01P_REG_RX_PW_P2, 0x00);
    write_register(NRF24L01P_REG_RX_PW_P3, 0x00);
    write_register(NRF24L01P_REG_RX_PW_P4, 0x00);
    write_register(NRF24L01P_REG_RX_PW_P5, 0x00);
    write_register(NRF24L01P_REG_FIFO_STATUS, 0x11);
    write_register(NRF24L01P_REG_DYNPD, 0x00);
    write_register(NRF24L01P_REG_FEATURE, 0x00);

    // Reset FIFO
    nrf24l01p_flush_rx_fifo();
    nrf24l01p_flush_tx_fifo();
}

void nrf24l01p_prx_mode()
{
    uint8_t new_config = read_register(NRF24L01P_REG_CONFIG);
    new_config |= 1 << 0;

    write_register(NRF24L01P_REG_CONFIG, new_config);
}

void nrf24l01p_ptx_mode()
{
    uint8_t new_config = read_register(NRF24L01P_REG_CONFIG);
    new_config &= 0xFE;

    write_register(NRF24L01P_REG_CONFIG, new_config);
}

uint8_t nrf24l01p_read_rx_fifo(uint8_t* rx_payload)
{
    uint8_t command = NRF24L01P_CMD_R_RX_PAYLOAD;
    uint8_t status;

    cs_low();
    HAL_SPI_TransmitReceive(NRF24L01P_SPI, &command, &status, 1, 2000);
    HAL_SPI_Receive(NRF24L01P_SPI, rx_payload, NRF24L01P_PAYLOAD_LENGTH, 2000);
    cs_high();

    return status;
}

uint8_t nrf24l01p_write_tx_fifo(uint8_t* tx_payload)
{
    uint8_t command = NRF24L01P_CMD_W_TX_PAYLOAD;
    uint8_t status;

    cs_low();
    HAL_SPI_TransmitReceive(NRF24L01P_SPI, &command, &status, 1, 2000);
    HAL_SPI_Transmit(NRF24L01P_SPI, tx_payload, NRF24L01P_PAYLOAD_LENGTH, 2000);
    cs_high(); 

    return status;
}

void nrf24l01p_flush_rx_fifo()
{
    uint8_t command = NRF24L01P_CMD_FLUSH_RX;
    uint8_t status;

    cs_low();
    HAL_SPI_TransmitReceive(NRF24L01P_SPI, &command, &status, 1, 2000);
    cs_high();
}

void nrf24l01p_flush_tx_fifo()
{
    uint8_t command = NRF24L01P_CMD_FLUSH_TX;
    uint8_t status;

    cs_low();
    HAL_SPI_TransmitReceive(NRF24L01P_SPI, &command, &status, 1, 2000);
    cs_high();
}

uint8_t nrf24l01p_get_status()
{
    uint8_t command = NRF24L01P_CMD_NOP;
    uint8_t status;

    cs_low();
    HAL_SPI_TransmitReceive(NRF24L01P_SPI, &command, &status, 1, 2000);
    cs_high(); 

    return status;
}

uint8_t nrf24l01p_get_fifo_status()
{
    return read_register(NRF24L01P_REG_FIFO_STATUS);
}

void nrf24l01p_rx_set_payload_widths(pipe_t pipe,widths bytes)
{
    write_register(pipe, bytes);
}

void nrf24l01p_clear_rx_dr()
{
    uint8_t new_status = nrf24l01p_get_status();
    new_status |= 0x40;

    write_register(NRF24L01P_REG_STATUS, new_status);
}

void nrf24l01p_clear_tx_ds()
{
    uint8_t new_status = nrf24l01p_get_status();
    new_status |= 0x20;

    write_register(NRF24L01P_REG_STATUS, new_status);     
}

void nrf24l01p_clear_max_rt()
{
    uint8_t new_status = nrf24l01p_get_status();
    new_status |= 0x10;

    write_register(NRF24L01P_REG_STATUS, new_status); 
}

void nrf24l01p_power_up()
{
    uint8_t new_config = read_register(NRF24L01P_REG_CONFIG);
    new_config |= 1 << 1;

    write_register(NRF24L01P_REG_CONFIG, new_config);
}

void nrf24l01p_power_down()
{
    uint8_t new_config = read_register(NRF24L01P_REG_CONFIG);
    new_config &= 0xFD;

    write_register(NRF24L01P_REG_CONFIG, new_config);
}

void nrf24l01p_set_crc_length(length bytes)
{
    uint8_t new_config = read_register(NRF24L01P_REG_CONFIG);
    
    switch(bytes)
    {
        // CRCO bit in CONFIG resiger set 0
        case 1:
            new_config &= 0xFB;
            break;
        // CRCO bit in CONFIG resiger set 1
        case 2:
            new_config |= 1 << 2;
            break;
    }

    write_register(NRF24L01P_REG_CONFIG, new_config);
}

void nrf24l01p_set_address_widths(widths bytes)
{
	nrf24l01p_addr_width = bytes;
    write_register(NRF24L01P_REG_SETUP_AW, bytes - 2);
}



void nrf24l01p_open_Writing_Pipe(uint8_t* address)
{

	// Enable RX pipe 0 for receiving acknowledgments
	uint8_t reg_val = read_register(NRF24L01P_REG_EN_RXADDR);
	reg_val |= 0x01;
	write_register(NRF24L01P_REG_EN_RXADDR, reg_val); // Enable data pipe 0

	//Enable acknowledgments
	reg_val = read_register(NRF24L01P_REG_EN_AA);
	reg_val |= 0x3F;   //enable for all pipes
	write_register(NRF24L01P_REG_EN_AA, reg_val); 

    //set address to rx pipe 0 to receive the ack
	nrf24l01p_write_bytes( NRF24L01P_REG_RX_ADDR_P0 ,address, nrf24l01p_addr_width);

	//set address to tx pipe
	nrf24l01p_write_bytes( NRF24L01P_REG_TX_ADDR ,address, nrf24l01p_addr_width);
}



void nrf24l01p_auto_retransmit_count(count cnt)
{
    uint8_t new_setup_retr = read_register(NRF24L01P_REG_SETUP_RETR);
    
    // Reset ARC register 0
    new_setup_retr |= 0xF0;
    new_setup_retr |= cnt;
    write_register(NRF24L01P_REG_SETUP_RETR, new_setup_retr);
}

void nrf24l01p_auto_retransmit_delay(delay us)
{
    uint8_t new_setup_retr = read_register(NRF24L01P_REG_SETUP_RETR);

    // Reset ARD register 0
    new_setup_retr |= 0x0F;
    new_setup_retr |= ((us / 250) - 1) << 4;
    write_register(NRF24L01P_REG_SETUP_RETR, new_setup_retr);
}

void nrf24l01p_set_rf_channel(channel channel_no)
{
    write_register(NRF24L01P_REG_RF_CH, channel_no);
}

void nrf24l01p_set_rf_tx_output_power(output_power dBm)
{
    uint8_t new_rf_setup = read_register(NRF24L01P_REG_RF_SETUP) & 0xF9;
    new_rf_setup |= (dBm << 1);

    write_register(NRF24L01P_REG_RF_SETUP, new_rf_setup);
}

void nrf24l01p_set_rf_air_data_rate(air_data_rate bps)
{
    // Set value to 0
    uint8_t new_rf_setup = read_register(NRF24L01P_REG_RF_SETUP) & 0xD7;
    
    switch(bps)
    {
        case _1Mbps: 
            break;
        case _2Mbps: 
            new_rf_setup |= 1 << 3;
            break;
        case _250kbps:
            new_rf_setup |= 1 << 5;
            break;
    }
    write_register(NRF24L01P_REG_RF_SETUP, new_rf_setup);
}


void NRF24_WritePayload(uint8_t *data, uint8_t length) {
	cs_low();
    uint8_t cmd = NRF24L01P_CMD_W_TX_PAYLOAD;
    HAL_SPI_Transmit(NRF24L01P_SPI, &cmd, 1, HAL_MAX_DELAY);
    HAL_SPI_Transmit(NRF24L01P_SPI, data, length, HAL_MAX_DELAY);
    cs_high();
}


void NRF24_SetRXMode(void) {
    uint8_t config = read_register(NRF24L01P_REG_CONFIG);
    write_register(NRF24L01P_REG_CONFIG, config | 0x01); // Set PRX mode
    ce_high();
}

void NRF24_SetTXMode(void) {
    uint8_t config = read_register(NRF24L01P_REG_CONFIG);
    write_register(NRF24L01P_REG_CONFIG, config & ~0x01); // Clear PRX mode
    ce_low();
}

// Updated Transmit Function with Acknowledgment Read
bool NRF24_TransmitWithAck(uint8_t *data, uint8_t length) {
    NRF24_SetTXMode();
    NRF24_WritePayload(data, length);
    nrf24l01p_clear_tx_ds();
    nrf24l01p_clear_max_rt();
    // Pulse CE to initiate transmission
    ce_high();
    HAL_Delay(1); // Short delay
    ce_low();

    // Wait for transmission to complete
    uint32_t timeout = HAL_GetTick() + 100; // 100ms timeout
    uint8_t status;
    do {
        status = read_register(NRF24L01P_REG_STATUS);
        if (status & (NRF24_MASK_TX_DS | NRF24_MASK_MAX_RT)) {
            break;
        }
    } while (HAL_GetTick() < timeout);

    // Clear flags in the STATUS register
    write_register(NRF24L01P_REG_STATUS, NRF24_MASK_TX_DS | NRF24_MASK_MAX_RT);

    // Check if data was sent successfully or if max retransmits occurred
    if (status & NRF24_MASK_TX_DS) {
        return 1; // Acknowledgment received
    } else if (status & NRF24_MASK_MAX_RT) {
        write_register(NRF24L01P_CMD_FLUSH_TX, NRF24L01P_CMD_NOP); // Flush TX FIFO
        return 0; // Acknowledgment failed
    }

    return 0; // Transmission failed
}



void NRF24_PrintAllRegisters(void) {
    uint8_t value;

    printf("NRF24L01+ Register Values:\n");

    // Loop through all 25 registers (0x00 to 0x17 + STATUS)
    for (uint8_t reg = 0x00; reg <= 0x17; reg++) {
        value = read_register(reg);
        printf("Reg 0x%02X: 0x%02X\n", reg, value);
    }

    // Print additional status-related information
    printf("STATUS: 0x%02X\n", read_register(NRF24L01P_REG_STATUS));
    printf("RX_ADDR_P0: ");
    NRF24_PrintAddress(NRF24L01P_REG_RX_ADDR_P0);
    printf("RX_ADDR_P1: ");
    NRF24_PrintAddress(NRF24L01P_REG_RX_ADDR_P1);
    printf("TX_ADDR: ");
    NRF24_PrintAddress(NRF24L01P_REG_TX_ADDR);
    printf("FIFO_STATUS: 0x%02X\n", read_register(NRF24L01P_REG_FIFO_STATUS));
    printf("DYNPD: 0x%02X\n", read_register(NRF24L01P_REG_DYNPD));
    printf("FEATURE: 0x%02X\n", read_register(NRF24L01P_REG_FEATURE));
}

// Function to read a multi-byte register (e.g., addresses)
void NRF24_ReadMultiRegister(uint8_t reg, uint8_t *data, uint8_t length) {
	cs_low();
    uint8_t cmd = NRF24L01P_CMD_R_REGISTER | reg;
    HAL_SPI_Transmit(NRF24L01P_SPI, &cmd, 1, HAL_MAX_DELAY);
    HAL_SPI_Receive(NRF24L01P_SPI, data, length, HAL_MAX_DELAY);
    cs_high();
}


// Helper function to print multi-byte addresses (e.g., RX_ADDR_P0, TX_ADDR)
void NRF24_PrintAddress(uint8_t reg) {
    uint8_t address[5];
    NRF24_ReadMultiRegister(reg, address, 5);
    for (uint8_t i = 0; i < 5; i++) {
        printf("0x%02X ", address[i]);
    }
    printf("\n");
}




















