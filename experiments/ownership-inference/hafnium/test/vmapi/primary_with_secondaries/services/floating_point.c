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

#include "hf/arch/std.h"
#include "hf/arch/vm/registers.h"

#include "hf/spci.h"

#include "vmapi/hf/call.h"

#include "../msr.h"
#include "test/hftest.h"

TEST_SERVICE(fp_fill)
{
	const double value = 0.75;
	fill_fp_registers(value);
	EXPECT_EQ(spci_yield().func, SPCI_SUCCESS_32);

	ASSERT_TRUE(check_fp_register(value));
	spci_yield();
}

TEST_SERVICE(fp_fpcr)
{
	uintreg_t value = 3 << 22; /* Set RMode to RZ */
	write_msr(fpcr, value);
	EXPECT_EQ(spci_yield().func, SPCI_SUCCESS_32);

	ASSERT_EQ(read_msr(fpcr), value);
	spci_yield();
}
