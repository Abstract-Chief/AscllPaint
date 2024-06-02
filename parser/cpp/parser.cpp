/*File "layer.cpp" create by debial, (Вт 15 ноя 2022 11:33:59)*/
#include "parser.h"
#include <ctime>
#include <iostream>
#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

Layer::Layer(const char *filename){
   FILE *file=fopen(filename,"rb");
   if(file==NULL){
      printf("error open %s",filename);
      exit(1);
   }
   deserialise(file);
   fclose(file);
}
Layer::Layer(FILE *file){
   deserialise(file);
}

void Layer::deserialise(FILE *file){
   fread(&cols,sizeof(int),1,file);
   fread(&rows,sizeof(int),1,file);
   data=new char*[rows];
   for(int i=0;i<rows;i++){
      data[i]=new char[cols];
      fread(data[i],sizeof(char),cols,file);
   }
}
void Layer::graphick(int x,int y){
   for(int i=0;i<rows;i++)
      mvprintw(y+i,x,"%s",data[i]);
}

Animation::Animation(const char *filename,float speed_){
   speed=speed_;
   n_layer=0;
   FILE *file=fopen(filename,"rb");
   if(file==NULL){
      printf("error open %s",filename);
      exit(1);
   }
   fread(&count, sizeof(int),1,file);
   layers=new Layer*[count];
   for(int i=0;i<count;i++){
      layers[i]=new Layer(file);
   }
   fclose(file);
   
}
void Animation::graphick(int x,int y){
   if(n_layer+speed>=count) n_layer=0;
   n_layer+=speed;
   layers[(int)n_layer]->graphick(x,y);
}

int main(int argc,char **argv){
   if(argc<2){
      std::cout << "need a filename in args" << std::endl;
      return 1;
   }
   int a=strlen(argv[1]);
   GraphickObj *obj;
   if(argv[1][a-1]=='r')
      obj=new Layer(argv[1]);
   else if(argv[1][a-1]=='m')
      obj=new Animation(argv[1],0.1);
   initscr();
   curs_set(0);
   cbreak();
   noecho();
   for(int i=0;i<100;i++){
      obj->graphick(1, 1);
      refresh();
      napms(100);
      
   }
   getchar();
   endwin();
}
