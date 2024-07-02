#include "../inc/maze.h"

/**
 * game_event_loop - handles SDL rendering loop and listening to events
 * @sdl: data structure of sdl_instance
 * @map: map_t data structure representing 2D map
 * Return: nothing
 */
void game_event_loop(sdl_instance *sdl, map_t *map)
{
	int quit = 0;
	SDL_Event e;
	player player = {{80, 70, PLAYER_WIDTH, PLAYER_WIDTH}, (FOV * 2.5)};
	SDL_Point mouse = {0, 0};
	SDL_bool map_active = SDL_TRUE;
	thread_data data = {sdl, map, &player, &map_active, &quit};
	SDL_Thread *thread_ID = NULL;

	printf("Creating rendering thread.\n"); // Debugging output
	thread_ID = SDL_CreateThread(render_thread, "RenderingThread", &data);

	printf("Entering main loop.\n"); // Debugging output
	while (!quit)
	{
           printf("Polling events.\n"); // Debugging output
           poll_events(&quit, &e, &player, &mouse, &map_active);
	   printf("Finished polling events.\n");

           printf("Checking player collisions.\n"); // Debugging output
           player_collision_detection(&player, map);
	   printf("Player collisions checked.\n"); // Debugging output
	}
	SDL_WaitThread(thread_ID, NULL);
	printf("Exiting main loop.\n"); // Debugging output
}

/**
 * poll_events - listens and handles SDL events
 * @quit: pointer to integer that holds status of SDL loop.
 * Default value (0) and (1) to break it
 * @e: pointer to SDL_Event data structure that holds information
 * @player: pointer to data structure of player holds players information
 * @mouse: Pointer to SDL_Point holding mouse x, y positions
 * @map_active: Boolean to indicate map displayed or not
 * concerning events
 *
 * Return: Nothing
 */
void poll_events(int *quit, SDL_Event *e, player *player, SDL_Point *mouse,
		SDL_bool *map_active)
{
	SDL_Point displacement = {0, 0};

	printf("Moving player.\n"); // Debugging output
	displacement = move_player(player);
	while (SDL_PollEvent(e) != 0)
	{
		printf("Event type: %d\n", e->type); // Debugging output
		if (e->type == SDL_QUIT)
		{
		     printf("Quit event received.\n");
		    *quit = 1;
		}

		if (e->type == SDL_MOUSEMOTION)
		{
		    rotate_player(player, mouse);
		}

		switch (e->key.keysym.sym)
		{
		case SDLK_ESCAPE:
			printf("Escape key pressed. Quitting.\n");
			*quit = 1;
			break;
		case SDLK_w:
			player->locale.x += displacement.x;
			player->locale.y -= displacement.y;
			break;
		case SDLK_s:
			player->locale.x -= displacement.x;
			player->locale.y += displacement.y;
			break;
		case SDLK_a:
			player->view_angle -= ROTATION_MAGNITUDE;
			break;
		case SDLK_d:
			player->view_angle += ROTATION_MAGNITUDE;
			break;
		case SDLK_m:
			*map_active = SDL_FALSE;
			break;
		case SDLK_n:
			*map_active = SDL_TRUE;
			break;
		default:
			break;
		}
	}
	printf("Finished polling events.\n"); // Debugging output
}
