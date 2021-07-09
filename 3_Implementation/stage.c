#include "header_files.h"

extern game_t game;
extern Stage stage;
static Item *player;
static SDL_Texture *alienBulletTexture;
static SDL_Texture *playerTexture;
static SDL_Texture *bulletTexture;
static SDL_Texture *enemyTexture;
static SDL_Texture *background;
static SDL_Texture *explosionTexture;
int enemySpawnTimer = 0;
int stageResetTimer = 0;
static int backgroundX;
Star stars[MAX_STARS];

void initialise(void)
{
    game.execute.logic = logic;
    game.execute.render_screen = draw;

    memset(&stage, 0, sizeof(Stage));
    stage.fighterTail = &stage.fighterHead;
    stage.bulletTail = &stage.bulletHead;
    stage.explosionTail = &stage.explosionHead;

    alienBulletTexture = loadTexture("Images/alienBullet.png");
    playerTexture = loadTexture("Images/plane1.png");
    bulletTexture = loadTexture("Images/laserBlue01.png");
    enemyTexture = loadTexture("Images/enemy.png");
    background = loadTexture("Images/Game_Background_142.png");
    explosionTexture = loadTexture("Images/explosion.png");

    loadMusic("music/BossMain.wav");
    playMusic(1);

    resetStage();
}

void resetStage(void)
{
    Item *e;
    Explosion *ex;
    while (stage.fighterHead.next)
    {
        e = stage.fighterHead.next;
        stage.fighterHead.next = e->next;
        free(e);
    }
    while (stage.explosionHead.next)
    {
        ex = stage.explosionHead.next;
        stage.explosionHead.next = ex->next;
        free(ex);
    }
    while (stage.bulletHead.next)
    {
        e = stage.bulletHead.next;
        stage.bulletHead.next = e->next;
        free(e);
    }
    memset(&stage, 0, sizeof(Stage));
    stage.fighterTail = &stage.fighterHead;
    stage.bulletTail = &stage.bulletHead;
    stage.explosionTail = &stage.explosionHead;
    initStarfield();
    initPlayer();
    enemySpawnTimer = 0;
    stageResetTimer = 60 * 3;
}
void initPlayer()
{
    player = malloc(sizeof(Item));
    memset(player, 0, sizeof(Item));
    stage.fighterTail->next = player;
    stage.fighterTail = player;

    player->health = 1;
    player->x = 100;
    player->y = 100;
    player->side = SIDE_PLAYER;
    player->texture = playerTexture;
    SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
}

void initStarfield(void)
{
    for (int i = 0; i < MAX_STARS; i++)
    {
        stars[i].x = rand() % WINDOW_WIDTH;
        stars[i].y = rand() % WINDOW_HEIGHT;
        stars[i].speed = 1 + rand() % 8;
    }
}

void logic(void)
{
    doBackground();
    doStarfield();
    run_players();
    doEnemies();
    run_enemies();
    run_bullets();
    create_enemies();
    doExplosions();
    clipPlayer();
    if (player == NULL && --stageResetTimer <= 0)
    {
        resetStage();
    }
}

void doBackground(void)
{
    if (--backgroundX < -WINDOW_WIDTH)
    {
        backgroundX = 0;
    }
}
void doStarfield(void)
{
    for (int i = 0; i < MAX_STARS; i++)
    {
        stars[i].x -= stars[i].speed;

        if (stars[i].x < 0)
        {
            stars[i].x = WINDOW_WIDTH + stars[i].x;
        }
    }
}
void run_players(void)
{
    if (player != NULL)
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
            playSound(SND_PLAYER_FIRE, CH_PLAYER);
            fireBullet();
        }
        player->x += player->dx;
        player->y += player->dy;
    }
}

void fireBullet(void)
{
    Item *bullet;
    bullet = malloc(sizeof(Item));
    memset(bullet, 0, sizeof(Item));
    stage.bulletTail->next = bullet;
    stage.bulletTail = bullet;
    bullet->x = player->x + 56;
    bullet->y = player->y;
    bullet->dx = PLAYER_BULLET_SPEED;
    bullet->health = 1;
    bullet->texture = bulletTexture;
    bullet->side = player->side;
    SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);
    bullet->y += (player->h / 2) - (bullet->h / 2) + 15;
    //bullet->y += (player->h / 10);
    player->reload = 8;
}
void doExplosions(void)
{
    Explosion *e, *prev;

    prev = &stage.explosionHead;

    for (e = stage.explosionHead.next; e != NULL; e = e->next)
    {
        e->x += e->dx;
        e->y += e->dy;

        if (--e->a <= 0)
        {
            if (e == stage.explosionTail)
            {
                stage.explosionTail = prev;
            }

            prev->next = e->next;
            free(e);
            e = prev;
        }

        prev = e;
    }
}
void doEnemies(void)
{
    Item *e;

    for (e = stage.fighterHead.next; e != NULL; e = e->next)
    {
        if (e != player && player != NULL && --e->reload <= 0)
        {
            fireAlienBullet(e);
            playSound(SND_ALIEN_FIRE, CH_ALIEN_FIRE);
        }
    }
}

