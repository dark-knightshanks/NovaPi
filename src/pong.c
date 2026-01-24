#include "pong.h"
#include "video.h"
#include "peripherals/mailbox.h" // For screen dimensions

// Extern the framebuffer info to get screen dimensions
extern volatile mailbox_fb_request fb1;

#define BACKGROUND_COLOR 0x00000000 // Assuming a black background
#define BORDER_MARGIN 40

void init_ball(Ball *ball, uint32_t radius, uint32_t color) {
    // Start the ball in the center of the screen
    ball->x = fb1.res.width / 2;
    ball->y = fb1.res.height / 2;

    // Initial velocity - adjust these values for desired speed
    ball->dx = 2; 
    ball->dy = 2; 

    ball->radius = radius;
    ball->color = color;
}

void update_ball_movement(Ball *ball) {
    // 1. Clear the ball from its old position using the background color
    draw_circle((uint32_t)ball->x, (uint32_t)ball->y, ball->radius, BACKGROUND_COLOR);

    // 2. Update position based on velocity
    ball->x += ball->dx;
    ball->y += ball->dy;

    // 3. Check for collisions with screen edges and reverse direction
    // The border width of 40 is assumed from your 'screen_border' function.
    uint32_t border_margin = 40; 

    // Collision with top or bottom wall
    if ((ball->y - ball->radius) <= border_margin || (ball->y + ball->radius) >= (fb1.res.height - border_margin)) {
        ball->dy = -ball->dy;
    }

    // Collision with left or right wall
    // In a full Pong game, hitting these walls would typically mean a point for the opponent
    if ((ball->x - ball->radius) <= border_margin || (ball->x + ball->radius) >= (fb1.res.width - border_margin)) {
        ball->dx = -ball->dx;
    }

    // 4. Draw the ball in its new position with its specified color
    draw_circle((uint32_t)ball->x, (uint32_t)ball->y, ball->radius, ball->color);
}

void init_player(Player *player, int x, int y, int width, int height, uint32_t color) {
    player->x = x;
    player->y = y;
    player->width = width;
    player->height = height;
    player->color = color;
    draw_player_paddle(player->x, player->y, player->height, player->width, player->color);
}

void move_player(Player *player, int dy) {
    // Erase the paddle from its old position
    draw_player_paddle(player->x, player->y, player->height, player->width, BACKGROUND_COLOR);

    // Update the player's y position
    player->y += dy;

    // Boundary checking to keep the paddle on the screen
    if (player->y < BORDER_MARGIN) {
        player->y = BORDER_MARGIN;
    }
    if (player->y + player->height > fb1.res.height - BORDER_MARGIN) {
        player->y = fb1.res.height - BORDER_MARGIN - player->height;
    }

    // Draw the paddle in its new position
    draw_player_paddle(player->x, player->y, player->height, player->width, player->color);
}