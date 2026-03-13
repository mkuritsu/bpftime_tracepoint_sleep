build: build-bpf build-victim build-agent

generate:
    cmake -B build -G Ninja -DENABLE_LLVM_SHARED=YES .

build-agent:
    cmake --build build

build-bpf:
    clang -O2 -g -target bpf -D__TARGET_ARCH_x86 -c write_trace.bpf.c -I/usr/include/$(uname -m)-linux-gnu -I . -o write_trace.bpf.o
    bpftool gen skeleton write_trace.bpf.o > write_trace.skel.h
    clang -O2 write_trace.c -o write_trace -lbpf

build-victim:
    clang victim.c -o victim
