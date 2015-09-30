set terminal postscript
set output '| ps2pdf - 3DNichtOptimiertGB.pdf'
set title "RAM und Raumgroesse "
set xlabel "Groesse der Matrix^3“
set ylabel "Speicher in GB“

set key top right

set xrange [0:600]
set zrange [0:16]


unset key
plot "./daten3dNichtOptimiertGB.dat" using 1:2 pt 6 ps 2

unset output
