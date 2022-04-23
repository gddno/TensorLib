#pragma once
#include <Arduino.h>

void action();
void cc_init();
void cc_send_to_pc(uint16_t address, unsigned char* data);
void cc_send_uint32(uint16_t address, uint32_t data);
void cc_send_float(uint16_t address,float data);
