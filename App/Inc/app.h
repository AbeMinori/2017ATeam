#ifndef __APP_H
#define __APP_H

/*NO Device mode*/
#define _NO_DEVICE 1

#include "DD_RC.h"
#include "DD_MD.h"

int appTask(void);
int appInit(void);

#define DD_NUM_OF_MD 8
#define DD_NUM_OF_AB 0
#define DD_NUM_OF_SV 0

/* 駆動用モータ */
#define MECHA1_MD0 0
#define MECHA1_MD1 1
#define MECHA1_MD2 2
#define MECHA1_MD3 3
/* 秘密道具移動用モータ */
#define MECHA1_MD4 4
#define MECHA1_MD5 5
/* 腕用モータ */
#define MECHA1_MD6 6
#define MECHA1_MD7 7
 
#define CENTRAL_THRESHOLD 0

#define MD_GAIN ( DD_MD_MAX_DUTY / DD_RC_ANALOG_MAX / 2 )

/* 腕振り用モータのduty */
#define _ARM_DUTY (DD_MD_MAX_DUTY-1)
#define MD_ARM_UP_DUTY -_ARM_DUTY
#define MD_ARM_DOWN_DUTY _ARM_DUTY

/* 秘密道具用モータのduty */
#define _WINDLASS_DUTY (DD_MD_MAX_DUTY-1)
#define MD_UP_DUTY _WINDLASS_DUTY
#define MD_DOWN_DUTY -_WINDLASS_DUTY
#define MD_BACK_DUTY _WINDLASS_DUTY
#define MD_FRONT_DUTY -_WINDLASS_DUTY

/* リミットスイッチ */
/* 秘密道具の横移動用のリミットスイッチ */
#define _SW_SIDE_LIMIT_GPIOxID GPIOCID
#define _SW_SIDE_LIMIT_GPIOPIN GPIO_PIN_0
#define _IS_PRESSED_SIDE_LIMITSW() (!(MW_GPIORead(_SW_SIDE_LIMIT_GPIOxID,_SW_SIDE_LIMIT_GPIOPIN)))

/* 秘密道具の縦移動用のリミットスイッチ */
#define _SW_VERTICAL_LIMIT_GPIOxID GPIOBID
#define _SW_VERTICAL_LIMIT_GPIOPIN GPIO_PIN_15
#define _IS_PRESSED_VERTICAL_LIMITSW() (!(MW_GPIORead(_SW_VERTICAL_LIMIT_GPIOxID,_SW_VERTICAL_LIMIT_GPIOPIN)))

#endif
