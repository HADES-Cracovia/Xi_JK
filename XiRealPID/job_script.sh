#!/bin/bash

date

#. /lustre/nyx/hades/user/jkubos/analiza/pp45/profile.sh
#. /lustre/nyx/hades/user/knowakow/HYPERON/Lambda1520/LambdaEpEm/profile.sh
. /u/jkubos/analiza/pp45/profile.sh

echo file=$pattern
echo events=$events
echo odir=$odir

root -b -q

cd /lustre/nyx/hades/user/jkubos/hades/pp45/simAna/xiAna

date

ofile=$(basename $pattern .root)_ana.root
#fname=$(echo $ofile | cut -d '_' -f 3)

#[ ! -d  $odir/$fname ] && mkdir $odir/$fname

echo ./vertex_rec -e 100 $pattern -o $odir/$ofile
time ./vertex_rec -e 100 $pattern -o $odir/$ofile
