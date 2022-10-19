/**
  ******************************************************************************
  * @file    MDR1986VK01_ebc.c
  * @author  Milandr Application Team
  * @version V1.1.0
  * @date    06/04/2022
  * @brief   This file contains all the EBC firmware functions.
  ******************************************************************************
  * <br><br>
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, MILANDR SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT
  * OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2022 Milandr</center></h2>
  ******************************************************************************
  * FILE MDR1986VK01_ebc.c
  */

/* Includes ------------------------------------------------------------------*/
#include "MDR1986VK01_config.h"
#include "MDR1986VK01_ebc.h"

#define ASSERT_INFO_FILE_ID FILEID__MDR1986VK01_EBC_C

/** @addtogroup __MDR1986VK01_StdPeriph_Driver MDR1986VK01 Standard Peripherial Driver
  * @{
  */

/** @defgroup EBC EBC
  * @{
  */

/** @defgroup EBC_Private_Functions EBC Private Functions
  * @{
  */


/**
  * @brief  Initializes the EBC peripheral according to
  *         the specified parameters in the EBC_RGN_InitStruct.
  * @param  EBC_RGN_InitStruct: pointer to a EBC_RGN_InitTypeDef structure
  *         that contains the configuration information for the specified EBC_RGN.
  * @retval None
  */
void EBC_RGNx_Init(uint32_t RGNx, const EBC_RGN_InitTypeDef* EBC_RGN_InitStruct)
{
  uint32_t tmpreg_RGNx_CNTRL;

	tmpreg_RGNx_CNTRL = (EBC_RGN_InitStruct->RGN_ECCEN          << EBC_ECCEN_pos)
					    | (EBC_RGN_InitStruct->RGN_ECCMODE 		<< EBC_ECCMODE_pos)
						| (EBC_RGN_InitStruct->RGN_RDYWAIT 		<< EBC_RDYWAIT_pos)
						| (EBC_RGN_InitStruct->RGN_MODE 	 	<< EBC_MODE_pos)
						| (EBC_RGN_InitStruct->RGN_ROM 		 	<< EBC_ROM_pos)
						| (EBC_RGN_InitStruct->RGN_CPOL 	 	<< EBC_CPOL_pos)
						| (EBC_RGN_InitStruct->RGN_WS_ACTIVE 	<< EBC_WS_ACTIVE_pos)
						| (EBC_RGN_InitStruct->RGN_WS_SETUP 	<< EBC_WS_SETUP_pos)
						| (EBC_RGN_InitStruct->RGN_WS_HOLD 		<< EBC_WS_HOLD_pos)
						| (EBC_RGN_InitStruct->RGN_ECC8BIT 		<< EBC_ECC8BIT_pos)
						| (EBC_RGN_InitStruct->RGN_ENOCLK 		<< EBC_ENOCLK_pos)
						| (EBC_RGN_InitStruct->RGN_DIVOCLK 		<< EBC_DIVOCLK_pos);
	switch (RGNx)
	{
		case RGN0: MDR_EBC->RGN0_CNTRL = tmpreg_RGNx_CNTRL;break;
		case RGN1: MDR_EBC->RGN1_CNTRL = tmpreg_RGNx_CNTRL;break;
		case RGN2: MDR_EBC->RGN2_CNTRL = tmpreg_RGNx_CNTRL;break;
		case RGN3: MDR_EBC->RGN3_CNTRL = tmpreg_RGNx_CNTRL;break;
		case RGN4: MDR_EBC->RGN4_CNTRL = tmpreg_RGNx_CNTRL;break;
		case RGN5: MDR_EBC->RGN5_CNTRL = tmpreg_RGNx_CNTRL;break;
		case RGN6: MDR_EBC->RGN6_CNTRL = tmpreg_RGNx_CNTRL;break;
		case RGN7: MDR_EBC->RGN7_CNTRL = tmpreg_RGNx_CNTRL;break;
	}
}

