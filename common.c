#include <common.h>

void memcpy(void *dst, const void *src, unsigned int size) {
	unsigned char *d = (unsigned char *)dst;
	unsigned char *s = (unsigned char *)src;
	for (; size > 0; size--)
		*d++ = *s++;
}
