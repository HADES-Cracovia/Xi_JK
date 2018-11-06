#!/bin/bash

evt=50000000
arr=( 090 010 021 022 023 062 100 )
for i in ${arr[@]}; do
    echo $i
    ./vertex_rec out/pluto_chan_${i}_events_50000_seed_????_1_dst_p4500p.root -d ./ -o ./outputs_ch/output_${i}_all5.root -e $evt  &
done
