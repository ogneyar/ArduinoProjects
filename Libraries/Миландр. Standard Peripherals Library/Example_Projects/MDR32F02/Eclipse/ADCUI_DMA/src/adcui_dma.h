#ifndef ADCUI_ADCUI_DMA_H
#define ADCUI_ADCUI_DMA_H

#include <MLDR187.h>
#include <MLDR187_lib.h>
#include <MLDR187_adcui.h>

/**
 * 	@brief	Configure DMA controller to receive \p len samples from ADCUI channel and place them into a buffer.
 * 	        After DMA transaction is complete, or refresh is needed, an interrupt will occur.
 * 	@param	channel     - adcuiChannel, from which samples will be taken
 * 	@param  dataV       - data buffer, where voltage samples will be stored.
 * 	@param  dataI       - data buffer, where current samples will be stored.
 * 	@param  dataIAlt    - data buffer, where alternative current (I3) samples will be stored.
 * 	@param  len         - number of samples to receive (1..1024)
 * 	@param  cycleMode   - if ENABLE, DMA transaction will occur in ping-pong mode.
 * 	        Convenient for continuous reception or for long data buffers, split into parts.
 * 	        If DISABLE, it will occur in normal mode (single transaction)
 * 	@param  itPriority  - priority for interrupt on complete
 * 	@note   All buffers may be null and
 * 	        must be of size \p len * sample_size. Sample size can be 2 bytes or 4 bytes, depending on ADCUI resolution.
 * 	@note   In interrupt handler DMA_IRQHandler, in cycle mode, user has to call ADCUI_DMACycleModeRefresh if transaction is not complete.
 * 	        If transaction is complete, user can either finish DMA cycles with ADCUI_DMAFinish, or reconfigure next cycle for same or other data buffer.
 */
void ADCUI_DMAReceive(adcuiChannel channel, void* dataV, void* dataI, void* dataIAlt, uint32_t len, FunctionalState cycleMode, uint8_t itPriority);

/**
 * @brief   Refresh DMA channel structures for active ADCUI transaction in ping-pong mode
 * @param   channel     - adcuiChannel, for which DMA transaction is configured
 * @param   dataV       - new data buffer for voltage
 * @param   dataI       - new data buffer for current
 * @param   dataIAlt    - new data buffer for alternative current
 * @param   len         - number of samples
 * @note    This function has to be called in DMA_IRQHandler if user wants to continue DMA transaction in ping-pong mode.
 *          It must be called soon enough while other half of DMA cycle is not done
 */
void ADCUI_DMACycleModeRefresh(adcuiChannel channel, void *dataV, void *dataI, void *dataIAlt, uint32_t len);

/**
 * @brief   Check if DMA transaction for that channel is valid and is already complete.
 * @param   channel     - adcuiChannel, for which DMA transaction is configured
 * @return  SET if DMA transaction is complete; RESET if it is not complete, or half-complete in ping-pong mode, or not active.
 */
BitStatus ADCUI_DMAIsComplete(adcuiChannel channel);

/**
 * @brief   Deactivate all DMA activity on that ADCUI channel and disable ADCUI channel itself.
 * @param   channel     - adcuiChannel, for which DMA transaction is configured
 */
void ADCUI_DMAFinish(adcuiChannel channel);

#endif //ADCUI_ADCUI_DMA_H

