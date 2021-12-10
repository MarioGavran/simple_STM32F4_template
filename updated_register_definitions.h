#define FSMC_BCR1_MTYP_Pos           (2U)                                      
#define FSMC_BCR1_MTYP_Msk           (0x3U << FSMC_BCR1_MTYP_Pos)              /*!< 0x0000000C */

#define FSMC_BCR1_CPSIZE_Pos         (16U)                                     
#define FSMC_BCR1_CPSIZE_Msk         (0x7U << FSMC_BCR1_CPSIZE_Pos)            /*!< 0x00070000 */

#define FSMC_BCR1_CCLKEN_Msk         (0x1U << FSMC_BCR1_CCLKEN_Pos)            /*!< 0x00100000 */
#define FSMC_BCR1_CCLKEN             FSMC_BCR1_CCLKEN_Msk                      /*!<Continous clock enable     */

#define FSMC_BCR1_WFDIS_Msk          (0x1U << FSMC_BCR1_WFDIS_Pos)             /*!< 0x00200000 */
#define FSMC_BCR1_WFDIS              FSMC_BCR1_WFDIS_Msk                       /*!<Write FIFO Disable         */

#define FSMC_BTR1_ACCMOD_Pos         (28U)                                     
#define FSMC_BTR1_ACCMOD_Msk         (0x3U << FSMC_BTR1_ACCMOD_Pos)            /*!< 0x30000000 */

#define FSMC_BTR1_BUSTURN_Pos        (16U)                                     
#define FSMC_BTR1_BUSTURN_Msk        (0xFU << FSMC_BTR1_BUSTURN_Pos)           /*!< 0x000F0000 */

#define FSMC_BTR1_DATAST_Pos         (8U)                                      
#define FSMC_BTR1_DATAST_Msk         (0xFFU << FSMC_BTR1_DATAST_Pos)           /*!< 0x0000FF00 */

#define FSMC_BTR1_ADDSET_Pos         (0U)                                      
#define FSMC_BTR1_ADDSET_Msk         (0xFU << FSMC_BTR1_ADDSET_Pos)            /*!< 0x0000000F */

#define FSMC_BWTR1_ACCMOD_Pos        (28U)                                     
#define FSMC_BWTR1_ACCMOD_Msk        (0x3U << FSMC_BWTR1_ACCMOD_Pos)           /*!< 0x30000000 */

#define FSMC_BWTR1_BUSTURN_Pos       (16U)                                     
#define FSMC_BWTR1_BUSTURN_Msk       (0xFU << FSMC_BWTR1_BUSTURN_Pos)          /*!< 0x000F0000 */

#define FSMC_BWTR1_DATAST_Pos        (8U)                                      
#define FSMC_BWTR1_DATAST_Msk        (0xFFU << FSMC_BWTR1_DATAST_Pos)          /*!< 0x0000FF00 */

#define FSMC_BWTR1_ADDSET_Pos        (0U)                                      
#define FSMC_BWTR1_ADDSET_Msk        (0xFU << FSMC_BWTR1_ADDSET_Pos)           /*!< 0x0000000F */




#define GPIO_MODER_MODER11_Pos       (22U)                                 
#define GPIO_MODER_MODER11_Msk       (0x3U << GPIO_MODER_MODER11_Pos)      /*!< 0x00C00000 */

#define GPIO_MODER_MODER12_Pos       (24U)                                 
#define GPIO_MODER_MODER12_Msk       (0x3U << GPIO_MODER_MODER12_Pos)      /*!< 0x03000000 */

#define GPIO_PUPDR_PUPDR6_Pos        (12U)                                 
#define GPIO_PUPDR_PUPDR6_Msk        (0x3U << GPIO_PUPDR_PUPDR6_Pos)       /*!< 0x00003000 */

#define GPIO_PUPDR_PUPDR11_Pos       (22U)                                 
#define GPIO_PUPDR_PUPDR11_Msk       (0x3U << GPIO_PUPDR_PUPDR11_Pos)      /*!< 0x00C00000 */

#define GPIO_PUPDR_PUPDR4_Pos        (8U)                                  
#define GPIO_PUPDR_PUPDR4_Msk        (0x3U << GPIO_PUPDR_PUPDR4_Pos)       /*!< 0x00000300 */

#define GPIO_PUPDR_PUPDR5_Pos        (10U)                                 
#define GPIO_PUPDR_PUPDR5_Msk        (0x3U << GPIO_PUPDR_PUPDR5_Pos)       /*!< 0x00000C00 */

#define GPIO_PUPDR_PUPDR7_Pos        (14U)                                 
#define GPIO_PUPDR_PUPDR7_Msk        (0x3U << GPIO_PUPDR_PUPDR7_Pos)       /*!< 0x0000C000 */

#define GPIO_PUPDR_PUPDR14_Pos       (28U)                                 
#define GPIO_PUPDR_PUPDR14_Msk       (0x3U << GPIO_PUPDR_PUPDR14_Pos)      /*!< 0x30000000 */

#define GPIO_PUPDR_PUPDR15_Pos       (30U)                                 
#define GPIO_PUPDR_PUPDR15_Msk       (0x3U << GPIO_PUPDR_PUPDR15_Pos)      /*!< 0xC0000000 */

