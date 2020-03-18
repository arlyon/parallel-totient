./run

mkdir -p results
for ((c=256; c>=1; c/=2)) do
  N=$((1+(c-1)/64))
  if [ $N -gt 1 ]; then
    queue="amd-longq"
  else
    queue="amd-shortq"
  fi
  for i in 15000 30000 100000; do
    FILE=results/${c}-${i}.log
    if [ ! -f "$FILE" ]; then
        ./run -b ${FILE} -n ${N} -t ${c} -q ${queue} totient_mpi -p 1 ${i}
    fi
  done
done