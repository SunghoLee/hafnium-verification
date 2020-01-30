/*
 * Copyright 2018 The Hafnium Authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "hf/arch/std.h"

void *memset(void *s, int c, size_t n)
{
	char *p = (char *)s;

	while (n--) {
		*p++ = c;
	}

	return s;
}

void *memcpy(void *dst, const void *src, size_t n)
{
	char *x = dst;
	const char *y = src;

	while (n--) {
		*x = *y;
		x++;
		y++;
	}

	return dst;
}

void *memmove(void *dst, const void *src, size_t n)
{
	char *x;
	const char *y;

	if (dst < src) {
		/*
		 * Clang analyzer doesn't like us calling unsafe memory
		 * functions, so make it ignore this while still knowing that
		 * the function returns.
		 */
#ifdef __clang_analyzer__
		return dst;
#else
		return memcpy(dst, src, n);
#endif
	}

	x = (char *)dst + n - 1;
	y = (const char *)src + n - 1;

	while (n--) {
		*x = *y;
		x--;
		y--;
	}

	return dst;
}

int memcmp(const void *a, const void *b, size_t n)
{
	const char *x = a;
	const char *y = b;

	while (n--) {
		if (*x != *y) {
			return *x - *y;
		}
		x++;
		y++;
	}

	return 0;
}

int strcmp(const char *a, const char *b)
{
	const char *x = a;
	const char *y = b;

	while (*x != 0 && *y != 0) {
		if (*x != *y) {
			return *x - *y;
		}
		x++;
		y++;
	}

	return *x - *y;
}
