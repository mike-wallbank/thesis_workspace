#!/bin/bash

filenumber="$1"
thefile=$(samweb list-files "run_number=$filenumber and data_tier sliced")
thepath=$(samweb -e lbne get-file-access-url "$thefile")
thelink=${thepath:29:57}/"$thefile"
ln -s /pnfs/lbne$thelink