void fireAlienBullet(Item *e)
{
    Item *bullet;

    bullet = malloc(sizeof(Item));
    memset(bullet, 0, sizeof(Item));
    stage.bulletTail->next = bullet;
    stage.bulletTail = bullet;

    bullet->x = e->x;
    bullet->y = e->y;
    bullet->health = 1;
    bullet->texture = alienBulletTexture;
    bullet->side = e->side;
    SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);

    bullet->x += (e->w / 2) - (bullet->w / 2);
    bullet->y += (e->h / 2) - (bullet->h / 2);

    calcSlope(player->x + (player->w / 2), player->y + (player->h / 2), e->x, e->y, &bullet->dx, &bullet->dy);

    bullet->dx *= ALIEN_BULLET_SPEED;
    bullet->dy *= ALIEN_BULLET_SPEED;

    bullet->side = SIDE_ALIEN;

    e->reload = (rand() % 60 * 2);
}

void run_enemies(void)
{
    Item *e, *prev;

    prev = &stage.fighterHead;

    for (e = stage.fighterHead.next; e != NULL; e = e->next)
    {
        e->x += e->dx;
        e->y += e->dy;

        if (e != player && e->x < -e->w)
        {
            e->health = 0;
        }

        if (e->health == 0)
        {
            if (e == player)
            {
                player = NULL;
            }

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

        if (bulletHitFighter(single_bullet) || single_bullet->x < -single_bullet->w || single_bullet->y < -single_bullet->h || single_bullet->x > WINDOW_WIDTH || single_bullet->y > WINDOW_HEIGHT)
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

int bulletHitFighter(Item *b)
{
    Item *e;
    for (e = stage.fighterHead.next; e != NULL; e = e->next)
    {
        if (e->side != b->side && collision(b->x, b->y, b->w, b->h, e->x, e->y, e->w, e->h))
        {
            b->health = 0;
            e->health = 0;
            addExplosions(e->x, e->y, 32);
            if (e == player)
            {
                playSound(SND_PLAYER_DIE, CH_PLAYER);
            }
            else
            {
                playSound(SND_ALIEN_DIE, CH_ANY);
            }
            return 1;
        }
    }
    return 0;
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
        enemy->side = SIDE_ALIEN;
        enemy->health = 1;
        enemy->dx = -(2 + (rand() % 4));
        enemy->reload = 60 * (1 + (rand() % 3));
        enemySpawnTimer = 30 + (rand() % 60);
    }
}

void draw(void)
{
    drawBackground();
    drawStarfield();
    drawPlayers();
    drawBullets();
    drawExplosions();
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

int collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
    return (MAX(x1, x2) < MIN(x1 + w1, x2 + w2)) && (MAX(y1, y2) < MIN(y1 + h1, y2 + h2));
}

void calcSlope(int x1, int y1, int x2, int y2, float *dx, float *dy)
{
    int steps = MAX(abs(x1 - x2), abs(y1 - y2));

    if (steps == 0)
    {
        *dx = *dy = 0;
        return;
    }

    *dx = (x1 - x2);
    *dx /= steps;

    *dy = (y1 - y2);
    *dy /= steps;
}

void clipPlayer(void)
{
    if (player != NULL)
    {
        if (player->x < 0)
        {
            player->x = 0;
        }
        if (player->y < 0)
        {
            player->y = 0;
        }
        if (player->x > WINDOW_WIDTH / 2)
        {
            player->x = WINDOW_WIDTH / 2;
        }
        if (player->y > WINDOW_HEIGHT - player->h)
        {
            player->y = WINDOW_HEIGHT - player->h;
        }
    }
}

void addExplosions(int x, int y, int num)
{
    Explosion *e;
    int i;

    for (i = 0; i < num; i++)
    {
        e = malloc(sizeof(Explosion));
        memset(e, 0, sizeof(Explosion));
        stage.explosionTail->next = e;
        stage.explosionTail = e;

        e->x = x + (rand() % 32) - (rand() % 32);
        e->y = y + (rand() % 32) - (rand() % 32);
        e->dx = (rand() % 10) - (rand() % 10);
        e->dy = (rand() % 10) - (rand() % 10);

        e->dx /= 10;
        e->dy /= 10;

        switch (rand() % 4)
        {
        case 0:
            e->r = 255;
            break;

        case 1:
            e->r = 255;
            e->g = 128;
            break;

        case 2:
            e->r = 255;
            e->g = 255;
            break;

        default:
            e->r = 255;
            e->g = 255;
            e->b = 255;
            break;
        }

        e->a = rand() % 60 * 3;
    }
}

void drawBackground(void)
{
    SDL_Rect dest;
    int x;

    for (x = backgroundX; x < WINDOW_WIDTH; x += WINDOW_WIDTH)
    {
        dest.x = x;
        dest.y = 0;
        dest.w = WINDOW_WIDTH;
        dest.h = WINDOW_HEIGHT;

        SDL_RenderCopy(game.renderer, background, NULL, &dest);
    }
}

void drawStarfield(void)
{
    int i, c;

    for (i = 0; i < MAX_STARS; i++)
    {
        c = 32 * stars[i].speed;

        SDL_SetRenderDrawColor(game.renderer, c, c, c, 255);

        SDL_RenderDrawLine(game.renderer, stars[i].x, stars[i].y, stars[i].x + 3, stars[i].y);
    }
}

void drawExplosions(void)
{
    Explosion *e;

    SDL_SetRenderDrawBlendMode(game.renderer, SDL_BLENDMODE_ADD);
    SDL_SetTextureBlendMode(explosionTexture, SDL_BLENDMODE_ADD);

    for (e = stage.explosionHead.next; e != NULL; e = e->next)
    {
        SDL_SetTextureColorMod(explosionTexture, e->r, e->g, e->b);
        SDL_SetTextureAlphaMod(explosionTexture, e->a);

        render_texture(explosionTexture, e->x, e->y);
    }

    SDL_SetRenderDrawBlendMode(game.renderer, SDL_BLENDMODE_NONE);
}