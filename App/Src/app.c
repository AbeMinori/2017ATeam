#include "app.h"
#include "DD_Gene.h"
#include "DD_RCDefinition.h"
#include "SystemTaskManager.h"
#include <stdlib.h>
#include "message.h"
#include "MW_GPIO.h"
#include "MW_IWDG.h"
#include "MW_flash.h"
#include "constManager.h"
#include "trapezoid_ctrl.h"

/*suspensionSystem*/
static
int suspensionSystem(void);

static
int armSystem(void);

static
int rollerVertical(void);

static
int rollerRotate(void);

static
int ABSystem(void);

/*メモ
 *g_ab_h...ABのハンドラ
 *g_md_h...MDのハンドラ
 *
 *g_rc_data...RCのデータ
 */

#define WRITE_ADDR (const void*)(0x8000000+0x400*(128-1))/*128[KiB]*/
  flashError_t checkFlashWrite(void){
  const char data[]="HelloWorld!!TestDatas!!!\n"
    "however you like this microcomputer, you don`t be kind to this computer.";
  return MW_flashWrite(data,WRITE_ADDR,sizeof(data));
}

int appInit(void){
  message("msg","hell");

  /* switch(checkFlashWrite()){ */
  /* case MW_FLASH_OK: */
  /*   message("msg","FLASH WRITE TEST SUCCESS\n%s",(const char*)WRITE_ADDR); */
  /*   break; */
  /* case MW_FLASH_LOCK_FAILURE: */
  /*   message("err","FLASH WRITE TEST LOCK FAILURE\n"); */
  /*   break; */
  /* case MW_FLASH_UNLOCK_FAILURE: */
  /*   message("err","FLASH WRITE TEST UNLOCK FAILURE\n"); */
  /*   break; */
  /* case MW_FLASH_ERASE_VERIFY_FAILURE: */
  /*   message("err","FLASH ERASE VERIFY FAILURE\n"); */
  /*   break; */
  /* case MW_FLASH_ERASE_FAILURE: */
  /*   message("err","FLASH ERASE FAILURE\n"); */
  /*   break; */
  /* case MW_FLASH_WRITE_VERIFY_FAILURE: */
  /*   message("err","FLASH WRITE TEST VERIFY FAILURE\n"); */
  /*   break; */
  /* case MW_FLASH_WRITE_FAILURE: */
  /*   message("err","FLASH WRITE TEST FAILURE\n"); */
  /*   break;         */
  /* default: */
  /*   message("err","FLASH WRITE TEST UNKNOWN FAILURE\n"); */
  /*   break; */
  /* } */
  /* flush(); */

  ad_init();

  message("msg","plz confirm\n%d\n",g_adjust.rightadjust.value);

  /*GPIO の設定などでMW,GPIOではHALを叩く*/
  return EXIT_SUCCESS;
}

/*application tasks*/
int appTask(void){
  int ret=0;

  if(__RC_ISPRESSED_R1(g_rc_data)&&__RC_ISPRESSED_R2(g_rc_data)&&
     __RC_ISPRESSED_L1(g_rc_data)&&__RC_ISPRESSED_L2(g_rc_data)){
    while(__RC_ISPRESSED_R1(g_rc_data)||__RC_ISPRESSED_R2(g_rc_data)||
	  __RC_ISPRESSED_L1(g_rc_data)||__RC_ISPRESSED_L2(g_rc_data));
    ad_main();
  }
  
  /*それぞれの機構ごとに処理をする*/
  /*途中必ず定数回で終了すること。*/
  ret = suspensionSystem();
  if(ret){
    return ret;
  }

  ret = armSystem();
  if(ret){
    return ret;
  }

  ret = rollerVertical();
  if(ret){
    return ret;
  }

  ret = rollerRotate();
  if(ret){
    return ret;
  }

  ret = ABSystem();
  if(ret){
    return ret;
  }
  
  
  return EXIT_SUCCESS;
}


