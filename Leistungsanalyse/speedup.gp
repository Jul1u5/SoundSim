set terminal postscript
set output '| ps2pdf - speedup.pdf'
set xlabel "Anzahl der Prozesse“
set ylabel "Speed Up“

set key top right

set xrange [0:30]
set yrange [0:15]

unset key
plot "./speedup.dat" using 1:2 pt 5 ps 2

unset output
