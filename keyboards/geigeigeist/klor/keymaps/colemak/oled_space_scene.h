#pragma once

#define SPACE_SCENE_FRAME_MS 33
#define SPACE_FIELD_CENTER_X (OLED_DISPLAY_WIDTH / 2)
#define SPACE_FIELD_CENTER_Y (OLED_DISPLAY_HEIGHT / 2)
#define SPACE_PROJECTION_SCALE 44

#define SPACE_Z_SHIFT 4
#define SPACE_Z_ONE (1 << SPACE_Z_SHIFT)

#define SPACE_TRIANGLE_CENTER_X (OLED_DISPLAY_WIDTH / 2)
#define SPACE_TRIANGLE_TOP_Y 13
#define SPACE_TRIANGLE_HEIGHT 38
#define SPACE_TRIANGLE_HALF_BASE 22

#define SPACE_STAR_COUNT 16
#define SPACE_PLANET_COUNT 2
#define SPACE_STAR_RESPAWN_Z16 (96 * SPACE_Z_ONE)
#define SPACE_STAR_MIN_Z16 (6 * SPACE_Z_ONE)
#define SPACE_PLANET_RESPAWN_Z16 (104 * SPACE_Z_ONE)
#define SPACE_PLANET_MIN_Z16 (10 * SPACE_Z_ONE)
#define SPACE_STAR_BASE_SPEED 5
#define SPACE_PLANET_BASE_SPEED 3

typedef struct {
    int16_t  x;
    int16_t  y;
    uint16_t z16;
    uint8_t  speed;
    bool     cross;
} space_star_t;

typedef struct {
    int16_t  x;
    int16_t  y;
    uint16_t z16;
    uint8_t  radius;
    uint8_t  speed;
    bool     ringed;
} space_planet_t;

static space_star_t   space_stars[SPACE_STAR_COUNT];
static space_planet_t space_planets[SPACE_PLANET_COUNT];
static bool           space_scene_initialized = false;
static uint32_t       space_scene_last_frame  = 0;
static uint32_t       space_scene_rng         = 0x9E3779B9u;
static uint8_t        space_scene_twinkle     = 0;

static uint8_t space_scene_random_u8(void) {
    space_scene_rng = space_scene_rng * 1664525u + 1013904223u;
    return (uint8_t)(space_scene_rng >> 24);
}

static int16_t space_scene_random_range(int16_t min, int16_t max) {
    return min + (space_scene_random_u8() % (uint8_t)(max - min + 1));
}

static int16_t space_scene_abs16(int16_t value) {
    return value < 0 ? -value : value;
}

static int16_t space_scene_max16(int16_t a, int16_t b) {
    return a > b ? a : b;
}

static void space_scene_set_pixel(int16_t x, int16_t y, bool on) {
    if (x < 0 || x >= OLED_DISPLAY_WIDTH || y < 0 || y >= OLED_DISPLAY_HEIGHT) {
        return;
    }

    oled_write_pixel((uint8_t)x, (uint8_t)y, on);
}

static int16_t space_scene_project_x(int16_t world_x, uint16_t z16) {
    return SPACE_FIELD_CENTER_X + ((int32_t)world_x * SPACE_PROJECTION_SCALE * SPACE_Z_ONE) / z16;
}

static int16_t space_scene_project_y(int16_t world_y, uint16_t z16) {
    return SPACE_FIELD_CENTER_Y + ((int32_t)world_y * SPACE_PROJECTION_SCALE * SPACE_Z_ONE) / z16;
}

static void space_scene_draw_line(int16_t x0, int16_t y0, int16_t x1, int16_t y1) {
    const int16_t dx    = x1 - x0;
    const int16_t dy    = y1 - y0;
    const int16_t steps = space_scene_max16(space_scene_abs16(dx), space_scene_abs16(dy));

    if (steps == 0) {
        space_scene_set_pixel(x0, y0, true);
        return;
    }

    for (int16_t i = 0; i <= steps; ++i) {
        space_scene_set_pixel(x0 + (dx * i) / steps, y0 + (dy * i) / steps, true);
    }
}

static void space_scene_draw_filled_circle(int16_t cx, int16_t cy, uint8_t radius) {
    const int16_t radius_sq = radius * radius;

    for (int16_t dy = -radius; dy <= radius; ++dy) {
        for (int16_t dx = -radius; dx <= radius; ++dx) {
            if (dx * dx + dy * dy <= radius_sq) {
                space_scene_set_pixel(cx + dx, cy + dy, true);
            }
        }
    }
}

