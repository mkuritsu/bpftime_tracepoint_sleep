# Build

First follow instructions in the bpftime documentation to install dependencies and build/install the bpftime binary
[https://eunomia.dev/bpftime/documents/build-and-test/](https://eunomia.dev/bpftime/documents/build-and-test/)

```bash
just genereate && just build
```

# Run

First run the daemon

```bash
sudo LD_PRELOAD=~/.bpftime/libbpftime-syscall-server.so ./write_trace
```

Then run the victim program

```bash
sudo AGENT_SO=~/.bpftime/libbpftime-agent.so LD_PRELOAD=~/.bpftime/libbpftime-agent-transformer.so ./victim
```

**Note:** The code present in `agent.cpp` is a small addition to [https://github.com/eunomia-bpf/bpftime/blob/master/runtime/agent/agent.cpp](https://github.com/eunomia-bpf/bpftime/blob/master/runtime/agent/agent.cpp), simply registering the ufunc for sleep
