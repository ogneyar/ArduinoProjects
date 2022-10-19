/**
  * FILE system_MDR32FG16S1QI.h
  */

/** @addtogroup __CMSIS CMSIS
  * @{
  */

/** @defgroup MDR32FG16S1QI
  * @{
  */

/** @defgroup MDR32FG16S1QI_System MDR32FG16S1QI System
  * @{
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SYSTEM_MDR32FG16S1QI_H
#define __SYSTEM_MDR32FG16S1QI_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h> /* standard types definitions */

/** @addtogroup __MDR32FG16S1QI_System_Exported_Variables MDR32FG16S1QI System Exported Variables
  * @{
  */

extern uint32_t SystemCoreClock;    /*!< System Clock Frequency (Core Clock) default value */

/** @} */ /* End of group __MDR32FG16S1QI_System_Exported_Variables */

/** @addtogroup __MDR32FG16S1QI_System_Exported_Functions MDR32FG16S1QI System Exported Functions
  * @{
  */

extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);

/** @} */ /* End of group __MDR32FG16S1QI_System_Exported_Functions */

#ifdef __cplusplus
}
#endif

#endif /*__SYSTEM_MDR32FG16S1QI_H */

/** @} */ /* End of group MDR32FG16S1QI_System */

/** @} */ /* End of group MDR32FG16S1QI */

/** @} */ /* End of group __CMSIS */

/*
*
* END OF FILE system_MDR32FG16S1QI.h */

