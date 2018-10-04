#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "hf/arch/cpu.h"

#include "hf/addr.h"
#include "hf/spinlock.h"

enum vcpu_state {
	/* The vcpu is switched off. */
	vcpu_state_off,

	/* The vcpu is ready to be run. */
	vcpu_state_ready,

	/* The vcpu is currently running. */
	vcpu_state_running,

	/* The vcpu is waiting for a message. */
	vcpu_state_blocked_mailbox,

	/* The vcpu is waiting for an interrupt. */
	vcpu_state_blocked_interrupt,
};

struct vcpu {
	struct spinlock lock;
	enum vcpu_state state;
	struct vm *vm;
	struct vcpu *mailbox_next;
	struct arch_regs regs;
};

/* TODO: Update alignment such that cpus are in different cache lines. */
struct cpu {
	/* CPU identifier. Doesn't have to be contiguous. */
	size_t id;

	struct vcpu *current;

	/* Pointer to bottom of the stack. */
	void *stack_bottom;

	/*
	 * Enabling/disabling irqs are counted per-cpu. They are enabled when
	 * the count is zero, and disabled when it's non-zero.
	 */
	uint32_t irq_disable_count;

	struct spinlock lock;

	/* Determines whether or not the cpu is currently on. */
	bool is_on;
};

void cpu_module_init(void);

void cpu_init(struct cpu *c);
size_t cpu_index(struct cpu *c);
void cpu_irq_enable(struct cpu *c);
void cpu_irq_disable(struct cpu *c);
bool cpu_on(struct cpu *c, ipaddr_t entry, size_t arg);
void cpu_off(struct cpu *c);
struct cpu *cpu_find(size_t id);

void vcpu_init(struct vcpu *vcpu, struct vm *vm);
void vcpu_on(struct vcpu *vcpu);
void vcpu_off(struct vcpu *vcpu);