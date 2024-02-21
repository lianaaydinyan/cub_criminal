#include <stdio.h>
#include <stdlib.h> // for dynamic memory allocation
#include "../cub3d.h"


// Function to initialize a vector
void initVector(Vector *vec, size_t initialCapacity) {
    vec->data = (unsigned int*)malloc(initialCapacity * sizeof(unsigned int)); // Allocate memory
    if (vec->data == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    vec->size = 0; // Initialize size to 0
    vec->capacity = initialCapacity; // Initialize capacity
}

// Function to add an element to the vector
void pushBack(Vector *vec, unsigned int value) {
    if (vec->size >= vec->capacity) {
        // If the vector is full, resize it
        vec->capacity *= 2; // Double the capacity
        vec->data = (unsigned int*)realloc(vec->data, vec->capacity * sizeof(unsigned int)); // Reallocate memory
        if (vec->data == NULL) {
            fprintf(stderr, "Memory reallocation failed.\n");
            exit(EXIT_FAILURE);
        }
    }
    // Add the new element to the end of the vector
    vec->data[vec->size++] = value;
}

// Function to free the memory allocated for the vector
void freeVector(Vector *vec) {
    free(vec->data); // Free the memory
    vec->data = NULL; // Set the pointer to NULL
    vec->size = vec->capacity = 0; // Reset size and capacity
}

    // Example usage: add elements to t
