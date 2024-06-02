/*File "reader.c" create by abstarct, (Вс 19 ноя 2023 21:06:01)*/
#include "g_struct.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ncurses.h>

void parse_color(FILE *file,short *r,short *g,short *b){
      fread(r,sizeof(short),1,file);
      fread(g,sizeof(short),1,file);
      fread(b,sizeof(short),1,file);
}
void ParseColors(FILE *file){
   int count=0;
   fread(&count,sizeof(char),1,file);
   for(int i=2;i<count;i++){
      short r,g,b;
      parse_color(file,&r,&g,&b);
      short a=(r*1000)/255,f=(g*1000)/255,c=(b*1000)/255;
      init_color(i+1,a,f,c);
   }
}
void ParsePair(FILE *file){
   ParseColors(file);
   short n;
   fread(&n,sizeof(n),1,file);
   short a,b;
   for(int i=1;i<=n;i++){
      fread(&a,sizeof(a),1,file);
      fread(&b,sizeof(b),1,file);
   }
}
Point* deserialize_point(FILE *file){
   Point* p=malloc(sizeof(Point));
   fread(&p->symbol,1,1,file);
   fread(&p->x,sizeof(short),1,file);
   fread(&p->y,sizeof(short),1,file);
   fread(&p->color,sizeof(short),1,file);
   return p;
}
Layer* ParseLayer(FILE *file){
   Layer* layer=malloc(sizeof(Layer));
   fread(&layer->count,sizeof(int),1,file);
   fread(&layer->cols,sizeof(int),1,file);
   fread(&layer->rows,sizeof(int),1,file);
   layer->data=malloc(sizeof(Point*)*layer->rows*layer->cols);
   for(int i=0;i<layer->count;i++){
      layer->data[i]=deserialize_point(file);
   }
   return layer;
}
Animation* ParseAnim(FILE *file){
   Animation* anim=malloc(sizeof(Animation));
   fread(&anim->count,sizeof(int),1,file);
   for(int i=0;i<anim->count;i++){
      anim->layers[i]=ParseLayer(file);
   }
   ParsePair(file);
   return anim;
}

Animation* Animation_parse(const char* filename){
   FILE *file=fopen(filename,"rb");
   if(file==NULL){
      printf("error open %s",filename);
      exit(1);
   }
   Animation* anim=ParseAnim(file);
   fclose(file);
   return anim;
}

Layer* Layer_parse(const char* filename){
   FILE *file=fopen(filename,"rb");
   if(file==NULL){
      printf("error open %s",filename);
      exit(1);
   }
   Layer* layer=ParseLayer(file);
   fclose(file);
   return layer;
}

void graphick_layer(int x,int y,Layer *layer){
   for(int i=0;i<layer->count;i++){
      Point *p=layer->data[i];
      attron(COLOR_PAIR(p->color));
      mvaddch(y+p->y,x+p->x,p->symbol);
      attroff(COLOR_PAIR(p->color));
   }
}
int main(int argc, char** argv){
   if(argc<2){
      printf("need animation file in args");
      exit(1);
   }
   initscr();
   start_color();
   use_default_colors();
   raw();//init 

   Animation* a=Animation_parse(argv[1]);

   for(int i=0;i<a->count;i++){
      graphick_layer(1,1,a->layers[i]);
      refresh();
      napms(500);
   }

   napms(5000);
   endwin();
}
