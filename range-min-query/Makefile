CC=g++
CFLAGS=-Wall -O3
PROFLAGS=-D PROFILE
TREE=segment_tree.cpp -o segment_tree
TABLE=sparse_table.cpp -o sparse_table

all: segment_tree sparse_table

profile: segment_tree_profile sparse_table_profile

segment_tree:
	$(CC) $(CFLAGS) $(TREE)

sparse_table:
	$(CC) $(CFLAGS) $(TABLE)

segment_tree_profile:
	$(CC) $(CFLAGS) $(PROFLAGS) $(TREE)

sparse_table_profile:
	$(CC) $(CFLAGS) $(PROFLAGS) $(TABLE)

clean:
	rm segment_tree sparse_table
