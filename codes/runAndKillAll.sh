#!/bin/bash

fibonacci/fibonacci1 &
pids[0]=$!
fibonacci/fibonacci2 &
pids[1]=$!
fibonacci/fibonacci3 &
pids[2]=$!
fibonacci/fibonacci4 &
pids[3]=$!
fibonacci/fibonacci5 &
pids[4]=$!
factorization/factorization1 &
pids[5]=$!
factorization/factorization2 &
pids[6]=$!
factorization/factorization3 &
pids[7]=$!
factorization/factorization4 &
pids[8]=$!
factorization/factorization5 &
pids[9]=$!
echo Programs will run for 10 minutes
sleep 600
echo Enough with the running lets kill them all
kill -2 "${pids[@]}"