#define GPIO_PUPDR_PUPDR11_Pos       (22U)                                 
#define GPIO_PUPDR_PUPDR11_Msk       (0x3U << GPIO_PUPDR_PUPDR11_Pos)      /*!< 0x00C00000 */

#define GPIO_PUPDR_PUPDR12_Pos       (24U)                                 
#define GPIO_PUPDR_PUPDR12_Msk       (0x3U << GPIO_PUPDR_PUPDR12_Pos)      /*!< 0x03000000 */

#define GPIO_PUPDR_PUPDR8_Pos        (16U)                                 
#define GPIO_PUPDR_PUPDR8_Msk        (0x3U << GPIO_PUPDR_PUPDR8_Pos)       /*!< 0x00030000 */

#define GPIO_PUPDR_PUPDR9_Pos        (18U)                                 
#define GPIO_PUPDR_PUPDR9_Msk        (0x3U << GPIO_PUPDR_PUPDR9_Pos)       /*!< 0x000C0000 */

#define GPIO_PUPDR_PUPDR10_Pos       (20U)                                 
#define GPIO_PUPDR_PUPDR10_Msk       (0x3U << GPIO_PUPDR_PUPDR10_Pos)      /*!< 0x00300000 */

#define GPIO_PUPDR_PUPDR13_Pos       (26U)                                 
#define GPIO_PUPDR_PUPDR13_Msk       (0x3U << GPIO_PUPDR_PUPDR13_Pos)      /*!< 0x0C000000 */






#define FSMC_BCR1_MTYP_Pos           (2U)                                      
#define FSMC_BCR1_MTYP_Msk           (0x3U << FSMC_BCR1_MTYP_Pos)              /*!< 0x0000000C */

#define FSMC_BCR1_CPSIZE_Pos         (16U)                                     
#define FSMC_BCR1_CPSIZE_Msk         (0x7U << FSMC_BCR1_CPSIZE_Pos)            /*!< 0x00070000 */

#define FSMC_BCR1_CCLKEN_Pos         (20U)                                     
#define FSMC_BCR1_CCLKEN_Msk         (0x1U << FSMC_BCR1_CCLKEN_Pos)            /*!< 0x00100000 */
#define FSMC_BCR1_CCLKEN             FSMC_BCR1_CCLKEN_Msk                      /*!<Continous clock enable     */

#define FSMC_BCR1_WFDIS_Pos          (21U)                                     
#define FSMC_BCR1_WFDIS_Msk          (0x1U << FSMC_BCR1_WFDIS_Pos)             /*!< 0x00200000 */
#define FSMC_BCR1_WFDIS              FSMC_BCR1_WFDIS_Msk                       /*!<Write FIFO Disable         */

#define FSMC_BTR1_ACCMOD_Pos         (28U)                                     
#define FSMC_BTR1_ACCMOD_Msk         (0x3U << FSMC_BTR1_ACCMOD_Pos)            /*!< 0x30000000 */

#define FSMC_BTR1_BUSTURN_Pos        (16U)                                     
#define FSMC_BTR1_BUSTURN_Msk        (0xFU << FSMC_BTR1_BUSTURN_Pos)           /*!< 0x000F0000 */

#define FSMC_BTR1_DATAST_Pos         (8U)                                      
#define FSMC_BTR1_DATAST_Msk         (0xFFU << FSMC_BTR1_DATAST_Pos)           /*!< 0x0000FF00 */

#define FSMC_BTR1_ADDSET_Pos         (0U)                                      
#define FSMC_BTR1_ADDSET_Msk         (0xFU << FSMC_BTR1_ADDSET_Pos)            /*!< 0x0000000F */

#define FSMC_BWTR1_ACCMOD_Pos        (28U)                                     
#define FSMC_BWTR1_ACCMOD_Msk        (0x3U << FSMC_BWTR1_ACCMOD_Pos)           /*!< 0x30000000 */

#define FSMC_BWTR1_BUSTURN_Pos       (16U)                                     
#define FSMC_BWTR1_BUSTURN_Msk       (0xFU << FSMC_BWTR1_BUSTURN_Pos)          /*!< 0x000F0000 */

#define FSMC_BWTR1_DATAST_Pos        (8U)                                      
#define FSMC_BWTR1_DATAST_Msk        (0xFFU << FSMC_BWTR1_DATAST_Pos)          /*!< 0x0000FF00 */

#define FSMC_BWTR1_ADDSET_Pos        (0U)                                      
#define FSMC_BWTR1_ADDSET_Msk        (0xFU << FSMC_BWTR1_ADDSET_Pos)           /*!< 0x0000000F */


#define GPIO_AFRH_AFSEL9_Pos         (4U)                                  
#define GPIO_AFRH_AFSEL9_Msk         (0xFU << GPIO_AFRH_AFSEL9_Pos)        /*!< 0x000000F0 */
#define GPIO_AFRH_AFSEL9             GPIO_AFRH_AFSEL9_Msk                  

#define RCC_CFGR_MCO2_Pos            (30U)                               
#define RCC_CFGR_MCO2_Msk            (0x3U << RCC_CFGR_MCO2_Pos)         /*!< 0xC0000000 */

#define RCC_CFGR_MCO2PRE_Pos         (27U)                               
#define RCC_CFGR_MCO2PRE_Msk         (0x7U << RCC_CFGR_MCO2PRE_Pos)      /*!< 0x38000000 */

