#ifndef _SYSREGS_H
#define _SYSREGS_H

// ***************************************
// SCTLR_EL1, System Control Register (EL1)
// ***************************************

#define SCTLR_RESERVED                  ((3 << 28) | (3 << 22) | (1 << 20) | (1 << 11))
#define SCTLR_EE_LITTLE_ENDIAN          (0 << 25)
#define SCTLR_EOE_LITTLE_ENDIAN         (0 << 24)
#define SCTLR_I_CACHE_DISABLED          (0 << 12)
#define SCTLR_D_CACHE_DISABLED          (0 << 2)
#define SCTLR_MMU_DISABLED              (0 << 0)
#define SCTLR_MMU_ENABLED               (1 << 0)

#define SCTLR_VALUE_MMU_DISABLED  (SCTLR_RESERVED | SCTLR_EE_LITTLE_ENDIAN | \
                                   SCTLR_I_CACHE_DISABLED | SCTLR_D_CACHE_DISABLED | \
                                   SCTLR_MMU_DISABLED)


// ***************************************
// HCR_EL2, Hypervisor Configuration Register (EL2)
// ***************************************

#define HCR_RW                 (1 << 31)  // Set next EL to AArch64
#define HCR_AMO                (1 << 5)   // Trap cache maintenance ops
#define HCR_IMO                (1 << 4)   // Trap physical IRQs
#define HCR_FMO                (1 << 3)   // Trap FIQs
#define HCR_VALUE              (HCR_RW)   // Only set RW=1, disable traps


// ***************************************
// SPSR_EL2, Saved Program Status Register (EL2)
// ***************************************

// PSTATE field: D, A, I, F (Debug, SError, IRQ, FIQ mask)
#define SPSR_MASK_ALL          (7 << 6)   // Mask D, A, I, F
#define SPSR_EL1h              (5 << 0)   // M[3:0] = 0101 = EL1h mode
#define SPSR_VALUE             (SPSR_MASK_ALL | SPSR_EL1h)

#endif // _SYSREGS_H
