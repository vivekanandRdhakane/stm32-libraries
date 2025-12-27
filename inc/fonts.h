/**
 * original author:  Tilen Majerle<tilen@majerle.eu>
 * modification for STM32f10x: Alexander Lutsai<s.lyra@ya.ru>
   ----------------------------------------------------------------------
   	Copyright (C) Alexander Lutsai, 2016
    Copyright (C) Tilen Majerle, 2015
    
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.
     
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
   ----------------------------------------------------------------------
 */
#ifndef FONTS_H
#define FONTS_H 120

/* C++ detection */
#ifdef __cplusplus
extern C {
#endif

/**
 *
 * Default fonts library. It is used in all LCD based libraries.
 *
 * \par Supported fonts
 * 
 * Currently, these fonts are supported:
 *  - 7 x 10 pixels
 *  - 11 x 18 pixels
 *  - 16 x 26 pixels
 */
#include "main.h"
#include "string.h"

/**
 * @defgroup LIB_Typedefs
 * @brief    Library Typedefs
 * @{
 */

/**
 * @brief  Font structure used on my LCD libraries
 */
typedef struct {
	uint8_t FontWidth;    /*!< Font width in pixels */
	uint8_t FontHeight;   /*!< Font height in pixels */
	const uint16_t *data; /*!< Pointer to data font data array */
} FontDef_t;

/** 
 * @brief  String length and height 
 */
typedef struct {
	uint16_t Length;      /*!< String length in units of pixels */
	uint16_t Height;      /*!< String height in units of pixels */
} FONTS_SIZE_t;

/**
 * @}
 */

/**
 * @defgroup FONTS_FontVariables
 * @brief    Library font variables
 * @{
 */

/**
 * @brief  7 x 10 pixels font size structure 
 */
extern FontDef_t Font_7x10;

/**
 * @brief  11 x 18 pixels font size structure 
 */
extern FontDef_t Font_11x18;

/**
 * @brief  16 x 26 pixels font size structure 
 */
extern FontDef_t Font_16x26;


extern FONTS_SIZE_t small;
extern FONTS_SIZE_t medium;
extern FONTS_SIZE_t big;


/**
 * @}
 */
 
#define SMALL_FONT_WIDTH   7
#define SMALL_FONT_HEIGHT  10

#define MEDIUM_FONT_WIDTH   11
#define MEDIUM_FONT_HEIGHT  18

#define BIG_FONT_WIDTH      16
#define BIG_FONT_HEIGHT     26


/**
 * @defgroup FONTS_Functions
 * @brief    Library functions
 * @{
 */

/**
 * @brief  Calculates string length and height in units of pixels depending on string and font used
 * @param  *str: String to be checked for length and height
 * @param  *SizeStruct: Pointer to empty @ref FONTS_SIZE_t structure where informations will be saved
 * @param  *Font: Pointer to @ref FontDef_t font used for calculations
 * @retval Pointer to string used for length and height
 */
char* FONTS_GetStringSize(char* str, FONTS_SIZE_t* SizeStruct, FontDef_t* Font);

/**
 * @}
 */
 
/**
 * @}
 */
 
/**
 * @}
 */

extern const uint16_t s_sp []     ;
extern const uint16_t s_exc []    ;
extern const uint16_t s_dic []    ;
extern const uint16_t s_hash []   ;
extern const uint16_t s_doller [] ;
extern const uint16_t s_perc []   ;
extern const uint16_t s_and []    ;
extern const uint16_t s_sic []    ;
extern const uint16_t s_bo []     ;
extern const uint16_t s_bc []     ;
extern const uint16_t s_star []   ;
extern const uint16_t s_plus []   ;
extern const uint16_t s_comma []  ;
extern const uint16_t s_minus []  ;
extern const uint16_t s_dot []    ;
extern const uint16_t s_fs []     ;
extern const uint16_t s_0 []      ;
extern const uint16_t s_1 []      ;
extern const uint16_t s_2 []      ;
extern const uint16_t s_3 []      ;
extern const uint16_t s_4 []      ;
extern const uint16_t s_5 []      ;
extern const uint16_t s_6 []      ;
extern const uint16_t s_7 []      ;
extern const uint16_t s_8 []      ;
extern const uint16_t s_9 []      ;
extern const uint16_t s_col []    ;
extern const uint16_t s_scol []   ;
extern const uint16_t s_lt []     ;
extern const uint16_t s_eq []     ;
extern const uint16_t s_gt []     ;
extern const uint16_t s_qm []     ;
extern const uint16_t s_at []     ;
extern const uint16_t s_A []      ;
extern const uint16_t s_B []      ;
extern const uint16_t s_C []      ;
extern const uint16_t s_D []      ;
extern const uint16_t s_E []      ;
extern const uint16_t s_F []      ;
extern const uint16_t s_G []      ;
extern const uint16_t s_H []      ;
extern const uint16_t s_I []      ;
extern const uint16_t s_J []      ;
extern const uint16_t s_K []      ;
extern const uint16_t s_L []      ;
extern const uint16_t s_M []      ;
extern const uint16_t s_N []      ;
extern const uint16_t s_O []      ;
extern const uint16_t s_P []      ;
extern const uint16_t s_Q []      ;
extern const uint16_t s_R []      ;
extern const uint16_t s_S []      ;
extern const uint16_t s_T []      ;
extern const uint16_t s_U []      ;
extern const uint16_t s_V []      ;
extern const uint16_t s_W []      ;
extern const uint16_t s_X []      ;
extern const uint16_t s_Y []      ;
extern const uint16_t s_Z []      ;
extern const uint16_t s_obrac []  ;
extern const uint16_t s_bs []     ;
extern const uint16_t s_cbrac []  ;
extern const uint16_t s_ua []     ;
extern const uint16_t s_us []     ;
extern const uint16_t s_tt []     ;
extern const uint16_t s_a []      ;
extern const uint16_t s_b []      ;
extern const uint16_t s_c []      ;
extern const uint16_t s_d []      ;
extern const uint16_t s_e []      ;
extern const uint16_t s_f []      ;
extern const uint16_t s_g []      ;
extern const uint16_t s_h []      ;
extern const uint16_t s_i []      ;
extern const uint16_t s_j []      ;
extern const uint16_t s_k []      ;
extern const uint16_t s_l []      ;
extern const uint16_t s_m []      ;
extern const uint16_t s_n []      ;
extern const uint16_t s_o []      ;
extern const uint16_t s_p []      ;
extern const uint16_t s_q []      ;
extern const uint16_t s_r []      ;
extern const uint16_t s_s []      ;
extern const uint16_t s_t []      ;
extern const uint16_t s_u []      ;
extern const uint16_t s_v []      ;
extern const uint16_t s_w []      ;
extern const uint16_t s_x []      ;
extern const uint16_t s_y []      ;
extern const uint16_t s_z []      ;
extern const uint16_t s_ocb []    ;
extern const uint16_t s_bar []    ;
extern const uint16_t s_ccb []    ;
extern const uint16_t s_tilda []  ;

extern const uint16_t m_sp []     ;
extern const uint16_t m_exc []    ;
extern const uint16_t m_dic []    ;
extern const uint16_t m_hash []   ;
extern const uint16_t m_doller [] ;
extern const uint16_t m_perc []   ;
extern const uint16_t m_and []    ;
extern const uint16_t m_sic []    ;
extern const uint16_t m_bo []     ;
extern const uint16_t m_bc []     ;
extern const uint16_t m_star []   ;
extern const uint16_t m_plus []   ;
extern const uint16_t m_comma []  ;
extern const uint16_t m_minus []  ;
extern const uint16_t m_dot []    ;
extern const uint16_t m_fs []     ;
extern const uint16_t m_0 []      ;
extern const uint16_t m_1 []      ;
extern const uint16_t m_2 []      ;
extern const uint16_t m_3 []      ;
extern const uint16_t m_4 []      ;
extern const uint16_t m_5 []      ;
extern const uint16_t m_6 []      ;
extern const uint16_t m_7 []      ;
extern const uint16_t m_8 []      ;
extern const uint16_t m_9 []      ;
extern const uint16_t m_col []    ;
extern const uint16_t m_scol []   ;
extern const uint16_t m_lt []     ;
extern const uint16_t m_eq []     ;
extern const uint16_t m_gt []     ;
extern const uint16_t m_qm []     ;
extern const uint16_t m_at []     ;
extern const uint16_t m_A []      ;
extern const uint16_t m_B []      ;
extern const uint16_t m_C []      ;
extern const uint16_t m_D []      ;
extern const uint16_t m_E []      ;
extern const uint16_t m_F []      ;
extern const uint16_t m_G []      ;
extern const uint16_t m_H []      ;
extern const uint16_t m_I []      ;
extern const uint16_t m_J []      ;
extern const uint16_t m_K []      ;
extern const uint16_t m_L []      ;
extern const uint16_t m_M []      ;
extern const uint16_t m_N []      ;
extern const uint16_t m_O []      ;
extern const uint16_t m_P []      ;
extern const uint16_t m_Q []      ;
extern const uint16_t m_R []      ;
extern const uint16_t m_S []      ;
extern const uint16_t m_T []      ;
extern const uint16_t m_U []      ;
extern const uint16_t m_V []      ;
extern const uint16_t m_W []      ;
extern const uint16_t m_X []      ;
extern const uint16_t m_Y []      ;
extern const uint16_t m_Z []      ;
extern const uint16_t m_obrac []  ;
extern const uint16_t m_bs []     ;
extern const uint16_t m_cbrac []  ;
extern const uint16_t m_ua []     ;
extern const uint16_t m_us []     ;
extern const uint16_t m_tt []     ;
extern const uint16_t m_a []      ;
extern const uint16_t m_b []      ;
extern const uint16_t m_c []      ;
extern const uint16_t m_d []      ;
extern const uint16_t m_e []      ;
extern const uint16_t m_f []      ;
extern const uint16_t m_g []      ;
extern const uint16_t m_h []      ;
extern const uint16_t m_i []      ;
extern const uint16_t m_j []      ;
extern const uint16_t m_k []      ;
extern const uint16_t m_l []      ;
extern const uint16_t m_m []      ;
extern const uint16_t m_n []      ;
extern const uint16_t m_o []      ;
extern const uint16_t m_p []      ;
extern const uint16_t m_q []      ;
extern const uint16_t m_r []      ;
extern const uint16_t m_s []      ;
extern const uint16_t m_t []      ;
extern const uint16_t m_u []      ;
extern const uint16_t m_v []      ;
extern const uint16_t m_w []      ;
extern const uint16_t m_x []      ;
extern const uint16_t m_y []      ;
extern const uint16_t m_z []      ;
extern const uint16_t m_ocb []    ;
extern const uint16_t m_bar []    ;
extern const uint16_t m_ccb []    ;
extern const uint16_t m_tilda []  ;



extern const uint16_t b_sp []     ;
extern const uint16_t b_exc []    ;
extern const uint16_t b_dic []    ;
extern const uint16_t b_hash []   ;
extern const uint16_t b_doller [] ;
extern const uint16_t b_perc []   ;
extern const uint16_t b_and []    ;
extern const uint16_t b_sic []    ;
extern const uint16_t b_bo []     ;
extern const uint16_t b_bc []     ;
extern const uint16_t b_star []   ;
extern const uint16_t b_plus []   ;
extern const uint16_t b_comma []  ;
extern const uint16_t b_minus []  ;
extern const uint16_t b_dot []    ;
extern const uint16_t b_fs []     ;
extern const uint16_t b_0 []      ;
extern const uint16_t b_1 []      ;
extern const uint16_t b_2 []      ;
extern const uint16_t b_3 []      ;
extern const uint16_t b_4 []      ;
extern const uint16_t b_5 []      ;
extern const uint16_t b_6 []      ;
extern const uint16_t b_7 []      ;
extern const uint16_t b_8 []      ;
extern const uint16_t b_9 []      ;
extern const uint16_t b_col []    ;
extern const uint16_t b_scol []   ;
extern const uint16_t b_lt []     ;
extern const uint16_t b_eq []     ;
extern const uint16_t b_gt []     ;
extern const uint16_t b_qm []     ;
extern const uint16_t b_at []     ;
extern const uint16_t b_A []      ;
extern const uint16_t b_B []      ;
extern const uint16_t b_C []      ;
extern const uint16_t b_D []      ;
extern const uint16_t b_E []      ;
extern const uint16_t b_F []      ;
extern const uint16_t b_G []      ;
extern const uint16_t b_H []      ;
extern const uint16_t b_I []      ;
extern const uint16_t b_J []      ;
extern const uint16_t b_K []      ;
extern const uint16_t b_L []      ;
extern const uint16_t b_M []      ;
extern const uint16_t b_N []      ;
extern const uint16_t b_O []      ;
extern const uint16_t b_P []      ;
extern const uint16_t b_Q []      ;
extern const uint16_t b_R []      ;
extern const uint16_t b_S []      ;
extern const uint16_t b_T []      ;
extern const uint16_t b_U []      ;
extern const uint16_t b_V []      ;
extern const uint16_t b_W []      ;
extern const uint16_t b_X []      ;
extern const uint16_t b_Y []      ;
extern const uint16_t b_Z []      ;
extern const uint16_t b_obrac []  ;
extern const uint16_t b_bs []     ;
extern const uint16_t b_cbrac []  ;
extern const uint16_t b_ua []     ;
extern const uint16_t b_us []     ;
extern const uint16_t b_tt []     ;
extern const uint16_t b_a []      ;
extern const uint16_t b_b []      ;
extern const uint16_t b_c []      ;
extern const uint16_t b_d []      ;
extern const uint16_t b_e []      ;
extern const uint16_t b_f []      ;
extern const uint16_t b_g []      ;
extern const uint16_t b_h []      ;
extern const uint16_t b_i []      ;
extern const uint16_t b_j []      ;
extern const uint16_t b_k []      ;
extern const uint16_t b_l []      ;
extern const uint16_t b_m []      ;
extern const uint16_t b_n []      ;
extern const uint16_t b_o []      ;
extern const uint16_t b_p []      ;
extern const uint16_t b_q []      ;
extern const uint16_t b_r []      ;
extern const uint16_t b_s []      ;
extern const uint16_t b_t []      ;
extern const uint16_t b_u []      ;
extern const uint16_t b_v []      ;
extern const uint16_t b_w []      ;
extern const uint16_t b_x []      ;
extern const uint16_t b_y []      ;
extern const uint16_t b_z []      ;
extern const uint16_t b_ocb []    ;
extern const uint16_t b_bar []    ;
extern const uint16_t b_ccb []    ;
extern const uint16_t b_tilda []  ;


extern const uint16_t m_fill []      ;

extern  const uint16_t* s_numbers[];
extern  const uint16_t* m_numbers[];
extern  const uint16_t* b_numbers[];













/* C++ detection */
#ifdef __cplusplus
}
#endif

 



















#endif
