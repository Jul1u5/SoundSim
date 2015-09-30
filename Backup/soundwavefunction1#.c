#include <stdio.h>
#include <stdlib.h>
#include "main.c"

int i,j,x,y = 0;

int main (int argc, char *argv[])
{

}

void addWave()
/*
 i und j sind wie x und y Koordinaten anzusehen. i gibt die spalte an und j die Zeile
 addwave lässt die Welle bis zu einer bestimmten Verschiebungsweite ungekrümmt, danach werden die resultierenden
 Teilchen "Kugelfunktionsartig" erzeugt und haben eine zugehörgkeit zur rechten oder linken Seite.
 */
{
//////////////////////
    if(room.data.Sound.movement < (x_format * 0.05))
        // Wenn das Hauptteilchen noch nicht weit genug gewandert ist, bleibt die Welle ungekrümmt.
        // Teichen erzeugt 2 Nahcbarn die die Wellenausbreitung Linear darstellen.
    {
        if(getDirectionID(i,j) == 1)
        // oben
            if( (room[x][y].data.Sound.sideofwave == 2) || (room[x][y].data.Sound.sideofwave == 0))
            {
                setItemID(i++,j, 0) // Neues Teilchen der rechten Seite
                setSideOfWave(i++,j,2)// der Zelle wird eine Zugehörigkeit zur Rechtenseite = 2
                
                room[i++][j].data.Sound.freq_20_40 = getFreq20b40(i,j) * 0.96 // dB reduziert um 4%
                room[i++][j].data.Sound.freq_40_100 = getFreq40b100(i,j) * 0.96 // value and Position i j
                room[i++][j].data.Sound.freq_100_150 = getFreq100b150(i,j) * 0.96
                room[i++][j].data.Sound.freq_150_400 = getFreq150b400(i,j) * 0.96
                room[i++][j].data.Sound.freq_400_1000 = getFreq400b1000(i,j) * 0.96
                room[i++][j].data.Sound.freq_1000_2000 = getFreq1000b2000(i,j) * 0.96
                room[i++][j].data.Sound.freq_2000_3500 = getFreq2000b3500(i,j) * 0.96
                room[i++][j].data.Sound.freq_3500_6000 = getFreq3500b6000(i,j) * 0.96
                room[i++][j].data.Sound.freq_6000_10000 = getFreq6000b10000(i,j) * 0.96
                room[i++][j].data.Sound.freq_10000_20000 = getFreq10000b20000(i,j) * 0.96
            }
        // linke Seite
        // Wenn du kein Seitenteil bist oder zur Linken seite gehörst
            else if( (room[x][y].data.Sound.sideofwave == 1) || (room[x][y].data.Sound.sideofwave == 0))
            {
                setItemID(i--,j, 0) // neues Teilchen der linken Seite
                setSideOfWave(i--,j,1)
                room[i--][j].data.Sound.freq_20_40 = getFreq20b40(i,j) * 0.96 // dB reduziert um 4%
                room[i--][j].data.Sound.freq_40_100 = getFreq40b100(i,j) * 0.96
                room[i--][j].data.Sound.freq_100_150 = getFreq100b150(i,j) * 0.96
                room[i--][j].data.Sound.freq_150_400 = getFreq150b400(i,j) * 0.96
                room[i--][j].data.Sound.freq_400_1000 = getFreq400b1000(i,j) * 0.96
                room[i--][j].data.Sound.freq_1000_2000 = getFreq1000b2000(i,j) * 0.96
                room[i--][j].data.Sound.freq_2000_3500 = getFreq2000b3500(i,j) * 0.96
                room[i--][j].data.Sound.freq_3500_6000 = getFreq3500b6000(i,j) * 0.96
                room[i--][j].data.Sound.freq_6000_10000 = getFreq6000b10000(i,j) * 0.96
                room[i--][j].data.Sound.freq_10000_20000 = getFreq10000b20000(i,j) * 0.96
            }
        
        else if( getDirectionID(i,j) == 2){
                // Nach oben rechts
                // rechte Seite der Welle für neue ID
                if( (room[x][y].data.Sound.sideofwave == 2) || (room[x][y].data.Sound.sideofwave == 0))
                {
                    setItemID(i++,j--, 0)
                    setSideOfWave(i++,j--,2)
                    room[i++][j--].data.Sound.freq_20_40 = getFreq20b40(i,j) * 0.96 // dB reduziert um 4%
                    room[i++][j--].data.Sound.freq_40_100 = getFreq40b100(i,j) * 0.96
                    room[i++][j--].data.Sound.freq_100_150 = getFreq100b150(i,j) * 0.96
                    room[i++][j--].data.Sound.freq_150_400 = getFreq150b400(i,j) * 0.96
                    room[i++][j--].data.Sound.freq_400_1000 = getFreq400b1000(i,j) * 0.96
                    room[i++][j--].data.Sound.freq_1000_2000 = getFreq1000b2000(i,j) * 0.96
                    room[i++][j--].data.Sound.freq_2000_3500 = getFreq2000b3500(i,j) * 0.96
                    room[i++][j--].data.Sound.freq_3500_6000 = getFreq3500b6000(i,j) * 0.96
                    room[i++][j--].data.Sound.freq_6000_10000 = getFreq6000b10000(i,j) * 0.96
                    room[i++][j--].data.Sound.freq_10000_20000 = getFreq10000b20000(i,j) * 0.96
                }
                // linke Seite
                else if( (room[x][y].data.Sound.sideofwave == 1) || (room[x][y].data.Sound.sideofwave == 0))
                {
                    setItemID(i--,j, 0)
                    setSideOfWave(i--,j,1)
                    room[i--][j++].data.Sound.freq_20_40 = getFreq20b40(i,j) * 0.96 // dB reduziert um 4%
                    room[i--][j++].data.Sound.freq_40_100 = getFreq40b100(i,j) * 0.96
                    room[i--][j++].data.Sound.freq_100_150 = getFreq100b150(i,j) * 0.96
                    room[i--][j++].data.Sound.freq_150_400 = getFreq150b400(i,j) * 0.96
                    room[i--][j++].data.Sound.freq_400_1000 = getFreq400b1000(i,j) * 0.96
                    room[i--][j++].data.Sound.freq_1000_2000 = getFreq1000b2000(i,j) * 0.96
                    room[i--][j++].data.Sound.freq_2000_3500 = getFreq2000b3500(i,j) * 0.96
                    room[i--][j++].data.Sound.freq_3500_6000 = getFreq3500b6000(i,j) * 0.96
                    room[i--][j++].data.Sound.freq_6000_10000 = getFreq6000b10000(i,j) * 0.96
                    room[i--][j++].data.Sound.freq_10000_20000 = getFreq10000b20000(i,j) * 0.96
                }
                
            }
        else if( getDirectionID(i,j) == 3){
            // Nach Rechts
            // rechte Seite der Welle für neue ID
            if( (room[x][y].data.Sound.sideofwave == 2) || (room[x][y].data.Sound.sideofwave == 0))
            {
                setSideOfWave(i,j--,2)
                setItemID(i,j--, 0)
                room[i][j--].data.Sound.freq_20_40 = getFreq20b40(i,j) * 0.96 // dB reduziert um 4%
                room[i][j--].data.Sound.freq_40_100 = getFreq40b100(i,j) * 0.96
                room[i][j--].data.Sound.freq_100_150 = getFreq100b150(i,j) * 0.96
                room[i][j--].data.Sound.freq_150_400 = getFreq150b400(i,j) * 0.96
                room[i][j--].data.Sound.freq_400_1000 = getFreq400b1000(i,j) * 0.96
                room[i][j--].data.Sound.freq_1000_2000 = getFreq1000b2000(i,j) * 0.96
                room[i][j--].data.Sound.freq_2000_3500 = getFreq2000b3500(i,j) * 0.96
                room[i][j--].data.Sound.freq_3500_6000 = getFreq3500b6000(i,j) * 0.96
                room[i][j--].data.Sound.freq_6000_10000 = getFreq6000b10000(i,j) * 0.96
                room[i][j--].data.Sound.freq_10000_20000 = getFreq10000b20000(i,j) * 0.96
            }
            // linke Seite
            else if( (room[x][y].data.Sound.sideofwave == 1) || (room[x][y].data.Sound.sideofwave == 0))
            {
                setSideOfWave(i,j++,1)
                setItemID(i,j++, 0)
                room[i][j++].data.Sound.freq_20_40 = getFreq20b40(i,j) * 0.96 // dB reduziert um 4%
                room[i][j++].data.Sound.freq_40_100 = getFreq40b100(i,j) * 0.96
                room[i][j++].data.Sound.freq_100_150 = getFreq100b150(i,j) * 0.96
                room[i][j++].data.Sound.freq_150_400 = getFreq150b400(i,j) * 0.96
                room[i][j++].data.Sound.freq_400_1000 = getFreq400b1000(i,j) * 0.96
                room[i][j++].data.Sound.freq_1000_2000 = getFreq1000b2000(i,j) * 0.96
                room[i][j++].data.Sound.freq_2000_3500 = getFreq2000b3500(i,j) * 0.96
                room[i][j++].data.Sound.freq_3500_6000 = getFreq3500b6000(i,j) * 0.96
                room[i][j++].data.Sound.freq_6000_10000 = getFreq6000b10000(i,j) * 0.96
                room[i][j++].data.Sound.freq_10000_20000 = getFreq10000b20000(i,j) * 0.96
            }
        }
        else if( getDirectionID(i,j) == 4){
            // unten rechts
            // rechte Seite der Welle für neue ID
            if( (room[x][y].data.Sound.sideofwave == 2) || (room[x][y].data.Sound.sideofwave == 0))
            {
                setItemID(i--,j--, 0)
                setSideOfWave(i--,j--,2)
                room[i--][j--].data.Sound.freq_20_40 = getFreq20b40(i,j) * 0.96 // dB reduziert um 4%
                room[i--][j--].data.Sound.freq_40_100 = getFreq40b100(i,j) * 0.96
                room[i--][j--].data.Sound.freq_100_150 = getFreq100b150(i,j) * 0.96
                room[i--][j--].data.Sound.freq_150_400 = getFreq150b400(i,j) * 0.96
                room[i--][j--].data.Sound.freq_400_1000 = getFreq400b1000(i,j) * 0.96
                room[i--][j--].data.Sound.freq_1000_2000 = getFreq1000b2000(i,j) * 0.96
                room[i--][j--].data.Sound.freq_2000_3500 = getFreq2000b3500(i,j) * 0.96
                room[i--][j--].data.Sound.freq_3500_6000 = getFreq3500b6000(i,j) * 0.96
                room[i--][j--].data.Sound.freq_6000_10000 = getFreq6000b10000(i,j) * 0.96
                room[i--][j--].data.Sound.freq_10000_20000 = getFreq10000b20000(i,j) * 0.96
            }
            // linke Seite
            else if( (room[x][y].data.Sound.sideofwave == 1) || (room[x][y].data.Sound.sideofwave == 0))
            {
                setSideOfWave(i++,j++,1)
                setItemID(i++,j++, 0)
                room[i++][j++].data.Sound.freq_20_40 = getFreq20b40(i,j) * 0.96 // dB reduziert um 4%
                room[i++][j++].data.Sound.freq_40_100 = getFreq40b100(i,j) * 0.96
                room[i++][j++].data.Sound.freq_100_150 = getFreq100b150(i,j) * 0.96
                room[i++][j++].data.Sound.freq_150_400 = getFreq150b400(i,j) * 0.96
                room[i++][j++].data.Sound.freq_400_1000 = getFreq400b1000(i,j) * 0.96
                room[i++][j++].data.Sound.freq_1000_2000 = getFreq1000b2000(i,j) * 0.96
                room[i++][j++].data.Sound.freq_2000_3500 = getFreq2000b3500(i,j) * 0.96
                room[i++][j++].data.Sound.freq_3500_6000 = getFreq3500b6000(i,j) * 0.96
                room[i++][j++].data.Sound.freq_6000_10000 = getFreq6000b10000(i,j) * 0.96
                room[i++][j++].data.Sound.freq_10000_20000 = getFreq10000b20000(i,j) * 0.96
            }
        }
        
        else if( getDirectionID(i,j) == 5){
            //unten
            // rechte Seite der Welle für neue ID
            if( (room[x][y].data.Sound.sideofwave == 2) || (room[x][y].data.Sound.sideofwave == 0))
            {
                setSideOfWave(i--,j,2)
                setItemID(i--,j, 0)
                room[i--][j].data.Sound.freq_20_40 = getFreq20b40(i,j) * 0.96 // dB reduziert um 4%
                room[i--][j].data.Sound.freq_40_100 = getFreq40b100(i,j) * 0.96
                room[i--][j].data.Sound.freq_100_150 = getFreq100b150(i,j) * 0.96
                room[i--][j].data.Sound.freq_150_400 = getFreq150b400(i,j) * 0.96
                room[i--][j].data.Sound.freq_400_1000 = getFreq400b1000(i,j) * 0.96
                room[i--][j].data.Sound.freq_1000_2000 = getFreq1000b2000(i,j) * 0.96
                room[i--][j].data.Sound.freq_2000_3500 = getFreq2000b3500(i,j) * 0.96
                room[i--][j].data.Sound.freq_3500_6000 = getFreq3500b6000(i,j) * 0.96
                room[i--][j].data.Sound.freq_6000_10000 = getFreq6000b10000(i,j) * 0.96
                room[i--][j].data.Sound.freq_10000_20000 = getFreq10000b20000(i,j) * 0.96
            }
            // linke Seite
            else if( (room[x][y].data.Sound.sideofwave == 1) || (room[x][y].data.Sound.sideofwave == 0))
            {
                setSideOfWave(i++,j,1)
                setItemID(i++,j, 0)
                room[i++][j].data.Sound.freq_20_40 = getFreq20b40(i,j) * 0.96 // dB reduziert um 4%
                room[i++][j].data.Sound.freq_40_100 = getFreq40b100(i,j) * 0.96
                room[i++][j].data.Sound.freq_100_150 = getFreq100b150(i,j) * 0.96
                room[i++][j].data.Sound.freq_150_400 = getFreq150b400(i,j) * 0.96
                room[i++][j].data.Sound.freq_400_1000 = getFreq400b1000(i,j) * 0.96
                room[i++][j].data.Sound.freq_1000_2000 = getFreq1000b2000(i,j) * 0.96
                room[i++][j].data.Sound.freq_2000_3500 = getFreq2000b3500(i,j) * 0.96
                room[i++][j].data.Sound.freq_3500_6000 = getFreq3500b6000(i,j) * 0.96
                room[i++][j].data.Sound.freq_6000_10000 = getFreq6000b10000(i,j) * 0.96
                room[i++][j].data.Sound.freq_10000_20000 = getFreq10000b20000(i,j) * 0.96
            }
        }
        else if( getDirectionID(i,j) == 6){
            //unten links
            // rechte Seite der Welle für neue ID
            if( (room[x][y].data.Sound.sideofwave == 2) || (room[x][y].data.Sound.sideofwave == 0))
            {
                setSideOfWave(i--,j++,2)
                setItemID(i--,j++, 0)
                room[i--][j++].data.Sound.freq_20_40 = getFreq20b40(i,j) * 0.96 // dB reduziert um 4%
                room[i--][j++].data.Sound.freq_40_100 = getFreq40b100(i,j) * 0.96
                room[i--][j++].data.Sound.freq_100_150 = getFreq100b150(i,j) * 0.96
                room[i--][j++].data.Sound.freq_150_400 = getFreq150b400(i,j) * 0.96
                room[i--][j++].data.Sound.freq_400_1000 = getFreq400b1000(i,j) * 0.96
                room[i--][j++].data.Sound.freq_1000_2000 = getFreq1000b2000(i,j) * 0.96
                room[i--][j++].data.Sound.freq_2000_3500 = getFreq2000b3500(i,j) * 0.96
                room[i--][j++].data.Sound.freq_3500_6000 = getFreq3500b6000(i,j) * 0.96
                room[i--][j++].data.Sound.freq_6000_10000 = getFreq6000b10000(i,j) * 0.96
                room[i--][j++].data.Sound.freq_10000_20000 = getFreq10000b20000(i,j) * 0.96
            }
            // linke Seite
            else if( (room[x][y].data.Sound.sideofwave == 1) || (room[x][y].data.Sound.sideofwave == 0))
            {
                setSideOfWave(i++,j--,1)
                setItemID(i++,j--, 0)
                room[i++][j--].data.Sound.freq_20_40 = getFreq20b40(i,j) * 0.96 // dB reduziert um 4%
                room[i++][j--].data.Sound.freq_40_100 = getFreq40b100(i,j) * 0.96
                room[i++][j--].data.Sound.freq_100_150 = getFreq100b150(i,j) * 0.96
                room[i++][j--].data.Sound.freq_150_400 = getFreq150b400(i,j) * 0.96
                room[i++][j--].data.Sound.freq_400_1000 = getFreq400b1000(i,j) * 0.96
                room[i++][j--].data.Sound.freq_1000_2000 = getFreq1000b2000(i,j) * 0.96
                room[i++][j--].data.Sound.freq_2000_3500 = getFreq2000b3500(i,j) * 0.96
                room[i++][j--].data.Sound.freq_3500_6000 = getFreq3500b6000(i,j) * 0.96
                room[i++][j--].data.Sound.freq_6000_10000 = getFreq6000b10000(i,j) * 0.96
                room[i++][j--].data.Sound.freq_10000_20000 = getFreq10000b20000(i,j) * 0.96
            }
        }
        else if( getDirectionID(i,j) == 7){
            // links
            // rechte Seite der Welle für neue ID
            if( (room[x][y].data.Sound.sideofwave == 2) || (room[x][y].data.Sound.sideofwave == 0))
            {
                setSideOfWave(i,j++,2)
                setItemID(i,j++, 0)
                room[i][j++].data.Sound.freq_20_40 = getFreq20b40(i,j) * 0.96 // dB reduziert um 4%
                room[i][j++].data.Sound.freq_40_100 = getFreq40b100(i,j) * 0.96
                room[i][j++].data.Sound.freq_100_150 = getFreq100b150(i,j) * 0.96
                room[i][j++].data.Sound.freq_150_400 = getFreq150b400(i,j) * 0.96
                room[i][j++].data.Sound.freq_400_1000 = getFreq400b1000(i,j) * 0.96
                room[i][j++].data.Sound.freq_1000_2000 = getFreq1000b2000(i,j) * 0.96
                room[i][j++].data.Sound.freq_2000_3500 = getFreq2000b3500(i,j) * 0.96
                room[i][j++].data.Sound.freq_3500_6000 = getFreq3500b6000(i,j) * 0.96
                room[i][j++].data.Sound.freq_6000_10000 = getFreq6000b10000(i,j) * 0.96
                room[i][j++].data.Sound.freq_10000_20000 = getFreq10000b20000(i,j) * 0.96
            }
            // linke Seite
            else if( (room[x][y].data.Sound.sideofwave == 1) || (room[x][y].data.Sound.sideofwave == 0))
            {
                setSideOfWave(i,j--,1)
                setItemID(i,j--, 0)
                room[i][j--].data.Sound.freq_20_40 = getFreq20b40(i,j) * 0.96 // dB reduziert um 4%
                room[i][j--].data.Sound.freq_40_100 = getFreq40b100(i,j) * 0.96
                room[i][j--].data.Sound.freq_100_150 = getFreq100b150(i,j) * 0.96
                room[i][j--].data.Sound.freq_150_400 = getFreq150b400(i,j) * 0.96
                room[i][j--].data.Sound.freq_400_1000 = getFreq400b1000(i,j) * 0.96
                room[i][j--].data.Sound.freq_1000_2000 = getFreq1000b2000(i,j) * 0.96
                room[i][j--].data.Sound.freq_2000_3500 = getFreq2000b3500(i,j) * 0.96
                room[i][j--].data.Sound.freq_3500_6000 = getFreq3500b6000(i,j) * 0.96
                room[i][j--].data.Sound.freq_6000_10000 = getFreq6000b10000(i,j) * 0.96
                room[i][j--].data.Sound.freq_10000_20000 = getFreq10000b20000(i,j) * 0.96
            }
        }
        else if( getDirectionID(i,j) == 8){
            //oben links
            // rechte Seite der Welle für neue ID
            if( (room[x][y].data.Sound.sideofwave == 2) || (room[x][y].data.Sound.sideofwave == 0))
            {
                setSideOfWave(i++,j--,2)
                setItemID(i++,j--, 0)
                room[i++][j--].data.Sound.freq_20_40 = getFreq20b40(i,j) * 0.96 // dB reduziert um 4%
                room[i++][j--].data.Sound.freq_40_100 = getFreq40b100(i,j) * 0.96
                room[i++][j--].data.Sound.freq_100_150 = getFreq100b150(i,j) * 0.96
                room[i++][j--].data.Sound.freq_150_400 = getFreq150b400(i,j) * 0.96
                room[i++][j--].data.Sound.freq_400_1000 = getFreq400b1000(i,j) * 0.96
                room[i++][j--].data.Sound.freq_1000_2000 = getFreq1000b2000(i,j) * 0.96
                room[i++][j--].data.Sound.freq_2000_3500 = getFreq2000b3500(i,j) * 0.96
                room[i++][j--].data.Sound.freq_3500_6000 = getFreq3500b6000(i,j) * 0.96
                room[i++][j--].data.Sound.freq_6000_10000 = getFreq6000b10000(i,j) * 0.96
                room[i++][j--].data.Sound.freq_10000_20000 = getFreq10000b20000(i,j) * 0.96
            }
            // linke Seite
            else if( (room[x][y].data.Sound.sideofwave == 1) || (room[x][y].data.Sound.sideofwave == 0))
            {
                setSideOfWave(i--,j++,1)
                setItemID(i--,j++, 0)
                room[i--][j++].data.Sound.freq_20_40 = getFreq20b40(i,j) * 0.96 // dB reduziert um 4%
                room[i--][j++].data.Sound.freq_40_100 = getFreq40b100(i,j) * 0.96
                room[i--][j++].data.Sound.freq_100_150 = getFreq100b150(i,j) * 0.96
                room[i--][j++].data.Sound.freq_150_400 = getFreq150b400(i,j) * 0.96
                room[i--][j++].data.Sound.freq_400_1000 = getFreq400b1000(i,j) * 0.96
                room[i--][j++].data.Sound.freq_1000_2000 = getFreq1000b2000(i,j) * 0.96
                room[i--][j++].data.Sound.freq_2000_3500 = getFreq2000b3500(i,j) * 0.96
                room[i--][j++].data.Sound.freq_3500_6000 = getFreq3500b6000(i,j) * 0.96
                room[i--][j++].data.Sound.freq_6000_10000 = getFreq6000b10000(i,j) * 0.96
                room[i--][j++].data.Sound.freq_10000_20000 = getFreq10000b20000(i,j) * 0.96
            }
        }

    }else
    {
    // evtl merken ob ein teil zur rechten oder linken seite gehört und dann nur noch einseitig
    // weiter verbreitet - neue variable die das anzeigt !
    
    if( getDirectionID(i,j) == 1){
        // Nach oben
        // rechte Seite der Welle für neue ID
        
        if( (room[x][y].data.Sound.sideofwave == 2) || (room[x][y].data.Sound.sideofwave == 0))
        {
        setItemID(i++,j--, 0) // Neues Teilchen der rechten Seite
        setSideOfWave(i++,j--,2)// der Zelle wird eine Zugehörigkeit zur Rechtenseite = 2
        
        room[i++][j--].data.Sound.freq_20_40 = getFreq20b40(i,j) * 0.96 // dB reduziert um 4%
        room[i++][j--].data.Sound.freq_40_100 = getFreq40b100(i,j) * 0.96 // value and Position i j
        room[i++][j--].data.Sound.freq_100_150 = getFreq100b150(i,j) * 0.96
        room[i++][j--].data.Sound.freq_150_400 = getFreq150b400(i,j) * 0.96
        room[i++][j--].data.Sound.freq_400_1000 = getFreq400b1000(i,j) * 0.96
        room[i++][j--].data.Sound.freq_1000_2000 = getFreq1000b2000(i,j) * 0.96
        room[i++][j--].data.Sound.freq_2000_3500 = getFreq2000b3500(i,j) * 0.96
        room[i++][j--].data.Sound.freq_3500_6000 = getFreq3500b6000(i,j) * 0.96
        room[i++][j--].data.Sound.freq_6000_10000 = getFreq6000b10000(i,j) * 0.96
        room[i++][j--].data.Sound.freq_10000_20000 = getFreq10000b20000(i,j) * 0.96
        }
        // linke Seite
        // Wenn du kein Seitenteil bist oder zur Linken seite gehörst
        else if( (room[x][y].data.Sound.sideofwave == 1) || (room[x][y].data.Sound.sideofwave == 0))
        {
        setItemID(i--,j--, 0) // neues Teilchen der linken Seite
        setSideOfWave(i--,j--,1)
        room[i--][j--].data.Sound.freq_20_40 = getFreq20b40(i,j) * 0.96 // dB reduziert um 4%
        room[i--][j--].data.Sound.freq_40_100 = getFreq40b100(i,j) * 0.96
        room[i--][j--].data.Sound.freq_100_150 = getFreq100b150(i,j) * 0.96
        room[i--][j--].data.Sound.freq_150_400 = getFreq150b400(i,j) * 0.96
        room[i--][j--].data.Sound.freq_400_1000 = getFreq400b1000(i,j) * 0.96
        room[i--][j--].data.Sound.freq_1000_2000 = getFreq1000b2000(i,j) * 0.96
        room[i--][j--].data.Sound.freq_2000_3500 = getFreq2000b3500(i,j) * 0.96
        room[i--][j--].data.Sound.freq_3500_6000 = getFreq3500b6000(i,j) * 0.96
        room[i--][j--].data.Sound.freq_6000_10000 = getFreq6000b10000(i,j) * 0.96
        room[i--][j--].data.Sound.freq_10000_20000 = getFreq10000b20000(i,j) * 0.96
        }
    }
    else if( getDirectionID(i,j) == 2){
        // Nach oben rechts
        // rechte Seite der Welle für neue ID
            if( (room[x][y].data.Sound.sideofwave == 2) || (room[x][y].data.Sound.sideofwave == 0))
        {
        setItemID(i,j--, 0)
        setSideOfWave(i,j--,2)
        room[i][j--].data.Sound.freq_20_40 = getFreq20b40(i,j) * 0.96 // dB reduziert um 4%
        room[i][j--].data.Sound.freq_40_100 = getFreq40b100(i,j) * 0.96
        room[i][j--].data.Sound.freq_100_150 = getFreq100b150(i,j) * 0.96
        room[i][j--].data.Sound.freq_150_400 = getFreq150b400(i,j) * 0.96
        room[i][j--].data.Sound.freq_400_1000 = getFreq400b1000(i,j) * 0.96
        room[i][j--].data.Sound.freq_1000_2000 = getFreq1000b2000(i,j) * 0.96
        room[i][j--].data.Sound.freq_2000_3500 = getFreq2000b3500(i,j) * 0.96
        room[i][j--].data.Sound.freq_3500_6000 = getFreq3500b6000(i,j) * 0.96
        room[i][j--].data.Sound.freq_6000_10000 = getFreq6000b10000(i,j) * 0.96
        room[i][j--].data.Sound.freq_10000_20000 = getFreq10000b20000(i,j) * 0.96
        }
        // linke Seite
        else if( (room[x][y].data.Sound.sideofwave == 1) || (room[x][y].data.Sound.sideofwave == 0))
        {
        setItemID(i--,j, 0)
        setSideOfWave(i--,j,1)
        room[i--][j].data.Sound.freq_20_40 = getFreq20b40(i,j) * 0.96 // dB reduziert um 4%
        room[i--][j].data.Sound.freq_40_100 = getFreq40b100(i,j) * 0.96
        room[i--][j].data.Sound.freq_100_150 = getFreq100b150(i,j) * 0.96
        room[i--][j].data.Sound.freq_150_400 = getFreq150b400(i,j) * 0.96
        room[i--][j].data.Sound.freq_400_1000 = getFreq400b1000(i,j) * 0.96
        room[i--][j].data.Sound.freq_1000_2000 = getFreq1000b2000(i,j) * 0.96
        room[i--][j].data.Sound.freq_2000_3500 = getFreq2000b3500(i,j) * 0.96
        room[i--][j].data.Sound.freq_3500_6000 = getFreq3500b6000(i,j) * 0.96
        room[i--][j].data.Sound.freq_6000_10000 = getFreq6000b10000(i,j) * 0.96
        room[i--][j].data.Sound.freq_10000_20000 = getFreq10000b20000(i,j) * 0.96
        }
    
    }
    else if( getDirectionID(i,j) == 4){
        // unten rechts
        // rechte Seite der Welle für neue ID
        if( (room[x][y].data.Sound.sideofwave == 2) || (room[x][y].data.Sound.sideofwave == 0))
        {
        setItemID(i--,j, 0)
        setSideOfWave(i--,j,2)
        room[i--][j].data.Sound.freq_20_40 = getFreq20b40(i,j) * 0.96 // dB reduziert um 4%
        room[i--][j].data.Sound.freq_40_100 = getFreq40b100(i,j) * 0.96
        room[i--][j].data.Sound.freq_100_150 = getFreq100b150(i,j) * 0.96
        room[i--][j].data.Sound.freq_150_400 = getFreq150b400(i,j) * 0.96
        room[i--][j].data.Sound.freq_400_1000 = getFreq400b1000(i,j) * 0.96
        room[i--][j].data.Sound.freq_1000_2000 = getFreq1000b2000(i,j) * 0.96
        room[i--][j].data.Sound.freq_2000_3500 = getFreq2000b3500(i,j) * 0.96
        room[i--][j].data.Sound.freq_3500_6000 = getFreq3500b6000(i,j) * 0.96
        room[i--][j].data.Sound.freq_6000_10000 = getFreq6000b10000(i,j) * 0.96
        room[i--][j].data.Sound.freq_10000_20000 = getFreq10000b20000(i,j) * 0.96
        }
        // linke Seite
        else if( (room[x][y].data.Sound.sideofwave == 1) || (room[x][y].data.Sound.sideofwave == 0))
        {
        setSideOfWave(i,j++,1)
        setItemID(i,j++, 0)
        room[i][j++].data.Sound.freq_20_40 = getFreq20b40(i,j) * 0.96 // dB reduziert um 4%
        room[i][j++].data.Sound.freq_40_100 = getFreq40b100(i,j) * 0.96
        room[i][j++].data.Sound.freq_100_150 = getFreq100b150(i,j) * 0.96
        room[i][j++].data.Sound.freq_150_400 = getFreq150b400(i,j) * 0.96
        room[i][j++].data.Sound.freq_400_1000 = getFreq400b1000(i,j) * 0.96
        room[i][j++].data.Sound.freq_1000_2000 = getFreq1000b2000(i,j) * 0.96
        room[i][j++].data.Sound.freq_2000_3500 = getFreq2000b3500(i,j) * 0.96
        room[i][j++].data.Sound.freq_3500_6000 = getFreq3500b6000(i,j) * 0.96
        room[i][j++].data.Sound.freq_6000_10000 = getFreq6000b10000(i,j) * 0.96
        room[i][j++].data.Sound.freq_10000_20000 = getFreq10000b20000(i,j) * 0.96
        }
    }
    
    else if( getDirectionID(i,j) == 3){
        // Nach Rechts
        // rechte Seite der Welle für neue ID
        if( (room[x][y].data.Sound.sideofwave == 2) || (room[x][y].data.Sound.sideofwave == 0))
        {
        setSideOfWave(i--,j--,2)
        setItemID(i--,j--, 0)
        room[i--][j--].data.Sound.freq_20_40 = getFreq20b40(i,j) * 0.96 // dB reduziert um 4%
        room[i--][j--].data.Sound.freq_40_100 = getFreq40b100(i,j) * 0.96
        room[i--][j--].data.Sound.freq_100_150 = getFreq100b150(i,j) * 0.96
        room[i--][j--].data.Sound.freq_150_400 = getFreq150b400(i,j) * 0.96
        room[i--][j--].data.Sound.freq_400_1000 = getFreq400b1000(i,j) * 0.96
        room[i--][j--].data.Sound.freq_1000_2000 = getFreq1000b2000(i,j) * 0.96
        room[i--][j--].data.Sound.freq_2000_3500 = getFreq2000b3500(i,j) * 0.96
        room[i--][j--].data.Sound.freq_3500_6000 = getFreq3500b6000(i,j) * 0.96
        room[i--][j--].data.Sound.freq_6000_10000 = getFreq6000b10000(i,j) * 0.96
        room[i--][j--].data.Sound.freq_10000_20000 = getFreq10000b20000(i,j) * 0.96
        }
        // linke Seite
        else if( (room[x][y].data.Sound.sideofwave == 1) || (room[x][y].data.Sound.sideofwave == 0))
        {
        setSideOfWave(i--,j++,1)
        setItemID(i--,j++, 0)
        room[i--][j++].data.Sound.freq_20_40 = getFreq20b40(i,j) * 0.96 // dB reduziert um 4%
        room[i--][j++].data.Sound.freq_40_100 = getFreq40b100(i,j) * 0.96
        room[i--][j++].data.Sound.freq_100_150 = getFreq100b150(i,j) * 0.96
        room[i--][j++].data.Sound.freq_150_400 = getFreq150b400(i,j) * 0.96
        room[i--][j++].data.Sound.freq_400_1000 = getFreq400b1000(i,j) * 0.96
        room[i--][j++].data.Sound.freq_1000_2000 = getFreq1000b2000(i,j) * 0.96
        room[i--][j++].data.Sound.freq_2000_3500 = getFreq2000b3500(i,j) * 0.96
        room[i--][j++].data.Sound.freq_3500_6000 = getFreq3500b6000(i,j) * 0.96
        room[i--][j++].data.Sound.freq_6000_10000 = getFreq6000b10000(i,j) * 0.96
        room[i--][j++].data.Sound.freq_10000_20000 = getFreq10000b20000(i,j) * 0.96
        }
    }
        else if( getDirectionID(i,j) == 5){
            //unten
            // rechte Seite der Welle für neue ID
            if( (room[x][y].data.Sound.sideofwave == 2) || (room[x][y].data.Sound.sideofwave == 0))
            {
            setSideOfWave(i--,j++,2)
            setItemID(i--,j++, 0)
            room[i--][j++].data.Sound.freq_20_40 = getFreq20b40(i,j) * 0.96 // dB reduziert um 4%
            room[i--][j++].data.Sound.freq_40_100 = getFreq40b100(i,j) * 0.96
            room[i--][j++].data.Sound.freq_100_150 = getFreq100b150(i,j) * 0.96
            room[i--][j++].data.Sound.freq_150_400 = getFreq150b400(i,j) * 0.96
            room[i--][j++].data.Sound.freq_400_1000 = getFreq400b1000(i,j) * 0.96
            room[i--][j++].data.Sound.freq_1000_2000 = getFreq1000b2000(i,j) * 0.96
            room[i--][j++].data.Sound.freq_2000_3500 = getFreq2000b3500(i,j) * 0.96
            room[i--][j++].data.Sound.freq_3500_6000 = getFreq3500b6000(i,j) * 0.96
            room[i--][j++].data.Sound.freq_6000_10000 = getFreq6000b10000(i,j) * 0.96
            room[i--][j++].data.Sound.freq_10000_20000 = getFreq10000b20000(i,j) * 0.96
            }
            // linke Seite
            else if( (room[x][y].data.Sound.sideofwave == 1) || (room[x][y].data.Sound.sideofwave == 0))
            {
            setSideOfWave(i++,j++,1)
            setItemID(i++,j++, 0)
            room[i++][j++].data.Sound.freq_20_40 = getFreq20b40(i,j) * 0.96 // dB reduziert um 4%
            room[i++][j++].data.Sound.freq_40_100 = getFreq40b100(i,j) * 0.96
            room[i++][j++].data.Sound.freq_100_150 = getFreq100b150(i,j) * 0.96
            room[i++][j++].data.Sound.freq_150_400 = getFreq150b400(i,j) * 0.96
            room[i++][j++].data.Sound.freq_400_1000 = getFreq400b1000(i,j) * 0.96
            room[i++][j++].data.Sound.freq_1000_2000 = getFreq1000b2000(i,j) * 0.96
            room[i++][j++].data.Sound.freq_2000_3500 = getFreq2000b3500(i,j) * 0.96
            room[i++][j++].data.Sound.freq_3500_6000 = getFreq3500b6000(i,j) * 0.96
            room[i++][j++].data.Sound.freq_6000_10000 = getFreq6000b10000(i,j) * 0.96
            room[i++][j++].data.Sound.freq_10000_20000 = getFreq10000b20000(i,j) * 0.96
            }
        }
        
        else if( getDirectionID(i,j) == 6){
            //unten links
            // rechte Seite der Welle für neue ID
            if( (room[x][y].data.Sound.sideofwave == 2) || (room[x][y].data.Sound.sideofwave == 0))
            {
            setSideOfWave(i,j++,2)
            setItemID(i,j++, 0)
            room[i][j++].data.Sound.freq_20_40 = getFreq20b40(i,j) * 0.96 // dB reduziert um 4%
            room[i][j++].data.Sound.freq_40_100 = getFreq40b100(i,j) * 0.96
            room[i][j++].data.Sound.freq_100_150 = getFreq100b150(i,j) * 0.96
            room[i][j++].data.Sound.freq_150_400 = getFreq150b400(i,j) * 0.96
            room[i][j++].data.Sound.freq_400_1000 = getFreq400b1000(i,j) * 0.96
            room[i][j++].data.Sound.freq_1000_2000 = getFreq1000b2000(i,j) * 0.96
            room[i][j++].data.Sound.freq_2000_3500 = getFreq2000b3500(i,j) * 0.96
            room[i][j++].data.Sound.freq_3500_6000 = getFreq3500b6000(i,j) * 0.96
            room[i][j++].data.Sound.freq_6000_10000 = getFreq6000b10000(i,j) * 0.96
            room[i][j++].data.Sound.freq_10000_20000 = getFreq10000b20000(i,j) * 0.96
            }
            // linke Seite
            else if( (room[x][y].data.Sound.sideofwave == 1) || (room[x][y].data.Sound.sideofwave == 0))
            {
            setSideOfWave(i++,j,1)
            setItemID(i++,j, 0)
            room[i++][j].data.Sound.freq_20_40 = getFreq20b40(i,j) * 0.96 // dB reduziert um 4%
            room[i++][j].data.Sound.freq_40_100 = getFreq40b100(i,j) * 0.96
            room[i++][j].data.Sound.freq_100_150 = getFreq100b150(i,j) * 0.96
            room[i++][j].data.Sound.freq_150_400 = getFreq150b400(i,j) * 0.96
            room[i++][j].data.Sound.freq_400_1000 = getFreq400b1000(i,j) * 0.96
            room[i++][j].data.Sound.freq_1000_2000 = getFreq1000b2000(i,j) * 0.96
            room[i++][j].data.Sound.freq_2000_3500 = getFreq2000b3500(i,j) * 0.96
            room[i++][j].data.Sound.freq_3500_6000 = getFreq3500b6000(i,j) * 0.96
            room[i++][j].data.Sound.freq_6000_10000 = getFreq6000b10000(i,j) * 0.96
            room[i++][j].data.Sound.freq_10000_20000 = getFreq10000b20000(i,j) * 0.96
            }
        }
        else if( getDirectionID(i,j) == 7){
            // links
            // rechte Seite der Welle für neue ID
            if( (room[x][y].data.Sound.sideofwave == 2) || (room[x][y].data.Sound.sideofwave == 0))
            {
            setSideOfWave(i--,j++,2)
            setItemID(i--,j++, 0)
            room[i--][j++].data.Sound.freq_20_40 = getFreq20b40(i,j) * 0.96 // dB reduziert um 4%
            room[i--][j++].data.Sound.freq_40_100 = getFreq40b100(i,j) * 0.96
            room[i--][j++].data.Sound.freq_100_150 = getFreq100b150(i,j) * 0.96
            room[i--][j++].data.Sound.freq_150_400 = getFreq150b400(i,j) * 0.96
            room[i--][j++].data.Sound.freq_400_1000 = getFreq400b1000(i,j) * 0.96
            room[i--][j++].data.Sound.freq_1000_2000 = getFreq1000b2000(i,j) * 0.96
            room[i--][j++].data.Sound.freq_2000_3500 = getFreq2000b3500(i,j) * 0.96
            room[i--][j++].data.Sound.freq_3500_6000 = getFreq3500b6000(i,j) * 0.96
            room[i--][j++].data.Sound.freq_6000_10000 = getFreq6000b10000(i,j) * 0.96
            room[i--][j++].data.Sound.freq_10000_20000 = getFreq10000b20000(i,j) * 0.96
            }
            // linke Seite
            else if( (room[x][y].data.Sound.sideofwave == 1) || (room[x][y].data.Sound.sideofwave == 0))
            {
            setSideOfWave(i++,j,1)
            setItemID(i++,j, 0)
            room[i++][j].data.Sound.freq_20_40 = getFreq20b40(i,j) * 0.96 // dB reduziert um 4%
            room[i++][j].data.Sound.freq_40_100 = getFreq40b100(i,j) * 0.96
            room[i++][j].data.Sound.freq_100_150 = getFreq100b150(i,j) * 0.96
            room[i++][j].data.Sound.freq_150_400 = getFreq150b400(i,j) * 0.96
            room[i++][j].data.Sound.freq_400_1000 = getFreq400b1000(i,j) * 0.96
            room[i++][j].data.Sound.freq_1000_2000 = getFreq1000b2000(i,j) * 0.96
            room[i++][j].data.Sound.freq_2000_3500 = getFreq2000b3500(i,j) * 0.96
            room[i++][j].data.Sound.freq_3500_6000 = getFreq3500b6000(i,j) * 0.96
            room[i++][j].data.Sound.freq_6000_10000 = getFreq6000b10000(i,j) * 0.96
            room[i++][j].data.Sound.freq_10000_20000 = getFreq10000b20000(i,j) * 0.96
            }
        }
        else if( getDirectionID(i,j) == 8){
            //oben links
            // rechte Seite der Welle für neue ID
            if( (room[x][y].data.Sound.sideofwave == 2) || (room[x][y].data.Sound.sideofwave == 0))
            {
            setSideOfWave(i++,j,2)
            setItemID(i++,j, 0)
            room[i++][j].data.Sound.freq_20_40 = getFreq20b40(i,j) * 0.96 // dB reduziert um 4%
            room[i++][j].data.Sound.freq_40_100 = getFreq40b100(i,j) * 0.96
            room[i++][j].data.Sound.freq_100_150 = getFreq100b150(i,j) * 0.96
            room[i++][j].data.Sound.freq_150_400 = getFreq150b400(i,j) * 0.96
            room[i++][j].data.Sound.freq_400_1000 = getFreq400b1000(i,j) * 0.96
            room[i++][j].data.Sound.freq_1000_2000 = getFreq1000b2000(i,j) * 0.96
            room[i++][j].data.Sound.freq_2000_3500 = getFreq2000b3500(i,j) * 0.96
            room[i++][j].data.Sound.freq_3500_6000 = getFreq3500b6000(i,j) * 0.96
            room[i++][j].data.Sound.freq_6000_10000 = getFreq6000b10000(i,j) * 0.96
            room[i++][j].data.Sound.freq_10000_20000 = getFreq10000b20000(i,j) * 0.96
            }
            // linke Seite
            else if( (room[x][y].data.Sound.sideofwave == 1) || (room[x][y].data.Sound.sideofwave == 0))
            {
            setSideOfWave(i,j--,1)
            setItemID(i,j--, 0)
            room[i][j--].data.Sound.freq_20_40 = getFreq20b40(i,j) * 0.96 // dB reduziert um 4%
            room[i][j--].data.Sound.freq_40_100 = getFreq40b100(i,j) * 0.96
            room[i][j--].data.Sound.freq_100_150 = getFreq100b150(i,j) * 0.96
            room[i][j--].data.Sound.freq_150_400 = getFreq150b400(i,j) * 0.96
            room[i][j--].data.Sound.freq_400_1000 = getFreq400b1000(i,j) * 0.96
            room[i][j--].data.Sound.freq_1000_2000 = getFreq1000b2000(i,j) * 0.96
            room[i][j--].data.Sound.freq_2000_3500 = getFreq2000b3500(i,j) * 0.96
            room[i][j--].data.Sound.freq_3500_6000 = getFreq3500b6000(i,j) * 0.96
            room[i][j--].data.Sound.freq_6000_10000 = getFreq6000b10000(i,j) * 0.96
            room[i][j--].data.Sound.freq_10000_20000 = getFreq10000b20000(i,j) * 0.96
            }
        }
}
}