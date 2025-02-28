#ifndef __PMSAV7_REG_H__
#define __PMSAV7_REG_H__

#include <pmsav7_regdef.h>

#define MPU_TYPE        (*(volatile PMSAV7_MPU_TYPE *)0xE000ED90)
#define MPU_CTRL        (*(volatile PMSAV7_MPU_CTRL *)0xE000ED94)
#define MPU_RNR         (*(volatile PMSAV7_MPU_RNR *)0xE000ED98)
#define MPU_RBAR        (*(volatile PMSAV7_MPU_RBAR *)0xE000ED9C)
#define MPU_RASR        (*(volatile PMSAV7_MPU_RASR *)0xE000EDA0)


#define MPU_RBAR_A1     (*(volatile PMSAV7_MPU_RBAR *)0xE000EDA4)
#define MPU_RASR_A1     (*(volatile PMSAV7_MPU_RASR *)0xE000EDA8)
#define MPU_RBAR_A2     (*(volatile PMSAV7_MPU_RBAR *)0xE000EDAC)
#define MPU_RASR_A2     (*(volatile PMSAV7_MPU_RASR *)0xE000EDB0)
#define MPU_RBAR_A3     (*(volatile PMSAV7_MPU_RBAR *)0xE000EDB4)
#define MPU_RASR_A3     (*(volatile PMSAV7_MPU_RASR *)0xE000EDB8)

#define MPU_Reserved_BEGIN      (0xE000EDBC)
#define MPU_Reserved_END        (0xE000EDEC)

#endif /* __PMSAV7_REG_H__ */