/**
  * @brief  Fills each EBC_RGN_InitStruct member with its default value.
  * @param  EBC_RGN_InitStruct: pointer to a EBC_RGN_InitTypeDef structure
  *         which will be initialized.
  * @retval None
  */
void EBC_RGNx_StructInit(EBC_RGN_InitTypeDef* EBC_RGN_InitStruct)
{
    EBC_RGN_InitStruct->RGN_ECCEN = DISABLE;
    EBC_RGN_InitStruct->RGN_ECCMODE = 0;
    EBC_RGN_InitStruct->RGN_RDYWAIT = 0;
    EBC_RGN_InitStruct->RGN_MODE = 0;
    EBC_RGN_InitStruct->RGN_ROM = 0;
    EBC_RGN_InitStruct->RGN_CPOL = 0;
    EBC_RGN_InitStruct->RGN_WS_ACTIVE = 0;
    EBC_RGN_InitStruct->RGN_WS_SETUP = 0;
    EBC_RGN_InitStruct->RGN_WS_HOLD = 0;
    EBC_RGN_InitStruct->RGN_ECC8BIT = 0;
    EBC_RGN_InitStruct->RGN_ENOCLK = DISABLE;
    EBC_RGN_InitStruct->RGN_DIVOCLK = 0;
}

/**
  * @brief  Enables or disables the EBC_RGNx.
  * @param  NewState: new state of the EBC_RGNx.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void EBC_RGNx_Cmd(uint32_t RGNx, FunctionalState NewState)
{
  uint32_t tmpreg_CNTRL;

  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

	switch (RGNx)
	{
		case RGN0: tmpreg_CNTRL = MDR_EBC->RGN0_CNTRL;break;
		case RGN1: tmpreg_CNTRL = MDR_EBC->RGN1_CNTRL;break;
		case RGN2: tmpreg_CNTRL = MDR_EBC->RGN2_CNTRL;break;
		case RGN3: tmpreg_CNTRL = MDR_EBC->RGN3_CNTRL;break;
		case RGN4: tmpreg_CNTRL = MDR_EBC->RGN4_CNTRL;break;
		case RGN5: tmpreg_CNTRL = MDR_EBC->RGN5_CNTRL;break;
		case RGN6: tmpreg_CNTRL = MDR_EBC->RGN6_CNTRL;break;
		case RGN7: tmpreg_CNTRL = MDR_EBC->RGN7_CNTRL;break;
	}

  /* Form new value */
  if (NewState != DISABLE)
  {
    /* Enable EBC_RGNx by setting the EBC_RGNx_CNTRL_EN bit in the CNTRL register */
    tmpreg_CNTRL |= EBC_RGNx_EN;
  }
  else
  {
    /* Disable EBC_RGNx by resetting the EBC_RGNx_CNTRL_EN bit in the CNTRL register */
    tmpreg_CNTRL &= ~EBC_RGNx_EN;
  }

  /* Configure CNTRL register with new value */
	switch (RGNx)
	{
		case RGN0: MDR_EBC->RGN0_CNTRL |= tmpreg_CNTRL;break;
		case RGN1: MDR_EBC->RGN1_CNTRL |= tmpreg_CNTRL;break;
		case RGN2: MDR_EBC->RGN2_CNTRL |= tmpreg_CNTRL;break;
		case RGN3: MDR_EBC->RGN3_CNTRL |= tmpreg_CNTRL;break;
		case RGN4: MDR_EBC->RGN4_CNTRL |= tmpreg_CNTRL;break;
		case RGN5: MDR_EBC->RGN5_CNTRL |= tmpreg_CNTRL;break;
		case RGN6: MDR_EBC->RGN6_CNTRL |= tmpreg_CNTRL;break;
		case RGN7: MDR_EBC->RGN7_CNTRL |= tmpreg_CNTRL;break;
	}
}

/** @} */ /* End of group EBC_Private_Functions */

/** @} */ /* End of group EBC */

/** @} */ /* End of group __MDR1986VK01_StdPeriph_Driver */

/******************* (C) COPYRIGHT 2022 Milandr *********************************
*
* END OF FILE MDR1986VK01_ebc.c */

