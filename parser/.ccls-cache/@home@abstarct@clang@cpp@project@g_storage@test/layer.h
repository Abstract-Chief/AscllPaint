/*File "layer.h" create by debial, (Вт 15 ноя 2022 11:33:59)*/
#ifndef DEBIAL_LAYER_H_SENTURY
#define DEBIAL_LAYER_H_SENTURY
#include "stdio.h"
#include <cstdlib>

class GraphickObj{
   public:
   virtual void graphick(int x,int y)=0;
};

class Layer : public GraphickObj{
   int cols,rows;
   char **data;
public:
   Layer(const char *filename);
   Layer(FILE *file);
   void deserialise(FILE *file);
   void graphick(int x,int y);
   
};

class Animation :public GraphickObj{
   int count;
   float n_layer,speed;
   Layer **layers;
   public:
   Animation(const char *filename,float speed);
   void graphick(int x,int y);
};


#endif
