# 1 "rmain.c" 1
# 1 "./rBarrel.c" 1
# 1 "./rBarrel.h" 1
# 1 "./barrel.h" 1



typedef struct {

    int visible;
    int posX, posY;
    int state;
    int broken;
    int dropTick;
    long timeSpawned;

} Barrel;

void updateBarrels(Barrel barrel[], long nowTime);
# 1 "./rBarrel.h" 2
# 1 "./raster.h" 1



typedef unsigned char UINT8;
typedef unsigned short UINT16;
typedef unsigned long UINT32;

typedef signed char INT8;
typedef signed short INT16;
typedef signed long INT32;
# 24 "./raster.h"
void clear_screen(UINT32 *base);
# 39 "./raster.h"
void clear_region(UINT32 *base, UINT16 row, UINT16 col, UINT16 length, UINT16 width);
# 52 "./raster.h"
void plot_pixel(UINT8 *base, UINT16 row, UINT16 col);
# 66 "./raster.h"
void plot_horizontal_line(UINT32 *base, UINT16 row, UINT16 col, UINT16 length);
# 80 "./raster.h"
void plot_vertical_line(UINT32 *base, UINT16 row, UINT16 col, UINT16 length);
# 94 "./raster.h"
void plot_line(UINT32 *base, INT16 start_row, INT16 start_col, INT16 end_row, INT16 end_col);
# 109 "./raster.h"
void plot_rectangle(UINT32 *base, UINT16 row, UINT16 col, UINT16 length, UINT16 width);
# 123 "./raster.h"
void plot_square(UINT32 *base, UINT16 row, UINT16 col, UINT16 side);
# 143 "./raster.h"
void plot_triangle(UINT32 *baseptr, UINT16 row, UINT16 col, UINT16 base, UINT16 height, UINT8 direction);
# 160 "./raster.h"
UINT16 clip_left_top_right_bottom(INT16 *row, INT16 *col, UINT16 *height, UINT16 sprite_width, UINT16 *skip_x, UINT16 *skip_y);
# 174 "./raster.h"
void plot_bitmap_8(UINT8 *base, INT16 row, INT16 col, UINT16 height, const UINT8 *bitmap_8);
# 188 "./raster.h"
void plot_bitmap_16(UINT16 *base, INT16 row, INT16 col, UINT16 height, const UINT16 *bitmap);
# 202 "./raster.h"
void plot_bitmap_32(UINT32 *base, INT16 row, INT16 col, UINT16 height, const UINT32 *bitmap);
# 216 "./raster.h"
void plot_character(UINT8 *base, INT16 row, INT16 col, char ch);
# 230 "./raster.h"
void plot_string(UINT8 *base, INT16 row, INT16 col, char *ch);

static const UINT32 testBM[32] = {
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
};
# 2 "./rBarrel.h" 2




UINT16 barrel_sidewaysBM[16 ] =
{
0x0000,
0x0000,
0x0000,
0x0000,
0x0000,
0x0000,
0x03C0,
0x0C30,
0x1608,
0x2624,
0x2044,
0x2084,
0x2104,
0x1008,
0x0C30,
0x03C0,
};

UINT16 barrel_downBM[16 ] =
{
0x0000,
0x0000,
0x0000,
0x1FF8,
0x700E,
0xC003,
0xFFFF,
0xFFFF,
0xFFFF,
0xFFFF,
0xC003,
0x700E,
0x1FF8,
0x0000,
0x0000,
0x0000,
};
# 1 "./rBarrel.c" 2


void renderBarrel(Barrel barrel, UINT16 *base) {

    if (barrel.visible == 1){
        int currPosX = barrel.posX;
        int currPosY = barrel.posY;

        if (barrel.state == 1){
            plot_bitmap_16(base, currPosY, currPosX, 16, barrel_downBM);
        }
        else {
            plot_bitmap_16(base, currPosY, currPosX, 16, barrel_sidewaysBM);
        }
    }
}
# 1 "rmain.c" 2
# 1 "./rDK.c" 1
# 1 "./rDK.h" 1
# 1 "./kong.h" 1
# 1 "./raster.h" 1
# 4 "./kong.h" 2



typedef struct {

    int visible;
    int posX, posY;
    int state;
    int topL, bottomR;
    int spawnX, spawnY;

    UINT32 stateTimer;
    float barrelCooldown;
    int spawnBarrel;
    int spawnFireBarrel;

} Kong;
# 35 "./kong.h"
int updateKong(Kong *kong, int canSpawnBarrel);
# 47 "./kong.h"
void requestFireBarrel(Kong *kong);
# 62 "./kong.h"
static void kongAction(Kong *kong, int canSpawnBarrel);
# 74 "./kong.h"
static void kongMock(Kong *kong);
# 86 "./kong.h"
static void kongSpawner(Kong *kong);
# 97 "./kong.h"
static void finishThrow(Kong *kong);
# 1 "./rDK.h" 2
# 1 "./raster.h" 1
# 2 "./rDK.h" 2




UINT32 kong_idleLBM[32 ] =
{
0x0000000F,
0x0000001F,
0x00000033,
0x00000061,
0x000003C6,
0x000004E4,
0x000004E0,
0x00001E03,
0x00007C00,
0x0000FC3F,
0x0003FC40,
0x0007FF80,
0x000FBF80,
0x000FCFE0,
0x000FE3FF,
0x000FF11F,
0x0007FF07,
0x0003FFA3,
0x0001FFC3,
0x00003FA3,
0x00001A04,
0x00007DF8,
0x0000FFC0,
0x0001FFD4,
0x0003FFEA,
0x0003FFFF,
0x0003FFE0,
0x0001FFC0,
0x00013F80,
0x00067300,
0x00088500,
0x001FFE00,
};

UINT32 kong_idleRBM[32 ] =
{
0xF0000000,
0xF8000000,
0XCC000000,
0x86000000,
0x63800000,
0x26400000,
0x06400000,
0xC0F00000,
0x007C0000,
0xFC7E0000,
0x027F8000,
0x01FFC000,
0x01FBE000,
0x07E7E000,
0xFF8FE000,
0xF11FE000,
0xC1FFC000,
0x8BFF8000,
0x87FF0000,
0x8BF80000,
0x41B80000,
0x3F7C0000,
0x07FE0000,
0x57FF0000,
0x6FFF8000,
0xFFFF8000,
0x0FFF8000,
0x07FF0000,
0x03FF0000,
0x019CC000,
0x01422000,
0x00FFF000,
};

UINT32 kong_mockLBM[32 ] =
{
0x0001E007,
0x0006500F,
0x001A2819,
0x00117030,
0x002890E3,
0x003CE132,
0x003F0230,
0x007FFF81,
0x007FFF30,
0x007FFF77,
0x003FFF22,
0x001FFFB7,
0x0007FFC7,
0x0003FFF0,
0x0000FFFF,
0x00003FFF,
0x00001FD5,
0x00000FE0,
0x00000FC0,
0x00000FC8,
0x00000FC1,
0x00001FFE,
0x00003FF0,
0x00007FF5,
0x0000FFFB,
0x0000FFFF,
0x0000FFF8,
0x00007FF0,
0x00007FE0,
0x00019CC0,
0x00022140,
0x0007FF80,
};

UINT32 kong_mockRBM[32 ] =
{
0xF0000000,
0xF8000000,
0XCC000000,
0x86000000,
0x63C00000,
0x27200000,
0x07200000,
0xC0700000,
0x063C0000,
0x773E0000,
0x223F8000,
0x767FC000,
0x70FBE000,
0x07F7E000,
0xFFCFE000,
0xF88FE000,
0xE0FFC000,
0xC5FF8000,
0xC3FF0000,
0xC5F80000,
0x20F80000,
0x1FFC0000,
0x03FE0000,
0x2BFF0000,
0x57FF8000,
0xFFFF8000,
0x01FF8000,
0x001F0000,
0x00FF0000,
0x009CC000,
0x00422000,
0x00FFF000,
};

UINT32 kong_grabLBM[32 ] =
{
0x01F80000,
0x03FE0000,
0x027F0000,
0x041FF000,
0x070FFF00,
0x1919FFC0,
0x2030FFE0,
0x4070F9F0,
0x40FBFDF8,
0x8073FDF8,
0xFC27FDFC,
0x420FFDFC,
0x210FF9FC,
0x1C0FFBFE,
0x03FFF3FE,
0x003FE7FF,
0x007FCFFF,
0x007F9FFF,
0x00FF9FFF,
0x00FF9FFF,
0x01FF1FFF,
0x03FFB7FF,
0x03FD71FF,
0x07FB107F,
0x3FF7E01F,
0x23E7F80F,
0x17CFFFFF,
0x13CFF807,
0x2087F803,
0x493ECC00,
0x56480400,
0x387FFC00,
};

UINT32 kong_grabRBM[32 ] =
{
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x80000000,
0xC0000000,
0xE0000000,
0xF0000000,
0xF8000000,
0xF8000000,
0xF8000000,
0xFE000000,
0xFFE00000,
0xFFD00000,
0xFF900000,
0xFF900000,
0xFFD00000,
0x07500000,
0x09200000,
0x1FC00000,
};

UINT32 kong_holdLBM[32 ] =
{
0x0000000F,
0x0000001F,
0x00000033,
0x00000061,
0x000001C6,
0x00003AE4,
0x00007CE0,
0x0000FB03,
0x0001FE00,
0x0003FE3F,
0x0007FE40,
0x0007FF80,
0x0007FF80,
0x0007FFE0,
0x000FFDFF,
0x000FF9FF,
0x000FF257,
0x000FF781,
0x0007F600,
0x0007EE3F,
0x0007FFE0,
0x0003E480,
0x0003E8FF,
0x0001EBFF,
0x0001D3FF,
0x0001EBFF,
0x0001F380,
0x0000F1E0,
0x0000F9BF,
0x00033F00,
0x00044200,
0x001FFF00,
};

UINT32 kong_holdRBM[32 ] =
{
0xF0000000,
0xF8000000,
0XCC000000,
0x86000000,
0x63800000,
0x275C0000,
0x073E0000,
0xC0DF0000,
0x007F8000,
0xFC7FC000,
0x027FE000,
0x01FFE000,
0x01FFE000,
0x07FFE000,
0xFFBFF000,
0xFF9FF000,
0xEA4FF000,
0x81EFF000,
0x006FE000,
0xFC77E000,
0x07FFE000,
0x0127C000,
0xFF17C000,
0xFFD78000,
0xFFCB8000,
0xFFD78000,
0x01CF8000,
0x078F0000,
0xFD9F0000,
0x00FCC000,
0x00422000,
0x00FFF800,
};

UINT32 kong_throwLBM[32 ] =
{
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000001,
0x00000003,
0x00000007,
0x0000000F,
0x0000001F,
0x0000001F,
0x0000001F,
0x0000007F,
0x000007FF,
0x00000BFF,
0x000009FF,
0x000009FF,
0x00000BFF,
0x00000AE0,
0x00000490,
0x000003F8,
};

UINT32 kong_throwRBM[32 ] =
{
0x00001F80,
0x00007FC0,
0x0000FE40,
0x000FF820,
0x00FFF0E0,
0x03FF9898,
0x07FF0C04,
0x0F9F0E02,
0x1FBFDF02,
0x1FBFCE01,
0x3FBFE43F,
0x3FBFF042,
0x3F9FF084,
0x7FDFF038,
0x7FCFFFC0,
0xFFE7FC00,
0xFFF3FE00,
0xFFF9FE00,
0xFFF9FF00,
0xFFF9FF00,
0xFFF8FF80,
0xFFEDFFC0,
0xFF8EBFC0,
0xFE08DFE0,
0xF8E7EFFC,
0xF01FE7C4,
0xFFFFF3E8,
0xE01FF3C8,
0xC01FE104,
0x00337C92,
0x0020126A,
0x003FFE1C,
};



