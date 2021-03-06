- `make build` generates `libsalty.a` and `libsalty-asm.a` for the
  `thumbv7em-none-eabihf` target (i.e., Cortex-M4F, also works for Cortex-M33)

- `make prepare-example build-example` creates an example binary,
  which can be run on QEMU (need version >=4)

- the signature is correct, as evidenced by setting a breakpoint,
  however I can't seem to C and make the example nicer. PRs welcome! ^^

```
(gdb) p/x signature
$4 = {0xec, 0x97, 0x27, 0x40, 0x7, 0xe7, 0x8, 0xc6, 0xd1, 0xee, 0xd6, 0x1, 0x9f, 0x5d, 0xf, 0xcb, 0xe1, 0x8a,
  0x67, 0x70, 0x8d, 0x17, 0x92, 0x4b, 0x95, 0xdb, 0x7e, 0x35, 0xcc, 0xaa, 0x6, 0x3a, 0xb8, 0x64, 0x8c, 0x9b,
  0xf5, 0x48, 0xb0, 0x9, 0x90, 0x6f, 0xa1, 0x31, 0x9, 0xf, 0xfe, 0x85, 0xa1, 0x7e, 0x89, 0x99, 0xb8, 0xc4, 0x2c,
  0x97, 0x32, 0xf9, 0xa6, 0x44, 0x2a, 0x17, 0xbc, 0x9}
```

#### LICENSE

<sup>The example is based on [libopencm3-template](https://github.com/libopencm3/libopencm3-template),
which was released into the public domain.</sup>
