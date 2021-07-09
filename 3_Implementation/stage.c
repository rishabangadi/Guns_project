#include "header_files.h"

extern game_t game;
extern Stage stage;
static Item *player;
static SDL_Texture *bulletTexture;
static SDL_Texture *enemyTexture;
int enemySpawnTimer;

void initialise(void)
{
    game.execute.logic = logic;
    game.execute.render_screen = draw;
    memset(&stage, 0, sizeof(Stage));
    stage.fighterTail = &stage.fighterHead;
    stage.bulletTail = &stage.bulletHead;
    initPlayer();
    bulletTexture = loadTexture("Images/playerBullet.png");
    enemyTexture = loadTexture("Images/enemy.png");
    enemySpawnTimer = 0;
}

void initPlayer()
{
    player = malloc(sizeof(Item));
    memset(player, 0, sizeof(Item));
    stage.fighterTail->next = player;
    stage.fighterTail = player;

    player->x = 100;
    player->y = 100;
    player->texture = loadTexture("Images/plane1.png");
    SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
}

void logic(void)
{
    run_players();
    run_enemies();
    run_bullets();
    create_enemies();
}

void run_players(void)
{
    player->dx = player->dy = 0;
    if (player->reload > 0)
    {
        player->reload--;
    }
    if (game.keyboard[SDL_SCANCODE_UP])
    {
        player->dy = -PLAYER_SPEED;
    }
    if (game.keyboard[SDL_SCANCODE_DOWN])
    {
        player->dy = PLAYER_SPEED;
    }
    if (game.keyboard[SDL_SCANCODE_LEFT])
    {
        player->dx = -PLAYER_SPEED;
    }
    if (game.keyboard[SDL_SCANCODE_RIGHT])
    {
        player->dx = PLAYER_SPEED;
    }
    if (game.keyboard[SDL_SCANCODE_LCTRL] && (player->reload == 0))
    {
        fireBullet();
    }
    player->x += player->dx;
    player->y += player->dy;
}

void fireBullet(void)
{
    Item *bullet;
    bullet = malloc(sizeof(Item));
    memset(bullet, 0, sizeof(Item));
    stage.bulletTail->next = bullet;
    stage.bulletTail = bullet;
    bullet->x = player->x;
    bullet->y = player->y;
    bullet->dx = PLAYER_BULLET_SPEED;
    bullet->health = 1;
    bullet->texture = bulletTexture;
    SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);
    //bullet->y += (player->h / 2) - (bullet->h / 2);
    bullet->y += (player->h / 10);
    player->reload = 8;
}

void run_enemies(void)
{
    Item *e, *prev;

    for (e = stage.fighterHead.next; e != NULL; e = e->next)
    {
        e->x += e->dx;
        e->y += e->dy;

        if (e != player && e->x < -e->w)
        {
            if (e == stage.fighterTail)
            {
                stage.fighterTail = prev;
            }
            prev->next = e->next;
            free(e);
            e = prev;
        }
        prev = e;
    }
}

void run_bullets(void)
{
    Item *single_bullet, *start;
    start = &stage.bulletHead;
    for (single_bullet = stage.bulletHead.next; single_bullet != NULL; single_bullet = single_bullet->next)
    {
        single_bullet->x += single_bullet->dx;
        single_bullet->y += single_bullet->dy;

        if (single_bullet->x > WINDOW_WIDTH)
        {
            if (single_bullet == stage.bulletTail)
            {
                stage.bulletTail = start;
            }
            start->next = single_bullet->next;
            free(single_bullet);
            single_bullet = start;
        }
        start = single_bullet;
    }
}

void create_enemies(void)
{
    Item *enemy;

    if (--enemySpawnTimer <= 0)
    {
        enemy = malloc(sizeof(Item));
        memset(enemy, 0, sizeof(Item));
        stage.fighterTail->next = enemy;
        stage.fighterTail = enemy;

        enemy->x = WINDOW_WIDTH;
        enemy->y = rand() % WINDOW_HEIGHT;
        enemy->texture = enemyTexture;
        SDL_QueryTexture(enemy->texture, NULL, NULL, &enemy->w, &enemy->h);

        enemy->dx = -(2 + (rand() % 4));

        enemySpawnTimer = 30 + (rand() % 60);
    }
}

void draw(void)
{
    drawPlayers();
    drawBullets();
}
void drawPlayers(void)
{
    Item *e;

    for (e = stage.fighterHead.next; e != NULL; e = e->next)
    {
        render_texture(e->texture, e->x, e->y);
    }
}
void drawBullets(void)
{
    Item *single_bullet;

    for (single_bullet = stage.bulletHead.next; single_bullet != NULL; single_bullet = single_bullet->next)
    {
        render_texture(single_bullet->texture, single_bullet->x, single_bullet->y);
    }
}