void renderDK(Kong kong, UINT32 *base);
# 1 "./rDK.c" 2


void renderDK(Kong kong, UINT32 *base) {

    if (kong.visible == 1){

        int currState = kong.state;

        if (currState == 0) {
            plot_bitmap_32(base, 110, 198, 32, kong_idleLBM);
            plot_bitmap_32(base, 110, 230, 32, kong_idleRBM);
        }
        else if (currState == 1) {
            plot_bitmap_32(base, 110, 198, 32, kong_grabLBM);
            plot_bitmap_32(base, 110, 230, 32, kong_grabRBM);
        }
        else if (currState == 2) {
            plot_bitmap_32(base, 110, 198, 32, kong_holdLBM);
            plot_bitmap_32(base, 110, 230, 32, kong_holdRBM);
        }
        else if (currState == 3) {
            plot_bitmap_32(base, 110, 198, 32, kong_throwLBM);
            plot_bitmap_32(base, 110, 230, 32, kong_throwRBM);
        }
        else {
            plot_bitmap_32(base, 110, 198, 32, kong_mockLBM);
            plot_bitmap_32(base, 110, 230, 32, kong_mockRBM);

        }
    }
}
# 2 "rmain.c" 2
# 1 "./rLady.c" 1
# 1 "./rLady.h" 1
# 1 "./lady.h" 1



typedef struct {

    int visible;
    int posX, posY;
    int state;

} Lady;
# 1 "./rLady.h" 2
# 1 "./raster.h" 1
# 2 "./rLady.h" 2




UINT32 lady_idleBM[32 ] =
{
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x000000FC,
0x000001FE,
0x000003C4,
0x0000634A,
0x00003184,
0x00001F08,
0x00007E10,
0x00003D90,
0x000053F0,
0x000007F0,
0x00000C18,
0x00001BFC,
0x000077F4,
0x000007FC,
0x00000FF8,
0x00000FF4,
0x00001387,
0x0000383D,
0x00007FFE,
0x00003FFC,
0x00001C08,
0x00000E00,
};

UINT32 lady_winBM[32 ] =
{
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x0000007E,
0x000000FF,
0x000001E2,
0x000031A1,
0x000018C2,
0x00000F8C,
0x00003FC0,
0x00001EC8,
0x000029F8,
0x000001F0,
0x000000FF,
0x0000001E,
0x000003F8,
0x00000FFE,
0x000077FE,
0x000071FC,
0x00003C7C,
0x00001F1C,
0x00003FC4,
0x0000197C,
0x00000C74,
0x0000002E,
};
# 1 "./rLady.c" 2


void renderLady(Lady lady, UINT32 *base) {

    if (lady.visible == 1){
       if (lady.state == 0) {
        plot_bitmap_32(base, lady.posY, lady.posX, 32, lady_idleBM);
       }
       else {
        plot_bitmap_32(base, lady.posY, lady.posX, 32, lady_winBM);
       }
    }
}
# 3 "rmain.c" 2
# 1 "./rMario.c" 1
# 1 "./rMario.h" 1
# 1 "./mario.h" 1
# 1 "./girder.h" 1



typedef struct {

    int visible;
    int posY, posX;
    int type;
    int size;
    int colLeft, colRight;

} Girder;
# 4 "./mario.h" 2
# 1 "./ladder.h" 1



typedef struct {

    int visible;
    int posY, posX;
    int broken;

    int size;
    int topSize;
    int bottomSize;
    int skipped;

    int leftB, rightB, topB, bottomB;
    int update;

} Ladder;

int isOnLadder(Ladder *ladder, int x, int y);
int canClimb(Ladder *ladder);
int barrelCanDescend(Ladder *ladder);
# 5 "./mario.h" 2
# 17 "./mario.h"
typedef struct {

    int visible;
    int posX, posY;
    int deltX, deltY;
    int state;
    int direction;
    int climbing;
    int collideLadder;
    int onGround;
    int hammerActive;
    long hammerTimer;
    int dead;

    int walkFrame;
    int climbFrame;


    int hammerFrame;
    long hammerFrameTimer;
    int hammerHitActive;

    int leftB, rightB, topB, bottomB;

} Mario;

void moveLeft(Mario *jm);
void moveRight(Mario *jm);
void jump(Mario *jm);
void applyGravity(Mario *jm);
void updateMario(Mario *jm, Girder girders[], int numGirders, Ladder ladders[], int numLadders, float deltaTime);
# 1 "./rMario.h" 2
# 1 "./raster.h" 1
# 2 "./rMario.h" 2




UINT16 mario_walkInRightBM[16 ] =
{
0x0780,
0x0FF0,
0x0F40,
0x1258,
0x1324,
0x3878,
0x0438,
0x0FC0,
0x1E60,
0x1C20,
0x1E10,
0x1F10,
0x1710,
0x1220,
0x1CE0,
0x1EF0,
};

UINT16 mario_walkOutRightBM[16 ] =
{
0x0780,
0x0FF0,
0x0F40,
0x1258,
0x1324,
0x3878,
0x0430,
0x3FC6,
0xFD7A,
0xAC1A,
0xC824,
0x101C,
0x238C,
0x7C7C,
0x7000,
0x3800,
};

UINT16 mario_jumpRightBM[16 ] =
{
0x0000,
0x03C0,
0x07F8,
0x07A0,
0x092C,
0x0992,
0x1C3C,
0x621B,
0xFEE7,
0x2E3E,
0x0690,
0x3411,
0x780F,
0xD0FF,
0x0900,
0x0600,
};

UINT16 mario_walkInLeftBM[16 ] =
{
0x01E0,
0x0FF0,
0x02F0,
0x1A48,
0x24C8,
0x1E1C,
0x1C20,
0x03F0,
0x0768,
0x0438,
0x0878,
0x08F8,
0x08E8,
0x0448,
0x0738,
0x0F78,
};

UINT16 mario_walkOutLeftBM[16 ] =
{
0x01E0,
0x0FF0,
0x02F0,
0x1A48,
0x24C8,
0x1E1C,
0x0C20,
0x63FC,
0x5EBF,
0x5835,
0x2413,
0x3808,
0x31C4,
0x3E3E,
0x000E,
0x001C,
};

UINT16 mario_jumpLeftBM[16 ] =
{
0x0000,
0x03C0,
0x1FE0,
0x05E0,
0x3490,
0x4990,
0x3C38,
0xD846,
0xE77F,
0x7C74,
0x0960,
0x882C,
0xF01E,
0xFF0B,
0x0090,
0x0060,
};

UINT16 mario_climbLeftBM[16 ] =
{
0x0038,
0x07F8,
0x07F8,
0x0FFC,
0x0FFC,
0x381C,
0x7FF8,
0x7BD8,
0x1188,
0x1004,
0x1004,
0x1008,
0x0878,
0x0F80,
0x0FC0,
0x07C0,
};

UINT16 mario_climbRightBM[16 ] =
{
0x1C00,
0x1FE0,
0x1FE0,
0x3FF0,
0x3FF0,
0x381C,
0x1FFE,
0x1BDE,
0x1188,
0x2008,
0x2008,
0x1008,
0x1E10,
0x01F0,
0x03F0,
0x03E0,
};

UINT16 mario_climbPullBM[16 ] =
{
0x0000,
0x07F8,
0x1BDE,
0x3197,
0x1003,
0x2002,
0x2002,
0x2004,
0x1088,
0x1088,
0x0870,
0x0870,
0x07C0,
0x07C0,
0x07E0,
0x03E0,
};

UINT16 mario_hitBM[16 ] =
{
0x03E0,
0x07F0,
0x0550,
0x0808,
0x1B6C,
0x59CE,
0xE631,
0xFDDF,
0x7DDE,
0x0888,
0x0410,
0x340B,
0x3807,
0x3CCF,
0x3F3E,
0x1C0C,
};

UINT16 mario_deadBM[16 ] =
{
0x007C,
0x0082,
0x0101,
0x0082,
0x1E7C,
0x3F80,
0x4580,
0x4800,
0x4410,
0x832B,
0x80E6,
0x81A3,
0x63B3,
0x5F8F,
0x9F27,
0xFFFE,
};

UINT16 mario_hammerUpLeftBM[16 ] =
{
0x00F0,
0x0710,
0x0118,
0x0DE4,
0x12E4,
0x0FFE,
0x06F0,
0x01F8,
0x0138,
0x0238,
0x1208,
0x1C04,
0x18E2,
0x1F1B,
0x0007,
0x000E,
};

UINT16 mario_hammerDownLeftBM[16 ] =
{
0x0000,
0x03C0,
0x1FE0,
0x05E0,
0x3490,
0x4990,
0x3C38,
0x1840,
0xE7F0,
0x9FF0,
0x7FD0,
0x080F,
0x08C3,
0x04BF,
0x0381,
0x0780,
};

UINT16 mario_hammerUpRightBM[16 ] =
{
0x0F00,
0x08E0,
0x1880,
0x27B0,
0x2748,
0x7FF0,
0x0F60,
0x1F80,
0x1C80,
0x1C40,
0x1048,
0x2038,
0x4718,
0xD8F8,
0xE000,
0x7000,
};

UINT16 mario_hammerDownRightBM[16 ] =
{
0x0000,
0x03C0,
0x07F8,
0x07A0,
0x092C,
0x0992,
0x1C3C,
0x0218,
0x0FE7,
0x0FF9,
0x0BFE,
0xF010,
0xC310,
0xFD20,
0x81C0,
0x01E0,
};

void renderMRight(Mario mario, UINT16 *base);
void renderMLeft(Mario mario, UINT16 *base);
# 1 "./rMario.c" 2


void renderMario(Mario mario, UINT16 *base) {

    if (mario.visible == 1){

        if (mario.hammerActive == 1) {
            if(mario.direction == 0) {
                plot_bitmap_16(base, mario.posY, mario.posX, 16, mario_hammerDownLeftBM);
            }
            else {
                plot_bitmap_16(base, mario.posY, mario.posX, 16, mario_hammerUpRightBM);
            }
        }
        else {
            if (mario.direction == 0) {

                renderMLeft(mario, base);

            }
            else {

                renderMRight(mario, base);

            }
        }
    }
}

void renderMLeft(Mario mario, UINT16 *base) {

    int currState = mario.state;

    if (currState == 0) {

        plot_bitmap_16(base, mario.posY, mario.posX, 16, mario_walkInLeftBM);

    } else if (currState == 1) {
        if (mario.walkFrame == 0) {
            plot_bitmap_16(base, mario.posY, mario.posX, 16, mario_walkInLeftBM);
            mario.walkFrame = 1;
        } else {
            plot_bitmap_16(base, mario.posY, mario.posX, 16, mario_walkOutLeftBM);
            mario.walkFrame = 0;
        }

    } else if (currState == 2) {
        if (mario.climbFrame == 0) {
            plot_bitmap_16(base, mario.posY, mario.posX, 16, mario_climbLeftBM);
            mario.walkFrame = 1;
        } else {
            plot_bitmap_16(base, mario.posY, mario.posX, 16, mario_climbRightBM);
            mario.walkFrame = 0;
        }

    } else if (currState == 3) {

        plot_bitmap_16(base, mario.posY, mario.posX, 16, mario_jumpLeftBM);

    } else {

        if (mario.dead == 1) {
            plot_bitmap_16(base, mario.posY, mario.posX, 16, mario_deadBM);
        } else {
            plot_bitmap_16(base, mario.posY, mario.posX, 16, mario_hitBM);
        }
    }
}

