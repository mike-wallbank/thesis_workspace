#!/bin/bash

filenumber="$1"
thefile=$(samweb list-files "run_number=$filenumber and data_tier raw")
thepath=$(samweb -e lbne get-file-access-url "$thefile")
thelink=${thepath:29:54}/"$thefile"
ln -s /pnfs/lbne$thelink
