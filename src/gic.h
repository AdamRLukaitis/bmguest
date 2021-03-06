#ifndef __GIC_H__
#define __GIC_H__

#include <stdint.h>

#define GIC_NUM_MAX_IRQS    1024
#define gic_cpumask_current()    (1u << smp_processor_id())
#define GIC_INT_PRIORITY_DEFAULT        0xa0

struct gic_hw_info {
    uint64_t base;              /**< GIC base address */
    uint32_t nr_irqs;           /**< The Maximum number of interrupts */
    uint32_t nr_cpus;           /**< The number of implemented CPU interfaces */
    uint32_t initialized;       /**< Check whether initializing GIC. */
};
static struct gic_hw_info gic_hw;

#define GIC_SIGNATURE_INITIALIZED   0x5108EAD7

enum gic_irq_polarity {
    GIC_INT_POLARITY_LEVEL = 0,
    GIC_INT_POLARITY_EDGE = 1
};

enum gic_sgi {
    GIC_SGI_SLOT_CHECK = 1,
};

void gic_enable_irq(uint32_t irq);
void gic_disable_irq(uint32_t irq);
void gic_init(void);
void gic_deactivate_irq(uint32_t irq);
void gic_completion_irq(uint32_t irq);

void gic_configure_irq(uint32_t irq,
                enum gic_irq_polarity polarity, uint8_t cpumask,
                uint8_t priority);

uint32_t gic_get_irq_number(void);

void gic_set_sgi(const uint32_t target, uint32_t sgi);


#endif
