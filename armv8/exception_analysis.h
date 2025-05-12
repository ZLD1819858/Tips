#ifndef __EXCEPTION_ANALYSIS_H__
#define __EXCEPTION_ANALYSIS_H__

typedef enum
{
    EC_UNKNOWN              = 0x00, // Unknown reason
    EC_WFI_WFE              = 0x01, // Trapped WFI/WFE instruction
    EC_INSTR_ABORT_LOWER    = 0x15, // Instruction Abort from lower EL
    EC_INSTR_ABORT_SAME     = 0x16, // Instruction Abort from same EL
    EC_DATA_ABORT_LOWER     = 0x20, // Data Abort from lower EL
    EC_DATA_ABORT_SAME      = 0x21, // Data Abort from same EL
    EC_FP_EXCEPTION         = 0x24, // Floating-point exception
    EC_SERROR               = 0x25  // SError interrupt[24:0] 
} ec_t;

typedef struct 
{
   uint64_t ISS :25;    /* Instruction Specific Syndrome [24:0], depends on EC  */
   uint64_t IL :1;      /* Instruction Length [25] (0 = 16-bit, 1 = 32-bit) */
   uint64_t EC :6;      /* Exception Class [31:26], see ec_t */ 
   uint64_t reserved :32;  /* Reserved [63:32], typically 0 */
} esr_elx_bits_t;

typedef union {
    uint64_t raw;
    esr_elx_bits_t fields;
} esr_elx_t;

#endif /* __EXCEPTION_ANALYSIS_H__ */
