// clang-format off
#include <vmlinux.h>
#include <bpf/bpf_helpers.h>
#include "ufunc.bpf.h"
// clang-format on

SEC("tracepoint/syscalls/sys_enter_write")
int trace_write(struct trace_event_raw_sys_enter* ctx) {
    bpf_printk("write syscall entered\n");
    UFUNC_CALL_1(101, 2);
    return 0;
}

char _license[] SEC("license") = "GPL";
