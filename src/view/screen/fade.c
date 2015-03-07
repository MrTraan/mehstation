/*
 * mehstation - Fading transition.
 *
 * Copyright © 2015 Rémy Mathieu
 */

#include "system/app.h"
#include "system/consts.h"
#include "view/screen.h"
#include "view/widget_rect.h"
#include "view/screen/fade.h"

#define MEH_FADE_DURATION 300 /* TODO In configuration file ? */

static void meh_screen_fade_send_empty_msg(App* app, Screen* screen, int msg_type);

Screen* meh_screen_fade_new(App* app, Screen* src_screen, Screen* dst_screen) {
	g_assert(app != NULL);

	Screen* screen = meh_screen_new();

	screen->name = g_strdup("Fading screen");
	screen->messages_handler = &meh_screen_fade_messages_handler;
	screen->destroy_data = &meh_screen_fade_destroy_data;

	/*
	 * Custom data
	 */
	FadeData* data = g_new(FadeData, 1);

	data->src_screen = src_screen;
	data->dst_screen = dst_screen;
	data->state = MEH_FADE_STATE_IN;

	/* Fading rect */
	SDL_Color black = { 0, 0, 0 ,0 };
	data->fade_widget = meh_widget_rect_new(0, 0, MEH_FAKE_WIDTH, MEH_FAKE_HEIGHT, black, TRUE);
	data->fade_widget->a = meh_transition_start(MEH_TRANSITION_LINEAR, 0, 255, MEH_FADE_DURATION);
	meh_screen_add_rect_transitions(screen, data->fade_widget);

	screen->data = data;

	return screen;
}

/*
 * meh_screen_fade_destroy_data destroys the additional data
 * of the fade screen.
 */
void meh_screen_fade_destroy_data(Screen* screen) {
	FadeData* data = meh_screen_fade_get_data(screen);
	meh_widget_rect_destroy(data->fade_widget);
	screen->data = NULL;
}

FadeData* meh_screen_fade_get_data(Screen* screen) {
	g_assert(screen != NULL);
	if (screen->data == NULL) {
		return NULL;
	}
	return (FadeData*) screen->data;
}

/*
 * meh_screen_fade_update udpates the content of the fade screen.
 */
int meh_screen_fade_update(struct App* app, Screen* screen) {
	/* Animate the fading rect. */
	meh_screen_update_transitions(screen);

	FadeData* data = meh_screen_fade_get_data(screen);
	g_assert(data != NULL);

	switch (data->state) {
		case MEH_FADE_STATE_IN:
			meh_screen_fade_send_empty_msg(app, data->src_screen, MEH_MSG_UPDATE);
			break;
		case MEH_FADE_STATE_OUT:
			meh_screen_fade_send_empty_msg(app, data->dst_screen, MEH_MSG_UPDATE);
			break;
	}

	if (data->fade_widget->a.ended == TRUE) {
		switch (data->state) {
			case MEH_FADE_STATE_IN:
				data->fade_widget->a = meh_transition_start(MEH_TRANSITION_LINEAR, 255, 0, MEH_FADE_DURATION);
				meh_screen_add_rect_transitions(screen, data->fade_widget);
				data->state = MEH_FADE_STATE_OUT;
				break;
			case MEH_FADE_STATE_OUT:
				meh_screen_destroy(data->src_screen);
				meh_app_set_current_screen(app, data->dst_screen);
				meh_screen_destroy(screen);
				return 0;
		}
	}

	return 0;
}

/*
 * meh_screen_fade_send_empty_msg sends an empty message to the given screen.
 */
static void meh_screen_fade_send_empty_msg(App* app, Screen* screen, int msg_type) {
	g_assert(screen != NULL);

	Message* message = meh_message_new(msg_type, NULL);
	screen->messages_handler(app, screen, message);
	meh_message_destroy(message);
}

int meh_screen_fade_messages_handler(struct App* app, Screen* screen, Message* message) {
	g_assert(app != NULL);
	g_assert(screen != NULL);

	if (message == NULL) {
		return 1;
	}

	switch (message->id) {
		case MEH_MSG_UPDATE:
			{
				meh_screen_fade_update(app, screen);
			}
			break;
		case MEH_MSG_RENDER:
			{
				meh_screen_fade_render(app, screen);
			}
			break;
	}

	return 0;
}

void meh_screen_fade_render(struct App* app, Screen* screen) {
	FadeData* data = meh_screen_fade_get_data(screen);
	g_assert(data != NULL);

	switch (data->state) {
		case MEH_FADE_STATE_OUT:
			meh_screen_fade_send_empty_msg(app, data->dst_screen, MEH_MSG_RENDER);
			break;
	}

	meh_widget_rect_render(app->window, data->fade_widget);

	meh_window_render(app->window);
}
