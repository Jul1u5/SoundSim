set terminal postscript
set output '| ps2pdf - 3DOptimiert.pdf'
set title "Laufzeit und Raumgroesse bei 100 Durchgaengen“
set xlabel "Groesse der Matrix^3“
set ylabel "Zeit in Sekunden“

set key top right

set xrange [0:600]
set yrange [0: 2500]

unset key
plot "./daten3dOptimiert.dat" using 1:2 pt 7 ps 2

unset output
