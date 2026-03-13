#include "signal.h"
#include "write_trace.skel.h"
#include <stdio.h>
#include <unistd.h>

static int libbpf_print_fn(enum libbpf_print_level level, const char* format, va_list args) {
    return vfprintf(stderr, format, args);
}

static volatile bool exiting = false;
static void sig_handler(int sig) {
    exiting = true;
}

int main() {
    libbpf_set_print(libbpf_print_fn);
    signal(SIGINT, sig_handler);
    signal(SIGTERM, sig_handler);

    struct write_trace_bpf* skel = write_trace_bpf__open_and_load();
    if (!skel) {
        fprintf(stderr, "Failed to open/load skeleton\n");
        return 1;
    }

    if (write_trace_bpf__attach(skel)) {
        fprintf(stderr, "Failed to attach\n");
        goto cleanup;
    }

    printf("Program running...\n");
    while (!exiting) {
        sleep(1);
    }

cleanup:
    write_trace_bpf__destroy(skel);
    return 0;
}
