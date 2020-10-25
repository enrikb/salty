#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "salty.h"

extern void  initialise_monitor_handles(void);

// NB: The way to do semihosting in C-land seems
// to be to link `newlib`, call `initialise_monitor_handles`,
// and then `printf`: [1]
//
// [1]: https://bgamari.github.io/posts/2014-10-31-semihosting.html

int main(void) {

    initialise_monitor_handles();

    uint8_t seed[32] = {
        0x35, 0xb3, 0x07, 0x76, 0x17, 0x9a, 0x78, 0x58,
        0x34, 0xf0, 0x4c, 0x82, 0x88, 0x59, 0x5d, 0xf4,
        0xac, 0xa1, 0x0b, 0x33, 0xaa, 0x12, 0x10, 0xad,
        0xec, 0x3e, 0x82, 0x47, 0x25, 0x3e, 0x6c, 0x65,
    };

    uint8_t public_key[32];

    const uint8_t data [] = "salty!";

    uint8_t signature[64];

    /* __asm__("BKPT"); */

    salty_public_key(&seed, &public_key);
    salty_sign(&seed, data, strlen((const char*) data), &signature);
    salty_Error err = salty_verify(&public_key, data, strlen((const char*) data), &signature);

    /* assert(1); */

    printf("signature generated, verify returns: %d\n", err);

    /*
     * non-contiguous two part message example
     * the message is treated as one logical message!
     */
    const uint8_t part1 [] = "salt";
    const uint8_t part2 [] = "y!";

    memset(signature, 0, sizeof(signature));
    salty_sign2(&seed, part1, strlen((const char*) part1), part2, strlen((const char*) part2), &signature);
    err = salty_verify(&public_key, data, strlen((const char*) data), &signature);

    printf("signature generated, verify returns: %d\n", err);

    /* let keypair = salty::Keypair::from(&seed); */

    /* let data = "salty!".as_bytes(); */

    /* let R_expected = [ */
    /*     0xec, 0x97, 0x27, 0x40, 0x07, 0xe7, 0x08, 0xc6, */
    /*     0xd1, 0xee, 0xd6, 0x01, 0x9f, 0x5d, 0x0f, 0xcb, */
    /*     0xe1, 0x8a, 0x67, 0x70, 0x8d, 0x17, 0x92, 0x4b, */
    /*     0x95, 0xdb, 0x7e, 0x35, 0xcc, 0xaa, 0x06, 0x3a, */
    /* ]; */

    /* let S_expected = [ */
    /*     0xb8, 0x64, 0x8c, 0x9b, 0xf5, 0x48, 0xb0, 0x09, */
    /*     0x90, 0x6f, 0xa1, 0x31, 0x09, 0x0f, 0xfe, 0x85, */
    /*     0xa1, 0x7e, 0x89, 0x99, 0xb8, 0xc4, 0x2c, 0x97, */
    /*     0x32, 0xf9, 0xa6, 0x44, 0x2a, 0x17, 0xbc, 0x09, */
    /* ]; */

	/*
	 * If running under QEMU, _exit() will also stop QEMU returning err.
	 * If running on hardware, libopencm3 should handle correctly.
	 */
	_exit(err);
}
