set terminal postscript
set output '| ps2pdf - 3DNichtOptimiert.pdf'
set title "Laufzeit und Raumgroesse"
set xlabel "Groesse der Matrix^3“
set ylabel "Zeit in Sekunden“
set zlabel "Speicher in GB“

set key top right

set xrange [0:600]
set yrange [0:100]
set zrange [0:16]

unset key
plot "./daten3dNichtOptimiert.dat" using 1:2 pt 6 ps 2

unset output
