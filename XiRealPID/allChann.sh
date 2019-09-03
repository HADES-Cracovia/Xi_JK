#!/bin/bash

#evt=5000000
arr=( 010 021 022 023 062 100 )
for i in ${arr[@]}; do
    echo $i
    ./vertex_rec out/pluto_chan_${i}_events_50000_seed_????_1_dst_p4500p.root -d ./ -o ./outputs_ch/output_${i}_all_0515.root &#-e $evt  &
done
