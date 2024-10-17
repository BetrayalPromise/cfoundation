#ifndef __NUMBER_H__
#define __NUMBER_H__

typedef enum format {
    original,   // 原码
    inverse,    // 反码
    complement, // 补码
} format_t;

void char2binary(char value, format_t fmt);
void short2binary(short value, format_t fmt);
void int2binary(int value, format_t fmt);
void long2binary(long value, format_t fmt);
void uchar2binary(unsigned char value, format_t fmt);
void ushort2binary(unsigned short value, format_t fmt);
void uint2binary(unsigned int value, format_t fmt);
void ulong2binary(unsigned long value, format_t fmt);
void float2binary(float value, format_t fmt);
void double2binary(double value, format_t fmt);

void showcolor();


#endif