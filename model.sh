#! /bin/bash

if [[ -z $MLINCPP_ROOT ]]; then 
    echo "Please set MLINCPP_ROOT"
    exit 1
fi

dir=$(echo "$@" | tr a-z A-Z) # makes uppercase
model_name_lower=$(echo "$@" | tr A-Z a-z) # makes lowercase

mkdir -p "$MLINCPP_ROOT/$dir/include" "$MLINCPP_ROOT/$dir/src"
touch "$MLINCPP_ROOT/$dir/Makefile"
touch "$MLINCPP_ROOT/$dir/include/$model_name_lower.hpp"
touch "$MLINCPP_ROOT/$dir/src/$model_name_lower.cpp"
