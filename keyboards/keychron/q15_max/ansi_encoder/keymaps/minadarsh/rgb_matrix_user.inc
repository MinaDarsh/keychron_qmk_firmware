RGB_MATRIX_EFFECT(lesbian_flag)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static bool lesbian_flag(effect_params_t* params) {
	RGB_MATRIX_USE_LIMITS(led_min, led_max);
	for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
		for (uint8_t c = 0; c < MATRIX_COLS; c++) {
			if (g_led_config.matrix_co[r][c] != 255) {
				switch (r) {
				case 0:
					rgb_matrix_set_color(g_led_config.matrix_co[r][c], 194, 13, 0);
					break;
				case 1:
					rgb_matrix_set_color(g_led_config.matrix_co[r][c], 213, 45, 0);
					break;
				case 2:
					rgb_matrix_set_color(g_led_config.matrix_co[r][c], 255, 237, 209);
					break;
				case 3:
					rgb_matrix_set_color(g_led_config.matrix_co[r][c], 252, 61, 153);
					break;
				case 4:
					rgb_matrix_set_color(g_led_config.matrix_co[r][c], 179, 0, 116);
					break;
				default:
					break;
				}
			}
		}
	}
	return rgb_matrix_check_finished_leds(led_max);
}

// pink: 252, 30, 104 white: 255, 237, 209 blue: 61, 173, 252

#endif