void renderMRight(Mario mario, UINT16 *base) {

    int currState = mario.state;

    if (currState == 0) {

        plot_bitmap_16(base, mario.posY, mario.posX, 16, mario_walkInRightBM);

    } else if (currState == 1) {
        if (mario.walkFrame == 0) {
            plot_bitmap_16(base, mario.posY, mario.posX, 16, mario_walkInRightBM);
        } else {
            plot_bitmap_16(base, mario.posY, mario.posX, 16, mario_walkOutRightBM);
        }

    } else if (currState == 2) {
        if (mario.climbing == 0) {
            plot_bitmap_16(base, mario.posY, mario.posX, 16, mario_climbPullBM);
        } else if (mario.climbFrame == 0) {
            plot_bitmap_16(base, mario.posY, mario.posX, 16, mario_climbLeftBM);
            mario.walkFrame = 1;
        } else {
            plot_bitmap_16(base, mario.posY, mario.posX, 16, mario_climbRightBM);
            mario.walkFrame = 0;
        }

    } else if (currState == 3) {

        plot_bitmap_16(base, mario.posY, mario.posX, 16, mario_jumpRightBM);

    } else {

        if (mario.dead == 1) {
            plot_bitmap_16(base, mario.posY, mario.posX, 16, mario_deadBM);
        } else {
            plot_bitmap_16(base, mario.posY, mario.posX, 16, mario_hitBM);
        }
    }
}

void updateMCollision(Mario mario) {

    mario.leftB = mario.posX;
    mario.rightB = mario.posX + 16;
    mario.topB = mario.posY;
    mario.bottomB = mario.posY + 16;

}
# 4 "rmain.c" 2
# 1 "./rSpirit.c" 1
# 1 "./rSpirit.h" 1
# 1 "./spirit.h" 1



typedef struct {

    int visible;
    int posX, posY;
    int direction;

} Spirit;
# 1 "./rSpirit.h" 2
# 1 "./raster.h" 1
# 2 "./rSpirit.h" 2




UINT16 spirit_LeftBM[16 ] =
{
0x0844,
0x1400,
0x0904,
0x0C82,
0x1265,
0x2594,
0x0FC8,
0x1AF0,
0x3060,
0x2030,
0x6930,
0x6930,
0x6030,
0x7020,
0x1FE0,
0x0F80,
};

UINT16 spirit_RightBM[16 ] =
{
0x2210,
0x0028,
0x2090,
0x4130,
0xA648,
0x29A4,
0x13F0,
0x0F58,
0x060C,
0x0C04,
0x0C96,
0x0C96,
0x0C06,
0x040E,
0x07F8,
0x01F0,
};
# 1 "./rSpirit.c" 2


void renderSpirit(Spirit spirit, UINT16 *base) {

    if (spirit.visible == 1){
       if (spirit.direction == 0) {
        plot_bitmap_16(base, spirit.posY, spirit.posX, 16, spirit_LeftBM);
       }
       else {
        plot_bitmap_16(base, spirit.posY, spirit.posX, 16, spirit_RightBM);
       }
    }
}
# 5 "rmain.c" 2
# 1 "./rHammer.c" 1
# 1 "./rHammer.h" 1
# 1 "./raster.h" 1
# 1 "./rHammer.h" 2
# 1 "./hammer.h" 1



typedef struct {

    int visible;
    int posX, posY;
    int state;

} Hammer;
# 2 "./rHammer.h" 2




UINT16 hammer_floatBM[16 ] =
{
0x0000,
0x0000,
0x0000,
0x0180,
0x0FF0,
0x1FF8,
0x1FF8,
0x1FF8,
0x1FF8,
0x1FF8,
0x0FF0,
0x0180,
0x0180,
0x0180,
0x0180,
0x0180,
};

UINT16 hammer_upBM[16 ] =


{
0x0000,
0x0000,
0x0000,
0x0180,
0x0FF0,
0x1FF8,
0x1FF8,
0x1FF8,
0x1FF8,
0x1FF8,
0x0FF0,
0x0180,
0x0180,
0x0180,
0x0180,
0x0180,
};

UINT16 hammer_downLeftBM[16 ] =

{
0x0000,
0x0000,
0x0000,
0x03E0,
0x07F0,
0x07F0,
0x07F0,
0x0FFF,
0x0FFF,
0x07F0,
0x07F0,
0x07F0,
0x03E0,
0x0000,
0x0000,
0x0000,
};

UINT16 hammer_downRightBM[16 ] =

{
0x0000,
0x0000,
0x0000,
0x07C0,
0x0FE0,
0x0FE0,
0x0FE0,
0xFFF0,
0xFFF0,
0x0FE0,
0x0FE0,
0x0FE0,
0x07C0,
0x0000,
0x0000,
0x0000,
};
# 1 "./rHammer.c" 2


void renderHammer(Hammer hammer, UINT16 *base) {

    if (hammer.visible == 1) {
        if (hammer.state == 0){
            plot_bitmap_16(base, hammer.posY, hammer.posX, 16, hammer_floatBM);
        }
    }
}
# 6 "rmain.c" 2
# 1 "./rItem.c" 1
# 1 "./rItem.h" 1
# 1 "./raster.h" 1
# 1 "./rItem.h" 2
# 1 "./item.h" 1



typedef struct {

    int visible;
    int posX, posY;
    int type;
    int worth;
    long lifetime;
    long maxLifetime;

} Item;
# 2 "./rItem.h" 2




UINT16 purse_BM[16 ] =
{
0x0000,
0x0000,
0x03C0,
0x0420,
0x0810,
0x0810,
0x0BD0,
0x07E0,
0x0A50,
0x0DB0,
0x0E70,
0x0FF0,
0x0FF0,
0x0000,
0x0000,
0x0000,
};

UINT16 umbrella_BM[16 ] =
{
0x0180,
0x07E0,
0x0990,
0x1BD8,
0x23CC,
0x63C6,
0xC7E3,
0xFD3F,
0x8101,
0x0100,
0x0100,
0x0140,
0x0080,
0x0000,
0x0000,
0x0000,
};

UINT16 hat_BM[16 ] =
{
0x0000,
0x0000,
0x0000,
0x0000,
0x03C8,
0x07F4,
0x0FF8,
0x0FF0,
0x0810,
0x7FFE,
0xFFFF,
0x71F2,
0x0000,
0x0000,
0x0000,
0x0000,
};
# 1 "./rItem.c" 2


void renderItem(Item item, UINT16 *base) {

    if (item.visible == 1) {
        if (item.type == 0){
            plot_bitmap_16(base, item.posY, item.posX, 16, umbrella_BM);
        } else if (item.type == 1){
            plot_bitmap_16(base, item.posY, item.posX, 16, purse_BM);
        } else {
            plot_bitmap_16(base, item.posY, item.posX, 16, hat_BM);
        }
    }
}
# 7 "rmain.c" 2
# 1 "./rBStack.c" 1
# 1 "./rBStack.h" 1
# 1 "./raster.h" 1
# 1 "./rBStack.h" 2
# 1 "./kong.h" 1
# 2 "./rBStack.h" 2




UINT32 stack_BM[32 ] =
{
0x00FC3F00,
0x01FE7F80,
0x017A5E80,
0x037BDEC0,
0x02799E40,
0x02799E40,
0x02799E40,
0x02799E40,
0x02799E40,
0x02799E40,
0x02799E40,
0x02799E40,
0x037BDEC0,
0x017A5E80,
0x01FE7F80,
0x00FE3F00,
0x00FC3F00,
0x01FE7F80,
0x017A5E80,
0x037BDEC0,
0x02799E40,
0x02799E40,
0x02799E40,
0x02799E40,
0x02799E40,
0x02799E40,
0x02799E40,
0x02799E40,
0x037BDEC0,
0x017A5E80,
0x01FE7F80,
0x00FE3F00,
};
# 1 "./rBStack.c" 2


void renderBStack(Kong kong, UINT32 *base) {

    plot_bitmap_32(base, 110, 172, 32, stack_BM);

}
# 8 "rmain.c" 2
# 1 "./rGirder.c" 1
# 1 "./rGirder.h" 1
# 1 "./girder.h" 1
# 1 "./rGirder.h" 2
# 1 "./raster.h" 1
# 2 "./rGirder.h" 2




UINT8 girder_BM[8] =
{
0xFF,
0x10,
0x38,
0x6C,
0xC6,
0x83,
0X01,
0xFF,
};
# 1 "./rGirder.c" 2


void renderGirder(Girder girder, UINT8 *base) {

    if (girder.visible == 1){
        int currPosX = girder.posX;
        int currPosY = girder.posY;
        int i;

        for (i = 0; i < girder.size; i++) {

            plot_bitmap_8(base, currPosX, currPosY, 8, girder_BM);
            currPosY += 8;
            plot_bitmap_8(base, currPosX, currPosY, 8, girder_BM);

            if (girder.type == 1) {
                currPosX -= 1;
            } else if (girder.type == 2) {
                currPosX += 1;
            }

            currPosY += 8;
        }
    }
}
# 9 "rmain.c" 2
# 1 "./rHeart.c" 1
# 1 "./rHeart.h" 1
# 1 "./heart.h" 1



typedef struct {

    int visible;
    int posX, posY;
    int broken;

} Heart;
# 1 "./rHeart.h" 2
# 1 "./raster.h" 1
# 2 "./rHeart.h" 2




UINT16 heart_fullBM[16 ] =
{
0x0000,
0x0000,
0x0000,
0x3838,
0x7C7C,
0xFEFE,
0xFFFE,
0xFFFE,
0xFFFE,
0x7FFC,
0x3FF8,
0x1FF0,
0x0FE0,
0x07C0,
0x0380,
0x0100,
};

UINT16 heartbrokenBM[16 ] =
{
0x0000,
0x0000,
0x0000,
0x3838,
0x7C7C,
0xFCFE,
0xF9FE,
0xFCFE,
0xFE7E,
0x7F3C,
0x3E78,
0x1CF0,
0x0E60,
0x0640,
0x0200,
0x0100,
};
# 1 "./rHeart.c" 2


void renderHeart(Heart heart, UINT16 *base) {

    if (heart.visible == 1){
       if (heart.broken == 0) {
        plot_bitmap_16(base, heart.posY, heart.posX, 16, heart_fullBM);
       }
       else {
        plot_bitmap_16(base, heart.posY, heart.posX, 16, heartbrokenBM);
       }
    }
}
# 10 "rmain.c" 2
# 1 "./rLadder.c" 1
# 1 "./rLadder.h" 1
# 1 "./ladder.h" 1
# 1 "./rLadder.h" 2
# 1 "./raster.h" 1
# 2 "./rLadder.h" 2




UINT8 ladder_BM[8] =
{
0x81,
0xFF,
0x81,
0x81,
0x81,
0xFF,
0x81,
0x81,
};
# 1 "./rLadder.c" 2


void renderLadder(Ladder ladder, UINT8 *base) {



    if (ladder.visible == 1) {

        int currPosX = ladder.posX;
        int currPosY = ladder.posY;
        int i;
        int j;
        int k;

        if (ladder.broken == 1) {
            for (i = 0; i < ladder.topSize; i++) {
                plot_bitmap_8(base, currPosX, currPosY, 8, ladder_BM);
                currPosX += 8;
            }
            for (j = 0; j < ladder.skipped; j++) {
                currPosX += 8;
            }
            for (i = 0; i < ladder.bottomSize; i++) {
                plot_bitmap_8(base, currPosX, currPosY, 8, ladder_BM);
                currPosX += 8;
            }
        } else {
            for (i = 0; i < ladder.size; i++) {
                plot_bitmap_8(base, currPosX, currPosY, 8, ladder_BM);
                currPosX += 8;
            }
        }
    }
}
# 11 "rmain.c" 2
# 1 "./rOil.c" 1
# 1 "./rOil.h" 1
# 1 "./oil.h" 1



typedef struct {

    int visible;
    int posX, posY;
    int state;
    int requestFireBarrel;

} Oil;

