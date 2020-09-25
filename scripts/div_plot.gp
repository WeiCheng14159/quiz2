set title "Division Time Comparison"
set xlabel "# of samples"
set ylabel "Time (cycles)"
set yrange [10:100]
set grid
set terminal png font " Times_New_Roman,12 "
set output "div_comp.png"

plot \
"../div.data" using 1:2 with points title "fast div", \
"../div.data" using 1:3 with points title "normal div" \