static void space_scene_draw_planet(const space_planet_t *planet) {
    const int16_t x = space_scene_project_x(planet->x, planet->z16);
    const int16_t y = space_scene_project_y(planet->y, planet->z16);
    const uint8_t radius = planet->radius + (uint8_t)((SPACE_PLANET_RESPAWN_Z16 > planet->z16 ? (SPACE_PLANET_RESPAWN_Z16 - planet->z16) : 0) / (24 * SPACE_Z_ONE));

    space_scene_draw_filled_circle(x, y, radius);

    if (planet->ringed && radius >= 4) {
        space_scene_draw_line(x - radius - 2, y, x + radius + 2, y);
    }
}

static void space_scene_draw_star(const space_star_t *star) {
    const int16_t x = space_scene_project_x(star->x, star->z16);
    const int16_t y = space_scene_project_y(star->y, star->z16);

    space_scene_set_pixel(x, y, true);

    if (star->cross || star->z16 < (22 * SPACE_Z_ONE)) {
        space_scene_set_pixel(x - 1, y, true);
        space_scene_set_pixel(x + 1, y, true);
        space_scene_set_pixel(x, y - 1, true);
        space_scene_set_pixel(x, y + 1, true);
    }

    if (star->z16 < (14 * SPACE_Z_ONE) && ((space_scene_twinkle + (uint8_t)star->x) & 0x01)) {
        space_scene_set_pixel(x - 1, y - 1, true);
        space_scene_set_pixel(x + 1, y + 1, true);
        space_scene_set_pixel(x - 1, y + 1, true);
        space_scene_set_pixel(x + 1, y - 1, true);
    }
}

static void space_scene_draw_triangle(void) {
    const int16_t apex_x      = SPACE_TRIANGLE_CENTER_X;
    const int16_t apex_y      = SPACE_TRIANGLE_TOP_Y;
    const int16_t base_y      = SPACE_TRIANGLE_TOP_Y + SPACE_TRIANGLE_HEIGHT - 1;
    const int16_t left_base_x = SPACE_TRIANGLE_CENTER_X - SPACE_TRIANGLE_HALF_BASE;
    const int16_t right_base_x = SPACE_TRIANGLE_CENTER_X + SPACE_TRIANGLE_HALF_BASE;

    for (uint8_t row = 0; row < SPACE_TRIANGLE_HEIGHT; ++row) {
        const int16_t y          = SPACE_TRIANGLE_TOP_Y + row;
        const int16_t half_width = (SPACE_TRIANGLE_HALF_BASE * row) / (SPACE_TRIANGLE_HEIGHT - 1);

        for (int16_t x = SPACE_TRIANGLE_CENTER_X - half_width; x <= SPACE_TRIANGLE_CENTER_X + half_width; ++x) {
            space_scene_set_pixel(x, y, false);
        }
    }

    space_scene_draw_line(apex_x, apex_y, left_base_x, base_y);
    space_scene_draw_line(apex_x, apex_y, right_base_x, base_y);
    space_scene_draw_line(left_base_x, base_y, right_base_x, base_y);
}

static void space_scene_respawn_star(space_star_t *star) {
    do {
        star->x = space_scene_random_range(-28, 28);
        star->y = space_scene_random_range(-18, 18);
    } while (space_scene_abs16(star->x) + space_scene_abs16(star->y) < 8);

    star->z16   = (72 + (space_scene_random_u8() % 24)) * SPACE_Z_ONE;
    star->speed = 1 + (space_scene_random_u8() % 3);
    star->cross = (space_scene_random_u8() & 0x01) != 0;
}

static void space_scene_respawn_planet(space_planet_t *planet) {
    do {
        planet->x = space_scene_random_range(-24, 24);
        planet->y = space_scene_random_range(-14, 14);
    } while (space_scene_abs16(planet->x) + space_scene_abs16(planet->y) < 14);

    planet->z16    = (88 + (space_scene_random_u8() % 16)) * SPACE_Z_ONE;
    planet->radius = 2 + (space_scene_random_u8() % 2);
    planet->speed  = 1 + (space_scene_random_u8() % 2);
    planet->ringed = (space_scene_random_u8() & 0x01) != 0;
}

static bool space_scene_star_offscreen(const space_star_t *star) {
    const int16_t x = space_scene_project_x(star->x, star->z16);
    const int16_t y = space_scene_project_y(star->y, star->z16);

    return x < -2 || x > OLED_DISPLAY_WIDTH + 1 || y < -2 || y > OLED_DISPLAY_HEIGHT + 1;
}

