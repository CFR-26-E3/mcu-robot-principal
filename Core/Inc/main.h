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
#include "stm32f7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "cmd_robot_pose_task.h"
#include "cmd_robot_vel_task.h"
#include "dc_motor.h"
#include "grip_task.h"
#include "lift_task.h"
#include "odometry_task.h"
#include "robot_config.h"
#include "servo_motor.h"
#include "spread_task.h"
#include "stepper_motor.h"
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
#define TIRETTE_Pin GPIO_PIN_6
#define TIRETTE_GPIO_Port GPIOE
#define ECHO_GAUCHE_AR_Pin GPIO_PIN_6
#define ECHO_GAUCHE_AR_GPIO_Port GPIOF
#define ECHO_GAUCHE_AV_Pin GPIO_PIN_7
#define ECHO_GAUCHE_AV_GPIO_Port GPIOF
#define ECHO_DROITE_AV_Pin GPIO_PIN_8
#define ECHO_DROITE_AV_GPIO_Port GPIOF
#define MCO_Pin GPIO_PIN_0
#define MCO_GPIO_Port GPIOH
#define ENCA_ROUE_GAUCHE_Pin GPIO_PIN_0
#define ENCA_ROUE_GAUCHE_GPIO_Port GPIOA
#define ENCB_ROUE_GAUCHE_Pin GPIO_PIN_1
#define ENCB_ROUE_GAUCHE_GPIO_Port GPIOA
#define ENCA_ROUE_DROITE_Pin GPIO_PIN_6
#define ENCA_ROUE_DROITE_GPIO_Port GPIOA
#define ENCB_ROUE_DROITE_Pin GPIO_PIN_7
#define ENCB_ROUE_DROITE_GPIO_Port GPIOA
#define DIRA_ROUE_GAUCHE_Pin GPIO_PIN_0
#define DIRA_ROUE_GAUCHE_GPIO_Port GPIOG
#define DIRB_ROUE_GAUCHE_Pin GPIO_PIN_1
#define DIRB_ROUE_GAUCHE_GPIO_Port GPIOG
#define PWM_ROUE_GAUCHE_Pin GPIO_PIN_9
#define PWM_ROUE_GAUCHE_GPIO_Port GPIOE
#define PWM_ROUE_DROITE_Pin GPIO_PIN_11
#define PWM_ROUE_DROITE_GPIO_Port GPIOE
#define PWM_LEVAGE_Pin GPIO_PIN_13
#define PWM_LEVAGE_GPIO_Port GPIOE
#define DIRA_ROUE_DROITE_Pin GPIO_PIN_14
#define DIRA_ROUE_DROITE_GPIO_Port GPIOB
#define DIRB_ROUE_DROITE_Pin GPIO_PIN_15
#define DIRB_ROUE_DROITE_GPIO_Port GPIOB
#define STLK_RX_Pin GPIO_PIN_8
#define STLK_RX_GPIO_Port GPIOD
#define STLK_TX_Pin GPIO_PIN_9
#define STLK_TX_GPIO_Port GPIOD
#define ENCA_LEVAGE_Pin GPIO_PIN_12
#define ENCA_LEVAGE_GPIO_Port GPIOD
#define ENCB_LEVAGE_Pin GPIO_PIN_13
#define ENCB_LEVAGE_GPIO_Port GPIOD
#define TRIG_GAUCHE_AR_Pin GPIO_PIN_4
#define TRIG_GAUCHE_AR_GPIO_Port GPIOG
#define USB_PowerSwitchOn_Pin GPIO_PIN_6
#define USB_PowerSwitchOn_GPIO_Port GPIOG
#define USB_OverCurrent_Pin GPIO_PIN_7
#define USB_OverCurrent_GPIO_Port GPIOG
#define PWM_SERRAGE_Pin GPIO_PIN_6
#define PWM_SERRAGE_GPIO_Port GPIOC
#define PWM_RETOURNE_1_Pin GPIO_PIN_7
#define PWM_RETOURNE_1_GPIO_Port GPIOC
#define PWM_RETOURNE_2_Pin GPIO_PIN_8
#define PWM_RETOURNE_2_GPIO_Port GPIOC
#define PWM_RETOURNE_3_Pin GPIO_PIN_9
#define PWM_RETOURNE_3_GPIO_Port GPIOC
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define PWM_RETOURNE_4_Pin GPIO_PIN_10
#define PWM_RETOURNE_4_GPIO_Port GPIOC
#define PWM_ECARTEMENT_Pin GPIO_PIN_11
#define PWM_ECARTEMENT_GPIO_Port GPIOC
#define ECHO_DROITE_AVD3_Pin GPIO_PIN_3
#define ECHO_DROITE_AVD3_GPIO_Port GPIOD
#define ECHO_DROITE_AVD3_EXTI_IRQn EXTI3_IRQn
#define TRIG_DROITE_AV_Pin GPIO_PIN_4
#define TRIG_DROITE_AV_GPIO_Port GPIOD
#define TRIG_GAUCHE_AV_Pin GPIO_PIN_10
#define TRIG_GAUCHE_AV_GPIO_Port GPIOG
#define INTER_EQUIPE_Pin GPIO_PIN_12
#define INTER_EQUIPE_GPIO_Port GPIOG
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define DIRA_LEVAGE_Pin GPIO_PIN_8
#define DIRA_LEVAGE_GPIO_Port GPIOB
#define DIRB_LEVAGE_Pin GPIO_PIN_9
#define DIRB_LEVAGE_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
