#include <stdlib.h>
#include <glib.h>

#include "system/transition.h"
#include "view/screen.h"

Screen* meh_screen_new() {
	Screen* screen = g_new(Screen, 1);
	screen->parent_screen = NULL;
	screen->data = NULL;
	screen->transitions = g_queue_new();
	screen->destroy_data = NULL;
	return screen;
}

/*
 * meh_screen_destroy releases all the memory of the given screen.
 */
void meh_screen_destroy(Screen* screen) {
	g_assert(screen != NULL);

	if (screen->data != NULL) {
		if (screen->destroy_data != NULL) {
			screen->destroy_data(screen);
		} else {
			g_warning("No destroy_data on Screen '%s', but the data isn't NULL!", screen->name);
		}
	}

	g_queue_free(screen->transitions);
	g_free(screen->name);
	g_free(screen);
}

/*
 * meh_screen_add_transition adds a transition to the screen.
 */
void meh_screen_add_transition(Screen* screen, Transition* transition) {
	g_assert(screen != NULL);
	g_assert(transition != NULL);

	g_queue_push_tail(screen->transitions, transition);
}

/*
 * meh_screen_update_transitions updates all the transitions of the given screen,
 * removing them from the queue if there are ended.
 */
void meh_screen_update_transitions(Screen* screen) {
	g_assert(screen != NULL);

	for (int i = 0; i < g_queue_get_length(screen->transitions); i++) {
		Transition* transition = g_queue_peek_nth(screen->transitions, i);
		gboolean ended = meh_transition_update(transition);
		/* if the transition is ended, remove it from the queue */
		if (ended == TRUE) {
			g_queue_pop_nth(screen->transitions, i);
		}
	}
}
