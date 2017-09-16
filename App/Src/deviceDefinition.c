#include "DD_Gene.h"
#include "app.h"
#include "SystemTaskManager.h"

/*Address Definition*/
#if DD_NUM_OF_MD
/*MD Definition*/
DD_MDHand_t g_md_h[DD_NUM_OF_MD] = {
  { .add = 0x10, /* address */
    .duty = 0, /* default duty */
    .mode = D_MMOD_FREE, /* mode */
  },
  { .add = 0x11, /* address */
    .duty = 0, /* default duty */
    .mode = D_MMOD_FREE, /* mode */
  },
  { .add = 0x12, 
    .duty = 0, /* default duty */
    .mode = D_MMOD_FREE, /* mode */
  },
  { .add = 0x13,
    .duty = 0, /* default duty */
    .mode = D_MMOD_FREE, /* mode */
  },
  { .add = 0x14,
    .duty = 0, /* default duty */
    .mode = D_MMOD_FREE, /* mode */
  },
  { .add = 0x15,
    .duty = 0, /* default duty */
    .mode = D_MMOD_FREE, /* mode */
  },
  { .add = 0x16,
    .duty = 0, /* default duty */
    .mode = D_MMOD_FREE, /* mode */
  },
  { .add = 0x17,
    .duty = 0, /* default duty */
    .mode = D_MMOD_FREE, /* mode */
  },
};
#endif
#if DD_NUM_OF_AB
/*AB Definition*/
DD_ABHand_t g_ab_h[DD_NUM_OF_AB] = {
  { .add = 0x11, /* address */
    .dat = 0x00, /* data */
  },
};
#endif
