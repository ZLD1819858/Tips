#ifndef __PMSAV7_REGDEF_H__
#define __PMSAV7_REGDEF_H__

typedef struct _PMSAV7_MPU_TYPE_BITS
{
    u32 SEPARATE    :1;
    u32 reserved_0  :7;
    u32 DREGION     :8;
    u32 IREGION     :8;
    u32 reserved_1  :8;
} PMSAV7_MPU_TYPE_BITS;

typedef struct _PMSAV7_MPU_CTRL_BITS
{
    u32 ENABLE      :1;
    u32 HFNMIENA    :1;
    u32 PRIVDEFENA  :1;
    u32 reserved_0  :29;
} PMSAV7_MPU_CTRL_BITS;

typedef struct _PMSAV7_MPU_RNR_BITS
{
    u32 REGION      :8;
    u32 reserved_0  :24;
} PMSAV7_MPU_RNR_BITS;

typedef struct _PMSAV7_MPU_RBAR_BITS
{
    u32 REGION      :4;
    u32 VALID       :1;
    u32 reserved_0  :27;
} PMSAV7_MPU_RBAR_BITS;

typedef struct _PMSAV7_MPU_RASR_BITS
{
    u32 ENABLE      :1;
    u32 SIZE        :5;
    u32 reserved_0  :2;
    u32 SRD         :8;

    /*  The MPU Region Attribute field. */
    u32 B           :1;
    u32 C           :1;
    u32 S           :1;
    u32 TEX         :3;
    u32 reserved_1  :2;
    u32 AP          :3;
    u32 reserved_2  :1;
    u32 XN          :1;
    u32 reserved_3  :3;
} PMSAV7_MPU_RASR_BITS;

/*******************************************************************************

*******************************************************************************/
typedef union
{
    u32 U;
    i32 I;
    PMSAV7_MPU_TYPE_BITS B;
} PMSAV7_MPU_TYPE;

typedef union
{
    u32 U;
    i32 I;
    PMSAV7_MPU_CTRL_BITS B;
} PMSAV7_MPU_CTRL;

typedef union
{
    u32 U;
    i32 I;
    PMSAV7_MPU_RNR_BITS B;
} PMSAV7_MPU_RNR;
typedef union
{
    u32 U;
    i32 I;
    PMSAV7_MPU_RBAR_BITS B;
} PMSAV7_MPU_RBAR;
typedef union
{
    u32 U;
    i32 I;
    PMSAV7_MPU_RASR_BITS B;
} PMSAV7_MPU_RASR;

#endif /* __PMSAV7_REGDEF_H__ */