void updateOil(Oil *oil, float deltaTime);
void igniteOil(Oil *oil);
void notifyFireSpiritDead(Oil *oil);
# 1 "./rOil.h" 2
# 1 "./raster.h" 1
# 2 "./rOil.h" 2




UINT32 oil_unlitBM[32 ] =
{
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00BFFF00,
0x005FFE00,
0x005FFE00,
0x005FFE00,
0x00400200,
0x005FFE00,
0x00512600,
0x00552600,
0x00512200,
0x005FFE00,
0x00400200,
0x005FFE00,
0x00524A00,
0x005FFE00,
0x005FFE00,
0x00BFFF00,
};

UINT32 oil_litBM[32 ] =
{
0x00010000,
0x00108400,
0x0008C400,
0x00098E00,
0x001B5A00,
0x002F6400,
0x00364A00,
0x00285400,
0x00B21800,
0x00D11800,
0x00550D00,
0x0023CE00,
0x00B2D500,
0x00FA6D00,
0x006E2200,
0x00443600,
0x00BFFF00,
0x005FFE00,
0x005FFE00,
0x005FFE00,
0x00400200,
0x005FFE00,
0x00512600,
0x00552600,
0x00512200,
0x005FFE00,
0x00400200,
0x005FFE00,
0x00524A00,
0x005FFE00,
0x005FFE00,
0x00BFFF00,
};
# 1 "./rOil.c" 2


void renderOil(Oil oil, UINT32 *base) {

    if (oil.visible == 1){
        if (oil.state == 0){
            plot_bitmap_32(base, oil.posY, oil.posX, 32, oil_unlitBM);
        }
        else {
            plot_bitmap_32(base, oil.posY, oil.posX, 32, oil_litBM);
        }
    }
}
# 12 "rmain.c" 2
# 1 "./rBonus.c" 1
# 1 "./rBonus.h" 1
# 1 "./raster.h" 1
# 1 "./rBonus.h" 2
# 1 "./timer.h" 1



typedef struct {

    int visible;
    int posX, posY;
    int value;
    int startValue;

} Timer;
# 2 "./rBonus.h" 2
# 1 "C:/c68/include/osbind.h" 1
# 1 "C:/c68/include/compiler.h" 1
# 9 "C:/c68/include/osbind.h" 2
# 1 "C:/c68/include/ostruct.h" 1
# 22 "C:/c68/include/ostruct.h"
typedef struct {
    long b_free;
    long b_total;
    long b_secsiz;
    long b_clsiz;
} _DISKINFO;


typedef struct {
  short time;
  short date;
} _DOSTIME;


typedef struct
{
        unsigned char maxlen;
        unsigned char actuallen;
        char    buffer[255];
} _CCONLINE;
# 48 "C:/c68/include/ostruct.h"
typedef struct _dta {
    char 	    dta_buf[21];
    char            dta_attribute;
    unsigned short  dta_time;
    unsigned short  dta_date;
    long            dta_size;
    char            dta_name[14];
} _DTA;
# 98 "C:/c68/include/ostruct.h"
typedef struct {
  short recsiz;
  short clsiz;
  short clsizb;
  short rdlen;
  short fsiz;
  short fatrec;
  short datrec;
  short numcl;
  short bflags;
} _BPB;




typedef struct _md {
    struct _md	*md_next;
    long	 md_start;
    long	 md_length;
    long	 md_owner;
} _MD;


typedef struct {
    _MD *mp_free;
    _MD *mp_used;
    _MD *mp_rover;
} _MPB;
# 141 "C:/c68/include/ostruct.h"
typedef struct {
    char    *ibuf;
    short   ibufsiz;
    volatile short   ibufhd;
    volatile short   ibuftl;
    short   ibuflow;
    short   ibufhi;
} _IOREC;


typedef struct {
	char	topmode;
	char	buttons;
	char	xparam;
	char	yparam;
	short	xmax;
	short	ymax;
	short	xstart;
	short	ystart;
} _PARAM;


typedef struct {
    void    (*midivec)	(void) ;
    void    (*vkbderr)	(void) ;
    void    (*vmiderr)	(void) ;
    void    (*statvec)	(void *) ;
    void    (*mousevec)	(void *) ;
    void    (*clockvec)	(void *) ;
    void    (*joyvec)	(void *) ;
    long    (*midisys)	(void) ;
    long    (*ikbdsys)	(void) ;
    char    kbstate;
} _KBDVECS;


typedef struct {
    void *unshift;
    void *shift;
    void *caps;
} _KEYTAB;


typedef struct
{
        void    *pb_scrptr;
        int     pb_offset;
        int     pb_width;
        int     pb_height;
        int     pb_left;
        int     pb_right;
        int     pb_screz;
        int     pb_prrez;
        void    *pb_colptr;
        int     pb_prtype;
        int     pb_prport;
        void    *pb_mask;
} _PBDEF;
# 17 "C:/c68/include/osbind.h" 2
# 33 "C:/c68/include/osbind.h"
 long _trap_1_w		(short) ;
 long _trap_1_ww	(short,short) ;
 long _trap_1_wl	(short,long) ;
 long _trap_1_wlw	(short,long,short) ;
 long _trap_1_wwll	(short,short,long,long) ;
 long _trap_1_wlww	(short,long,short,short) ;
 long _trap_1_www	(short,short,short) ;
 long _trap_1_wll	(short,long,long) ;
 long _trap_1_wwlll	(short,short,long,long,long) ;
 long _trap_1_wwwll	(short,short,short,long,long) ;
 long _trap_13_wl	(short,long) ;
 long _trap_13_w	(short) ;
 long _trap_13_ww	(short,short) ;
 long _trap_13_www	(short,short,short) ;
 long _trap_13_wwlwww	(short,short,long,short,short,short) ;
 long _trap_13_wwl	(short,short,long) ;
 long _trap_14_wwl	(short,short,long) ;
 long _trap_14_wwll	(short,short,long,long) ;
 long _trap_14_ww	(short,short) ;
 long _trap_14_w	(short) ;
 long _trap_14_wllw	(short,long,long,short) ;
 long _trap_14_wl	(short,long) ;
 long _trap_14_www	(short,short,short) ;
 long _trap_14_wllwwwww (short,long,long,short,short,short,short,short) ;
 long _trap_14_wllwwwwlw (short,long,long,short,short,short,short,long,short) ;
 long _trap_14_wllwwwwwlw (short,long,long,short,short,short,short,short,long,short) ;
 long _trap_14_wwwwwww	(short,short,short,short,short,short,short) ;
 long _trap_14_wlll	(short,long,long,long) ;
 long _trap_14_wllww	(short,long,long,short,short) ;
 long _trap_14_wwwwl	(short,short,short,short,long) ;
 long _trap_14_wwwl	(short,short,short,long) ;
 long _trap_14_wlwlw	(short,long,short,long,short) ;
# 103 "C:/c68/include/osbind.h"
 long _trap_1_ 	(short,...) ;
 long _trap_14_ 	(short,...) ;
 long _trap_13_ 	(short,...) ;
# 3 "./rBonus.h" 2
# 1 "C:/c68/include/linea.h" 1
# 325 "C:/c68/include/linea.h"
typedef struct {



   short  _VPLANES;
   short  _VWRAP;




   short  *_CONTRL;
   short  *_INTIN;
   short  *_PTSIN;
   short  *_INTOUT;
   short  *_PTSOUT;
# 349 "C:/c68/include/linea.h"
   short  _COLBIT0;
   short  _COLBIT1;
   short  _COLBIT2;
   short  _COLBIT3;




   short  _LSTLIN;



   short  _LNMASK;



   short  _WMODE;
# 372 "C:/c68/include/linea.h"
   short  _X1;

   short  _Y1;

   short  _X2;

   short  _Y2;


   short  *_PATPTR;

   short  _PATMSK;

   short  _MFILL;



   short  _CLIP;
   short  _XMINCL;
   short  _YMINCL;
   short  _XMAXCL;
   short  _YMAXCL;


   short  _XDDA;


   short  _DDAINC;



   short  _SCALDIR;
   short  _MONO;





   short  _SOURCEX;
# 417 "C:/c68/include/linea.h"
   short  _SOURCEY;

   short  _DESTX;
   short  _DESTY;
   short  _DELX;

   short  _DELY;

   short  *_FBASE;
   short  _FWIDTH;

   short  _STYLE;
# 435 "C:/c68/include/linea.h"
   short  _LITEMASK;

   short  _SKEWMASK;

   short  _WEIGHT;

   short  _ROFF;


   short  _LOFF;


   short  _SCALE;

   short  _CHUP;




   short  _TEXTFG;

   char  *_SCRTCHP;




   short  _SCRPT2;



   short  _TEXTBG;


   short  _COPYTRAN;
# 476 "C:/c68/include/linea.h"
 short(*_SEEDABORT) (void) ;
# 484 "C:/c68/include/linea.h"
} __LINEA;
# 546 "C:/c68/include/linea.h"
typedef struct _font {



   short  font_id;

   short  size;

   char   name[32];

   short  first_ade;


   short  last_ade;


   short  top;

   short  ascent;

   short  half;

   short  descent;

   short  bottom;



short max_char_width;

short max_cell_width;

  short left_offset;

  short right_offset;

   short  thicken;

   short  ul_size;

   short  lighten;

   short  skew;



   short  flags;





   char   *h_table;

   short  *off_table;

   char   *dat_table;

   short  form_width;

   short  form_height;

 struct _font *next_font;


} __FONT;
# 620 "C:/c68/include/linea.h"
typedef short(*FPTR) (void) ;
typedef FPTR *FUNCPTR;
# 628 "C:/c68/include/linea.h"
typedef struct {



   char   fg0bg0;
   char   fg0bg1;
   char   fg1bg0;
   char   fg1bg1;

} OP_TAB;





typedef struct  {
	short	bl_xmin;
	short	bl_ymin;
	char	*bl_form;
	short	bl_nxwd;
	short 	bl_nxln;
	short 	bl_nxpl;
}SDDB;
# 673 "C:/c68/include/linea.h"
typedef struct {



   short   bb_b_wd;
   short   bb_b_ht;
   short   bb_plane_ct;
   short   bb_fg_col;
   short   bb_bg_col;
   OP_TAB  bb_op_tab;
   SDDB	   bb_s;
   SDDB	   bb_d;
   short   *bb_p_addr;
   short   bb_p_nxln;
   short   bb_p_nxpl;
   short   bb_p_mask;
   char	   bb_fill[24];

} BBPB;
# 700 "C:/c68/include/linea.h"
typedef struct
{
	char		*fd_addr;


	short		fd_w;
	short		fd_h;
	short		fd_wdwidth;
	short		fd_stand;
	short		fd_nplanes;
	short		fd_r1;
	short		fd_r2;
	short		fd_r3;
} MFDB;
# 720 "C:/c68/include/linea.h"
typedef struct
{
	short	sp_xhot;
	short	sp_yhot;
	short	sp_format;
	short	sp_bg;
	short	sp_fg;
	short	sp_data[32];





} SFORM;
# 750 "C:/c68/include/linea.h"
extern __LINEA *__aline;



extern __FONT  **__fonts;



extern short  (**__funcs) (void) ;
# 1013 "C:/c68/include/linea.h"
 void linea0 (void) ;
 void linea1 (void) ;
 int linea2 (void) ;
 void linea3 (void) ;
 void linea4 (void) ;
 void linea5 (void) ;
 void linea6 (void) ;
 void linea7 (BBPB *P) ;
 void linea8 (void) ;
 void linea9 (void) ;
 void lineaa (void) ;
 void lineab (void) ;
 void lineac (void *P) ;
 void linead (int x, int y, SFORM *sd, void *ss) ;
 void lineae (void) ;
 void lineaf (void) ;
