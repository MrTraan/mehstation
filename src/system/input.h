#pragma once

#include "glib-2.0/glib.h"
#include "SDL2/SDL.h"

#include "system/consts.h"
#include "system/event.h"

/*
 * InputManager role is to receive events from
 * keyboard, gamepads, ..., and to deal with them.
 */
typedef struct {
	struct App* app;
	GHashTable*  keyboard_mapping;

	/* contains all the pressed buttons after reading of the events */
	gboolean pressed_buttons[MEH_INPUT_END];
} InputManager;


/* input manager */
InputManager* meh_input_manager_new();
void meh_input_manager_destroy(InputManager* input_manager);
void meh_input_manager_keyboard_read_event(InputManager* input_manager, SDL_Event* event);
GSList* meh_input_manager_generate_events(InputManager* input_manager);
GHashTable* meh_input_create_default_keyboard_mapping();