/*プライベート 足回りシステム*/
static
int suspensionSystem(void){
  const int num_of_motor = 4;/*モータの個数*/
  //  int rc_analogdata;/*アナログデータ*/
  unsigned int idx;/*インデックス*/
  int i,m,x,y,w;

  const tc_const_t tc ={
    .inc_con = 100,
    .dec_con = 225,
  };

  x = DD_RCGetLY(g_rc_data);
  y = DD_RCGetLX(g_rc_data);
  if(__RC_ISPRESSED_R2(g_rc_data)){
    w = 60;
  }else if(__RC_ISPRESSED_L2(g_rc_data)){
    w = -60;
  } else {
    w = 0;
  }


  /*for each motor*/
  for(i=0;i<num_of_motor;i++){
    /*それぞれの差分*/
    switch(i){
    case 0:
      idx = MECHA1_MD0;
      m =  x + y + w;
      break;
    case 1:
      idx = MECHA1_MD1;
      m =  x - y + w;
      break;     
    case 2:
      idx = MECHA1_MD2;
      m = - x - y + w;
      break;
    case 3:
      idx = MECHA1_MD3;
      m = - x + y + w;
      break;
    
    default:
      return EXIT_FAILURE;
    }

   
    trapezoidCtrl(m * MD_GAIN,&g_md_h[idx],&tc);
  }

  return EXIT_SUCCESS;
}

/* アームの回転 */
static
int armSystem(void){
  const tc_const_t arm_tcon = {
    .inc_con = 250,
    .dec_con = 250,
  };

  /* アームの回転部のduty */
  int arm_target;
  const int ahead_rotate_duty = MD_AHEAD_ROTATE_DUTY;
  const int backward_rotate_duty = MD_BACKWARD_ROTATE_DUTY;

  /* コントローラのボタンは押されてるか */
  if(__RC_ISPRESSED_RIGHT(g_rc_data)){
    arm_target = ahead_rotate_duty;
    trapezoidCtrl(arm_target,&g_md_h[MECHA1_MD4],&arm_tcon);
  }else if(__RC_ISPRESSED_LEFT(g_rc_data)){
    arm_target = backward_rotate_duty;
    trapezoidCtrl(arm_target,&g_md_h[MECHA1_MD4],&arm_tcon);
  }else{
    arm_target = 0;
    trapezoidCtrl(arm_target,&g_md_h[MECHA1_MD4],&arm_tcon);
  }

  /* リミットスイッチは押されてるか */
  /*if(_IS_PRESSED_AHEAD_LIMITSW()){
    arm_target = 0;
    trapezoidCtrl(arm_target,&g_md_h[MECHA1_MD4],&arm_tcon);
  }else if(_IS_PRESSED_BACKWARD_LIMITSW()){
    arm_target = 0;
    trapezoidCtrl(arm_target,&g_md_h[MECHA1_MD4],&arm_tcon);
  }
  */
  return EXIT_SUCCESS;
} 

/* 腕振り */
static
int ABSystem(void){

  /* コントローラのボタンは押されてるか */
  g_ab_h[0].dat = 0x00;
  if(__RC_ISPRESSED_CIRCLE(g_rc_data)){
    g_ab_h[0].dat |= AB0;
  }
  return EXIT_SUCCESS;
}

/* ローラー機構の上下 */
static
int rollerVertical (void){
  const tc_const_t vertical_tcon = {
    .inc_con = 250,
    .dec_con = 250,
  };

  /* ローラー機構上下部のduty */
  int vertical_target;
  const int roller_up_duty = MD_ROLLER_UP_DUTY;
  const int roller_down_duty = MD_ROLLER_DOWN_DUTY;


  /* コントローラのボタンは押されてるか */
  if((DD_RCGetRY(g_rc_data)) > 0){
    vertical_target = roller_up_duty;
  }else if((DD_RCGetRY(g_rc_data)) < 0){
    vertical_target = roller_down_duty;
  }else{
    vertical_target = 0;
  }

  /* 台形制御 */
  trapezoidCtrl(vertical_target,&g_md_h[MECHA1_MD5],&vertical_tcon);

  return EXIT_SUCCESS;
}

/* ローラー機構の回転 */
static
int rollerRotate(void){
  const tc_const_t rotate_tcon = {
    .inc_con = 500,
    .dec_con = 500,
  };

  /* ローラー機構回転部のduty */
  int rotate_target;
  const int rotate_duty = MD_ROTATE_DUTY;
  
  /* コントローラのボタンは押されてるか */
  if(__RC_ISPRESSED_L1(g_rc_data)){
    rotate_target = rotate_duty;
  }else{
    rotate_target = 0;
  }

  /* 台形制御 */
  trapezoidCtrl(rotate_target,&g_md_h[MECHA1_MD6],&rotate_tcon);
  trapezoidCtrl(-rotate_target,&g_md_h[MECHA1_MD7],&rotate_tcon);

  return EXIT_SUCCESS;
}
