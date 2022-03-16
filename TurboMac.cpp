//
//  TurboMac.c
//  TurboMac
#include "TurboMac.h"
#include <IOKit/IOLib.h>

#define super IOService
OSDefineMetaClassAndStructors(TurboMac, IOService);

extern "C" kern_return_t TurboMac_start(kmod_info_t * ki, void *d);
extern "C" kern_return_t TurboMac_stop(kmod_info_t * ki, void *d);

const uint32_t MSR_TURBO_RATIO_LIMIT = 0x1AD;
const uint32_t IA32_PERF_CTL = 0x199;
const uint32_t IA32_PM_ENABLE = 0x770;
const uint32_t HWP_ENABLE_VALUE = 0x1;
const uint32_t IA32_HWP_CAPABILITIES = 0x771;
const uint32_t IA32_HWP_REQUEST = 0x774;
const uint32_t BASE_HWP_VALUE = 0x80000000;

const uint32_t FIRST_BYTE_MASK = (1 << 8) - 1;
const uint32_t SECOND_BYTE_MASK = ((1 << 16) - 1) ^ FIRST_BYTE_MASK;

bool TurboMac::init(OSDictionary* dict) {
    bool res = super::init(dict);
    IOLog("Initializing TurboMac...\n");
    return res;
}

IOService* TurboMac::probe(IOService *provider, SInt32 *score) {
    IOService* res = super::probe(provider, score);
    IOLog("Probing TurboMac...\n");
    return res;
}

bool TurboMac::start(IOService *provider)
{
    bool res = super::start(provider);
    IOLog("Starting TurboMac...");
    IOLog("Checking whether CPU supports SpeedShift...");
    
    CPUID hwpID(0x06);
    if (hwpID.EAX() & (1 << 7)) {
        IOLog("CPU supports SpeedShift.");
        
        IOLog("Writing to IA32_PM_ENABLE to enable SpeedShift...");
        wrmsr64(IA32_PM_ENABLE, HWP_ENABLE_VALUE);
        
        IOLog("Reading from IA32_HWP_CAPABILITIES...");
        uint64_t hwpCapabilities = rdmsr64(IA32_HWP_CAPABILITIES);
        uint64_t highestPerformance = hwpCapabilities & FIRST_BYTE_MASK;
        uint64_t guaranteedPerformance = (hwpCapabilities & SECOND_BYTE_MASK) >> 8;
        
        IOLog("Writing to IA32_HWP_REQUEST to request performance between HighestPerformance and GuaranteedPerformance...");
        wrmsr64(IA32_HWP_REQUEST, BASE_HWP_VALUE | (highestPerformance << 8) | guaranteedPerformance);
    }
    else {
        IOLog("CPU does not support SpeedShift.");
        
        IOLog("Reading from MSR_TURBO_RATIO_LIMIT...");
        uint64_t maxTurboRatio = rdmsr64(MSR_TURBO_RATIO_LIMIT) % (1 << 8);
        
        IOLog("Reading from MSR_PLATFORM_INFO to determine CPU base frequency...");
        uint64_t baseRatio = (rdmsr64(MSR_PLATFORM_INFO) >> 8) % (1 << 8);
        
        IOLog("Writing 3/4 (to prevent overheating) between turbo and base frequencies to IA32_PERF_CTL...");
        uint64_t desiredRatio = (maxTurboRatio + baseRatio) / 2;
        desiredRatio = (maxTurboRatio + desiredRatio) / 2;
        wrmsr64(IA32_PERF_CTL, desiredRatio << 8);
    }
    
    IOLog("TurboMac fully initialized.");
    return res;
}

void TurboMac::stop(IOService *provider) {
    super::stop(provider);
    IOLog("Stopping TurboMac...");
}

extern "C" kern_return_t TurboMac_start(kmod_info_t * ki, void *d) {
    IOLog("Starting!");
    return KERN_SUCCESS;
}

extern "C" kern_return_t TurboMac_stop(kmod_info_t *ki, void *d) {
    IOLog("Stopping!");
    return KERN_SUCCESS;
}
