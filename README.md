This program is a **Custom DLL Loader** designed for malware analysis, serving as a controlled execution harness for a malicious library (`lab8.dll`).

### How it Works

* **Library Injection:** It utilizes the Windows `LoadLibrary` API to map the specified DLL into the address space of the current process.
* **Manual Entry Point Resolution:** Because malware authors often hide export names, this loader manually calculates the function entry point using a hardcoded memory offset (`0x1000`) from the library's base address.
* **Environment Mimicry:** The loader constructs a stable environment for the malware to execute by preparing a "fake" argument vector (`fake_argv`), satisfying the requirements of the malware's internal `strtol` logic which expects specific command-line inputs.
* **Execution Trigger:** It casts the resolved memory address to a function pointer (`MaliciousFunc`) and executes the payload, allowing analysts to observe behavior in a safe, controlled manner.

### Pedagogical Utility

This script acts as a "Gatekeeper" that provides the minimal conditions (stable stack, argument passing) necessary to trigger malicious code that would otherwise refuse to run in a standard debugger or environment.

### Implementation Details

* **Language:** C
* **Target OS:** Windows
* **Key API Used:** `LoadLibrary()`

Would you like me to write a `README.md` for this loader as well to help your students understand the setup requirements for their lab environment?
