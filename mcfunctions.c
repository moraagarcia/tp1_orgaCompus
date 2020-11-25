unsigned int mcd(unsigned int n1, unsigned int n2){
    if (n2 == 0) return n1;
    return mcd(n2, n1%n2);
}

unsigned int mcm(unsigned int n1, unsigned int n2) {
    int numerator = n1 * n2;
    unsigned int denominator = mcd(n1, n2);
    return numerator/denominator;
}