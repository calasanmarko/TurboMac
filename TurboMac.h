#ifndef TurboMac_h
#define TurboMac_h
#endif

#include "CPUID.hpp"

#include <mach/mach_types.h>
#include <i386/proc_reg.h>
#include <IOKit/IOService.h>

class TurboMac : public IOService {
    OSDeclareDefaultStructors(TurboMac);
    
public:
    virtual bool init(OSDictionary* dict);
    virtual IOService* probe(IOService* provider, SInt32 *score);
    virtual bool start(IOService* provider);
    virtual void stop(IOService* provider);
    virtual void free(void);
};
