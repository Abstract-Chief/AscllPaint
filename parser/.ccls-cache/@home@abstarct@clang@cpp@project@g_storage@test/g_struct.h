/*File "g_struct.h" create by abstarct, (Вс 19 ноя 2023 21:06:01)*/
#ifndef ABSTARCT_G_STRUCT_H_SENTURY
#define ABSTARCT_G_STRUCT_H_SENTURY

struct Layer{
   int cols,rows;
   char **data;
};
struct Animation{
   int count;
   float n_layer,speed;
   struct Layer **layers;
};

#endif
