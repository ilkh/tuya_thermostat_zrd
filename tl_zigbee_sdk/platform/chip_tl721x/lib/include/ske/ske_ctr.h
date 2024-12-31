/********************************************************************************************************
 * @file    ske_ctr.h
 *
 * @brief   This is the header file for TL721X
 *
 * @author  Driver Group
 * @date    2024
 *
 * @par     Copyright (c) 2024, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *
 *          Licensed under the Apache License, Version 2.0 (the "License");
 *          you may not use this file except in compliance with the License.
 *          You may obtain a copy of the License at
 *
 *              http://www.apache.org/licenses/LICENSE-2.0
 *
 *          Unless required by applicable law or agreed to in writing, software
 *          distributed under the License is distributed on an "AS IS" BASIS,
 *          WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *          See the License for the specific language governing permissions and
 *          limitations under the License.
 *
 *******************************************************************************************************/
#ifndef SKE_CTR_H
#define SKE_CTR_H


#include "ske.h"



#ifdef __cplusplus
extern "C" {
#endif






//APIs

unsigned int ske_lp_ctr_init(SKE_ALG alg, SKE_CRYPTO crypto, unsigned char *key, unsigned short sp_key_idx, unsigned char *iv);

unsigned int ske_lp_ctr_update_blocks(unsigned char *in, unsigned char *out, unsigned int bytes);

unsigned int ske_lp_ctr_final(void);

unsigned int ske_lp_ctr_crypto(SKE_ALG alg, SKE_CRYPTO crypto, unsigned char *key, unsigned short sp_key_idx, unsigned char *iv,
        unsigned char *in, unsigned char *out, unsigned int bytes);


#ifdef SKE_LP_DMA_FUNCTION
unsigned int ske_lp_dma_ctr_init(SKE_ALG alg, SKE_CRYPTO crypto, unsigned char *key, unsigned short sp_key_idx, unsigned char *iv);

unsigned int ske_lp_dma_ctr_update_blocks(unsigned int *in, unsigned int *out, unsigned int words, SKE_CALLBACK callback);

unsigned int ske_lp_dma_ctr_final(void);

unsigned int ske_lp_dma_ctr_crypto(SKE_ALG alg, SKE_CRYPTO crypto, unsigned char *key, unsigned short sp_key_idx, unsigned char *iv,
        unsigned int *in, unsigned int *out, unsigned int words, SKE_CALLBACK callback);
#endif







#ifdef __cplusplus
}
#endif

#endif
