/*File "g_struct.h" create by abstarct, (Вс 19 ноя 2023 21:06:01)*/
#ifndef ABSTARCT_G_STRUCT_H_SENTURY
#define ABSTARCT_G_STRUCT_H_SENTURY

typedef struct{
   char symbol;
   short x,y;
   short color;
}Point;

typedef struct{
   int count;
   int cols,rows;
   Point **data;
}Layer;
typedef struct{
   int count;
   float n_layer,speed;
   Layer *layers[32];
} Animation;

#endif
