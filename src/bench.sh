./run

  for i in 15000 30000 100000; do
    FILE=results/${c}-${i}.log
    if [ ! -f "$FILE" ]; then
        ./run -b ${FILE} totient -p 1 ${i}
    fi
  done