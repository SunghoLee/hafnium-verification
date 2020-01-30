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

#include "hf/arch/irq.h"
#include "hf/arch/vm/interrupts.h"

#include "hf/dlog.h"

#include "vmapi/hf/call.h"

#include "primary_with_secondary.h"
#include "test/hftest.h"

/*
 * Secondary VM that enables an interrupt, disables interrupts globally, and
 * calls WFI.
 */

static void irq(void)
{
	uint32_t interrupt_id = hf_interrupt_get();
	FAIL("Unexpected secondary IRQ %d from current", interrupt_id);
}

TEST_SERVICE(wfi)
{
	int32_t i;
	const char message[] = "Done waiting";

	exception_setup(irq, NULL);
	arch_irq_disable();
	hf_interrupt_enable(EXTERNAL_INTERRUPT_ID_A, true);

	for (i = 0; i < 10; ++i) {
		interrupt_wait();
	}

	memcpy_s(SERVICE_SEND_BUFFER(), SPCI_MSG_PAYLOAD_MAX, message,
		 sizeof(message));

	spci_msg_send(hf_vm_get_id(), HF_PRIMARY_VM_ID, sizeof(message), 0);
}
