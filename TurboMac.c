//
//  TurboMac.c
//  TurboMac

#include <mach/mach_types.h>
#include <i386/proc_reg.h>

#include "CPUID.h"

kern_return_t TurboMac_start(kmod_info_t * ki, void *d);
kern_return_t TurboMac_stop(kmod_info_t *ki, void *d);

const uint32_t IA32_ENABLE_MSR = 0x770;
const uint32_t IA32_ENABLE_MSR_TRUE = 0x1;
const uint32_t IA32_HWP_CAPABILITIES = 0x771;
const uint32_t IA32_HWP_REQUEST = 0x774;
const uint32_t BASE_HWP_VALUE = 0x80000000;

const uint32_t FIRST_BYTE_MASK = (1 << 8) - 1;
const uint32_t SECOND_BYTE_MASK = ((1 << 16) - 1) ^ FIRST_BYTE_MASK;

kern_return_t TurboMac_start(kmod_info_t * ki, void *d)
{
    CPUID hwpID(0x06);
    
    // Check if CPU supports HWP
    if (hwpID.EAX() & (1 << 7)) {
        // Enable HWP
        wrmsr64(IA32_ENABLE_MSR, IA32_ENABLE_MSR_TRUE);
        
        // Read HWP capabilities
        uint64_t highestPerformance = rdmsr64(IA32_HWP_CAPABILITIES) & FIRST_BYTE_MASK;
        uint64_t guaranteedPerformance = (rdmsr64(IA32_HWP_CAPABILITIES) & SECOND_BYTE_MASK) >> 8;
        
        /*  Send a HWP_REQUEST with the following properties
            Minimum performance: IA32_HWP_CAPABILITIES.Guaranteed_Performance
            Maximum performance: IA32_HWP_CAPABILITIES.Highest_Performance */
        wrmsr64(IA32_HWP_REQUEST, BASE_HWP_VALUE | (highestPerformance << 8) | guaranteedPerformance);
        return KERN_SUCCESS;
    }
    else {
        return KERN_FAILURE;
    }
}

kern_return_t TurboMac_stop(kmod_info_t *ki, void *d)
{
    return KERN_SUCCESS;
}
