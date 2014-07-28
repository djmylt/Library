CC=g++
CFLAGS=-Wall -O3

all: segment_tree sparse_table

profile: segment_tree_profile sparse_table_profile

segment_tree:
	$(CC) $(CFLAGS) segment_tree.cpp -o segment_tree

sparse_table:
	$(CC) $(CFLAGS) sparse_table.cpp -o sparse_table

segment_tree_profile:
	$(CC) $(CFLAGS) segment_tree_profile.cpp -o segment_tree

sparse_table_profile:
	$(CC) $(CFLAGS) sparse_table_profile.cpp -o sparse_table

clean:
	rm segment_tree sparse_table
