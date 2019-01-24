# Questions

## What's `stdint.h`?

Defines standardised fixed width types for integers that can be used.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

So that we can be completely certain about the number of bytes that our integer takes up and also know exactly the maximum and minimum values we can store.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

1 byte, 4 bytes, 4 bytes, 2 bytes

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

Must be "BM" in ASCII, 0x424d in hex

## What's the difference between `bfSize` and `biSize`?

bfSize is the size in bytes of the bitmap file.
biSize is the size in bytes of the BITMAPINFOHEADER

## What does it mean if `biHeight` is negative?

It indicates the place of the origin pixel, if biHeight is negative the origin is in the upper left and the bitmap is a top down DIB.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

Read issues from the disk, disk full for writing or other catastrophic things happening.

## Why is the third argument to `fread` always `1` in our code? (For example, see lines 40, 44, and 75.)

Because we are always reading 1 element at a time.

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

1

## What does `fseek` do?

Allows to move the file pointer forward/back by a desired offset.

## What is `SEEK_CUR`?

The current position of the file pointer.