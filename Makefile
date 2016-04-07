test_mt: test_mt.c mtwist.c
	gcc -O3 -o test_mt test_mt.c mtwist.c -I.
compare_rngs: compare_rngs.c mtwist.c
	gcc -O3 -o compare_rngs compare_rngs.c mtwist.c -I.
