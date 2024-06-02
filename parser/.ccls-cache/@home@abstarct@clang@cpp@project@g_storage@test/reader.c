/*File "reader.c" create by abstarct, (Вс 19 ноя 2023 21:06:01)*/
#include "g_struct.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct Layer* LayerBin_parse(FILE *file){
   struct Layer *layer=malloc(sizeof(struct Layer));  
   fread(layer,sizeof(int)*2,1,file);
   layer->data=malloc(sizeof(char*)*layer->rows);
   for(int i=0;i<layer->rows;i++){
      layer->data[i]=malloc(layer->cols*sizeof(char));
      fread(layer->data[i],sizeof(char),layer->cols,file);
   }
   return layer;
}
struct Layer* Layer_parse(const char* filename){
   FILE *file=fopen(filename,"rb");
   if(file==NULL){
      printf("error open %s",filename);
      exit(1);
   }
   struct Layer* layer=LayerBin_parse(file);
   fclose(file);
   return layer;
}
struct Animation* Animation_parse(const char *filename){
   struct Animation* an=malloc(sizeof(struct Animation));
   an->n_layer=0;
   FILE *file=fopen(filename,"rb");
   if(file==NULL){
      printf("error open %s",filename);
      exit(1);
   }
   fread(&an->count, sizeof(int),1,file);
   an->layers=malloc(sizeof(struct Layer*)*an->count);
   printf("%d\n",an->count);
   for(int i=0;i<an->count;i++){
      an->layers[i]=LayerBin_parse(file);
   }
   fclose(file);
   return an;
}

int main(){
   struct Animation* a=Animation_parse("animation.anim");
   printf("%d %d\n",a->layers[0]->cols,a->layers[0]->rows);
   for(int i=0;i<a->layers[0]->rows;i++){
      printf("  |");
      for(int j=0;j<a->count;j++)
         printf("%s%s",a->layers[j]->data[i],(j+1==a->count ? "|\n" : "|") );
   }
}
