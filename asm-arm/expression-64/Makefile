CC:=/opt/gcc-linaro-7.5.0-2019.12-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-gcc
LINARO_SYSROOT_AARCH64:=/opt/sysroot-glibc-linaro-2.25-2019.12-aarch64-linux-gnu

all: solution

solution: main.c solution.S
	$(CC) -o solution main.c solution.S

test: solution tests/001.dat tests/001.ans
	qemu-aarch64 -L $(LINARO_SYSROOT_AARCH64) ./solution < tests/001.dat > tests/my.ans
	diff tests/my.ans tests/001.ans
