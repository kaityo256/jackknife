set term png 
set out "test1.png"

set xlabel "1/N"
set ylabel "1/<x^2>"

set key at 0.02, 1.4
p "test1.dat" u (1.0/$1):2 w lp pt 6 t "Simple" \
, "test1.dat" u (1.0/$1):3 w lp pt 7 t "Jackknife" \
, 1 lt 1 lc "black" t "1.0"


set out "test2.png"
set ylabel "<x^4>/<x^2>^2"
set key at 0.02, 2.75
p "test2.dat" u (1.0/$1):2 w lp pt 6 t "Simple" \
, "test2.dat" u (1.0/$1):3 w lp pt 7 t "Jackknife" \
, 3 lt 1 lc "black" t "3.0"

set out "test3.png"
set ylabel "<x^6>/<x^4>/<x^2>"
set yrange [3.5:5.1]
set key at 0.02, 3.8
p "test3.dat" u (1.0/$1):2 w lp pt 6 t "Simple" \
, "test3.dat" u (1.0/$1):3 w lp pt 7 t "Jackknife" \
, 5 lt 1 lc "black" t "5.0"


