/**
 * @file CircBuf.c
 * @author Ian Ress
 * \brief Circular buffer for USB buffer.
 * @date 2023-02-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "CircBuf.h"

/**
 * \brief Writes data to the circular buffer if there's space. Increments the head accordingly.
 * 
 * \param cb pointer to circbuf_t struct.
 * \param data the data to write.
 * 
 * \return 0 if the write failed (buffer full). 0 if write successful.
 * 
 */
uint8_t circbuf_write(circbuf_t * const cb, uint8_t data) {
    uint16_t next;
    next = cb->head + 1;

    if (next >= cb->maxlen) {
        next = 0;
    }

    if (next == cb->tail) { /* Buffer full. Don't overwrite data. */
        return 0;
    }

    cb->buf[cb->head] = data;
    cb->head = next;
    return 1;
}

/**
 * \brief Reads data to the circular buffer if there's data available. 
 * Increments the tail accordingly.
 * 
 * \param cb pointer to circbuf_t struct.
 * \param data the data to read.
 * 
 * \return 0 if the buffer is empty. 1 on successful read.
 * 
 */
uint8_t circbuf_read(circbuf_t * const cb, uint8_t * data) {
    uint16_t next;

    if (cb->head == cb->tail) { /* Buffer empty. */
        return 0;
    }

    next = cb->tail + 1;
    if (next >= cb->maxlen) {
        next = 0;
    }

    *data = cb->buf[cb->tail];
    cb->tail = next;
    return 1;
}
