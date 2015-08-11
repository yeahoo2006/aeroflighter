/*
 * File:   usart.h
 * Author: Administrator
 *
 * Created on 2015?3?15?, ??8:00
 */
extern void DRV_usart_init(void);
extern boolean DRV_usart_read_cmd(uint8_t *data, uint8_t buf_len);
