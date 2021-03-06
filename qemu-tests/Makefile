main-test:
	cargo run --bin qemu-tests --release

../tests/eddsa_test.json:
	$(MAKE) -C .. tests/eddsa_test.json

../tests/x25519_test.json:
	$(MAKE) -C .. tests/x25519_test.json

test: ../tests/eddsa_test.json ../tests/x25519_test.json
	@echo "\nTesting Haase field implementation, debug build\n"
	time cargo run --bin qemu-tests
	@echo "\nTesting Haase field implementation, release build\n"
	time cargo run --bin qemu-tests --release
	@echo "\nRunnine project Wycheproof EDDSA tests, release build\n"
	time cargo run --bin eddsa_verify --release
	@echo "\nRunnine project Wycheproof X25519 tests, release build\n"
	time cargo run --bin x25519_comp --release

size: build
	arm-none-eabi-size $(KERNEL)

build:
	cargo build

build-release:
	cargo build --release

size-release: build-release
	arm-none-eabi-size $(KERNEL_RELEASE)
	arm-none-eabi-size $(KERNEL_RELEASE) -A

run:
	cargo run

run-release:
	# cargo size --features $(IMPL) --release
	arm-none-eabi-size $(KERNEL_RELEASE)
	cargo run --release

SEMIHOSTING = -semihosting-config enable=on,target=native
KERNEL = target/thumbv8m.main-none-eabi/debug/qemu-tests
KERNEL_RELEASE = target/thumbv8m.main-none-eabi/release/qemu-tests
CPU = cortex-m33
MACHINE = musca-b1
QEMU = ../../qemu/arm-softmmu/qemu-system-arm
# QEMU_DEBUG = -d in_asm,int,exec,cpu,guest_errors,unimp

qemu: #build
	$(QEMU) -cpu $(CPU) -machine $(MACHINE) -nographic $(SEMIHOSTING) -kernel $(KERNEL) $(QEMU_DEBUG)

qemu-gdb: #build
	# Exit with <Ctrl-A X>
	$(QEMU) -cpu $(CPU) -machine $(MACHINE) -nographic $(SEMIHOSTING) -kernel $(KERNEL) -gdb tcp::1234 -S $(QEMU_DEBUG)

# assume gcc-arm-none-eabi-8-2019-q3-update
gdb:
	arm-none-eabi-gdb -q -x qemu.gdb target/thumbv8m.main-none-eabi/debug/qemu-tests

