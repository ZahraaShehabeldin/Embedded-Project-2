/*
 * mylibrary.h
 *
 *  Created on: Feb 7, 2020
 *      Author: Viktor Vano
 */

#ifndef INC_MYLIBRARY_H_
#define INC_MYLIBRARY_H_

#include "main.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

extern char buffer[50];

extern char BluetoothMsg[50];
extern uint8_t timer_count, buffer_index;
extern UART_HandleTypeDef huart1,huart2 ;

uint8_t string_compare(char array1[], char array2[], uint16_t length);
void Message_handler();

#endif /* INC_MYLIBRARY_H_ */
