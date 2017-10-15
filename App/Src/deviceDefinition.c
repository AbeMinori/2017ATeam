#include "DD_Gene.h"
#include "app.h"
#include "SystemTaskManager.h"

/*Address Definition*/
#if DD_NUM_OF_MD
/*MD Definition*/
DD_MDHand_t g_md_h[DD_NUM_OF_MD] = {
  { 0x10, /* address */
    0, /* default duty */
    D_MMOD_FREE, /* mode */
  },
  { 0x11, /* address */
    0, /* default duty */
    D_MMOD_FREE, /* mode */
  },
  { 0x12, 
    0, /* default duty */
    D_MMOD_FREE, /* mode */
  },
  { 0x13,
    0, /* default duty */
    D_MMOD_FREE, /* mode */
  },
  { 0x14,
    0, /* default duty */
    D_MMOD_FREE, /* mode */
  },
};
#endif
