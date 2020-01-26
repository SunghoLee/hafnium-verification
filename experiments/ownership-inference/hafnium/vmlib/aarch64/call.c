/*
 * Copyright 2019 The Hafnium Authors.
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

#include "hf/call.h"

#include "hf/spci.h"
#include "hf/types.h"

int64_t hf_call(uint64_t arg0, uint64_t arg1, uint64_t arg2, uint64_t arg3)
{
	register uint64_t r0 __asm__("x0") = arg0;
	register uint64_t r1 __asm__("x1") = arg1;
	register uint64_t r2 __asm__("x2") = arg2;
	register uint64_t r3 __asm__("x3") = arg3;

	__asm__ volatile(
		"hvc #0"
		: /* Output registers, also used as inputs ('+' constraint). */
		"+r"(r0), "+r"(r1), "+r"(r2), "+r"(r3)
		:
		: /* Clobber registers. */
		"x4", "x5", "x6", "x7");

	return r0;
}

struct spci_value spci_call(struct spci_value args)
{
	register uint64_t r0 __asm__("x0") = args.func;
	register uint64_t r1 __asm__("x1") = args.arg1;
	register uint64_t r2 __asm__("x2") = args.arg2;
	register uint64_t r3 __asm__("x3") = args.arg3;
	register uint64_t r4 __asm__("x4") = args.arg4;
	register uint64_t r5 __asm__("x5") = args.arg5;
	register uint64_t r6 __asm__("x6") = args.arg6;
	register uint64_t r7 __asm__("x7") = args.arg7;

	__asm__ volatile(
		"hvc #0"
		: /* Output registers, also used as inputs ('+' constraint). */
		"+r"(r0), "+r"(r1), "+r"(r2), "+r"(r3), "+r"(r4), "+r"(r5),
		"+r"(r6), "+r"(r7));

	return (struct spci_value){.func = r0,
				   .arg1 = r1,
				   .arg2 = r2,
				   .arg3 = r3,
				   .arg4 = r4,
				   .arg5 = r5,
				   .arg6 = r6,
				   .arg7 = r7};
}
