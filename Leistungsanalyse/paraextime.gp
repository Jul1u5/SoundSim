set terminal postscript
set output '| ps2pdf - paraextime.pdf'
set xlabel "Anzahl der Prozesse“
set ylabel "Durchlaufzeit einer 200x200x200 Matrix in Sekunden“

set key top right

set xrange [0:40]
set yrange [0:150]

unset key
plot "./paraextime.dat" using 1:2 pt 5 ps 2

unset output
