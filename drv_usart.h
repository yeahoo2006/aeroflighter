/* 
 * File:   drv_usart.h
 * Author: Administrator
 *
 * Created on 2015?3?11?, ??9:22
 */

#ifndef DRV_USART_H
#define	DRV_USART_H
extern void DRV_usart_putchar(uint8_t c);
extern void DRV_usart_tx(uint8_t msg);
extern void DRV_usart_rx(uint8_t data);
extern void DRV_usart_init(void);
extern boolean DRV_usart_read_cmd(uint8_t *data, uint8_t buf_len);
#endif	/* DRV_USART_H */

