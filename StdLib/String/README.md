# String

## Definition and Motivation

A string is a sequence of characters. A character is usually 1 byte long. C strings are terminated using a `'\0'` or a null character. All the standard C functions  depend on the strings being null-terminated. This can lead to slower code as a lot of unnecessary byte-by-byte traversal takes place.

This implementation is not null terminated; it is length prefixed. Consequently, it is safer and easier to use this version over the regular one. The length of the string can be extracted from the struct. In addition to that, there are several library functions to help perform string operations more easily.
