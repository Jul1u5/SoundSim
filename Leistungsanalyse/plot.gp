set terminal postscript
set output '| ps2pdf - plot.pdf'
set xlabel "Groeße der Matrix^3“
set ylabel "Zeit in Sekunden“

set key top right

set xrange [0:11000]
set yrange [0:1500]

unset key
plot "./daten.dat" using 1:2 pt 5 ps 2

unset output
