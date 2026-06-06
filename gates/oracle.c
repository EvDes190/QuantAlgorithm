#include <string.h>
#include <stdio.h>

#include "oracle.h"

int answer = 0;

void set_answer(int x) {
    answer = x;
}

int get_answer() {
    return answer;
}

void Uf(const int n, double complex amplitudes[n]) {
    amplitudes[get_answer()] *= -1;
}