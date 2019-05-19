// Fails for max(a++, b++): a++ or b++ returned.
#define max(a,b) ((a<b)?b:a)

// Better: type checking, no copy/paste behaviour.
inline int max(int a, int b) { return ((a < b) ? b : a); }