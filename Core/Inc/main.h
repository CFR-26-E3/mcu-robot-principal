/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define DIRB_LEVAGE1_Pin GPIO_PIN_13
#define DIRB_LEVAGE1_GPIO_Port GPIOC
#define DIRA_PAP_RAIL_Pin GPIO_PIN_0
#define DIRA_PAP_RAIL_GPIO_Port GPIOC
#define DIRB_PAP_RAIL_Pin GPIO_PIN_1
#define DIRB_PAP_RAIL_GPIO_Port GPIOC
#define DIRC_PAP_RAIL_Pin GPIO_PIN_2
#define DIRC_PAP_RAIL_GPIO_Port GPIOC
#define DIRD_PAP_RAIL_Pin GPIO_PIN_3
#define DIRD_PAP_RAIL_GPIO_Port GPIOC
#define ENCA_LEVAGE1_Pin GPIO_PIN_0
#define ENCA_LEVAGE1_GPIO_Port GPIOA
#define ENCB_LEVAGE1_Pin GPIO_PIN_1
#define ENCB_LEVAGE1_GPIO_Port GPIOA
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define CC_SDA_PINCE1_Pin GPIO_PIN_11
#define CC_SDA_PINCE1_GPIO_Port GPIOB
#define FDC_RAIL_AR_Pin GPIO_PIN_5
#define FDC_RAIL_AR_GPIO_Port GPIOA
#define ENCB_ROUE_DROITE_Pin GPIO_PIN_6
#define ENCB_ROUE_DROITE_GPIO_Port GPIOA
#define ENCA_ROUE_DROITE_Pin GPIO_PIN_7
#define ENCA_ROUE_DROITE_GPIO_Port GPIOA
#define DIRA_ROUE_DROITE_Pin GPIO_PIN_4
#define DIRA_ROUE_DROITE_GPIO_Port GPIOC
#define DIRB_ROUE_DROITE_Pin GPIO_PIN_5
#define DIRB_ROUE_DROITE_GPIO_Port GPIOC
#define DIRA_ROUE_GAUCHE_Pin GPIO_PIN_0
#define DIRA_ROUE_GAUCHE_GPIO_Port GPIOB
#define DIRB_ROUE_GAUCHE_Pin GPIO_PIN_1
#define DIRB_ROUE_GAUCHE_GPIO_Port GPIOB
#define DIRA_LEVAGE1_Pin GPIO_PIN_2
#define DIRA_LEVAGE1_GPIO_Port GPIOB
#define CC_SCL_PINCE1_Pin GPIO_PIN_10
#define CC_SCL_PINCE1_GPIO_Port GPIOB
#define PWMA_PAP_RAIL_Pin GPIO_PIN_14
#define PWMA_PAP_RAIL_GPIO_Port GPIOB
#define PWMB_PAP_RAIL_Pin GPIO_PIN_15
#define PWMB_PAP_RAIL_GPIO_Port GPIOB
#define PWM_ROUE_DROITE_Pin GPIO_PIN_7
#define PWM_ROUE_DROITE_GPIO_Port GPIOC
#define PWM_LEVAGE1_Pin GPIO_PIN_8
#define PWM_LEVAGE1_GPIO_Port GPIOC
#define PWM_ROUE_GAUCHE_Pin GPIO_PIN_9
#define PWM_ROUE_GAUCHE_GPIO_Port GPIOC
#define PWM_SERRAGE1_Pin GPIO_PIN_8
#define PWM_SERRAGE1_GPIO_Port GPIOA
#define PWM_SERRAGE2_Pin GPIO_PIN_9
#define PWM_SERRAGE2_GPIO_Port GPIOA
#define PWM_RETOURNE1_Pin GPIO_PIN_10
#define PWM_RETOURNE1_GPIO_Port GPIOA
#define PWM_RETOURNE2_Pin GPIO_PIN_11
#define PWM_RETOURNE2_GPIO_Port GPIOA
#define FDC_RAIL_AV_Pin GPIO_PIN_12
#define FDC_RAIL_AV_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define ECHO_GAUCHE_AV_Pin GPIO_PIN_15
#define ECHO_GAUCHE_AV_GPIO_Port GPIOA
#define TRIG_GAUCHE_AV_Pin GPIO_PIN_10
#define TRIG_GAUCHE_AV_GPIO_Port GPIOC
#define TRIG_GAUCHE_AR_Pin GPIO_PIN_11
#define TRIG_GAUCHE_AR_GPIO_Port GPIOC
#define TRIG_DROITE_AV_Pin GPIO_PIN_12
#define TRIG_DROITE_AV_GPIO_Port GPIOC
#define TRIG_DROITE_AR_Pin GPIO_PIN_2
#define TRIG_DROITE_AR_GPIO_Port GPIOD
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define ECHO_GAUCHE_AR_Pin GPIO_PIN_5
#define ECHO_GAUCHE_AR_GPIO_Port GPIOB
#define ENCB_ROUE_GAUCHE_Pin GPIO_PIN_6
#define ENCB_ROUE_GAUCHE_GPIO_Port GPIOB
#define ENCA_ROUE_DROITEB7_Pin GPIO_PIN_7
#define ENCA_ROUE_DROITEB7_GPIO_Port GPIOB
#define ECHO_DROITE_AV_Pin GPIO_PIN_8
#define ECHO_DROITE_AV_GPIO_Port GPIOB
#define ECHO_DROITE_AR_Pin GPIO_PIN_9
#define ECHO_DROITE_AR_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
