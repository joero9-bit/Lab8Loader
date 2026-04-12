#include <windows.h>
#include <stdio.h>

// Define a function pointer that matches the signature 
// of the malicious function we've been debugging.
typedef void (__stdcall *MaliciousFunc)(int, char**);

int main() {
    // 1. Load the DLL into our process memory
    HMODULE hLib = LoadLibrary("lab8.dll");
    if (hLib == NULL) {
        printf("Error: Could not find lab8.dll\n");
        return 1;
    }

    // 2. Find the entry point. 
    // Malicious DLLs often don't name their exports. 
    // Based on our debugging, the logic starts at offset 0x1000.
    // We calculate the address: Base Address + Offset.
    MaliciousFunc runMalware = (MaliciousFunc)((char*)hLib + 0x1000);

    // 3. Prepare the arguments. 
    // The malware uses strtol on the second argument (argv[1]).
    // We provide "51966" (which is 0xCAFE in decimal).
    char* fake_argv[] = { "loader.exe", "51966", NULL };
    int fake_argc = 2;

    printf("Satisfying gatekeeper... Triggering payload.\n");

    // 4. Fire the function
    // This provides the stable stack and CRT environment it needs.
    runMalware(fake_argc, fake_argv);

    // Clean up (though if the MBR wipe works, you won't get here)
    FreeLibrary(hLib);
    return 0;
}