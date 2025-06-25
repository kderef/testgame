#include <stdbool.h>

#include "game/game.h"
#include "game/draw.h"
#include "game/update.h"

int main(int argc, char** argv) {
    game_t game = game_create();

    game_init(&game);

    debug("Test");
    
    while (game.running) {
        game_update(&game);
        
        if (game_should_close(&game))
            game.running = false;
        

        game_draw(&game);
    }

    game_close(&game);

    return 0;
}