# 4 "./rBonus.h" 2
# 12 "./rBonus.h"
UINT32 bonus_leftBM[32 ] =

{
0x70000000,
0xF0000000,
0xF0000000,
0x80000000,
0x80000000,
0x80000000,
0x80000000,
0x80000000,
0x80000000,
0x80000000,
0x80000000,
0x80000000,
0x80000000,
0xBFFFFFFF,
0xA0000000,
0xA0000000,
0xA0000000,
0xA0000000,
0xA0000000,
0xA0000000,
0xA0000000,
0xA0000000,
0xA0000000,
0xA0000000,
0xA0000000,
0xA0000000,
0xA0000000,
0xA0000000,
0xBFFFFFFF,
0x80000000,
0xFFFFFFFF,
0x7FFFFFFF,
};


UINT32 bonus_rightBM[32 ] =

{
0x000E0000,
0x000F0000,
0x000F0000,
0x00010000,
0x00010000,
0x00010000,
0x00010000,
0x00010000,
0x00010000,
0x00010000,
0x00010000,
0x00010000,
0x00010000,
0xFFFD0000,
0x00050000,
0x00050000,
0x00050000,
0x00050000,
0x00050000,
0x00050000,
0x00050000,
0x00050000,
0x00050000,
0x00050000,
0x00050000,
0x00050000,
0x00050000,
0x00050000,
0xFFFD0000,
0x00010000,
0xFFFF0000,
0xFFFE0000,
};
# 1 "./rBonus.c" 2
# 1 "C:/c68/include/stdio.h" 1
# 20 "C:/c68/include/stdio.h"
typedef unsigned long  size_t;
# 69 "C:/c68/include/stdio.h"
typedef	struct
	{
	long		_cnt;
	unsigned char	*_ptr;
	unsigned char	*_base;
	unsigned int	_flag;
	int		_file;
	long		_bsiz;
	unsigned char	_ch;
	}
	FILE;


typedef unsigned long fpos_t;
# 92 "C:/c68/include/stdio.h"
extern	FILE	_iob[];
# 108 "C:/c68/include/stdio.h"
 char *	ctermid	(char *) ;




 int	remove	(const char *) ;
 int	rename	(const char *, const char *) ;
 char *	tmpnam	(char *) ;
 FILE *	tmpfile	(void) ;

 int	fclose	(FILE *) ;
 int	fflush	(FILE *) ;

 FILE *	fopen	(const char *, const char *) ;
 FILE *	freopen	(const char *, const char *, FILE *) ;

 void	setbuf	(FILE *, char *) ;
 int	setvbuf	(FILE *, char *, int, size_t) ;
# 132 "C:/c68/include/stdio.h"
 int  fscanf  (FILE *, const char *, ...) ;
 int  scanf   (const char *, ...) ;
 int  sscanf  (const char *, const char *, ...) ;


 int	fprintf	(FILE *, const char *, ...) ;
 int	printf	(const char *, ...) ;
 int	sprintf	(char *, const char *, ...) ;

 int 	vfprintf (FILE *, const char *, char * ) ;
 int 	vprintf	 (const char *, char * ) ;
 int 	vsprintf (char *, const char *, char * ) ;

 int	vscanf  (const char *, char * ) ;
 int	vfscanf (FILE *, const char *, char * ) ;
 int	vsscanf	(const char *, const char *, char * ) ;


 int	fgetc	(FILE *) ;
 char	*fgets	(char *, int, FILE *) ;
 char	*gets	(char *) ;
 int	fputc	(int c, FILE *) ;
 int	fputs	(const char *, FILE *) ;
 int	puts	(const char *) ;

 size_t	fread	(void *, size_t, size_t, FILE *) ;
 size_t	fwrite	(const void *, size_t, size_t, FILE *) ;

 int	fgetpos	(FILE *, fpos_t *) ;
 int	fsetpos	(FILE *, fpos_t *) ;

 int	fseek	(FILE *, long, int) ;
 long	ftell	(FILE *) ;
 void	rewind	(FILE *) ;

 void	perror	(const char *) ;


 FILE	*fdopen	(int, const char *) ;


 FILE *	fopenp	(const char *, const char *) ;
 int 	fungetc	(int, FILE *) ;
 int	pclose	(FILE *) ;
 FILE *	popen	(const char *, const char *) ;
 void	setlinebuf	(FILE *) ;

 void	_binmode	(int) ;
 long 	getl	(FILE *) ;
 long 	putl	(long, FILE *) ;
 short 	getw	(FILE *) ;
 short 	putw	(short, FILE *) ;
 void	_getbuf	(FILE *fp) ;
# 192 "C:/c68/include/stdio.h"
 int	_filbuf	(FILE *) ;
# 2 "./rBonus.c" 2


char currTimer[5];

void intToStr(int val, char *str){

    int i = 3;

    while(i > -1){
		str[i--] = val % 10 + '0';
		val /= 10;
	}
}

void renderBonus(Timer timer, UINT32 *base) {

    linea0();

    if (timer.visible == 1){

        linea0();
        plot_string((UINT8 *)base, timer.posY - 4, timer.posX, "BONUS");

        intToStr(timer.value, currTimer);
        currTimer[4] = '\0';

        plot_string((UINT8 *)base, timer.posY + 11, timer.posX + 4, currTimer);

        plot_bitmap_32(base, timer.posY - 2, timer.posX - 4, 32, bonus_leftBM);
        plot_bitmap_32(base, timer.posY - 2, timer.posX + 28, 32, bonus_rightBM);
    }
}
# 13 "rmain.c" 2
# 1 "./rLives.c" 1
# 1 "./rLives.h" 1
# 1 "./raster.h" 1
# 1 "./rLives.h" 2
# 1 "./lives.h" 1



typedef struct {

    int visible;
    int posX, posY;
    int count;

} Lives;
# 2 "./rLives.h" 2
# 8 "./rLives.h"
UINT8 lives_BM[8] =
{
0x7C,
0xFF,
0xF4,
0xFE,
0xFF,
0xFE,
0X78,
0x00,
};
# 1 "./rLives.c" 2


void renderLives(Lives lives, UINT8 *base) {

    int currPosX = lives.posX;
    int i;

    if (lives.visible == 1){
        for (i = 0; i < lives.count; i++) {

            plot_bitmap_8(base, lives.posY, currPosX, 8, lives_BM);
            currPosX += 10;
        }
    }
}
# 14 "rmain.c" 2
# 1 "./rScore.c" 1
# 1 "./rScore.h" 1
# 1 "./score.h" 1



typedef struct {

    int visible;
    int posX, posY;
    long value;
    long highValue;

} Score;
# 1 "./rScore.h" 2
# 1 "./raster.h" 1
# 2 "./rScore.h" 2
# 1 "C:/c68/include/osbind.h" 1
# 3 "./rScore.h" 2
# 1 "C:/c68/include/linea.h" 1
# 4 "./rScore.h" 2
# 1 "./rScore.c" 2
# 1 "C:/c68/include/stdio.h" 1
# 2 "./rScore.c" 2


char currScore[7];
char highScore[7];

void longToStr(long val, char *str){

    int i = 5;

    while(i > -1){
		str[i--] = val % 10 + '0';
		val /= 10;
	}
}

void renderScore(Score score, UINT32 *base) {

    linea0();

    if (score.visible == 1){

        plot_string((UINT8 *)base, score.posY, score.posX, "HIGH SCORE");

        longToStr(score.value, currScore);
        currScore[6] = '\0';

        plot_string((UINT8 *)base, score.posY+16, score.posX-62, currScore);

        longToStr(score.highValue, highScore);
        highScore[6] = '\0';

        plot_string((UINT8 *)base, score.posY+16, score.posX+16, highScore);
    }
}
# 15 "rmain.c" 2
# 1 "./model.h" 1
# 1 "./mario.h" 1
# 4 "./model.h" 2
# 1 "./girder.h" 1
# 5 "./model.h" 2
# 1 "./ladder.h" 1
# 6 "./model.h" 2
# 1 "./kong.h" 1
# 7 "./model.h" 2
# 1 "./oil.h" 1
# 8 "./model.h" 2
# 1 "./hammer.h" 1
# 9 "./model.h" 2
# 1 "./lady.h" 1
# 10 "./model.h" 2
# 1 "./barrel.h" 1
# 11 "./model.h" 2
# 1 "./spirit.h" 1
# 12 "./model.h" 2
# 1 "./item.h" 1
# 13 "./model.h" 2
# 1 "./heart.h" 1
# 14 "./model.h" 2
# 1 "./timer.h" 1
# 15 "./model.h" 2
# 1 "./score.h" 1
# 16 "./model.h" 2
# 1 "./lives.h" 1
# 17 "./model.h" 2
# 29 "./model.h"
typedef struct {

    Mario mario;
    Girder girders[9];
    Ladder ladders[19];
    Kong kong;
    Oil oil;
    Hammer hammers[2];
    Lady lady;
    Barrel barrels[9];
    Spirit spirit;
    Item item;
    Heart heart;
    Timer timer;
    Score score;
    Lives lives;

} Model;
# 17 "rmain.c" 2
# 1 "./raster.c" 1
# 1 "./raster.h" 1
# 1 "./raster.c" 2
# 1 "C:/c68/include/stdio.h" 1
# 2 "./raster.c" 2
# 1 "C:/c68/include/osbind.h" 1
# 3 "./raster.c" 2
# 1 "C:/c68/include/linea.h" 1
# 4 "./raster.c" 2
# 13 "./raster.c"
void clear_screen(UINT32 *base) {
    int i;
    UINT32 *loc;
    i = 0;
    loc = base;
    while (i++ < 8000 )
        *(loc++) = 0;
}

void clear_region(UINT32 *base, UINT16 row, UINT16 col, UINT16 length, UINT16 width) {
    UINT8 *base8 = (UINT8 *)base;
    UINT16 visible;
    UINT16 x_skip, y_skip;
    UINT8 *line;
    UINT8 *start;
    UINT8 *end;
    UINT8 *curr;
    UINT16 start_byte, end_byte;
    UINT8 start_bit, end_bit;
    UINT16 r;
    UINT16 h = length;
    INT16 r0 = (INT16)row;
    INT16 c0 = (INT16)col;

    visible = clip_left_top_right_bottom(&r0, &c0, &h, width, &x_skip, &y_skip);
    if (visible == 0 || h == 0)
        return;

    start_byte = ((UINT16)c0) >> 3;
    end_byte = (UINT16)(((UINT16)c0 + visible - 1) >> 3);

    start_bit = (UINT8)(((UINT16)c0) & 7);
    end_bit = (UINT8)((((UINT16)c0 + visible - 1) & 7));

    for (r = 0; r < h; r++) {
        line = base8 + (UINT32)((UINT16)r0 + r) * 80 ;
        start = line + start_byte;
        end = line + end_byte;
        curr = start;
        while (curr <= end) {
            if (curr == start && curr == end) {
                UINT8 left, right, mask;
                left = (UINT8)(0xFF >> start_bit);
                right = (UINT8)(0xFF << (7 - end_bit));
                mask = (UINT8)(left & right);
                *curr &= (UINT8)~mask;
            } else if (curr == start) {
                UINT8 mask;
                mask = (UINT8)(0xFF >> start_bit);
                *curr &= (UINT8)~mask;
            } else if (curr == end) {
                UINT8 mask;
                mask = (UINT8)(0xFF << (7 - end_bit));
                *curr &= (UINT8)~mask;
            } else {
                *curr = 0x00;
            }
            curr++;
        }
    }
}

void plot_pixel(UINT8 *base, UINT16 row, UINT16 col) {
    if (row >= 0 && row < 640  && col >= 0 && col < 400 ) {
        *(base + col * 80 + (row >> 3)) |= 1 << (7 - (row & 7));
    }
}

