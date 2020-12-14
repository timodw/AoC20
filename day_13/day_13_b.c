#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* INPUT_FILE_PATH = "input_13.txt";

int64_t mul_inv(int64_t a, int64_t b)
{
	int64_t b0 = b, t, q;
	int64_t x0 = 0, x1 = 1;
	if (b == 1) return 1;
	while (a > 1) {
		q = a / b;
		t = b, b = a % b, a = t;
		t = x0, x0 = x1 - q * x0, x1 = t;
	}
	if (x1 < 0) x1 += b0;
	return x1;
}
 
int64_t chinese_remainder(int64_t *n, int64_t *a, int64_t len)
{
	int64_t p, i, prod = 1, sum = 0;
 
	for (i = 0; i < len; i++) {
        prod *= n[i];
    }
 
	for (i = 0; i < len; i++) {
		p = prod / n[i];
		sum += a[i] * mul_inv(p, n[i]) * p;
	}
 
	return sum % prod;
}
 

int main() {
    FILE* file = fopen(INPUT_FILE_PATH, "r");
    char buffer[128] = { 0 };

    fgets(buffer, 128, file);

    int64_t x[16] = { 0 };
    int64_t mod[16] = { 0 };

    fgets(buffer, 128, file);
    char* buffer_end = buffer + strlen(buffer) - 1;
    char* str_i = buffer;
    size_t bus_count = 0;
    size_t slot_count = 0;
    while (str_i >= buffer && str_i < buffer_end) {
        if (*str_i != 'x') {
            char* next_comma = strchr(str_i, ',');
            if (next_comma > buffer) *next_comma = '\0';
            uint64_t bus_id = atoll(str_i);
            mod[bus_count] = bus_id;
            if (slot_count % bus_id == 0) {
                x[bus_count] = 0;
            } else {
                x[bus_count] = bus_id - slot_count;
            }
            bus_count++;
            str_i = next_comma + 1;
        } else {
            str_i = strchr(str_i, ',') + 1;
        }
        slot_count++;
    }

    printf("%llu\n", chinese_remainder(mod, x, bus_count));
}