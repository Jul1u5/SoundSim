#include <stdio.h>
#include <stdlib.h>
#include "main.c"

void absorption(item_node *node, float coeff){
    // der Absoprtionsfaktor ist für Hindernisse und wird auf alle dB Zahlen angewandt.

         item_node *temp;
         temp = getItem_Root(x,y);

         while(temp != NULL){

        setFreq20b40(temp, getFreq20b40(temp) * coeff);
        setFreq40b100(temp, getFreq40b100(temp) * coeff);
        setFreq100b150(temp, getFreq100b150(temp) * coeff);
        setFreq150b400(temp, getFreq150b400(temp) * coeff);
        setFreq400b1000(temp, getFreq400b1000(temp) * coeff);
        setFreq1000b2000(temp, getFreq1000b2000(temp) * coeff);
        setFreq2000b3500(temp, getFreq2000b3500(temp) * coeff);
        setFreq3500b6000(temp, getFreq3500b6000(temp) * coeff);
        setFreq6000b10000(temp, getFreq6000b10000(temp) * coeff);
        setFreq10000b20000(temp, getFreq10000b20000(temp) * coeff);
        
        temp = temp->next;
    }
    
}
    
void interference()
    /*
    for(each Sound auf einem Feld{
      averagedB20b40 = ElementN.getFreq20b40(x,y) + ElementN+1.getFreq20b40(x,y) / N;
     ElemntN.setFreq20b40(x,y, averagedB);
    
    // TODO wenn Zwei Frequenzen sich auf einer Zelle Überlagern.
}