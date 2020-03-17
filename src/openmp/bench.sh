./run

for c in $(seq 64 -2 1); do
  for i in 15000 30000 100000; do
    FILE=results/${c}-${i}.log
    if [ ! -f "$FILE" ]; then
        ./run -b ${FILE} totient_openmp -p -t ${c} 1 ${i}
    fi
  done
done