void plot_horizontal_line(UINT32 *base, UINT16 row, UINT16 col, UINT16 length) {
    UINT8 *base8;
    INT16 r;
    INT16 c;
    UINT16 visible, x_skip, y_skip;
    UINT16 h;
    UINT16 start_byte, end_byte;
    UINT8 start_bit, end_bit;
    UINT8 *line;
    UINT8 *curr;
    UINT8 *endp;
    base8 = (UINT8 *)base;


    r = (INT16)row;
    c = (INT16)col;
    h = 1;
    visible = clip_left_top_right_bottom(&r, &c, &h, length, &x_skip, &y_skip);
    if (visible == 0)
        return;
    if (h == 0)
        return;

    start_byte = ((UINT16)c) >> 3;
    end_byte = (UINT16)(((UINT16)c + visible - 1) >> 3);

    start_bit = (UINT8)(((UINT16)c) & 7);
    end_bit = (UINT8)((((UINT16)c + visible - 1) & 7));

    line = base8 + ((UINT32)((UINT16)r) * 80 );
    curr = line + start_byte;
    endp = line + end_byte;

    while (curr <= endp) {
        if (curr == (line + start_byte) && curr == endp) {
            UINT8 left, right;
            left = (UINT8)(0xFF >> start_bit);
            right = (UINT8)(0xFF << (7 - end_bit));
            *curr |= (UINT8)(left & right);
        } else if (curr == (line + start_byte)) {
            *curr |= (UINT8)(0xFF >> start_bit);
        } else if (curr == endp) {
            *curr |= (UINT8)(0xFF << (7 - end_bit));
        } else {
            *curr |= 0xFF;
        }
        curr++;
    }
}

void plot_vertical_line(UINT32 *base, UINT16 row, UINT16 col, UINT16 length) {
    UINT8 *base8;
    INT16 r;
    INT16 c;
    UINT16 h;
    UINT16 x_skip, y_skip;
    UINT16 visible;
    UINT16 i;

    base8 = (UINT8 *)base;

    r = (INT16)row;
    c = (INT16)col;
    h = length;

    visible = clip_left_top_right_bottom(&r, &c, &h, 1, &x_skip, &y_skip);
    if (visible == 0 || h == 0)
        return;

    for (i = 0; i < h; i++) {
        INT16 rr = (INT16)(r + i);

        if (rr >= 0 && rr < 400 ) {
            base8[(UINT32)rr * 80  + ((UINT16)c >> 3)] |=
                (UINT8)(1 << (7 - ((UINT16)c & 7)));
        }
    }
}

void plot_line(UINT32 *base, INT16 start_row, INT16 start_col, INT16 end_row, INT16 end_col) {
    UINT8 *byte_base;
    int abs_distance_x, abs_distance_y;
    int step_x, step_y;
    int error, temp_error;
    INT16 current_row, current_col;

    byte_base = (UINT8 *)base;

    current_row = start_row;
    current_col = start_col;

    abs_distance_x = end_row > start_row ? end_row - start_row : start_row - end_row;
    abs_distance_y = end_col > start_col ? end_col - start_col : start_col - end_col;

    step_x = start_row < end_row ? 1 : -1;
    step_y = start_col < end_col ? 1 : -1;

    error = abs_distance_x - abs_distance_y;

    while (1) {

        if (current_row >= 0 && current_row < 400  && current_col >= 0 && current_col < 640 ) {

            byte_base[(UINT32)current_row * 80  + ((UINT16)current_col >> 3)] |=
                (UINT8)(1 << (7 - ((UINT16)current_col & 7)));
        }

        if (current_row == end_row && current_col == end_col)
            break;

        temp_error = 2 * error;

        if (temp_error > -abs_distance_y) {
            error -= abs_distance_y;
            current_row = (INT16)(current_row + step_x);
        }

        if (temp_error < abs_distance_x) {
            error += abs_distance_x;
            current_col = (INT16)(current_col + step_y);
        }
    }
}

void plot_rectangle(UINT32 *base, UINT16 row, UINT16 col, UINT16 length, UINT16 width) {
    UINT16 bottom_row = row + length - 1;
    UINT16 right_col = col + width - 1;


    plot_horizontal_line(base, row, col, width);
    plot_horizontal_line(base, bottom_row, col, width);


    plot_vertical_line(base, row, col, length);
    plot_vertical_line(base, row, right_col, length);
}

void plot_square(UINT32 *base, UINT16 row, UINT16 col, UINT16 side) {
    UINT16 bottom_row = row + side - 1;
    UINT16 right_col = col + side - 1;

    plot_horizontal_line(base, row, col, side);
    plot_horizontal_line(base, bottom_row, col, side);

    plot_vertical_line(base, row, col, side);
    plot_vertical_line(base, row, right_col, side);
}

void plot_triangle(UINT32 *baseptr, UINT16 row, UINT16 col, UINT16 base, UINT16 height, UINT8 direction) {
    INT16 r0, c0, r1, c1, r2, c2;

    if (direction == 0) {

        r0 = (INT16)row;
        c0 = (INT16)col;
        r1 = (INT16)row;
        c1 = (INT16)(col + base - 1);
        r2 = (INT16)(row + height - 1);
        c2 = (INT16)col;
        plot_horizontal_line(baseptr, row, col, base);
        plot_vertical_line(baseptr, row, col, height);
        plot_line(baseptr, r1, c1, r2, c2);
    } else if (direction == 1) {

        r0 = (INT16)row;
        c0 = (INT16)col;
        r1 = (INT16)row;
        c1 = (INT16)(col - (INT16)base + 1);
        r2 = (INT16)(row + height - 1);
        c2 = (INT16)col;

        plot_horizontal_line(baseptr, row, (INT16)(col - base + 1), base);
        plot_vertical_line(baseptr, row, col, height);
        plot_line(baseptr, r1, c1, r2, c2);
    } else if (direction == 2) {

        r0 = (INT16)row;
        c0 = (INT16)col;
        r1 = (INT16)row;
        c1 = (INT16)(col + base - 1);
        r2 = (INT16)(row - (INT16)height + 1);
        c2 = (INT16)col;

        plot_horizontal_line(baseptr, row, col, base);
        plot_vertical_line(baseptr, (INT16)(row - height + 1), col, height);
        plot_line(baseptr, r1, c1, r2, c2);
    } else if (direction == 3) {

        r0 = (INT16)row;
        c0 = (INT16)col;
        r1 = (INT16)row;
        c1 = (INT16)(col - (INT16)base + 1);
        r2 = (INT16)(row - (INT16)height + 1);
        c2 = (INT16)col;

        plot_horizontal_line(baseptr, row, (INT16)(col - base + 1), base);
        plot_vertical_line(baseptr, (INT16)(row - height + 1), col, height);
        plot_line(baseptr, r1, c1, r2, c2);
    }
}

UINT16 clip_left_top_right_bottom(INT16 *row, INT16 *col, UINT16 *height, UINT16 sprite_width, UINT16 *x_skip, UINT16 *y_skip) {
    INT16 r = *row;
    INT16 c = *col;
    UINT16 visible;
    UINT16 remaining;

    *x_skip = 0;
    *y_skip = 0;


    if (r < 0) {
        UINT16 s = -r;
        if (s >= *height)
            return 0;
        *y_skip = s;
        *height -= s;
        r = 0;
    }



    if (r >= 400 ) {
        return 0;
    }

    if (r + *height > 400 ) {
        *height = 400  - r;
    }


    if (c < 0) {
        UINT16 s;
        s = -c;
        if (s >= sprite_width) {
            return 0;
        }
        *x_skip = s;
        c = 0;
    }


    if (c >= 640 ) {
        return 0;
    }


    visible = 640  - c;
    remaining = sprite_width - *x_skip;

    if (visible > remaining) {
        visible = remaining;
    }
    *row = (UINT16)r;
    *col = (UINT16)c;
    return visible;
}

void plot_bitmap_8(UINT8 *base, INT16 row, INT16 col, UINT16 height, const UINT8 *bitmap_8) {
    UINT16 r, byte_col, bit_shift, visible, x_skip, y_skip;
    UINT32 offset;
    UINT8 *dest;
    UINT8 src, mask;

    visible = clip_left_top_right_bottom(&row, &col, &height, 8, &x_skip, &y_skip);
    if (visible == 0) {
        return;
    }

    bitmap_8 += y_skip;
    byte_col = col >> 3;
    bit_shift = col & 7;

    for (r = 0; r < height; r++) {

        offset = (row + r) * 80  + byte_col;
        dest = base + offset;
        src = bitmap_8[r];

        if (x_skip != 0) {
            src = src << x_skip;
        }

        if (visible < 8 - x_skip) {
            mask = 0xFF << (8 - visible);
            src &= mask;
        }

        if (bit_shift == 0) {
            *dest |= src;
        } else {
            *dest |= src >> bit_shift;

            if (visible + bit_shift > 8 && byte_col + 1 < 80 ) {
                dest[1] |= src << (8 - bit_shift);
            }
        }
    }
}

void plot_bitmap_16(UINT16 *base, INT16 row, INT16 col, UINT16 height, const UINT16 *bitmap_16) {
    UINT16 x_skip, y_skip, visible;
    UINT16 word_col, bit_shift, r;
    UINT8 *base8 = (UINT8 *)base;

    visible = clip_left_top_right_bottom(&row, &col, &height, 16, &x_skip, &y_skip);
    if (visible == 0)
        return;

    bitmap_16 += y_skip;
    word_col = col >> 4;
    bit_shift = col & 15;

    for (r = 0; r < height; r++) {
        UINT32 offset = (UINT32)(row + r) * (80  / 2) + word_col;
        UINT16 *dest = (UINT16 *)base8 + offset;
        UINT16 src = bitmap_16[r];


        if (x_skip != 0) {
            src = src << x_skip;
        }


        if (visible < 16 - x_skip) {
            UINT16 mask = (UINT16)(0xFFFF << (16 - visible));
            src &= mask;
        }

        if (bit_shift == 0) {
            *dest |= src;
        } else {
            *dest |= (src >> bit_shift);

            if (visible + bit_shift > 16 && word_col + 1 < (80  / 2)) {
                dest[1] |= (src << (16 - bit_shift));
            }
        }
    }
}

void plot_bitmap_32(UINT32 *base, INT16 row, INT16 col, UINT16 height, const UINT32 *bitmap_32) {
    UINT16 x_skip, y_skip, visible;
    UINT16 byte_col, bit_shift, r;
    UINT8 *base8 = (UINT8 *)base;
    UINT8 b0, b1, b2, b3;
    visible = clip_left_top_right_bottom(&row, &col, &height, 32, &x_skip, &y_skip);
    if (visible == 0) {
        return;
    }
    bitmap_32 += y_skip;
    byte_col = col >> 3;
    bit_shift = col & 7;

    for (r = 0; r < height; r++) {
        UINT8 *dest = base8 + (UINT32)(row + r) * 80  + byte_col;
        UINT32 src = bitmap_32[r];


        if (x_skip != 0) {
            src = src << x_skip;
        }


        if (visible < 32 - x_skip) {
            UINT32 mask;
            mask = (UINT32)(0xFFFFFFFF << (32 - (UINT32)visible));
            src &= mask;
        }

        b0 = src >> 24;
        b1 = src >> 16;
        b2 = src >> 8;
        b3 = src;

        if (bit_shift == 0) {
            dest[0] |= b0;
            dest[1] |= b1;
            dest[2] |= b2;
            dest[3] |= b3;
        } else {
            dest[0] |= (b0 >> bit_shift);
            dest[1] |= (b0 << (8 - bit_shift)) | (b1 >> bit_shift);
            dest[2] |= (b1 << (8 - bit_shift)) | (b2 >> bit_shift);
            dest[3] |= (b2 << (8 - bit_shift)) | (b3 >> bit_shift);

            if (visible + bit_shift > 32 && byte_col + 4 < 80 ) {
                dest[4] |= (b3 << (8 - bit_shift));
            }
        }
    }
}