static bool space_scene_planet_offscreen(const space_planet_t *planet) {
    const int16_t x = space_scene_project_x(planet->x, planet->z16);
    const int16_t y = space_scene_project_y(planet->y, planet->z16);
    const uint8_t radius = planet->radius + (uint8_t)((SPACE_PLANET_RESPAWN_Z16 > planet->z16 ? (SPACE_PLANET_RESPAWN_Z16 - planet->z16) : 0) / (24 * SPACE_Z_ONE));

    return x < -(int16_t)(radius + 2) || x > OLED_DISPLAY_WIDTH + radius + 1 || y < -(int16_t)(radius + 2) || y > OLED_DISPLAY_HEIGHT + radius + 1;
}

static void space_scene_reset(void) {
    for (uint8_t i = 0; i < SPACE_STAR_COUNT; ++i) {
        space_scene_respawn_star(&space_stars[i]);
        space_stars[i].z16 = SPACE_STAR_MIN_Z16 + (uint16_t)(12 + (space_scene_random_u8() % 79)) * SPACE_Z_ONE;
    }

    for (uint8_t i = 0; i < SPACE_PLANET_COUNT; ++i) {
        space_scene_respawn_planet(&space_planets[i]);
        space_planets[i].z16 = SPACE_PLANET_MIN_Z16 + (uint16_t)(16 + (space_scene_random_u8() % 78)) * SPACE_Z_ONE;
    }

    space_scene_twinkle     = 0;
    space_scene_last_frame  = timer_read32() - SPACE_SCENE_FRAME_MS;
    space_scene_rng         = 0x9E3779B9u;
    space_scene_initialized = true;
}

static void space_scene_update(uint16_t elapsed_ms) {
    const uint8_t wpm = get_current_wpm();

    for (uint8_t i = 0; i < SPACE_STAR_COUNT; ++i) {
        const uint16_t speed16_per_s = (uint16_t)(SPACE_STAR_BASE_SPEED + space_stars[i].speed + (wpm / 7)) * SPACE_Z_ONE;
        uint16_t       delta16       = ((uint32_t)speed16_per_s * elapsed_ms) / 1000;

        if (delta16 == 0) {
            delta16 = 1;
        }

        space_stars[i].z16 = (space_stars[i].z16 > delta16) ? (space_stars[i].z16 - delta16) : 0;

        if (space_stars[i].z16 <= SPACE_STAR_MIN_Z16 || space_scene_star_offscreen(&space_stars[i])) {
            space_scene_respawn_star(&space_stars[i]);
        }
    }

    for (uint8_t i = 0; i < SPACE_PLANET_COUNT; ++i) {
        const uint16_t speed16_per_s = (uint16_t)(SPACE_PLANET_BASE_SPEED + space_planets[i].speed + (wpm / 18)) * SPACE_Z_ONE;
        uint16_t       delta16       = ((uint32_t)speed16_per_s * elapsed_ms) / 1000;

        if (delta16 == 0) {
            delta16 = 1;
        }

        space_planets[i].z16 = (space_planets[i].z16 > delta16) ? (space_planets[i].z16 - delta16) : 0;

        if (space_planets[i].z16 <= SPACE_PLANET_MIN_Z16 || space_scene_planet_offscreen(&space_planets[i])) {
            space_scene_respawn_planet(&space_planets[i]);
        }
    }

    ++space_scene_twinkle;
}

static void space_scene_render(void) {
    oled_clear();

    for (uint8_t i = 0; i < SPACE_STAR_COUNT; ++i) {
        space_scene_draw_star(&space_stars[i]);
    }

    for (uint8_t i = 0; i < SPACE_PLANET_COUNT; ++i) {
        space_scene_draw_planet(&space_planets[i]);
    }

    space_scene_draw_triangle();
}

bool oled_task_user(void) {
    if (!space_scene_initialized) {
        space_scene_reset();
    }

    if (timer_elapsed32(space_scene_last_frame) >= SPACE_SCENE_FRAME_MS) {
        uint32_t elapsed_ms = timer_elapsed32(space_scene_last_frame);
        if (elapsed_ms > 100) {
            elapsed_ms = 100;
        }

        space_scene_last_frame = timer_read32();
        space_scene_update((uint16_t)elapsed_ms);
        space_scene_render();
    }

    return false;
}
