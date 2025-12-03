#ifndef GETLEDINDEX_H
#define GETLEDINDEX_H

#include <Arduino.h>

const byte ROW_SIZES[7] = {17, 18, 19, 20, 19, 18, 17};



inline int getLedIndex(int row, int col) {
    int index = 0;

    if(row ==0){
        index=12;
        for (int i = 0; i < col; i++)
        {
            if(i%2==0)
                index+=1;
            else
                index+=13;
        }
    }else if(row==1){
        index=1;
        for(int i=0; i<col; i++){
            if (i==0){
                index+=10;
            }else{
                if(i%2==0)
                    index+=11;
                else
                    index+=3;
            
                }   
                 
        }      
    }else if(row ==2){
        index = 2;
        for(int i=0; i<col; i++){
            if (i==0){
                index+=8;
            }else if(i==17){
                index+=3;
            }else{
                if(i%2==0)
                    index+=9;
                else
                    index+=5;
            }
        }
         
    }else if(row ==3){
        index = 0;
        for(int i=0; i<col; i++){
            if (i==0){
                index+=3;
            }else if(i==1){
                index+=6;
            }else if(i==18){
                index+=5;
            }else{
                index+=7;
            }
        }         
    }else if(row ==4){
        index = 4;
        for(int i=0; i<col; i++){
            if (i==0){
                index+=4;
            }else if(i==17){
                index+=7;
            }else{
                if(i%2==0)
                    index+=5;
                else
                    index+=9;
            }
        }         
    }else if(row ==5){
        index = 5;
        for(int i=0; i<col; i++){
            if (i==0){
                index+=2;
            }else{
                if(i%2==0)
                    index+=3;
                else
                    index+=11;
            }
        }         
    }else if(row ==6){
        index = 6;
        for(int i=0; i<col; i++){
            if(i%2==0)
                index+=13;
            else
                index+=1;
            
        }         
    }
  return index;
}


#endif