void plot_character(UINT8 *base, INT16 row, INT16 col, char c) {
    UINT8 *font;
    UINT16 byte_col, bit_shift;
    UINT16 r;
    UINT32 offset;
    UINT8 *dest;
    UINT8 src;

    INT16 rr;
    INT16 cc;
    UINT16 h;
    UINT16 visible, x_skip, y_skip;


    rr = (INT16)row;
    cc = (INT16)col;
    h = 16;

    visible = clip_left_top_right_bottom(&rr, &cc, &h, 8, &x_skip, &y_skip);
    if (visible == 0 || h == 0)
        return;
    font = (UINT8 *)(*((char  **)((char  *)__aline + -22L))) ;

    byte_col = (UINT16)cc >> 3;
    bit_shift = (UINT16)cc & 7;

    for (r = 0; r < h; r++) {

        src = font[(UINT16)(UINT8)c + (UINT16)(256 * (r + y_skip))];

        if (x_skip != 0)
            src = (UINT8)(src << x_skip);


        if (visible < (UINT16)(8 - x_skip)) {
            UINT8 mask;
            mask = (UINT8)(0xFFu << (8 - visible));
            src = (UINT8)(src & mask);
        }

        offset = (UINT32)((UINT16)rr + r) * 80  + byte_col;
        dest = base + offset;

        if (bit_shift == 0) {
            dest[0] |= src;
        } else {
            dest[0] |= (UINT8)(src >> bit_shift);


            if ((visible + bit_shift > 8) && (byte_col < (80  - 1)))
                dest[1] |= (UINT8)(src << (8 - bit_shift));
        }
    }
}

void plot_string(UINT8 *base, INT16 row, INT16 col, char *str) {
    while (*str) {
        if (col >= 640 )
            return;
        plot_character(base, row, col, *str++);
        col = (UINT16)(col + 8);
    }
}
# 18 "rmain.c" 2
# 1 "./clock.c" 1
# 1 "./clock.h" 1
# 1 "C:/c68/include/stdio.h" 1
# 1 "./clock.h" 2
# 1 "C:/c68/include/osbind.h" 1
# 2 "./clock.h" 2
# 1 "./raster.h" 1
# 3 "./clock.h" 2


UINT32 getTime();
# 1 "./clock.c" 2


UINT32 getTime() {

    volatile long currTime;

    long *timer = (long *)0x0462;
    long old_ssp;

    old_ssp = _trap_1_wl((short)0x20,(long)(0)) ;

    currTime = *timer;

    _trap_1_wl((short)0x20,(long)(old_ssp)) ;

    return currTime;
}
# 19 "rmain.c" 2
# 1 "./item.c" 1
# 1 "./item.h" 1
# 1 "./item.c" 2


void spawnItem(Item item) {

    item.visible = 1;


    if (item.type == 0) {
        item.worth = 5000;
    } else if (item.type == 1) {
        item.worth = 2000;
    } else {
        item.worth = 1000;
    }


    item.lifetime = 0;
    item.maxLifetime = 20;
}
# 20 "rmain.c" 2
# 1 "./kong.c" 1
# 1 "./kong.h" 1
# 1 "./kong.c" 2
# 1 "./clock.h" 1
# 1 "C:/c68/include/stdio.h" 1
# 1 "./clock.h" 2
# 1 "C:/c68/include/osbind.h" 1
# 2 "./clock.h" 2
# 1 "./raster.h" 1
# 3 "./clock.h" 2


UINT32 getTime();
# 2 "./kong.c" 2
# 23 "./kong.c"
int updateKong(Kong *kong, int canSpawnBarrel)
{
    kong->stateTimer++;
    switch (kong->state)
    {
    case 0 :
        if (kong->stateTimer >= 9 )
            kongAction(kong, canSpawnBarrel);
        break;

    case 1 :
        if (kong->stateTimer >= 5 )
        {
            kong->state = 2 ;
            kong->stateTimer = 0;
        }
        break;

    case 2 :
        if (kong->stateTimer >= 4 )
        {
            kong->spawnBarrel = 1 ;
            kong->state = 3 ;
            kong->stateTimer = 0;
        }
        break;

    case 3 :
        if (kong->stateTimer >= 10 )
            finishThrow(kong);
        break;

    case 4 :

        if (kong->stateTimer >= 12 )
        {
            kong->state = 0 ;
            kong->stateTimer = 0;
        }
        break;

    default:

        kong->state = 0 ;
        kong->stateTimer = 0;
        break;
    }

    return kong->state;
}

static void kongAction(Kong *kong, int canSpawnBarrel)
{
    static int missedThrows = 0;
    kong->stateTimer = 0;

    if (missedThrows >= 1)
    {

        missedThrows = 0;
        kongSpawner(kong);
        return;
    }
    if (canSpawnBarrel == 0)
    {

        missedThrows = 0;
        kongSpawner(kong);
    }
    else
    {

        missedThrows++;
        kongMock(kong);
    }
}

static void kongMock(Kong *kong)
{
    kong->state = 4 ;
    kong->stateTimer = 0;
}

static void kongSpawner(Kong *kong)
{
    kong->state = 1 ;
    kong->stateTimer = 0;
}

static void finishThrow(Kong *kong)
{
    kong->state = 0 ;
    kong->stateTimer = 0;
}
# 21 "rmain.c" 2
# 1 "./barrel.c" 1
# 1 "./barrel.h" 1
# 1 "./barrel.c" 2


long spawnedTime;

void updateBarrels(Barrel barrel[], long nowTime) {

    int i;
    for (i = 0; i < 9; i++) {

        if(barrel[i].visible == 1) {

            spawnedTime = nowTime - barrel[i].timeSpawned;

            if (spawnedTime < 250) {

                barrel[i].posX += 4;
                barrel[i].dropTick = 4;

            } else if (spawnedTime >= 250 && spawnedTime < 760) {

                if (barrel[i].dropTick == 4) {
                    barrel[i].posY++;
                    barrel[i].dropTick = 0;
                }
                barrel[i].posX += 4;
                barrel[i].dropTick++;

            } else if (spawnedTime >= 760 && spawnedTime < 930){

                barrel[i].posY += 6;
                barrel[i].dropTick = 2;

            } else  if (spawnedTime >= 930 && spawnedTime < 1520) {

                if (barrel[i].dropTick == 2) {
                    barrel[i].posY++;
                    barrel[i].dropTick = 0;
                }
                barrel[i].posX -= 8;
                barrel[i].dropTick++;

            } else if (spawnedTime >= 1540 && spawnedTime < 1730){

                barrel[i].posY += 4;
                barrel[i].dropTick = 2;

            } else if (spawnedTime >= 1730 && spawnedTime < 2340) {

                if (barrel[i].dropTick == 2) {
                    barrel[i].posY++;
                    barrel[i].dropTick = 0;
                }
                barrel[i].posX += 8;
                barrel[i].dropTick++;

            } else if (spawnedTime >= 2340 && spawnedTime < 2360){

                barrel[i].posX += 4;

            } else if (spawnedTime >= 2360 && spawnedTime < 2480){

                barrel[i].posY += 6;
                barrel[i].dropTick = 2;

            } else if (spawnedTime >= 2480 && spawnedTime < 3090) {

                if (barrel[i].dropTick == 2) {
                    barrel[i].posY++;
                    barrel[i].dropTick = 0;
                }
                barrel[i].posX -= 8;
                barrel[i].dropTick++;

            } else if (spawnedTime >= 3110 && spawnedTime < 3290){

                barrel[i].posY += 4;
                barrel[i].dropTick = 2;

            } else if (spawnedTime >= 3290 && spawnedTime < 3900) {

                if (barrel[i].dropTick == 2) {
                    barrel[i].posY++;
                    barrel[i].dropTick = 0;
                }
                barrel[i].posX += 8;
                barrel[i].dropTick++;

            } else if (spawnedTime >= 3900 && spawnedTime < 3920){

                barrel[i].posX += 4;

            } else if (spawnedTime >= 3920 && spawnedTime < 4240){

                barrel[i].posY += 2;
                barrel[i].dropTick = 2;

            } else if (spawnedTime >= 4240 && spawnedTime < 4580) {

                if (barrel[i].dropTick == 2) {
                    barrel[i].posY++;
                    barrel[i].dropTick = 0;
                }
                barrel[i].posX -= 8;
                barrel[i].dropTick++;

            } else if (spawnedTime > 4960) {

                barrel[i].visible = 0;
                barrel[i].timeSpawned = 0;

            } else {

                barrel[i].posX -= 4;

            }
        }
    }

    return;
}
# 22 "rmain.c" 2
# 1 "./input.c" 1
# 1 "C:/c68/include/stdio.h" 1
# 1 "./input.c" 2
# 1 "./input.h" 1



typedef enum { FALSE, TRUE } boolean;

static boolean held = FALSE;
static boolean released = FALSE;
# 19 "./input.h"
boolean has_input();
# 30 "./input.h"
char get_input();
# 42 "./input.h"
void is_held();
# 2 "./input.c" 2
# 1 "C:/c68/include/osbind.h" 1
# 3 "./input.c" 2


boolean has_input() {
    return ((short)_trap_1_w((short)0x0B)  != 0) ? TRUE : FALSE;
}

char get_input() {
    return (char)_trap_1_w((short)0x08) ;
}


void is_held() {
# 24 "./input.c"
    char current_input;
    char next_input;


    printf("Waiting for first input...\n");
    while (!has_input());

    current_input = get_input();
    printf("First input is: %c\n", current_input);

    while(TRUE) {
        printf("Waiting for next input...\n");
        if (has_input()) {
            next_input = get_input();
            printf("Next input is: %c\n", next_input);
            if (current_input != next_input) {
                printf("Input released, different character pressed.\n");
                return;
            }
        } else {
            printf("Input released.\n");
            return;
        }
    }
}
# 23 "rmain.c" 2
# 1 "C:/c68/include/osbind.h" 1
# 25 "rmain.c" 2
# 1 "C:/c68/include/stdio.h" 1
# 26 "rmain.c" 2
# 1 "C:/c68/include/string.h" 1
# 25 "C:/c68/include/string.h"
 void *memcpy (void *dst, const void *src, size_t size) ;
 void *memmove (void *dst, const void *src, size_t size) ;
 int memcmp (const void *s1, const void *s2, size_t size) ;
 void *memchr (const void *s, int ucharwanted, size_t size) ;
 void *memset (void *s, int ucharfill, size_t size) ;

 char *strcpy (char *dst, const char *src) ;
 char *strncpy (char *dst, const char *src, size_t n) ;
 char *strcat (char *dst, const char *src) ;
 char *strncat (char *dst, const char *src, size_t n) ;
 int strcmp (const char *scan1, const char *scan2) ;
 int strncmp (const char *scan1, const char *scan2, size_t n) ;
 int strcoll (const char *scan1, const char *scan2) ;
 size_t	strxfrm (char *to, const char *from, size_t maxsize) ;
 char *strchr (const char *s, int charwanted) ;
 size_t strcspn (const char *s, const char *reject) ;
 char *strpbrk (const char *s, const char *breakat) ;
 char *strrchr (const char *s, int charwanted) ;
 size_t strspn (const char *s, const char *accept) ;
 char *strstr (const char *s, const char *wanted) ;
 char *strtok (char *s, const char *delim) ;
 size_t strlen (const char *scan) ;
 char *strerror (int errnum) ;
