task:my_ls_file.out my_cat_file.out my_rm_file.out my_mkdir_file.out my_date_file.out
	gcc -o Shell.out Shell.c -no-pie
	make clean
	./Shell.out

my_ls_file.out:Shell.c
	gcc -o ./External/my_ls_file.out ./External/my_ls_file.c

my_cat_file.out:Shell.c
	gcc -o ./External/my_cat_file.out ./External/my_cat_file.c

my_rm_file.out:Shell.c
	gcc -o ./External/my_rm_file.out ./External/my_rm_file.c
	
my_mkdir_file.out:Shell.c
	gcc -o ./External/my_mkdir_file.out ./External/my_mkdir_file.c

my_date_file.out:Shell.c
	gcc -o ./External/my_date_file.out ./External/my_date_file.c


.PHONY: clean
	rm Shell.o
