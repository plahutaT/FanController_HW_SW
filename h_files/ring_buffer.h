/* 
 * File:   ring_buffer.h
 * Author: tilen
 *
 * Created on May 2, 2023, 3:03 PM
 */

#ifndef RING_BUFFER_H
#define	RING_BUFFER_H

#include <stdint.h>

typedef struct {
    uint8_t *buffer;
    uint8_t size;
    uint8_t head;
    uint8_t tail;

}ring_buffer; 

void ring_buffer_push(ring_buffer *rb, uint8_t value);
uint8_t ring_buffer_pop(ring_buffer *rb);
uint8_t ring_buffer_peek(const ring_buffer *rb);
uint8_t ring_buffer_full(const ring_buffer *rb);
uint8_t ring_buffer_empty(const ring_buffer *rb);


#endif	/* RING_BUFFER_H */

