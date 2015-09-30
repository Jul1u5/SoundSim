#include <stdio.h>
#include <stdlib.h>
#include "main.c"

int main (int argc, char *argv[])
{

}


// Seite der "Welle" 0 = nicht von betroffen , 1 == Links , 2 = Rechts
void setSideOfWave(int x, int y, int side)
 {
 if(getItemID(x,y)==0){
 room[x][y].data.Sound.sideofwave = side;
 }
 }
 int getSideOfWave(int x, int y)
 {
 if(getItemID(x,y)==0){
 return room[x][y].data.Sound.sideofwave;
 }
 }
 
void changeSideOfWave(int x, int y)
{
 if(getSideOfWave(x,y) == 1)
 // der Rebound der Teilchen muss auch die Seitenzugehörigkeit ändern.
 {
     setSideOfWave(x,y) = 2;
 }
else if(getSideOfWave(j,k) == 2){
    setSideOfWave(x,y) = 1;
 }
else{
     setSideofWave(x,y) = 0;
 }
}
    
void addWave()
/*
 addwave lässt die Welle bis zu einer bestimmten Verschiebungsweite ungekrümmt, danach werden die resultierenden
 Teilchen "Kugelfunktionsartig" erzeugt und haben eine zugehörgkeit zur rechten oder linken Seite.
 */
{
//////////////////////
    if((getMovement(x,y) < (x_format * 0.05)) || (getMovement(x,y) < (y_format * 0.5))
        // Wenn das Hauptteilchen noch nicht weit genug gewandert ist, bleibt die Welle ungekrümmt.
        // Teichen erzeugt 2 Nahcbarn die die Wellenausbreitung Linear darstellen.
    {
        if(getDirectionID(x,y) == 1)
        // oben
            if( (getSideOfWave(x,y) == 2) || (getSideOfWave(x,y) == 0))
            {
                setItemID(x++,y, 0) // Neues Teilchen der rechten Seite
                setSideOfWave(x++,y,2)// der Zelle wird eine Zugehörigkeit zur Rechtenseite = 2
                            }
        // linke Seite
        // Wenn du kein Seitenteil bist oder zur Linken seite gehörst
            else if( (getSideOfWave(x,y) == 1) || (getSideOfWave(x,y) == 0))
            {
                setItemID(x--,y, 0) // neues Teilchen der linken Seite
                setSideOfWave(x--,y,1)
                setFreq20b40(x--,y, getFreq20b40(x,y) * 0.96);
                setFreq40b100(x--,y, getFreq40b100(x,y) * 0.96 );
                setFreq100b150(x--,y, getFreq100b150(x,y) * 0.96);
                setFreq150b400(x--,y, getFreq150b400(x,y) * 0.96);
                setFreq400b1000(x--,y, getFreq400b1000(x,y) * 0.96);
                setFreq1000b2000(x--,y, getFreq1000b2000(x,y) * 0.96);
                setFreq2000b3500(x--,y, getFreq2000b3500(x,y) * 0.96);
                setFreq3500b6000(x--,y, getFreq3500b6000(x,y) * 0.96 );
                setFreq6000b10000(x--,y, getFreq6000b10000(x,y) * 0.96);
                setFreq10000b20000(x--,y, getFreq10000b20000(x,y) * 0.96);
            }
        
        else if( getDirectionID(x,y) == 2){
                // Nach oben rechts
                // rechte Seite der Welle für neue ID
                if( (getSideOfWave(x,y) == 2) || (getSideOfWave(x,y) == 0))
                {
                    setItemID(x++,y--, 0)
                    setSideOfWave(x++,y--,2)
                    setFreq20b40(x++,y--, getFreq20b40(x,y) * 0.96);
                    setFreq40b100(x++,y--, getFreq40b100(x,y) * 0.96 );
                    setFreq100b150(x++,y--, getFreq100b150(x,y) * 0.96);
                    setFreq150b400(x++,y--, getFreq150b400(x,y) * 0.96);
                    setFreq400b1000(x++,y--, getFreq400b1000(x,y) * 0.96);
                    setFreq1000b2000(x++,y--, getFreq1000b2000(x,y) * 0.96);
                    setFreq2000b3500(x++,y--, getFreq2000b3500(x,y) * 0.96);
                    setFreq3500b6000(x++,y--, getFreq3500b6000(x,y) * 0.96 );
                    setFreq6000b10000(x++,y--, getFreq6000b10000(x,y) * 0.96);
                    setFreq10000b20000(x++,y--, getFreq10000b20000(x,y) * 0.96);
                }
                // linke Seite
                else if( (getSideOfWave(x,y) == 1) || (getSideOfWave(x,y) == 0))
                {
                    setItemID(x--,y, 0)
                    setSideOfWave(x--,y,1)
                    setFreq20b40(x--,y, getFreq20b40(x,y) * 0.96);
                    setFreq40b100(x--,y, getFreq40b100(x,y) * 0.96 );
                    setFreq100b150(x--,y, getFreq100b150(x,y) * 0.96);
                    setFreq150b400(x--,y, getFreq150b400(x,y) * 0.96);
                    setFreq400b1000(x--,y, getFreq400b1000(x,y) * 0.96);
                    setFreq1000b2000(x--,y, getFreq1000b2000(x,y) * 0.96);
                    setFreq2000b3500(x--,y, getFreq2000b3500(x,y) * 0.96);
                    setFreq3500b6000(x--,y, getFreq3500b6000(x,y) * 0.96 );
                    setFreq6000b10000(x--,y, getFreq6000b10000(x,y) * 0.96);
                    setFreq10000b20000(x--,y, getFreq10000b20000(x,y) * 0.96);
                }
                
            }
        else if( getDirectionID(x,y) == 3){
            // Nach Rechts
            // rechte Seite der Welle für neue ID
            if( (getSideOfWave(x,y) == 2) || (getSideOfWave(x,y) == 0))
            {
                setSideOfWave(x,y--,2)
                setItemID(x,y--, 0)
                setFreq20b40(x,y--, getFreq20b40(x,y) * 0.96);
                setFreq40b100(x,y--, getFreq40b100(x,y) * 0.96 );
                setFreq100b150(x,y--, getFreq100b150(x,y) * 0.96);
                setFreq150b400(x,y--, getFreq150b400(x,y) * 0.96);
                setFreq400b1000(x,y--, getFreq400b1000(x,y) * 0.96);
                setFreq1000b2000(x,y--, getFreq1000b2000(x,y) * 0.96);
                setFreq2000b3500(x,y--, getFreq2000b3500(x,y) * 0.96);
                setFreq3500b6000(x,y--, getFreq3500b6000(x,y) * 0.96 );
                setFreq6000b10000(x,y--, getFreq6000b10000(x,y) * 0.96);
                setFreq10000b20000(x,y--, getFreq10000b20000(x,y) * 0.96);
            }
            // linke Seite
            else if( (getSideOfWave(x,y) == 1) || (getSideOfWave(x,y) == 0))
            {
                setSideOfWave(x,y++,1)
                setItemID(x,y++, 0)
                setFreq20b40(x,y++, getFreq20b40(x,y) * 0.96);
                setFreq40b100(x,y++, getFreq40b100(x,y) * 0.96 );
                setFreq100b150(x,y++, getFreq100b150(x,y) * 0.96);
                setFreq150b400(x,y++, getFreq150b400(x,y) * 0.96);
                setFreq400b1000(x,y++, getFreq400b1000(x,y) * 0.96);
                setFreq1000b2000(x,y++, getFreq1000b2000(x,y) * 0.96);
                setFreq2000b3500(x,y++, getFreq2000b3500(x,y) * 0.96);
                setFreq3500b6000(x,y++, getFreq3500b6000(x,y) * 0.96 );
                setFreq6000b10000(x,y++, getFreq6000b10000(x,y) * 0.96);
                setFreq10000b20000(x,y++, getFreq10000b20000(x,y) * 0.96);
            }
        }
        else if( getDirectionID(x,y == 4){
            // unten rechts
            // rechte Seite der Welle für neue ID
            if( (getSideOfWave(x,y) == 2) || (getSideOfWave(x,y) == 0))
            {
                setItemID(x--,y--, 0)
                setSideOfWave(x--,y--,2)
                setFreq20b40(x--,y--, getFreq20b40(x,y) * 0.96);
                setFreq40b100(x--,y--, getFreq40b100(x,y) * 0.96 );
                setFreq100b150(x--,y--, getFreq100b150(x,y) * 0.96);
                setFreq150b400(x--,y--, getFreq150b400(x,y) * 0.96);
                setFreq400b1000(x--,y--, getFreq400b1000(x,y) * 0.96);
                setFreq1000b2000(x--,y--, getFreq1000b2000(x,y) * 0.96);
                setFreq2000b3500(x--,y--, getFreq2000b3500(x,y) * 0.96);
                setFreq3500b6000(x--,y--, getFreq3500b6000(x,y) * 0.96 );
                setFreq6000b10000(x--,y--, getFreq6000b10000(x,y) * 0.96);
                setFreq10000b20000(x--,y--, getFreq10000b20000(x,y) * 0.96);
            }
            // linke Seite
            else if( (getSideOfWave(x,y) == 1) || (getSideOfWave(x,y) == 0))
            {
                setSideOfWave(x++,y++,1)
                setItemID(x++,y++, 0)
                setFreq20b40(x++,y++, getFreq20b40(x,y) * 0.96);
                setFreq40b100(x++,y++, getFreq40b100(x,y) * 0.96 );
                setFreq100b150(x++,y++, getFreq100b150(x,y) * 0.96);
                setFreq150b400(x++,y++, getFreq150b400(x,y) * 0.96);
                setFreq400b1000(x++,y++, getFreq400b1000(x,y) * 0.96);
                setFreq1000b2000(x++,y++, getFreq1000b2000(x,y) * 0.96);
                setFreq2000b3500(x++,y++, getFreq2000b3500(x,y) * 0.96);
                setFreq3500b6000(x++,y++, getFreq3500b6000(x,y) * 0.96 );
                setFreq6000b10000(x++,y++, getFreq6000b10000(x,y) * 0.96);
                setFreq10000b20000(x++,y++, getFreq10000b20000(x,y) * 0.96);
            }
        }
        
        else if( getDirectionID(x,y) == 5){
            //unten
            // rechte Seite der Welle für neue ID
            if( (getSideOfWave(x,y) == 2) || (getSideOfWave(x,y) == 0))
            {
                setSideOfWave(x--,y,2)
                setItemID(x--,y, 0)
                setFreq20b40(x--,y, getFreq20b40(x,y) * 0.96);
                setFreq40b100(x--,y, getFreq40b100(x,y) * 0.96 );
                setFreq100b150(x--,y, getFreq100b150(x,y) * 0.96);
                setFreq150b400(x--,y, getFreq150b400(x,y) * 0.96);
                setFreq400b1000(x--,y, getFreq400b1000(x,y) * 0.96);
                setFreq1000b2000(x--,y, getFreq1000b2000(x,y) * 0.96);
                setFreq2000b3500(x--,y, getFreq2000b3500(x,y) * 0.96);
                setFreq3500b6000(x--,y, getFreq3500b6000(x,y) * 0.96 );
                setFreq6000b10000(x--,y, getFreq6000b10000(x,y) * 0.96);
                setFreq10000b20000(x--,y, getFreq10000b20000(x,y) * 0.96);
            }
            // linke Seite
            else if( (getSideOfWave(x,y) == 1) || (getSideOfWave(x,y) == 0))
            {
                setSideOfWave(x++,y,1)
                setItemID(x++,y, 0)
                setFreq20b40(x++,y, getFreq20b40(x,y) * 0.96);
                setFreq40b100(x++,y, getFreq40b100(x,y) * 0.96 );
                setFreq100b150(x++,y, getFreq100b150(x,y) * 0.96);
                setFreq150b400(x++,y, getFreq150b400(x,y) * 0.96);
                setFreq400b1000(x++,y, getFreq400b1000(x,y) * 0.96);
                setFreq1000b2000(x++,y, getFreq1000b2000(x,y) * 0.96);
                setFreq2000b3500(x++,y, getFreq2000b3500(x,y) * 0.96);
                setFreq3500b6000(x++,y, getFreq3500b6000(x,y) * 0.96 );
                setFreq6000b10000(x++,y, getFreq6000b10000(x,y) * 0.96);
                setFreq10000b20000(x++,y, getFreq10000b20000(x,y) * 0.96);
            }
        }
        else if( getDirectionID(x,y) == 6){
            //unten links
            // rechte Seite der Welle für neue ID
            if( (getSideOfWave(x,y) == 2) || (getSideOfWave(x,y) == 0))
            {
                setSideOfWave(x--,y++,2)
                setItemID(x--,y++, 0)
                setFreq20b40(x--,y++, getFreq20b40(x,y) * 0.96);
                setFreq40b100(x--,y++, getFreq40b100(x,y) * 0.96 );
                setFreq100b150(x--,y++, getFreq100b150(x,y) * 0.96);
                setFreq150b400(x--,y++, getFreq150b400(x,y) * 0.96);
                setFreq400b1000(x--,y++, getFreq400b1000(x,y) * 0.96);
                setFreq1000b2000(x--,y++, getFreq1000b2000(x,y) * 0.96);
                setFreq2000b3500(x--,y++, getFreq2000b3500(x,y) * 0.96);
                setFreq3500b6000(x--,y++, getFreq3500b6000(x,y) * 0.96 );
                setFreq6000b10000(x--,y++, getFreq6000b10000(x,y) * 0.96);
                setFreq10000b20000(x--,y++, getFreq10000b20000(x,y) * 0.96);
            }
            // linke Seite
            else if( (getSideOfWave(x,y) == 1) || (getSideOfWave(x,y) == 0))
            {
                setSideOfWave(x++,y--,1)
                setItemID(x++,y--, 0)
                setFreq20b40(x++,y--, getFreq20b40(x,y) * 0.96);
                setFreq40b100(x++,y--, getFreq40b100(x,y) * 0.96 );
                setFreq100b150(x++,y--, getFreq100b150(x,y) * 0.96);
                setFreq150b400(x++,y--, getFreq150b400(x,y) * 0.96);
                setFreq400b1000(x++,y--, getFreq400b1000(x,y) * 0.96);
                setFreq1000b2000(x++,y--, getFreq1000b2000(x,y) * 0.96);
                setFreq2000b3500(x++,y--, getFreq2000b3500(x,y) * 0.96);
                setFreq3500b6000(x++,y--, getFreq3500b6000(x,y) * 0.96 );
                setFreq6000b10000(x++,y--, getFreq6000b10000(x,y) * 0.96);
                setFreq10000b20000(x++,y--, getFreq10000b20000(x,y) * 0.96);
            }
        }
        else if( getDirectionID(x,y) == 7){
            // links
            // rechte Seite der Welle für neue ID
            if( (getSideOfWave(x,y) == 2) || (getSideOfWave(x,y) == 0))
            {
                setSideOfWave(x,y++,2)
                setItemID(x,y++, 0)
                setFreq20b40(x,y++, getFreq20b40(x,y) * 0.96);
                setFreq40b100(x,y++, getFreq40b100(x,y) * 0.96 );
                setFreq100b150(x,y++, getFreq100b150(x,y) * 0.96);
                setFreq150b400(x,y++, getFreq150b400(x,y) * 0.96);
                setFreq400b1000(x,y++, getFreq400b1000(x,y) * 0.96);
                setFreq1000b2000(x,y++, getFreq1000b2000(x,y) * 0.96);
                setFreq2000b3500(x,y++, getFreq2000b3500(x,y) * 0.96);
                setFreq3500b6000(x,y++, getFreq3500b6000(x,y) * 0.96 );
                setFreq6000b10000(x,y++, getFreq6000b10000(x,y) * 0.96);
                setFreq10000b20000(x,y++, getFreq10000b20000(x,y) * 0.96);
            }
            // linke Seite
            else if( (getSideOfWave(x,y) == 1) || (getSideOfWave(x,y) == 0))
            {
                setSideOfWave(x,y--,1)
                setItemID(x,y--, 0)
                setFreq20b40(x,y--, getFreq20b40(x,y) * 0.96);
                setFreq40b100(x,y--, getFreq40b100(x,y) * 0.96 );
                setFreq100b150(x,y--, getFreq100b150(x,y) * 0.96);
                setFreq150b400(x,y--, getFreq150b400(x,y) * 0.96);
                setFreq400b1000(x,y--, getFreq400b1000(x,y) * 0.96);
                setFreq1000b2000(x,y--, getFreq1000b2000(x,y) * 0.96);
                setFreq2000b3500(x,y--, getFreq2000b3500(x,y) * 0.96);
                setFreq3500b6000(x,y--, getFreq3500b6000(x,y) * 0.96 );
                setFreq6000b10000(x,y--, getFreq6000b10000(x,y) * 0.96);
                setFreq10000b20000(x,y--, getFreq10000b20000(x,y) * 0.96);
            }
        }
        else if( getDirectionID(x,y) == 8){
            //oben links
            // rechte Seite der Welle für neue ID
            if( (getSideOfWave(x,y) == 2) || (getSideOfWave(x,y) == 0))
            {
                setSideOfWave(x++,y--,2)
                setItemID(x++,y--, 0)
                setFreq20b40(x++,y--, getFreq20b40(x,y) * 0.96);
                setFreq40b100(x++,y--, getFreq40b100(x,y) * 0.96 );
                setFreq100b150(x++,y--, getFreq100b150(x,y) * 0.96);
                setFreq150b400(x++,y--, getFreq150b400(x,y) * 0.96);
                setFreq400b1000(x++,y--, getFreq400b1000(x,y) * 0.96);
                setFreq1000b2000(x++,y--, getFreq1000b2000(x,y) * 0.96);
                setFreq2000b3500(x++,y--, getFreq2000b3500(x,y) * 0.96);
                setFreq3500b6000(x++,y--, getFreq3500b6000(x,y) * 0.96 );
                setFreq6000b10000(x++,y--, getFreq6000b10000(x,y) * 0.96);
                setFreq10000b20000(x++,y--, getFreq10000b20000(x,y) * 0.96);
            }
            // linke Seite
            else if( (getSideOfWave(x,y) == 1) || (getSideOfWave(x,y) == 0))
            {
                setSideOfWave(x--,y++,1)
                setItemID(x--,y++, 0)
                setFreq20b40(x--,y++, getFreq20b40(x,y) * 0.96);
                setFreq40b100(x--,y++, getFreq40b100(x,y) * 0.96 );
                setFreq100b150(x--,y++, getFreq100b150(x,y) * 0.96);
                setFreq150b400(x--,y++, getFreq150b400(x,y) * 0.96);
                setFreq400b1000(x--,y++, getFreq400b1000(x,y) * 0.96);
                setFreq1000b2000(x--,y++, getFreq1000b2000(x,y) * 0.96);
                setFreq2000b3500(x--,y++, getFreq2000b3500(x,y) * 0.96);
                setFreq3500b6000(x--,y++, getFreq3500b6000(x,y) * 0.96 );
                setFreq6000b10000(x--,y++, getFreq6000b10000(x,y) * 0.96);
                setFreq10000b20000(x--,y++, getFreq10000b20000(x,y) * 0.96);
            }
        }

    }else
    {
    // evtl merken ob ein teil zur rechten oder linken seite gehört und dann nur noch einseitig
    // weiter verbreitet - neue variable die das anzeigt !
    
    if( getDirectionID(x,y) == 1){
        // Nach oben
        // rechte Seite der Welle für neue ID
        
        if( (getSideOfWave(x,y) == 2) || (getSideOfWave(x,y) == 0))
        {
        setItemID(x++,y--, 0) // Neues Teilchen der rechten Seite
        setSideOfWave(x++,y--,2)// der Zelle wird eine Zugehörigkeit zur Rechtenseite = 2
        
            setFreq20b40(x++,y--, getFreq20b40(x,y) * 0.96);
            setFreq40b100(x++,y--, getFreq40b100(x,y) * 0.96 );
            setFreq100b150(x++,y--, getFreq100b150(x,y) * 0.96);
            setFreq150b400(x++,y--, getFreq150b400(x,y) * 0.96);
            setFreq400b1000(x++,y--, getFreq400b1000(x,y) * 0.96);
            setFreq1000b2000(x++,y--, getFreq1000b2000(x,y) * 0.96);
            setFreq2000b3500(x++,y--, getFreq2000b3500(x,y) * 0.96);
            setFreq3500b6000(x++,y--, getFreq3500b6000(x,y) * 0.96 );
            setFreq6000b10000(x++,y--, getFreq6000b10000(x,y) * 0.96);
            setFreq10000b20000(x++,y--, getFreq10000b20000(x,y) * 0.96);
        }
        // linke Seite
        // Wenn du kein Seitenteil bist oder zur Linken seite gehörst
        else if( (getSideOfWave(x,y) == 1) || (getSideOfWave(x,y) == 0))
        {
        setItemID(x--,y--, 0) // neues Teilchen der linken Seite
        setSideOfWave(x--,y--,1)
            setFreq20b40(x--,y--, getFreq20b40(x,y) * 0.96);
            setFreq40b100(x--,y--, getFreq40b100(x,y) * 0.96 );
            setFreq100b150(x--,y--, getFreq100b150(x,y) * 0.96);
            setFreq150b400(x--,y--, getFreq150b400(x,y) * 0.96);
            setFreq400b1000(x--,y--, getFreq400b1000(x,y) * 0.96);
            setFreq1000b2000(x--,y--, getFreq1000b2000(x,y) * 0.96);
            setFreq2000b3500(x--,y--, getFreq2000b3500(x,y) * 0.96);
            setFreq3500b6000(x--,y--, getFreq3500b6000(x,y) * 0.96 );
            setFreq6000b10000(x--,y--, getFreq6000b10000(x,y) * 0.96);
            setFreq10000b20000(x--,y--, getFreq10000b20000(x,y) * 0.96);
        }
    }
    else if( getDirectionID(x,y) == 2){
        // Nach oben rechts
        // rechte Seite der Welle für neue ID
            if( (getSideOfWave(x,y) == 2) || (getSideOfWave(x,y) == 0))
        {
        setItemID(x,y--, 0)
        setSideOfWave(x,y--,2)
            setFreq20b40(x,y--, getFreq20b40(x,y) * 0.96);
            setFreq40b100(x,y--, getFreq40b100(x,y) * 0.96 );
            setFreq100b150(x,y--, getFreq100b150(x,y) * 0.96);
            setFreq150b400(x,y--, getFreq150b400(x,y) * 0.96);
            setFreq400b1000(x,y--, getFreq400b1000(x,y) * 0.96);
            setFreq1000b2000(x,y--, getFreq1000b2000(x,y) * 0.96);
            setFreq2000b3500(x,y--, getFreq2000b3500(x,y) * 0.96);
            setFreq3500b6000(x,y--, getFreq3500b6000(x,y) * 0.96 );
            setFreq6000b10000(x,y--, getFreq6000b10000(x,y) * 0.96);
            setFreq10000b20000(x,y--, getFreq10000b20000(x,y) * 0.96);
        }
        // linke Seite
        else if( (getSideOfWave(x,y) == 1) || (getSideOfWave(x,y) == 0))
        {
        setItemID(x--,y, 0)
        setSideOfWave(x--,y,1)
            setFreq20b40(x--,y, getFreq20b40(x,y) * 0.96);
            setFreq40b100(x--,y, getFreq40b100(x,y) * 0.96 );
            setFreq100b150(x--,y, getFreq100b150(x,y) * 0.96);
            setFreq150b400(x--,y, getFreq150b400(x,y) * 0.96);
            setFreq400b1000(x--,y, getFreq400b1000(x,y) * 0.96);
            setFreq1000b2000(x--,y, getFreq1000b2000(x,y) * 0.96);
            setFreq2000b3500(x--,y, getFreq2000b3500(x,y) * 0.96);
            setFreq3500b6000(x--,y, getFreq3500b6000(x,y) * 0.96 );
            setFreq6000b10000(x--,y, getFreq6000b10000(x,y) * 0.96);
            setFreq10000b20000(x--,y, getFreq10000b20000(x,y) * 0.96);
        }
    
    }
    else if( getDirectionID(x,y) == 4){
        // unten rechts
        // rechte Seite der Welle für neue ID
        if( (getSideOfWave(x,y) == 2) || (getSideOfWave(x,y) == 0))
        {
        setItemID(x--,y, 0)
        setSideOfWave(x--,y,2)
            setFreq20b40(x--,y, getFreq20b40(x,y) * 0.96);
            setFreq40b100(x--,y, getFreq40b100(x,y) * 0.96 );
            setFreq100b150(x--,y, getFreq100b150(x,y) * 0.96);
            setFreq150b400(x--,y, getFreq150b400(x,y) * 0.96);
            setFreq400b1000(x--,y, getFreq400b1000(x,y) * 0.96);
            setFreq1000b2000(x--,y, getFreq1000b2000(x,y) * 0.96);
            setFreq2000b3500(x--,y, getFreq2000b3500(x,y) * 0.96);
            setFreq3500b6000(x--,y, getFreq3500b6000(x,y) * 0.96 );
            setFreq6000b10000(x--,y, getFreq6000b10000(x,y) * 0.96);
            setFreq10000b20000(x--,y, getFreq10000b20000(x,y) * 0.96);
        }
        // linke Seite
        else if( (getSideOfWave(x,y) == 1) || (getSideOfWave(x,y) == 0))
        {
        setSideOfWave(x,y++,1)
        setItemID(x,y++, 0)
            setFreq20b40(x,y++, getFreq20b40(x,y) * 0.96);
            setFreq40b100(x,y++, getFreq40b100(x,y) * 0.96 );
            setFreq100b150(x,y++, getFreq100b150(x,y) * 0.96);
            setFreq150b400(x,y++, getFreq150b400(x,y) * 0.96);
            setFreq400b1000(x,y++, getFreq400b1000(x,y) * 0.96);
            setFreq1000b2000(x,y++, getFreq1000b2000(x,y) * 0.96);
            setFreq2000b3500(x,y++, getFreq2000b3500(x,y) * 0.96);
            setFreq3500b6000(x,y++, getFreq3500b6000(x,y) * 0.96 );
            setFreq6000b10000(x,y++, getFreq6000b10000(x,y) * 0.96);
            setFreq10000b20000(x,y++, getFreq10000b20000(x,y) * 0.96);
        }
    }
    
    else if( getDirectionID(x,y) == 3){
        // Nach Rechts
        // rechte Seite der Welle für neue ID
        if( (getSideOfWave(x,y) == 2) || (getSideOfWave(x,y) == 0))
        {
        setSideOfWave(x--,y--,2)
        setItemID(x--,y--, 0)
            setFreq20b40(x--,y--, getFreq20b40(x,y) * 0.96);
            setFreq40b100(x--,y--, getFreq40b100(x,y) * 0.96 );
            setFreq100b150(x--,y--, getFreq100b150(x,y) * 0.96);
            setFreq150b400(x--,y--, getFreq150b400(x,y) * 0.96);
            setFreq400b1000(x--,y--, getFreq400b1000(x,y) * 0.96);
            setFreq1000b2000(x--,y--, getFreq1000b2000(x,y) * 0.96);
            setFreq2000b3500(x--,y--, getFreq2000b3500(x,y) * 0.96);
            setFreq3500b6000(x--,y--, getFreq3500b6000(x,y) * 0.96 );
            setFreq6000b10000(x--,y--, getFreq6000b10000(x,y) * 0.96);
            setFreq10000b20000(x--,y--, getFreq10000b20000(x,y) * 0.96);
        }
        // linke Seite
        else if( (getSideOfWave(x,y) == 1) || (getSideOfWave(x,y) == 0))
        {
        setSideOfWave(x--,y++,1)
        setItemID(x--,y++, 0)
            setFreq20b40(x--,y++, getFreq20b40(x,y) * 0.96);
            setFreq40b100(x--,y++, getFreq40b100(x,y) * 0.96 );
            setFreq100b150(x--,y++, getFreq100b150(x,y) * 0.96);
            setFreq150b400(x--,y++, getFreq150b400(x,y) * 0.96);
            setFreq400b1000(x--,y++, getFreq400b1000(x,y) * 0.96);
            setFreq1000b2000(x--,y++, getFreq1000b2000(x,y) * 0.96);
            setFreq2000b3500(x--,y++, getFreq2000b3500(x,y) * 0.96);
            setFreq3500b6000(x--,y++, getFreq3500b6000(x,y) * 0.96 );
            setFreq6000b10000(x--,y++, getFreq6000b10000(x,y) * 0.96);
            setFreq10000b20000(x--,y++, getFreq10000b20000(x,y) * 0.96);
        }
    }
        else if( getDirectionID(x,y) == 5){
            //unten
            // rechte Seite der Welle für neue ID
            if( (getSideOfWave(x,y) == 2) || (getSideOfWave(x,y) == 0))
            {
            setSideOfWave(x--,y++,2)
            setItemID(x--,y++, 0)
                setFreq20b40(x--,y++, getFreq20b40(x,y) * 0.96);
                setFreq40b100(x--,y++, getFreq40b100(x,y) * 0.96 );
                setFreq100b150(x--,y++, getFreq100b150(x,y) * 0.96);
                setFreq150b400(x--,y++, getFreq150b400(x,y) * 0.96);
                setFreq400b1000(x--,y++, getFreq400b1000(x,y) * 0.96);
                setFreq1000b2000(x--,y++, getFreq1000b2000(x,y) * 0.96);
                setFreq2000b3500(x--,y++, getFreq2000b3500(x,y) * 0.96);
                setFreq3500b6000(x--,y++, getFreq3500b6000(x,y) * 0.96 );
                setFreq6000b10000(x--,y++, getFreq6000b10000(x,y) * 0.96);
                setFreq10000b20000(x--,y++, getFreq10000b20000(x,y) * 0.96);
            }
            // linke Seite
            else if( (getSideOfWave(x,y) == 1) || (getSideOfWave(x,y) == 0))
            {
            setSideOfWave(x++,y++,1)
            setItemID(x++,y++, 0)
                setFreq20b40(x++,y--, getFreq20b40(x,y) * 0.96);
                setFreq40b100(x++,y--, getFreq40b100(x,y) * 0.96 );
                setFreq100b150(x++,y--, getFreq100b150(x,y) * 0.96);
                setFreq150b400(x++,y--, getFreq150b400(x,y) * 0.96);
                setFreq400b1000(x++,y--, getFreq400b1000(x,y) * 0.96);
                setFreq1000b2000(x++,y--, getFreq1000b2000(x,y) * 0.96);
                setFreq2000b3500(x++,y--, getFreq2000b3500(x,y) * 0.96);
                setFreq3500b6000(x++,y--, getFreq3500b6000(x,y) * 0.96 );
                setFreq6000b10000(x++,y--, getFreq6000b10000(x,y) * 0.96);
                setFreq10000b20000(x++,y--, getFreq10000b20000(x,y) * 0.96);
            }
        }
        
        else if( getDirectionID(x,y) == 6){
            //unten links
            // rechte Seite der Welle für neue ID
            if( (getSideOfWave(x,y) == 2) || (getSideOfWave(x,y) == 0))
            {
            setSideOfWave(x,y++,2)
            setItemID(x,y++, 0)
                setFreq20b40(x,y++, getFreq20b40(x,y) * 0.96);
                setFreq40b100(x,y++, getFreq40b100(x,y) * 0.96 );
                setFreq100b150(x,y++, getFreq100b150(x,y) * 0.96);
                setFreq150b400(x,y++, getFreq150b400(x,y) * 0.96);
                setFreq400b1000(x,y++, getFreq400b1000(x,y) * 0.96);
                setFreq1000b2000(x,y++, getFreq1000b2000(x,y) * 0.96);
                setFreq2000b3500(x,y++, getFreq2000b3500(x,y) * 0.96);
                setFreq3500b6000(x,y++, getFreq3500b6000(x,y) * 0.96 );
                setFreq6000b10000(x,y++, getFreq6000b10000(x,y) * 0.96);
                setFreq10000b20000(x,y++, getFreq10000b20000(x,y) * 0.96);
            }
            // linke Seite
            else if( (getSideOfWave(x,y) == 1) || (getSideOfWave(x,y) == 0))
            {
            setSideOfWave(x++,y,1)
            setItemID(x++,y, 0)
                setFreq20b40(x++,y, getFreq20b40(x,y) * 0.96);
                setFreq40b100(x++,y, getFreq40b100(x,y) * 0.96 );
                setFreq100b150(x++,y, getFreq100b150(x,y) * 0.96);
                setFreq150b400(x++,y, getFreq150b400(x,y) * 0.96);
                setFreq400b1000(x++,y, getFreq400b1000(x,y) * 0.96);
                setFreq1000b2000(x++,y, getFreq1000b2000(x,y) * 0.96);
                setFreq2000b3500(x++,y, getFreq2000b3500(x,y) * 0.96);
                setFreq3500b6000(x++,y, getFreq3500b6000(x,y) * 0.96 );
                setFreq6000b10000(x++,y, getFreq6000b10000(x,y) * 0.96);
                setFreq10000b20000(x++,y, getFreq10000b20000(x,y) * 0.96);
            }
        }
        else if( getDirectionID(x,y) == 7){
            // links
            // rechte Seite der Welle für neue ID
            if( (getSideOfWave(x,y) == 2) || (getSideOfWave(x,y) == 0))
            {
            setSideOfWave(x--,y++,2)
            setItemID(x--,y++, 0)
                setFreq20b40(x--,y++, getFreq20b40(x,y) * 0.96);
                setFreq40b100(x--,y++, getFreq40b100(x,y) * 0.96 );
                setFreq100b150(x--,y++, getFreq100b150(x,y) * 0.96);
                setFreq150b400(x--,y++, getFreq150b400(x,y) * 0.96);
                setFreq400b1000(x--,y++, getFreq400b1000(x,y) * 0.96);
                setFreq1000b2000(x--,y++, getFreq1000b2000(x,y) * 0.96);
                setFreq2000b3500(x--,y++, getFreq2000b3500(x,y) * 0.96);
                setFreq3500b6000(x--,y++, getFreq3500b6000(x,y) * 0.96 );
                setFreq6000b10000(x--,y++, getFreq6000b10000(x,y) * 0.96);
                setFreq10000b20000(x--,y++, getFreq10000b20000(x,y) * 0.96);
            }
            // linke Seite
            else if( (getSideOfWave(x,y) == 1) || (getSideOfWave(x,y) == 0))
            {
            setSideOfWave(x++,y,1)
            setItemID(x++,y, 0)
                setFreq20b40(x++,y, getFreq20b40(x,y) * 0.96);
                setFreq40b100(x++,y, getFreq40b100(x,y) * 0.96 );
                setFreq100b150(x++,y, getFreq100b150(x,y) * 0.96);
                setFreq150b400(x++,y, getFreq150b400(x,y) * 0.96);
                setFreq400b1000(x++,y, getFreq400b1000(x,y) * 0.96);
                setFreq1000b2000(x++,y, getFreq1000b2000(x,y) * 0.96);
                setFreq2000b3500(x++,y, getFreq2000b3500(x,y) * 0.96);
                setFreq3500b6000(x++,y, getFreq3500b6000(x,y) * 0.96 );
                setFreq6000b10000(x++,y, getFreq6000b10000(x,y) * 0.96);
                setFreq10000b20000(x++,y, getFreq10000b20000(x,y) * 0.96);
            }
        }
        else if( getDirectionID(x,y) == 8){
            //oben links
            // rechte Seite der Welle für neue ID
            if( (getSideOfWave(x,y) == 2) || (getSideOfWave(x,y) == 0))
            {
            setSideOfWave(x++,y,2)
            setItemID(x++,y, 0)
                setFreq20b40(x++,y, getFreq20b40(x,y) * 0.96);
                setFreq40b100(x++,y, getFreq40b100(x,y) * 0.96 );
                setFreq100b150(x++,y, getFreq100b150(x,y) * 0.96);
                setFreq150b400(x++,y, getFreq150b400(x,y) * 0.96);
                setFreq400b1000(x++,y, getFreq400b1000(x,y) * 0.96);
                setFreq1000b2000(x++,y, getFreq1000b2000(x,y) * 0.96);
                setFreq2000b3500(x++,y, getFreq2000b3500(x,y) * 0.96);
                setFreq3500b6000(x++,y, getFreq3500b6000(x,y) * 0.96 );
                setFreq6000b10000(x++,y, getFreq6000b10000(x,y) * 0.96);
                setFreq10000b20000(x++,y, getFreq10000b20000(x,y) * 0.96);
            }
            // linke Seite
            else if( (getSideOfWave(x,y) == 1) || (getSideOfWave(x,y) == 0))
            {
            setSideOfWave(x,y--,1)
            setItemID(x,y--, 0)
                setFreq20b40(x,y--, getFreq20b40(x,y) * 0.96);
                setFreq40b100(x,y--, getFreq40b100(x,y) * 0.96 );
                setFreq100b150(x,y--, getFreq100b150(x,y) * 0.96);
                setFreq150b400(x,y--, getFreq150b400(x,y) * 0.96);
                setFreq400b1000(x,y--, getFreq400b1000(x,y) * 0.96);
                setFreq1000b2000(x,y--, getFreq1000b2000(x,y) * 0.96);
                setFreq2000b3500(x,y--, getFreq2000b3500(x,y) * 0.96);
                setFreq3500b6000(x,y--, getFreq3500b6000(x,y) * 0.96 );
                setFreq6000b10000(x,y--, getFreq6000b10000(x,y) * 0.96);
                setFreq10000b20000(x,y--, getFreq10000b20000(x,y) * 0.96);
            }
        }
}
}