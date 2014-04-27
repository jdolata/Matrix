let j=2
#!/bin/bash
for((i=5; $i<=4096; i=i+j)) ; do
    ./generator $i $i ""$i"x"$i"A.txt"
    ./generator $i $i ""$i"x"$i"B.txt"
    j=$j*4;
done