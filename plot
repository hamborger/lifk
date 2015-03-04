reset

gn = 10
npg = 100

set terminal postscript enhanced font "Helvetica,5" 
set output '| ps2pdf - output_V.pdf'
set tic scale 0
set multiplot layout gn,1 title "Synfire chain" font ",7"  

set datafile separator ","
set grid

do for [i=0:gn-1] {
	plot for [j=0:npg-1] "if.dat" u 1:(column(i*npg+j+2)) w l t "N = ".(i*npg+j+1),
}
unset multiplot

set terminal postscript enhanced font "Helvetica,5" 
set output '| ps2pdf - output_I.pdf'
set tic scale 0
set multiplot layout gn,1 title "Synaptic current" font ",7"  

set datafile separator ","
set grid

do for [i=0:gn-1] {
	plot for [j=0:npg-1] "if.dat" u 1:(column(i*npg+j+2+gn*npg)) w l t "N = ".(i*npg+j+1),
}
unset multiplot
