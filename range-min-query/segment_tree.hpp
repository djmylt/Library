template <class T>
class SegmentTree {
    public:

    SegmentTree(T* a, int n)
    : A(a), nodes(0), count(0), size(n) {
        int h = 0;
        while((1 << h) < size)
            h++;
        // Maximum 2*2^h - 1 nodes
        count = (1 << (h + 1)) - 1;
        nodes = new int[count];

        init(0, 0, size-1);
    }

    int rmq(int i, int j) {
        return query(0, 0, size-1, i, j);
    }

    private:
    T *A;
    int *nodes;
    int count;// No. of nodes
    int size; // Size of the interval

    void init(int idx, int i, int j) {
        if(i == j)
            nodes[idx] = i;
        else {
            int left = 2 * idx + 1, mid = (i + j) / 2;
            init(left, i, mid);
            init(left+1, mid+1, j);
            nodes[idx] = (A[nodes[left]] <= A[nodes[left+1]]) ? nodes[left] : nodes[left+1];
        }
    }

    int query(int idx, int start, int end, int i, int j) {
        if(start > j || end < i)
            return -1;

        if(start >= i && end <= j) {
            return nodes[idx];
        }

        int left = 2 * idx + 1, mid = (start + end) / 2;
        int q1 = query(left, start, mid, i, j);
        int q2 = query(left+1, mid+1, end, i, j);
        if(q1 == -1)
            return q2;
        if(q2 == -1)
            return q1;
        return (A[q1] <= A[q2] ? q1 : q2);
    }
};