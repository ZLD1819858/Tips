#ifndef __EXCEPTION_ANALYSIS_H__
#define __EXCEPTION_ANALYSIS_H__

#include "stdint.h"

typedef enum
{
    EC_UNKNOWN              = 0x00, // Unknown reason
    EC_WFI_WFE              = 0x01, // Trapped WFI/WFE instruction

    EC_ // 0b000011,
    EC_ // 0b000100,
    EC_ // 0b000101,
    EC_ // 0b000110,
    EC_ // 0b000111,
    EC_ // 0b001100,
    EC_BRANCH_TARGET        = 0x0D, // 0b001101,
    EC_ILLEGAL_EXE_STATE    = 0x0E, // 0b001110, Illegal Execution state
    EC_ // 0b010001,
    EC_ // 0b010101,
    EC_ // 0b011000,
    EC_ // 0b011001,
    EC_ // 0b011100,

    EC_INSTR_ABORT_LOWER    = 0x20, // 0b100000, Instruction Abort from lower EL
    EC_INSTR_ABORT_SAME     = 0x21, // 0b100001, Instruction Abort from same EL

    EC_PC_ALIGNMENT_FAULT   = 0x22, // 0b100010, PC alignment fault exception

    EC_FP_EXCEPTION         = 0x24, // 0b100100, Data abort from a lower Exception level.
    EC_SERROR               = 0x25, // 0b100101, Data abort taken without a change in Exception level.

    EC_SP_ALIGNMENT_FAULT   = 0x26, // 0b100110, SP alignment fault exception

    EC_ // 0b101000,
    EC_ // 0b101100,
    EC_SERROR_INTR          = 0x2F, // 0b101111, SError interrupt
    EC_BREAKPOINT_LOWER     = 0x30, // 0b110000,
    EC_BREAKPOINT_SAME      = 0x31, // 0b110001,
    EC_SOFTWARE_STEP_LOWER  = 0x32, // 0b110010,
    EC_SOFTWARE_STEP_SAME   = 0x33, // 0b110011,
    EC_WATCHPOINT_LOWER     = 0x34, // 0b110100,
    EC_WATCHPOINT_SAME      = 0x35, // 0b110101,
    EC_ // 0b111000,
    EC_ // 0b111100,
} ec_t;

typedef struct
{
    uint32_t DFSC       :6; // Data Fault Status Code [5:0]
    uint32_t WnR        :1; // Write not Read [6]
    uint32_t S1PTW      :1; // [7]
    uint32_t CM         :1; // Cache maintenance [8]
    uint32_t EA         :1; // External abort type [9]
    uint32_t FnV        :1; // FAR not Valid [10]
    uint32_t SET        :2; // Synchronous Error Type [12:11]
    uint32_t VNCR       :1; // [13]
    uint32_t AR         :1; // Acquire/Release [14]
    uint32_t SF         :1; // Sixty-Four [15]
    uint32_t SRT        :5; // Syndrome Register Transfer [20:16]
    uint32_t SSE        :1; // Syndrome Size Extend [21]
    uint32_t SAS        :2; // Syndrome Address Size [23:22]
    uint32_t ISV        :1; // Instruction (Specific) Syndrome Valid [24]
    uint32_t invalid   :7; // Invalid [31:25]
} ec_iss_data_abort_t;

typedef struct
{
    uint32_t IFSC       :6; // Instruction Fault Status Code [5:0]
    uint32_t reserved_0   :1; // Reserved [6]
    uint32_t S1PTW      :1; // [7]
    uint32_t reserved_1 :1; // Cache maintenance [8]
    uint32_t EA         :1; // External abort type [9]
    uint32_t FnV        :1; // FAR not Valid [10]
    uint32_t SET        :2; // Synchronous Error Type [12:11]
    uint32_t reserved_2   :12; // Reserved [24:13]
    uint32_t invalid   :7; // Invalid [31:25]
} ec_iss_instruction_abort_t;

typedef struct
{
    uint32_t reserved_0     :25; // Reserved [24:0]
    uint32_t invalid        :7; // Invalid [31:25]
} ec_iss_reserved_t; /* Illegal Execution state, or a PC or SP alignment fault. */

typedef struct
{
    uint32_t TI         :1; // [0]
    uint32_t reserved_0 :19; // Reserved [19:1]
    uint32_t COND       :4; // Condition [23:20]
    uint32_t CV         :1; // Condition code valid [24]
    uint32_t invalid        :7; // Invalid [31:25]
} ec_iss_wfi_wfe_t;

typedef struct
{
    uint32_t DFSC           :6; // Data Fault Status Code [5:0]
    uint32_t reserved_0     :3; // Reserved [8:6]
    uint32_t EA             :1; // External abort type [9]
    uint32_t AET            :3; // Asynchronous Error Type [12:10]
    uint32_t IESB           :1; // Implicit error synchronization event [13]
    uint32_t reserved_1     :10; // Reserved [23:14]
    uint32_t IDS            :1; // [24]
    uint32_t invalid        :7; // Invalid [31:25]
} ec_iss_serror_t; /* Illegal Execution state, or a PC or SP alignment fault. */

typedef struct
{
    uint32_t IFSC           :6; // Instruction Fault Status Code [5:0]
    uint32_t reserved_0     :19; // Reserved [24:6]
    uint32_t invalid        :7; // Invalid [31:25]
} ec_iss_bp_vec_catch_t; /* Breakpoint or Vector Catch debug exception. */

typedef struct
{
    uint32_t IFSC           :6; // Instruction Fault Status Code [5:0]
    uint32_t EX             :1; // Exclusive operation [6]
    uint32_t reserved_0     :17; // Reserved [23:7]
    uint32_t ISV            :1; // Instruction syndrome valid [24]
    uint32_t invalid        :7; // Invalid [31:25]
} ec_iss_sw_step_t; /* Software Step exception. */

typedef struct
{
    uint32_t DFSC           :6; // Data Fault Status Code [5:0]
    uint32_t WnR            :1; // Write not Read [6]
    uint32_t reserved_0     :1; // Reserved [7]
    uint32_t CM             :1; // Cache maintenance [8]
    uint32_t reserved_1     :4; // Reserved [12:9]
    uint32_t VNCR           :1; // [13]
    uint32_t reserved_2     :11; // Reserved [24:14]
    uint32_t invalid        :7; // Invalid [31:25]
} ec_iss_wp_t; /* Software Step exception. */

typedef enum
{
    IL_16BIT = 0,
    IL_32BIT = 1
} il_t;

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
