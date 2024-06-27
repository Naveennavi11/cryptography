#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define STATE_SIZE 25  // 5x5 matrix
#define LANE_SIZE 8    // Each lane is 64 bits (8 bytes)

typedef struct {
    uint64_t lanes[STATE_SIZE];  // 25 lanes, each 64 bits
} State;

void initialize_state(State *state) {
    memset(state->lanes, 0, STATE_SIZE * sizeof(uint64_t));
}

void absorb(State *state, const uint8_t *block) {
    for (int i = 0; i < STATE_SIZE; i++) {
        state->lanes[i] ^= ((uint64_t *)block)[i];
    }
}

int all_lanes_nonzero(const State *state) {
    for (int i = 0; i < STATE_SIZE; i++) {
        if (state->lanes[i] == 0) {
            return 0;
        }
    }
    return 1;
}

void print_state(const State *state) {
    for (int i = 0; i < STATE_SIZE; i++) {
        printf("Lane %d: 0x%016lx\n", i, state->lanes[i]);
    }
}

int main() {
    State state;
    uint8_t block[STATE_SIZE * LANE_SIZE] = {0};  // 1024 bits block, 128 bytes

    // Initialize block P0 with at least one nonzero bit in each lane
    for (int i = 0; i < STATE_SIZE; i++) {
        block[i * LANE_SIZE] = (i + 1);  // Simplified initialization
    }

    // Initialize state
    initialize_state(&state);

    printf("Initial state:\n");
    print_state(&state);

    // Absorb the first block
    absorb(&state, block);

    printf("\nState after absorbing P0:\n");
    print_state(&state);

    // Determine how long it will take before all lanes are non-zero
    int rounds = 1;  // We have already absorbed one block
    while (!all_lanes_nonzero(&state)) {
        absorb(&state, block);
        rounds++;
    }

    printf("\nTotal rounds to make all lanes non-zero: %d\n", rounds);
    printf("Final state:\n");
    print_state(&state);

    return 0;
}