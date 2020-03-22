#define MIN(a,b) (((a)<(b)) ? (a) : (b))
#define MAX(a,b) (((a)>(b)) ? (a) : (b))
#define MINIDX(oldidx, i, arr) (((arr[oldidx]) < (arr[i])) ? (oldidx) : (i))
#define MAXIDX(oldidx, i, arr) (((arr[oldidx]) > (arr[i])) ? (oldidx) : (i))
