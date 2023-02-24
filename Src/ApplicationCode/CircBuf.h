/**
 * @file CircBuf.h
 * @author Ian Ress
 * \brief Circular buffer for USB buffer.
 * @date 2023-02-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef CIRCBUF_H
#define CIRCBUF_H

#include <stdint.h>

typedef struct {
    uint8_t * const buf;
    uint8_t head; /* write */
    uint8_t tail; /* read */
    const uint8_t maxlen; 
} circbuf_t;

uint8_t circbuf_write(circbuf_t * const cb, uint8_t data);
uint8_t circbuf_read(circbuf_t * const cb, uint8_t * data);

#endif /* CIRCBUF_H */
