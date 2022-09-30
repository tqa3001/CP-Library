#include <stdlib.h>
#include <stdio.h>

typedef struct {
    unsigned long long number;
    unsigned long long divisors;
} small_max;

static const unsigned long long primes[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47 };
static const unsigned long long primorials[] =
    { 2, 6, 30, 210, 2310, 30030, 510510, 9699690, 223092870, 6469693230,
      200560490130, 7420738134810, 304250263527210, 13082761331670030,
      614889782588491410 };

static const unsigned num_primes = sizeof primorials / sizeof primorials[0];

small_max max_divisors(unsigned long long limit);
small_max best_with(unsigned long long limit, unsigned index, unsigned multiplicity);
void factor(unsigned long long number);

int main(int argc, char *argv[]) {
    unsigned long long limit;
    limit = argc > 1 ? strtoull(argv[1],NULL,0) : 1000000;
    small_max best = max_divisors(limit);
    printf("\nSmallest number not exceeding %llu with most divisors:\n",limit);
    printf("%llu with %llu divisors\n", best.number, best.divisors);
    factor(best.number);
    return 0;
}

small_max max_divisors(unsigned long long limit) {
    small_max result;
    if (limit < 3) {
        result.number = limit;
        result.divisors = limit;
        return result;
    }
    unsigned idx = num_primes;
    small_max best = best_with(limit,0,1);
    printf("Largest power of 2: %llu = 2^%llu\n", best.number, best.divisors-1);
    for(idx = 1; idx < num_primes && primorials[idx] <= limit; ++idx) {
        printf("Using primes to %llu:\n", primes[idx]);
        unsigned long long test = limit, remaining = limit;
        unsigned multiplicity = 0;
        do {
            ++multiplicity;
            test /= primorials[idx];
            remaining /= primes[idx];
            result = best_with(remaining, idx-1, multiplicity);
            for(unsigned i = 0; i < multiplicity; ++i) {
                result.number *= primes[idx];
            }
            result.divisors *= multiplicity + 1;
            if (result.divisors > best.divisors) {
                printf("New largest divisor count: %llu for\n  ", result.divisors); 
                factor(result.number);
                best = result;
            } else if (result.divisors == best.divisors && result.number < best.number) {
                printf("Smaller number with %llu divisors:\n  ", result.divisors); 
                factor(result.number);
                best = result;
            }
        }while(test >= primorials[idx]);
    }
    return best;
}

small_max best_with(unsigned long long limit, unsigned index, unsigned multiplicity) {
    small_max result = {1, 1};
    if (index == 0) {
        while(limit > 1) {
            result.number *= 2;
            ++result.divisors;
            limit /= 2;
        }
        return result;
    }
    small_max best = {0,0};
    unsigned long long test = limit, remaining = limit;
    --multiplicity;
    for(unsigned i = 0; i < multiplicity; ++i) {
        test /= primorials[index];
        remaining /= primes[index];
    }
    do {
        ++multiplicity;
        test /= primorials[index];
        remaining /= primes[index];
        result = best_with(remaining, index-1, multiplicity);
        for(unsigned i = 0; i < multiplicity; ++i) {
            result.number *= primes[index];
        }
        result.divisors *= multiplicity + 1;
        if (result.divisors > best.divisors) {
            best = result;
        } else if (result.divisors == best.divisors && result.number < best.number) {
            best = result;
        }
    }while(test >= primorials[index]);
    return best;
}

void factor(unsigned long long number) {
    unsigned long long num = number;
    unsigned idx, mult;
    printf("%llu =", number);
    for(idx = 0; num > 1 && idx < num_primes; ++idx) {
        mult = 0;
        while(num % primes[idx] == 0) {
            num /= primes[idx];
            ++mult;
        }
        printf("%s %llu ^ %u", idx ? " *" : "", primes[idx], mult);
    }
    printf("\n");
}
