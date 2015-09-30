#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "soundwavefunction.h"

// Anzahl der Teilchenverschiebunngen
void increaseMovement(item_node *node){
    if(getItemID(node)==0){
        node->data.Sound.movement++;
    }
}

int getMovement(item_node *node){
    if(getItemID(node)==0){
        return node->data.Sound.movement;
    }
}


// Seite der "Welle" 0 = nicht von betroffen , 1 == Links , 2 = Rechts
void setSideOfWave(item_node *node, int side){
     if(getItemID(node)==0){
         node->data.Sound.sideofwave = side;
     }
}

int getSideOfWave(item_node *node){
    if(getItemID(node)==0){
        return node->data.Sound.sideofwave;
    }
}
 
void changeReboundSideOfWave(item_node *node)
{
 if(getSideOfWave(node) == 1)
 // der Rebound der Teilchen muss auch die Seitenzugehörigkeit ändern.
 {
     setSideOfWave(node,2);
 }
else if(getSideOfWave(node) == 2){
    setSideOfWave(node,1);
 }
else{
     setSideOfWave(node,0);
 }
}
    
void addWave(item_node *node,int x, int y)
/*
 addwave lässt die Welle bis zu einer bestimmten Verschiebungsweite ungekrümmt, danach werden die resultierenden
 Teilchen "Kugelfunktionsartig" erzeugt und haben eine zugehörgkeit zur rechten oder linken Seite.
 */
{
item_node *temp;
item_node *tempAdd; // ein temporäres Teilchen was hinzugefügt wird.
temp = getItem_Root(x,y);
    
while(temp != NULL){
    
    
    // Wenn das Hauptteilchen noch nicht weit genug gewandert ist, bleibt die Welle ungekrümmt.
        // Teichen erzeugt 2 Nahcbarn die die Wellenausbreitung Linear darstellen.
if( ( getMovement(node) < (x_format * 0.05)) || (getMovement(node) < (y_format * 0.5) ))
{
        if(getDirectionID(node) == 1){
        // oben
            if( (getSideOfWave(node) == 2) || (getSideOfWave(node) == 0))
            {
                tempAdd = createItem(x++,y,0); // Neues Teilchen der rechten Seite
                setSideOfWave(tempAdd,2); // der Zelle wird eine Zugehörigkeit zur Rechtenseite = 2

                setFreq20b40(tempAdd, getFreq20b40(temp) * 0.96);
                setFreq40b100(tempAdd, getFreq40b100(temp) * 0.96 );
                setFreq100b150(tempAdd, getFreq100b150(temp) * 0.96);
                setFreq150b400(tempAdd, getFreq150b400(temp) * 0.96);
                setFreq400b1000(tempAdd, getFreq400b1000(temp) * 0.96);
                setFreq1000b2000(tempAdd, getFreq1000b2000(temp) * 0.96);
                setFreq2000b3500(tempAdd, getFreq2000b3500(temp) * 0.96);
                setFreq3500b6000(tempAdd, getFreq3500b6000(temp) * 0.96 );
                setFreq6000b10000(tempAdd, getFreq6000b10000(temp) * 0.96);
                setFreq10000b20000(tempAdd, getFreq10000b20000(temp) * 0.96);
                            }
        // linke Seite
        // Wenn du kein Seitenteil bist oder zur Linken seite gehörst
            else if( (getSideOfWave(node) == 1) || (getSideOfWave(node) == 0))
            {
                tempAdd = createItem(x--,y,0);// neues Teilchen der linken Seite
                setSideOfWave(tempAdd,1);
                
                setFreq20b40(tempAdd, getFreq20b40(temp) * 0.96);
                setFreq40b100(tempAdd, getFreq40b100(temp) * 0.96 );
                setFreq100b150(tempAdd, getFreq100b150(temp) * 0.96);
                setFreq150b400(tempAdd, getFreq150b400(temp) * 0.96);
                setFreq400b1000(tempAdd, getFreq400b1000(temp) * 0.96);
                setFreq1000b2000(tempAdd, getFreq1000b2000(temp) * 0.96);
                setFreq2000b3500(tempAdd, getFreq2000b3500(temp) * 0.96);
                setFreq3500b6000(tempAdd, getFreq3500b6000(temp) * 0.96 );
                setFreq6000b10000(tempAdd, getFreq6000b10000(temp) * 0.96);
                setFreq10000b20000(tempAdd, getFreq10000b20000(temp) * 0.96);
            }
        }
        
        else if( getDirectionID(node) == 2){
                // Nach oben rechts
                // rechte Seite der Welle für neue ID
                if( (getSideOfWave(node) == 2) || (getSideOfWave(node) == 0))
                {
                    tempAdd = createItem(x++,y--,0); // Neues Teilchen der rechten Seite
                    setSideOfWave(tempAdd,2); // der Zelle wird eine Zugehörigkeit zur Rechtenseite = 2
                    
                    setFreq20b40(tempAdd, getFreq20b40(temp) * 0.96);
                    setFreq40b100(tempAdd, getFreq40b100(temp) * 0.96 );
                    setFreq100b150(tempAdd, getFreq100b150(temp) * 0.96);
                    setFreq150b400(tempAdd, getFreq150b400(temp) * 0.96);
                    setFreq400b1000(tempAdd, getFreq400b1000(temp) * 0.96);
                    setFreq1000b2000(tempAdd, getFreq1000b2000(temp) * 0.96);
                    setFreq2000b3500(tempAdd, getFreq2000b3500(temp) * 0.96);
                    setFreq3500b6000(tempAdd, getFreq3500b6000(temp) * 0.96 );
                    setFreq6000b10000(tempAdd, getFreq6000b10000(temp) * 0.96);
                    setFreq10000b20000(tempAdd, getFreq10000b20000(temp) * 0.96);
                }
                // linke Seite
                else if( (getSideOfWave(node) == 1) || (getSideOfWave(node) == 0))
                {
                    tempAdd = createItem(x--,y++,0);// neues Teilchen der linken Seite
                	setSideOfWave(tempAdd,1);

                    setFreq20b40(tempAdd, getFreq20b40(temp) * 0.96);
                    setFreq40b100(tempAdd, getFreq40b100(temp) * 0.96 );
                    setFreq100b150(tempAdd, getFreq100b150(temp) * 0.96);
                    setFreq150b400(tempAdd, getFreq150b400(temp) * 0.96);
                    setFreq400b1000(tempAdd, getFreq400b1000(temp) * 0.96);
                    setFreq1000b2000(tempAdd, getFreq1000b2000(temp) * 0.96);
                    setFreq2000b3500(tempAdd, getFreq2000b3500(temp) * 0.96);
                    setFreq3500b6000(tempAdd, getFreq3500b6000(temp) * 0.96 );
                    setFreq6000b10000(tempAdd, getFreq6000b10000(temp) * 0.96);
                    setFreq10000b20000(tempAdd, getFreq10000b20000(temp) * 0.96);
                }
                
            }
        else if( getDirectionID(node) == 3){
            // Nach Rechts
            // rechte Seite der Welle für neue ID
            if( (getSideOfWave(node) == 2) || (getSideOfWave(node) == 0))
            {
                tempAdd = createItem(x,y--,0); // Neues Teilchen der rechten Seite
            	setSideOfWave(tempAdd,2);

                setFreq20b40(tempAdd, getFreq20b40(temp) * 0.96);
                setFreq40b100(tempAdd, getFreq40b100(temp) * 0.96 );
                setFreq100b150(tempAdd, getFreq100b150(temp) * 0.96);
                setFreq150b400(tempAdd, getFreq150b400(temp) * 0.96);
                setFreq400b1000(tempAdd, getFreq400b1000(temp) * 0.96);
                setFreq1000b2000(tempAdd, getFreq1000b2000(temp) * 0.96);
                setFreq2000b3500(tempAdd, getFreq2000b3500(temp) * 0.96);
                setFreq3500b6000(tempAdd, getFreq3500b6000(temp) * 0.96 );
                setFreq6000b10000(tempAdd, getFreq6000b10000(temp) * 0.96);
                setFreq10000b20000(tempAdd, getFreq10000b20000(temp) * 0.96);
            }
            // linke Seite
            else if( (getSideOfWave(node) == 1) || (getSideOfWave(node) == 0))
            {
                tempAdd = createItem(x,y++,0);// neues Teilchen der linken Seite
                setSideOfWave(tempAdd,1);

                setFreq20b40(tempAdd, getFreq20b40(temp) * 0.96);
                setFreq40b100(tempAdd, getFreq40b100(temp) * 0.96 );
                setFreq100b150(tempAdd, getFreq100b150(temp) * 0.96);
                setFreq150b400(tempAdd, getFreq150b400(temp) * 0.96);
                setFreq400b1000(tempAdd, getFreq400b1000(temp) * 0.96);
                setFreq1000b2000(tempAdd, getFreq1000b2000(temp) * 0.96);
                setFreq2000b3500(tempAdd, getFreq2000b3500(temp) * 0.96);
                setFreq3500b6000(tempAdd, getFreq3500b6000(temp) * 0.96 );
                setFreq6000b10000(tempAdd, getFreq6000b10000(temp) * 0.96);
                setFreq10000b20000(tempAdd, getFreq10000b20000(temp) * 0.96);
            }
        }
        else if( getDirectionID(node) == 4){
            // unten rechts
            // rechte Seite der Welle für neue ID
            if( (getSideOfWave(node) == 2) || (getSideOfWave(node) == 0))
            {
                tempAdd = createItem(x--,y--,0); // Neues Teilchen der rechten Seite
               	setSideOfWave(tempAdd,2);

                setFreq20b40(tempAdd, getFreq20b40(temp) * 0.96);
                setFreq40b100(tempAdd, getFreq40b100(temp) * 0.96);
                setFreq100b150(tempAdd, getFreq100b150(temp) * 0.96);
                setFreq150b400(tempAdd, getFreq150b400(temp) * 0.96);
                setFreq400b1000(tempAdd, getFreq400b1000(temp) * 0.96);
                setFreq1000b2000(tempAdd, getFreq1000b2000(temp) * 0.96);
                setFreq2000b3500(tempAdd, getFreq2000b3500(temp) * 0.96);
                setFreq3500b6000(tempAdd, getFreq3500b6000(temp) * 0.96 );
                setFreq6000b10000(tempAdd, getFreq6000b10000(temp) * 0.96);
                setFreq10000b20000(tempAdd, getFreq10000b20000(temp) * 0.96);
            }
            // linke Seite
            else if( (getSideOfWave(node) == 1) || (getSideOfWave(node) == 0))
            {
                tempAdd = createItem(x++,y++,0);// neues Teilchen der linken Seite
                setSideOfWave(tempAdd,1);

                setFreq20b40(tempAdd, getFreq20b40(temp) * 0.96);
                setFreq40b100(tempAdd, getFreq40b100(temp) * 0.96 );
                setFreq100b150(tempAdd, getFreq100b150(temp) * 0.96);
                setFreq150b400(tempAdd, getFreq150b400(temp) * 0.96);
                setFreq400b1000(tempAdd, getFreq400b1000(temp) * 0.96);
                setFreq1000b2000(tempAdd, getFreq1000b2000(temp) * 0.96);
                setFreq2000b3500(tempAdd, getFreq2000b3500(temp) * 0.96);
                setFreq3500b6000(tempAdd, getFreq3500b6000(temp) * 0.96 );
                setFreq6000b10000(tempAdd, getFreq6000b10000(temp) * 0.96);
                setFreq10000b20000(tempAdd, getFreq10000b20000(temp) * 0.96);
            }
        }
        
        else if( getDirectionID(node) == 5){
            //unten
            // rechte Seite der Welle für neue ID
            if( (getSideOfWave(node) == 2) || (getSideOfWave(node) == 0))
            {
                tempAdd = createItem(x--,y,0); // Neues Teilchen der rechten Seite
                setSideOfWave(tempAdd,2);

                setFreq20b40(tempAdd, getFreq20b40(temp) * 0.96);
                setFreq40b100(tempAdd, getFreq40b100(temp) * 0.96 );
                setFreq100b150(tempAdd, getFreq100b150(temp) * 0.96);
                setFreq150b400(tempAdd, getFreq150b400(temp) * 0.96);
                setFreq400b1000(tempAdd, getFreq400b1000(temp) * 0.96);
                setFreq1000b2000(tempAdd, getFreq1000b2000(temp) * 0.96);
                setFreq2000b3500(tempAdd, getFreq2000b3500(temp) * 0.96);
                setFreq3500b6000(tempAdd, getFreq3500b6000(temp) * 0.96 );
                setFreq6000b10000(tempAdd, getFreq6000b10000(temp) * 0.96);
                setFreq10000b20000(tempAdd, getFreq10000b20000(temp) * 0.96);
            }
            // linke Seite
            else if( (getSideOfWave(node) == 1) || (getSideOfWave(node) == 0))
            {
                tempAdd = createItem(x++,y,0);// neues Teilchen der linken Seite
                setSideOfWave(tempAdd,1);

                setFreq20b40(tempAdd, getFreq20b40(temp) * 0.96);
                setFreq40b100(tempAdd, getFreq40b100(temp) * 0.96 );
                setFreq100b150(tempAdd, getFreq100b150(temp) * 0.96);
                setFreq150b400(tempAdd, getFreq150b400(temp) * 0.96);
                setFreq400b1000(tempAdd, getFreq400b1000(temp) * 0.96);
                setFreq1000b2000(tempAdd, getFreq1000b2000(temp) * 0.96);
                setFreq2000b3500(tempAdd, getFreq2000b3500(temp) * 0.96);
                setFreq3500b6000(tempAdd, getFreq3500b6000(temp) * 0.96 );
                setFreq6000b10000(tempAdd, getFreq6000b10000(temp) * 0.96);
                setFreq10000b20000(tempAdd, getFreq10000b20000(temp) * 0.96);
            }
        }
        else if( getDirectionID(node) == 6){
            //unten links
            // rechte Seite der Welle für neue ID
            if( (getSideOfWave(node) == 2) || (getSideOfWave(node) == 0))
            {
                tempAdd = createItem(x--,y++,0); // Neues Teilchen der rechten Seite
                setSideOfWave(tempAdd,2);

                setFreq20b40(tempAdd, getFreq20b40(temp) * 0.96);
                setFreq40b100(tempAdd, getFreq40b100(temp) * 0.96 );
                setFreq100b150(tempAdd, getFreq100b150(temp) * 0.96);
                setFreq150b400(tempAdd, getFreq150b400(temp) * 0.96);
                setFreq400b1000(tempAdd, getFreq400b1000(temp) * 0.96);
                setFreq1000b2000(tempAdd, getFreq1000b2000(temp) * 0.96);
                setFreq2000b3500(tempAdd, getFreq2000b3500(temp) * 0.96);
                setFreq3500b6000(tempAdd, getFreq3500b6000(temp) * 0.96 );
                setFreq6000b10000(tempAdd, getFreq6000b10000(temp) * 0.96);
                setFreq10000b20000(tempAdd, getFreq10000b20000(temp) * 0.96);
            }
            // linke Seite
            else if( (getSideOfWave(node) == 1) || (getSideOfWave(node) == 0))
            {
                tempAdd = createItem(x++,y--,0);// neues Teilchen der linken Seite
                setSideOfWave(tempAdd,1);

                setFreq20b40(tempAdd, getFreq20b40(temp) * 0.96);
                setFreq40b100(tempAdd, getFreq40b100(temp) * 0.96 );
                setFreq100b150(tempAdd, getFreq100b150(temp) * 0.96);
                setFreq150b400(tempAdd, getFreq150b400(temp) * 0.96);
                setFreq400b1000(tempAdd, getFreq400b1000(temp) * 0.96);
                setFreq1000b2000(tempAdd, getFreq1000b2000(temp) * 0.96);
                setFreq2000b3500(tempAdd, getFreq2000b3500(temp) * 0.96);
                setFreq3500b6000(tempAdd, getFreq3500b6000(temp) * 0.96 );
                setFreq6000b10000(tempAdd, getFreq6000b10000(temp) * 0.96);
                setFreq10000b20000(tempAdd, getFreq10000b20000(temp) * 0.96);
            }
        }
        else if( getDirectionID(node) == 7){
            // links
            // rechte Seite der Welle für neue ID
            if( (getSideOfWave(node) == 2) || (getSideOfWave(node) == 0))
            {
                tempAdd = createItem(x,y++,0); // Neues Teilchen der rechten Seite
                setSideOfWave(tempAdd,2);

                setFreq20b40(tempAdd, getFreq20b40(temp) * 0.96);
                setFreq40b100(tempAdd, getFreq40b100(temp) * 0.96 );
                setFreq100b150(tempAdd, getFreq100b150(temp) * 0.96);
                setFreq150b400(tempAdd, getFreq150b400(temp) * 0.96);
                setFreq400b1000(tempAdd, getFreq400b1000(temp) * 0.96);
                setFreq1000b2000(tempAdd, getFreq1000b2000(temp) * 0.96);
                setFreq2000b3500(tempAdd, getFreq2000b3500(temp) * 0.96);
                setFreq3500b6000(tempAdd, getFreq3500b6000(temp) * 0.96 );
                setFreq6000b10000(tempAdd, getFreq6000b10000(temp) * 0.96);
                setFreq10000b20000(tempAdd, getFreq10000b20000(temp) * 0.96);
            }
            // linke Seite
            else if( (getSideOfWave(node) == 1) || (getSideOfWave(node) == 0))
            {
                tempAdd = createItem(x,y--,0);// neues Teilchen der linken Seite
                setSideOfWave(tempAdd,1);

                setFreq20b40(tempAdd, getFreq20b40(temp) * 0.96);
                setFreq40b100(tempAdd, getFreq40b100(temp) * 0.96 );
                setFreq100b150(tempAdd, getFreq100b150(temp) * 0.96);
                setFreq150b400(tempAdd, getFreq150b400(temp) * 0.96);
                setFreq400b1000(tempAdd, getFreq400b1000(temp) * 0.96);
                setFreq1000b2000(tempAdd, getFreq1000b2000(temp) * 0.96);
                setFreq2000b3500(tempAdd, getFreq2000b3500(temp) * 0.96);
                setFreq3500b6000(tempAdd, getFreq3500b6000(temp) * 0.96 );
                setFreq6000b10000(tempAdd, getFreq6000b10000(temp) * 0.96);
                setFreq10000b20000(tempAdd, getFreq10000b20000(temp) * 0.96);
            }
        }
        else if( getDirectionID(node) == 8){
            //oben links
            // rechte Seite der Welle für neue ID
            if( (getSideOfWave(node) == 2) || (getSideOfWave(node) == 0))
            {
                tempAdd = createItem(x++,y--,0); // Neues Teilchen der rechten Seite
                setSideOfWave(tempAdd,2);

                setFreq20b40(tempAdd, getFreq20b40(temp) * 0.96);
                setFreq40b100(tempAdd, getFreq40b100(temp) * 0.96 );
                setFreq100b150(tempAdd, getFreq100b150(temp) * 0.96);
                setFreq150b400(tempAdd, getFreq150b400(temp) * 0.96);
                setFreq400b1000(tempAdd, getFreq400b1000(temp) * 0.96);
                setFreq1000b2000(tempAdd, getFreq1000b2000(temp) * 0.96);
                setFreq2000b3500(tempAdd, getFreq2000b3500(temp) * 0.96);
                setFreq3500b6000(tempAdd, getFreq3500b6000(temp) * 0.96 );
                setFreq6000b10000(tempAdd, getFreq6000b10000(temp) * 0.96);
                setFreq10000b20000(tempAdd, getFreq10000b20000(temp) * 0.96);
            }
            // linke Seite
            else if( (getSideOfWave(node) == 1) || (getSideOfWave(node) == 0))
            {
                tempAdd = createItem(x--,y++,0);// neues Teilchen der linken Seite
                setSideOfWave(tempAdd,1);

                setFreq20b40(tempAdd, getFreq20b40(temp) * 0.96);
                setFreq40b100(tempAdd, getFreq40b100(temp) * 0.96 );
                setFreq100b150(tempAdd, getFreq100b150(temp) * 0.96);
                setFreq150b400(tempAdd, getFreq150b400(temp) * 0.96);
                setFreq400b1000(tempAdd, getFreq400b1000(temp) * 0.96);
                setFreq1000b2000(tempAdd, getFreq1000b2000(temp) * 0.96);
                setFreq2000b3500(tempAdd, getFreq2000b3500(temp) * 0.96);
                setFreq3500b6000(tempAdd, getFreq3500b6000(temp) * 0.96 );
                setFreq6000b10000(tempAdd, getFreq6000b10000(temp) * 0.96);
                setFreq10000b20000(tempAdd, getFreq10000b20000(temp) * 0.96);
            }
        }
        
}
else
	{
    // evtl merken ob ein teil zur rechten oder linken seite gehört und dann nur noch einseitig
    // weiter verbreitet - neue variable die das anzeigt !
    
    if( getDirectionID(node) == 1){
        // Nach oben
        // rechte Seite der Welle für neue ID
        
        if( (getSideOfWave(node) == 2) || (getSideOfWave(node) == 0))
        {
        	tempAdd = createItem(x++,y--,0); // Neues Teilchen der rechten Seite
        	setSideOfWave(tempAdd,2);
        
            setFreq20b40(tempAdd, getFreq20b40(temp) * 0.96);
            setFreq40b100(tempAdd, getFreq40b100(temp) * 0.96 );
            setFreq100b150(tempAdd, getFreq100b150(temp) * 0.96);
            setFreq150b400(tempAdd, getFreq150b400(temp) * 0.96);
            setFreq400b1000(tempAdd, getFreq400b1000(temp) * 0.96);
            setFreq1000b2000(tempAdd, getFreq1000b2000(temp) * 0.96);
            setFreq2000b3500(tempAdd, getFreq2000b3500(temp) * 0.96);
            setFreq3500b6000(tempAdd, getFreq3500b6000(temp) * 0.96 );
            setFreq6000b10000(tempAdd, getFreq6000b10000(temp) * 0.96);
            setFreq10000b20000(tempAdd, getFreq10000b20000(temp) * 0.96);
        }
        // linke Seite
        // Wenn du kein Seitenteil bist oder zur Linken seite gehörst
        else if( (getSideOfWave(node) == 1) || (getSideOfWave(node) == 0))
        {
        	tempAdd = createItem(x--,y--,0);// neues Teilchen der linken Seite
            setSideOfWave(tempAdd,1);

            setFreq20b40(tempAdd, getFreq20b40(temp) * 0.96);
            setFreq40b100(tempAdd, getFreq40b100(temp) * 0.96 );
            setFreq100b150(tempAdd, getFreq100b150(temp) * 0.96);
            setFreq150b400(tempAdd, getFreq150b400(temp) * 0.96);
            setFreq400b1000(tempAdd, getFreq400b1000(temp) * 0.96);
            setFreq1000b2000(tempAdd, getFreq1000b2000(temp) * 0.96);
            setFreq2000b3500(tempAdd, getFreq2000b3500(temp) * 0.96);
            setFreq3500b6000(tempAdd, getFreq3500b6000(temp) * 0.96 );
            setFreq6000b10000(tempAdd, getFreq6000b10000(temp) * 0.96);
            setFreq10000b20000(tempAdd, getFreq10000b20000(temp) * 0.96);
        }
    }
    else if( getDirectionID(node) == 2){
        // Nach oben rechts
        // rechte Seite der Welle für neue ID
            if( (getSideOfWave(node) == 2) || (getSideOfWave(node) == 0))
        {
        	tempAdd = createItem(x,y--,0); // Neues Teilchen der rechten Seite
            setSideOfWave(tempAdd,2);

            setFreq20b40(tempAdd, getFreq20b40(temp) * 0.96);
            setFreq40b100(tempAdd, getFreq40b100(temp) * 0.96 );
            setFreq100b150(tempAdd, getFreq100b150(temp) * 0.96);
            setFreq150b400(tempAdd, getFreq150b400(temp) * 0.96);
            setFreq400b1000(tempAdd, getFreq400b1000(temp) * 0.96);
            setFreq1000b2000(tempAdd, getFreq1000b2000(temp) * 0.96);
            setFreq2000b3500(tempAdd, getFreq2000b3500(temp) * 0.96);
            setFreq3500b6000(tempAdd, getFreq3500b6000(temp) * 0.96 );
            setFreq6000b10000(tempAdd, getFreq6000b10000(temp) * 0.96);
            setFreq10000b20000(tempAdd, getFreq10000b20000(temp) * 0.96);
        }
        // linke Seite
        else if( (getSideOfWave(node) == 1) || (getSideOfWave(node) == 0))
        {
        	tempAdd = createItem(x--,y,0);// neues Teilchen der linken Seite
            setSideOfWave(tempAdd,1);

            setFreq20b40(tempAdd, getFreq20b40(temp) * 0.96);
            setFreq40b100(tempAdd, getFreq40b100(temp) * 0.96 );
            setFreq100b150(tempAdd, getFreq100b150(temp) * 0.96);
            setFreq150b400(tempAdd, getFreq150b400(temp) * 0.96);
            setFreq400b1000(tempAdd, getFreq400b1000(temp) * 0.96);
            setFreq1000b2000(tempAdd, getFreq1000b2000(temp) * 0.96);
            setFreq2000b3500(tempAdd, getFreq2000b3500(temp) * 0.96);
            setFreq3500b6000(tempAdd, getFreq3500b6000(temp) * 0.96 );
            setFreq6000b10000(tempAdd, getFreq6000b10000(temp) * 0.96);
            setFreq10000b20000(tempAdd, getFreq10000b20000(temp) * 0.96);
        }
    
    }
    else if( getDirectionID(node) == 4){
        // unten rechts
        // rechte Seite der Welle für neue ID
        if( (getSideOfWave(node) == 2) || (getSideOfWave(node) == 0))
        {
        	tempAdd = createItem(x--,y,0); // Neues Teilchen der rechten Seite
            setSideOfWave(tempAdd,2);

            setFreq20b40(tempAdd, getFreq20b40(temp) * 0.96);
            setFreq40b100(tempAdd, getFreq40b100(temp) * 0.96 );
            setFreq100b150(tempAdd, getFreq100b150(temp) * 0.96);
            setFreq150b400(tempAdd, getFreq150b400(temp) * 0.96);
            setFreq400b1000(tempAdd, getFreq400b1000(temp) * 0.96);
            setFreq1000b2000(tempAdd, getFreq1000b2000(temp) * 0.96);
            setFreq2000b3500(tempAdd, getFreq2000b3500(temp) * 0.96);
            setFreq3500b6000(tempAdd, getFreq3500b6000(temp) * 0.96 );
            setFreq6000b10000(tempAdd, getFreq6000b10000(temp) * 0.96);
            setFreq10000b20000(tempAdd, getFreq10000b20000(temp) * 0.96);
        }
        // linke Seite
        else if( (getSideOfWave(node) == 1) || (getSideOfWave(node) == 0))
        {
        	tempAdd = createItem(x,y++,0);// neues Teilchen der linken Seite
            setSideOfWave(tempAdd,1);

            setFreq20b40(tempAdd, getFreq20b40(temp) * 0.96);
            setFreq40b100(tempAdd, getFreq40b100(temp) * 0.96 );
            setFreq100b150(tempAdd, getFreq100b150(temp) * 0.96);
            setFreq150b400(tempAdd, getFreq150b400(temp) * 0.96);
            setFreq400b1000(tempAdd, getFreq400b1000(temp) * 0.96);
            setFreq1000b2000(tempAdd, getFreq1000b2000(temp) * 0.96);
            setFreq2000b3500(tempAdd, getFreq2000b3500(temp) * 0.96);
            setFreq3500b6000(tempAdd, getFreq3500b6000(temp) * 0.96 );
            setFreq6000b10000(tempAdd, getFreq6000b10000(temp) * 0.96);
            setFreq10000b20000(tempAdd, getFreq10000b20000(temp) * 0.96);
        }
    }
    
    else if( getDirectionID(node) == 3){
        // Nach Rechts
        // rechte Seite der Welle für neue ID
        if( (getSideOfWave(node) == 2) || (getSideOfWave(node) == 0))
        {
        	tempAdd = createItem(x--,y--,0); // Neues Teilchen der rechten Seite
            setSideOfWave(tempAdd,2);

            setFreq20b40(tempAdd, getFreq20b40(temp) * 0.96);
            setFreq40b100(tempAdd, getFreq40b100(temp) * 0.96 );
            setFreq100b150(tempAdd, getFreq100b150(temp) * 0.96);
            setFreq150b400(tempAdd, getFreq150b400(temp) * 0.96);
            setFreq400b1000(tempAdd, getFreq400b1000(temp) * 0.96);
            setFreq1000b2000(tempAdd, getFreq1000b2000(temp) * 0.96);
            setFreq2000b3500(tempAdd, getFreq2000b3500(temp) * 0.96);
            setFreq3500b6000(tempAdd, getFreq3500b6000(temp) * 0.96 );
            setFreq6000b10000(tempAdd, getFreq6000b10000(temp) * 0.96);
            setFreq10000b20000(tempAdd, getFreq10000b20000(temp) * 0.96);
        }
        // linke Seite
        else if( (getSideOfWave(node) == 1) || (getSideOfWave(node) == 0))
        {
        	tempAdd = createItem(x--,y++,0);// neues Teilchen der linken Seite
            setSideOfWave(tempAdd,1);

            setFreq20b40(tempAdd, getFreq20b40(temp) * 0.96);
            setFreq40b100(tempAdd, getFreq40b100(temp) * 0.96 );
            setFreq100b150(tempAdd, getFreq100b150(temp) * 0.96);
            setFreq150b400(tempAdd, getFreq150b400(temp) * 0.96);
            setFreq400b1000(tempAdd, getFreq400b1000(temp) * 0.96);
            setFreq1000b2000(tempAdd, getFreq1000b2000(temp) * 0.96);
            setFreq2000b3500(tempAdd, getFreq2000b3500(temp) * 0.96);
            setFreq3500b6000(tempAdd, getFreq3500b6000(temp) * 0.96 );
            setFreq6000b10000(tempAdd, getFreq6000b10000(temp) * 0.96);
            setFreq10000b20000(tempAdd, getFreq10000b20000(temp) * 0.96);
        }
    }
        else if( getDirectionID(node) == 5){
            //unten
            // rechte Seite der Welle für neue ID
            if( (getSideOfWave(node) == 2) || (getSideOfWave(node) == 0))
            {
            	tempAdd = createItem(x--,y++,0); // Neues Teilchen der rechten Seite
                setSideOfWave(tempAdd,2);

                setFreq20b40(tempAdd, getFreq20b40(temp) * 0.96);
                setFreq40b100(tempAdd, getFreq40b100(temp) * 0.96 );
                setFreq100b150(tempAdd, getFreq100b150(temp) * 0.96);
                setFreq150b400(tempAdd, getFreq150b400(temp) * 0.96);
                setFreq400b1000(tempAdd, getFreq400b1000(temp) * 0.96);
                setFreq1000b2000(tempAdd, getFreq1000b2000(temp) * 0.96);
                setFreq2000b3500(tempAdd, getFreq2000b3500(temp) * 0.96);
                setFreq3500b6000(tempAdd, getFreq3500b6000(temp) * 0.96 );
                setFreq6000b10000(tempAdd, getFreq6000b10000(temp) * 0.96);
                setFreq10000b20000(tempAdd, getFreq10000b20000(temp) * 0.96);
            }
            // linke Seite
            else if( (getSideOfWave(node) == 1) || (getSideOfWave(node) == 0))
            {
            	tempAdd = createItem(x++,y--,0);// neues Teilchen der linken Seite
                setSideOfWave(tempAdd,1);

                setFreq20b40(tempAdd, getFreq20b40(temp) * 0.96);
                setFreq40b100(tempAdd, getFreq40b100(temp) * 0.96 );
                setFreq100b150(tempAdd, getFreq100b150(temp) * 0.96);
                setFreq150b400(tempAdd, getFreq150b400(temp) * 0.96);
                setFreq400b1000(tempAdd, getFreq400b1000(temp) * 0.96);
                setFreq1000b2000(tempAdd, getFreq1000b2000(temp) * 0.96);
                setFreq2000b3500(tempAdd, getFreq2000b3500(temp) * 0.96);
                setFreq3500b6000(tempAdd, getFreq3500b6000(temp) * 0.96 );
                setFreq6000b10000(tempAdd, getFreq6000b10000(temp) * 0.96);
                setFreq10000b20000(tempAdd, getFreq10000b20000(temp) * 0.96);
            }
        }
        
        else if( getDirectionID(node) == 6){
            //unten links
            // rechte Seite der Welle für neue ID
            if( (getSideOfWave(node) == 2) || (getSideOfWave(node) == 0))
            {
            	tempAdd = createItem(x,y++,0); // Neues Teilchen der rechten Seite
                setSideOfWave(tempAdd,2);

                setFreq20b40(tempAdd, getFreq20b40(temp) * 0.96);
                setFreq40b100(tempAdd, getFreq40b100(temp) * 0.96 );
                setFreq100b150(tempAdd, getFreq100b150(temp) * 0.96);
                setFreq150b400(tempAdd, getFreq150b400(temp) * 0.96);
                setFreq400b1000(tempAdd, getFreq400b1000(temp) * 0.96);
                setFreq1000b2000(tempAdd, getFreq1000b2000(temp) * 0.96);
                setFreq2000b3500(tempAdd, getFreq2000b3500(temp) * 0.96);
                setFreq3500b6000(tempAdd, getFreq3500b6000(temp) * 0.96 );
                setFreq6000b10000(tempAdd, getFreq6000b10000(temp) * 0.96);
                setFreq10000b20000(tempAdd, getFreq10000b20000(temp) * 0.96);
            }
            // linke Seite
            else if( (getSideOfWave(node) == 1) || (getSideOfWave(node) == 0))
            {
            	tempAdd = createItem(x++,y,0);// neues Teilchen der linken Seite
                setSideOfWave(tempAdd,1);

                setFreq20b40(tempAdd, getFreq20b40(temp) * 0.96);
                setFreq40b100(tempAdd, getFreq40b100(temp) * 0.96 );
                setFreq100b150(tempAdd, getFreq100b150(temp) * 0.96);
                setFreq150b400(tempAdd, getFreq150b400(temp) * 0.96);
                setFreq400b1000(tempAdd, getFreq400b1000(temp) * 0.96);
                setFreq1000b2000(tempAdd, getFreq1000b2000(temp) * 0.96);
                setFreq2000b3500(tempAdd, getFreq2000b3500(temp) * 0.96);
                setFreq3500b6000(tempAdd, getFreq3500b6000(temp) * 0.96 );
                setFreq6000b10000(tempAdd, getFreq6000b10000(temp) * 0.96);
                setFreq10000b20000(tempAdd, getFreq10000b20000(temp) * 0.96);
            }
        }
        else if( getDirectionID(node) == 7){
            // links
            // rechte Seite der Welle für neue ID
            if( (getSideOfWave(node) == 2) || (getSideOfWave(node) == 0))
            {
            	tempAdd = createItem(x--,y++,0); // Neues Teilchen der rechten Seite
                setSideOfWave(tempAdd,2);

                setFreq20b40(tempAdd, getFreq20b40(temp) * 0.96);
                setFreq40b100(tempAdd, getFreq40b100(temp) * 0.96 );
                setFreq100b150(tempAdd, getFreq100b150(temp) * 0.96);
                setFreq150b400(tempAdd, getFreq150b400(temp) * 0.96);
                setFreq400b1000(tempAdd, getFreq400b1000(temp) * 0.96);
                setFreq1000b2000(tempAdd, getFreq1000b2000(temp) * 0.96);
                setFreq2000b3500(tempAdd, getFreq2000b3500(temp) * 0.96);
                setFreq3500b6000(tempAdd, getFreq3500b6000(temp) * 0.96 );
                setFreq6000b10000(tempAdd, getFreq6000b10000(temp) * 0.96);
                setFreq10000b20000(tempAdd, getFreq10000b20000(temp) * 0.96);
            }
            // linke Seite
            else if( (getSideOfWave(node) == 1) || (getSideOfWave(node) == 0))
            {
            	tempAdd = createItem(x++,y,0);// neues Teilchen der linken Seite
                setSideOfWave(tempAdd,1);

                setFreq20b40(tempAdd, getFreq20b40(temp) * 0.96);
                setFreq40b100(tempAdd, getFreq40b100(temp) * 0.96 );
                setFreq100b150(tempAdd, getFreq100b150(temp) * 0.96);
                setFreq150b400(tempAdd, getFreq150b400(temp) * 0.96);
                setFreq400b1000(tempAdd, getFreq400b1000(temp) * 0.96);
                setFreq1000b2000(tempAdd, getFreq1000b2000(temp) * 0.96);
                setFreq2000b3500(tempAdd, getFreq2000b3500(temp) * 0.96);
                setFreq3500b6000(tempAdd, getFreq3500b6000(temp) * 0.96 );
                setFreq6000b10000(tempAdd, getFreq6000b10000(temp) * 0.96);
                setFreq10000b20000(tempAdd, getFreq10000b20000(temp) * 0.96);
            }
        }
        else if( getDirectionID(node) == 8){
            //oben links
            // rechte Seite der Welle für neue ID
            if( (getSideOfWave(node) == 2) || (getSideOfWave(node) == 0))
            {
            	tempAdd = createItem(x++,y,0); // Neues Teilchen der rechten Seite
                setSideOfWave(tempAdd,2);

                setFreq20b40(tempAdd, getFreq20b40(temp) * 0.96);
                setFreq40b100(tempAdd, getFreq40b100(temp) * 0.96 );
                setFreq100b150(tempAdd, getFreq100b150(temp) * 0.96);
                setFreq150b400(tempAdd, getFreq150b400(temp) * 0.96);
                setFreq400b1000(tempAdd, getFreq400b1000(temp) * 0.96);
                setFreq1000b2000(tempAdd, getFreq1000b2000(temp) * 0.96);
                setFreq2000b3500(tempAdd, getFreq2000b3500(temp) * 0.96);
                setFreq3500b6000(tempAdd, getFreq3500b6000(temp) * 0.96 );
                setFreq6000b10000(tempAdd, getFreq6000b10000(temp) * 0.96);
                setFreq10000b20000(tempAdd, getFreq10000b20000(temp) * 0.96);
            }
            // linke Seite
            else if( (getSideOfWave(node) == 1) || (getSideOfWave(node) == 0))
            {
            	tempAdd = createItem(x,y--,0);// neues Teilchen der linken Seite
                setSideOfWave(tempAdd,1);

                setFreq20b40(tempAdd, getFreq20b40(temp) * 0.96);
                setFreq40b100(tempAdd, getFreq40b100(temp) * 0.96 );
                setFreq100b150(tempAdd, getFreq100b150(temp) * 0.96);
                setFreq150b400(tempAdd, getFreq150b400(temp) * 0.96);
                setFreq400b1000(tempAdd, getFreq400b1000(temp) * 0.96);
                setFreq1000b2000(tempAdd, getFreq1000b2000(temp) * 0.96);
                setFreq2000b3500(tempAdd, getFreq2000b3500(temp) * 0.96);
                setFreq3500b6000(tempAdd, getFreq3500b6000(temp) * 0.96 );
                setFreq6000b10000(tempAdd, getFreq6000b10000(temp) * 0.96);
                setFreq10000b20000(tempAdd, getFreq10000b20000(temp) * 0.96);
            }
        }
    }
    temp = temp->next;
}
}
