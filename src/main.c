#include "../inc/maze.h"

/**
 * main - Entry point
 * @argc: Number of arguments passed to the program
 * @argv: Pointer to string arguments passed to the program
 * Return: (0) on success, exits with failure status on failure
 */
int main(int argc, char **argv)
{
	sdl_instance sdl = {NULL, NULL, NULL, NULL, NULL, NULL};
	map_t map;
	char *map_path;

	if (argc < 2)
	{
		printf("Usage: %s 'map_path'", argv[0]);
		exit(EXIT_FAILURE);
	}
	map_path = concat("maps", argv[1]);
	printf("Attempting to open file: %s\n", map_path);  // Debugging output

	map = handle_file(map_path);
	printf("File opened and map loaded successfully.\n"); // Debugging output


	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error:%s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	printf("SDL initialized successfully.\n"); // Debugging output

	create_window(WINDOW_TITLE, &sdl);
	printf("Window created successfully.\n"); // Debugging output

	create_renderer(&sdl);
	printf("Renderer created successfully.\n"); // Debugging output

	printf("Entering game event loop.\n"); // Debugging output
	game_event_loop(&sdl, &map);
	printf("Exited game event loop.\n"); // Debugging output

	free_map(&map);
	safe_close_sdl(&sdl);
	free(map_path); // Free the allocated memory for map_path

	return (0);
}
