CC=clang
CFLAGS=-Wall -O3 -march=native -I../utils
DAY=14

day_$(DAY)_a: day_$(DAY)_a.c ../utils/hash_map.c
	$(CC) $(CFLAGS) -o day_$(DAY)_a day_$(DAY)_a.c ../utils/hash_map.c

day_$(DAY)_b: day_$(DAY)_a.c ../utils/hash_map.c
	$(CC) $(CFLAGS) -o day_$(DAY)_b day_$(DAY)_b.c ../utils/hash_map.c