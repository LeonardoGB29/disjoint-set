#include <stdio.h>
#include <stdlib.h>

struct dsjSet {
    int *parent;
    int *rank;
    int n;
};

struct dsjSet makeSet(int size) {
    struct dsjSet ds;
    ds.parent = (int*) malloc(size * sizeof(int));
    ds.rank = (int*) malloc(size * sizeof(int));

    for (int i = 0; i < size; i++) {
        ds.parent[i] = i + 1;
        ds.rank[i] = 0;
    }
    return ds;
}

int findParent(dsjSet *ds, int a) {
    if (a != ds->parent[a - 1]) {
        ds->parent[a - 1] = findParent(ds, ds->parent[a - 1]);
    }
    return ds->parent[a - 1];
}

void unionSet(dsjSet *ds, int a, int b) {
    int root_a = findParent(ds, a) - 1;
    int root_b = findParent(ds, b) - 1;
    if (root_a != root_b) {
        if (ds->rank[root_a] < ds->rank[root_b]) {
            ds->parent[root_a] = root_b + 1;
	    ds->rank[root_b] += 1;
        }
        else {
            ds->parent[root_b] = root_a + 1;
            ds->rank[root_a] += 1;
        }
    }
}

void printSet(dsjSet *ds, int size){
    for (int i = 0; i < size; i++){
	int parent = findParent(ds, i+1);
        printf("Node %d: Representative = %d --- Rank = %d\n", i + 1, parent, ds->rank[i]);
    }
}

int main() {
    int size = 10;
    dsjSet ds = makeSet(size);
    
    unionSet(&ds, 1, 3);
    unionSet(&ds, 2, 4);
    unionSet(&ds, 3, 5);
    unionSet(&ds, 4, 6);
    unionSet(&ds, 7, 8);
    unionSet(&ds, 9, 10);
    unionSet(&ds, 5, 7);
    unionSet(&ds, 6, 9);
    unionSet(&ds, 8, 10);

    printSet(&ds, size);

    return 0;
}
