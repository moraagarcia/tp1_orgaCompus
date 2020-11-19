unsigned int mcd(unsigned int n1, unsigned int n2) {
    unsigned int n_aux;
    while (n2 != 0) {
        n_aux = n2;
        n2 = n1 % n2;  //n2 = residuo de n1/n2
        n1 = n_aux;  //n1 toma el valor de n2 previo a ser asignado con el residuo
    }
    return n1;
}

unsigned int mcm(unsigned int n1, unsigned int n2) {
    int numerator = n1 * n2;
    unsigned int denominator = mcd(n1, n2);
    return numerator/denominator;
}