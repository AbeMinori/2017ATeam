#ifndef __APP_H
#define __APP_H

/*NO Device mode*/
#define _NO_DEVICE 0

#include "DD_RC.h"
#include "DD_MD.h"

int appTask(void);
int appInit(void);

#define DD_NUM_OF_MD 8
#define DD_NUM_OF_AB 1
#define DD_NUM_OF_SV 0

/* 駆動用モータ */
#define MECHA1_MD0 0
#define MECHA1_MD1 1
#define MECHA1_MD2 2
#define MECHA1_MD3 3
/* 腕回転用モータ */
#define MECHA1_MD4 4
/* ローラー機構の上下用モータ */
#define MECHA1_MD5 5
/* ローラー機構の回転用モータ */
#define MECHA1_MD6 6
#define MECHA1_MD7 7
 
#define CENTRAL_THRESHOLD 0

#define MD_GAIN ( DD_MD_MAX_DUTY / DD_RC_ANALOG_MAX / 2 )

/* 腕回転部のduty */
#define _ARM_DUTY (DD_MD_MAX_DUTY-1)
#define MD_RIGHT_ROTATE_DUTY -_ARM_DUTY
#define MD_LEFT_ROTATE_DUTY _ARM_DUTY

/* ローラー機構の上下部のduty */
#define _VERTICAL_DUTY (DD_MD_MAX_DUTY-1)
#define MD_ROLLER_UP_DUTY -_VERTICAL_DUTY
#define MD_ROLLER_DOWN_DUTY _VERTICAL_DUTY

/* ローラー機構の回転部のduty */
#define _ROTATE_DUTY (DD_MD_MAX_DUTY-1)
#define MD_ROTATE_DUTY _ROTATE_DUTY

/* 腕前方向回転用のリミットスイッチ */
#define _SW_RIGHT_LIMIT_GPIOxPIN GPIOBID
#define _SW_RIGHT_LIMIT_GPIOPIN GPIO_PIN_15
#define _IS_PRESSED_RIGHT_LIMITSW() (!(MW_GPIORead(_SW_RIGHT_LIMIT_GPIOxPIN,_SW_RIGHT_LIMIT_GPIOPIN)))

/* 腕後方向回転用のリミットスイッチ */
#define _SW_LEFT_LIMIT_GPIOxPIN GPIOCID
#define _SW_LEFT_LIMIT_GPIOPIN GPIO_PIN_0
#define _IS_PRESSED_LEFT_LIMITSW() (!(MW_GPIORead(_SW_LEFT_LIMIT_GPIOxPIN,_SW_LEFT_LIMIT_GPIOPIN)))

#define AB0 (1<<0)
#define AB1 (1<<1)

#endif
