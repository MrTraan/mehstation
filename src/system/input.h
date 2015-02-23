#pragma once

#include "glib-2.0/glib.h"
#include "SDL2/SDL.h"

#include "system/consts.h"
#include "system/message.h"
#include "system/settings.h"

#define MEH_INPUT_NOT_PRESSED 0
#define MEH_INPUT_JUST_PRESSED 1
#define MEH_INPUT_HOLD 2

#define MEH_INPUT_MAX_AXIS (32767-1)

/*
 * InputManager role is to receive events from
 * keyboard, gamepads, ..., and to deal with them.
 */
typedef struct {
	/* application settings */
	Settings settings;

	/* set gamepad mapping */
	GHashTable*  keyboard_mapping;
	GHashTable*  gamepad_mapping;

	/* contains all the pressed buttons after reading of the events */
	guint buttons_state[MEH_INPUT_END];
	/* time at which the key produce a new message */
	guint buttons_next_message[MEH_INPUT_END];

	/* attached game pads */
	GQueue* gamepads;
} InputManager;


/* input manager */
InputManager* meh_input_manager_new(Settings settings);
void meh_input_manager_destroy(InputManager* input_manager);
void meh_input_manager_reset_buttons_state(InputManager* input_manager);
void meh_input_manager_read_event(InputManager* input_manager, SDL_Event* event);
GSList* meh_input_manager_generate_messages(InputManager* input_manager);
GSList* meh_input_manager_append_button_pressed(GSList* list, int pressed_button);
