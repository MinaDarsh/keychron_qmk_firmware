#pragma once

#undef PRODUCT
#define PRODUCT "Nicky\'s Q15 Max"

#if defined(RGB_MATRIX_ENABLE) || defined(LED_MATRIX_ENABLE)

# 	undef BT_HOST_LED_MATRIX_LIST

# 	define BT_HOST_LED_MATRIX_LIST \
		{ 40,  41,  42 }

#	undef P2P4G_HOST_LED_MATRIX_LIST

#	define P2P4G_HOST_LED_MATRIX_LIST \
		{ 43 }
#endif