# 54 "C:/c68/include/string.h"
 void *memccpy (void *dst, const void *src, int ucharstop, size_t size) ;
 char *strlwr (char *string) ;
 char *strupr (char *string) ;



 char *strrev (char *string) ;
 char *strdup (const char *s) ;




 char *index (const char *s, int charwanted) ;
 char *rindex (const char *s, int charwanted) ;
 void bcopy (const void *src, void *dst, size_t length) ;
 int bcmp (const void *src, const void *dst, size_t n) ;
 void bzero (void *b, size_t n) ;

 void _bcopy (const void *src, void *dst, unsigned long length) ;
 int  _bcmp (const void *s1, const void *s2, unsigned long length) ;
 void _bzero (void *dst, unsigned long length) ;

 int stricmp ( const char *, const char * ) ;
 int strnicmp ( const char *, const char *, size_t ) ;
 int strcmpi ( const char *, const char * ) ;
 int strncmpi ( const char *, const char *, size_t ) ;
# 27 "rmain.c" 2
# 1 "C:/c68/include/stdlib.h" 1
# 23 "C:/c68/include/stdlib.h"
typedef char  wchar_t;
# 44 "C:/c68/include/stdlib.h"
typedef struct {
    int		quot;
    int		rem;
} div_t;

typedef struct {
    long	quot;
    long	rem;
} ldiv_t;

 double atof (const char *s) ;
 int atoi (const char *str) ;
 long atol (const char *str) ;
 long int strtol (const char *nptr, char **endptr, int base) ;
 unsigned long int strtoul (const char *nptr, char **endptr, int base) ;
 double strtod (const char *s, char **endptr) ;

 void srand (unsigned int seed) ;
 int rand (void) ;

 void *malloc (size_t n) ;
 void free (void *param) ;
 void *realloc (void *_r, size_t n) ;
 void *calloc (size_t n, size_t sz) ;





 void *alloca (size_t) ;
# 89 "C:/c68/include/stdlib.h"
 void  abort (void) ;


 int atexit (void (*)(void)) ;

 void  exit (int) ;

 char *getenv (const char *tag) ;
 int system (const char *s) ;

 void *bsearch (const void *key, const void *base, size_t num, size_t size, int (*cmp )(const void *, const void *)) ;
 void qsort (void *base, size_t total_elems, size_t size, int (*cmp )(const void *, const void *)) ;

 int abs (int x) ;
 long labs (long x) ;

 div_t div (int num, int denom) ;
 ldiv_t ldiv (long num, long denom) ;

 int mblen (const char *, size_t) ;
 size_t mbstowcs (wchar_t *, const char *, size_t) ;
 int mbtowc (wchar_t *, const char *, size_t) ;
 size_t wcstombs (char *, const wchar_t *, size_t) ;
 int wctomb (char *, wchar_t) ;

 wchar_t *wcscat (wchar_t *, const wchar_t *) ;
 int wcscmp (const wchar_t *, const wchar_t *) ;
 wchar_t *wcscpy (wchar_t *, const wchar_t *) ;
 size_t wcslen (const wchar_t *) ;
 wchar_t *wcsncat (wchar_t *, const wchar_t *, size_t) ;
 int wcsncmp (const wchar_t *, const wchar_t *, size_t) ;
 wchar_t *wcsncpy (wchar_t *, const wchar_t *, size_t) ;
# 28 "rmain.c" 2





Model testModel = {


{1, 236, 352, 0, 0, 1, 1, 0, -1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 306, 322, 300, 316},


{ {1, 176, 142, 0, 8, 0, 0},
{1, 272, 106, 0, 3, 0, 0},
{1, 304, 142, 2, 5, 0, 0},
{1, 192, 202, 1, 13, 0, 0},
{1, 176, 234, 2, 13, 0, 0},
{1, 192, 290, 1, 13, 0, 0},
{1, 176, 322, 2, 13, 0, 0},
{1, 272, 368, 1, 8, 0, 0},
{1, 176, 368, 0, 6, 0, 0} },


{{1, 248, 78, 0, 8, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 264, 78, 0, 8, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 312, 112, 0, 4, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 272, 150, 1, 6, 1, 3, 2, 0, 0, 0, 0, 1},
{1, 360, 153, 0, 5, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 208, 207, 0, 4, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 248, 206, 0, 4, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 344, 199, 1, 6, 1, 2, 3, 0, 0, 0, 0, 1},
{1, 256, 247, 1, 5, 1, 2, 2, 0, 0, 0, 0, 1},
{1, 320, 251, 0, 4, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 360, 252, 0, 4, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 208, 295, 0, 4, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 288, 291, 0, 5, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 272, 336, 1, 4, 1, 1, 2, 0, 0, 0, 0, 1},
{1, 356, 340, 0, 3, 0, 0, 0, 0, 0, 0, 0, 1} },


{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},


{1, 184, 336, 1, 0},


{ {1, 190, 162, 0},
{1, 338, 296, 0} },


{1, 256, 74, 0},


{ {0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0} },


{0, 240, 352, 1},


{0, 358, 300, 2, 0, 0, 0},


{0, 288, 66, 0},


{1, 352, 78, 5000, 5000},


{1, 240, 11, 0, 70981},


{1, 186, 48, 3},
};

int l = 0;

void render(Model *model, UINT16 *base) {

    renderDK(model->kong,(UINT32 *)base);
    renderMario(model->mario, base);
    renderHeart(model->heart, base);
    renderLady(model->lady,(UINT32 *) base);
    renderSpirit(model->spirit, base);

    renderBStack(model->kong, (UINT32 *)base);
    renderOil(model->oil,(UINT32 *) base);

    renderHammer(model->hammers[0], base);
    renderHammer(model->hammers[1], base);
    renderItem(model->item, base);

}

void renderLevel(Model *model, UINT32 *base) {

    int i;
    int j;
    int k;

    for (i = 0; i < 9; i++)
    {
        renderGirder(model->girders[i], (UINT8 *)base);
    }

    for (i = 0; i < 15; i++)
    {
        renderLadder(model->ladders[i], (UINT8 *)base);
    }

    for (i = 0; i < 7; i++)
    {
        renderBarrel(model->barrels[i], (UINT16 *)base);
    }

    renderBonus(model->timer, base);
    renderLives(model->lives, (UINT8 *)base);
    renderScore(model->score, (UINT32 *)base);

}

int checkMCollision(int jmXleft, int jmYtop, int otherXleft, int otherYtop, int otherSize) {


    int jmXright = jmXleft + 15;
    int jmYbottom = jmYtop + 15;


    int otherXright = otherXleft + (otherSize - 1);
    int otherYbottom = otherYtop + (otherSize - 1);


    if ((jmXleft <= otherXleft <= jmXright) || (jmXleft <= otherXright <= jmXright)) {


        if ((jmYtop <= otherYtop <= jmYbottom) || (jmYtop <= otherYbottom <= jmYbottom)) {


            return 1;
        }
    }

    return 0;
}

void draw (Model *model, UINT32 *buffer) {

    render(model,(UINT16 *)buffer);
    renderLevel(model, buffer);
    renderDK(model->kong,buffer);
    renderBStack(model->kong,buffer);
    renderLives(model->lives, (UINT8 *)buffer);
    renderScore(model->score, buffer);

}
# 200 "rmain.c"
void inputHandler(Model *model, int *gameRunning) {

    model->mario.state = 0;

    if (has_input()) {

        char input_val = get_input();

        while (has_input()) input_val = get_input();




        if (input_val == 'a') {
            model->mario.posX -= 4;
            model->mario.direction = 0;
            model->mario.state = 1;
            model->mario.walkFrame = 1 - model->mario.walkFrame;
        }
        else if (input_val == 'd') {
            model->mario.posX += 4;
            model->mario.direction = 1;
            model->mario.state = 1;
            model->mario.walkFrame = 1 - model->mario.walkFrame;
        }
        else if (input_val == 'w') {
            model->mario.posY -= 4;
            model->mario.state = 2;
            model->mario.climbFrame = 1 - model->mario.climbFrame;
        }
        else if (input_val == 's') {
            model->mario.posY += 4;
            model->mario.state = 2;
            model->mario.climbFrame = 1 - model->mario.climbFrame;
        }
        else if (input_val == 'q') {
            *gameRunning = 0;
        }
    }
}

int main() {


    UINT8 *raw1 = (UINT8 *)(long)_trap_1_wl((short)0x48,(long)(32000  + 256)) ;
    UINT8 *raw2 = (UINT8 *)(long)_trap_1_wl((short)0x48,(long)(32000  + 256)) ;

    UINT8 *screen1 = (UINT8 *)(((long)raw1 + 255) & 0xFFFFFF00);
    UINT8 *screen2 = (UINT8 *)(((long)raw2 + 255) & 0xFFFFFF00);

    UINT8 *original_screen = (void*)_trap_14_w((short)0x2) ;

    UINT8 *front_buffer = (void*)_trap_14_w((short)0x2) ;
    UINT8 *back_buffer  = screen1;

    long nowTime;
    volatile long startTime = getTime();
    long passedTime;


    int stepUpTick;
    int deathTick;

    int gameRunning = 1;
    int lastFrameTick = -1;

    int canSpawnBarrel = rand() % 10;
    Model *model = &testModel;


    memset(back_buffer, 0, 32000 );


    render(model, (UINT16 *)back_buffer);
    renderLevel(model, (UINT32 *)back_buffer);
    renderBonus(model->timer, (UINT32 *)back_buffer);
    renderLives(model->lives, (UINT8 *)back_buffer);
    renderScore(model->score, (UINT32 *)back_buffer);
    renderDK(model->kong, (UINT32 *)back_buffer);
    renderBStack(model->kong, (UINT32 *)back_buffer);

    (void)_trap_14_w((short)0x25) ;
    (void)_trap_14_wllw((short)0x5,(long)(back_buffer),(long)back_buffer,(short)(-1)) ;


    {
        UINT8 *temp = front_buffer;
        front_buffer = back_buffer;
        back_buffer = temp;
    }

    while (gameRunning) {

        nowTime = getTime();
        passedTime = nowTime - startTime;

        if (passedTime % 2000 == 0) {

            model->timer.value -= 200;
            clear_region((UINT8 *)back_buffer, model->timer.posY + 11, model->timer.posX + 4, 16, 48);
            renderBonus(model->timer, (UINT16 *)back_buffer);

            if (model->timer.value == 4000) {

                gameRunning = 0;
                model->mario.state = 4;
            }
        }


        if (passedTime % 12  == 0 && passedTime != lastFrameTick) {

            lastFrameTick = passedTime;



            memset(back_buffer, 0, 32000 );



            inputHandler(model, &gameRunning);





            if (passedTime > 40000) {
                gameRunning = 0;
            }


            updateKong(&model->kong, canSpawnBarrel);




            updateMCollision(model->mario);



            if (model->kong.spawnBarrel == 1) {
                model->kong.spawnBarrel = 0;
                model->barrels[l].visible = 1;
                model->barrels[l].posY = 126;
                model->barrels[l].posX = 254;
                model->barrels[l].timeSpawned = nowTime;
                l++;
                if (l > 8) {
                    l = 0;
                }
            }

            updateBarrels(model->barrels, nowTime);





            draw(model, (UINT32 *)back_buffer);


            (void)_trap_14_w((short)0x25) ;
            (void)_trap_14_wllw((short)0x5,(long)(back_buffer),(long)back_buffer,(short)(-1)) ;

            {
                UINT8 *temp = front_buffer;
                front_buffer = back_buffer;
                back_buffer = temp;
            }
        }
    }

    (void)_trap_14_w((short)0x25) ;
    (void)_trap_14_wllw((short)0x5,(long)(original_screen),(long)original_screen,(short)(-1)) ;

    (short)_trap_1_wl((short)0x49,(long)(raw1)) ;
    (short)_trap_1_wl((short)0x49,(long)(raw2)) ;

    return 0;
}
