_print:
    movi 2, cc // set the system call code register to the code for writing(2)
    adr hello, a0 // set the string memory address argument to the address of our string
    movi 15, a1 // set the string length argument to the length of our string(the length is 14 + a newline)
    ecall // tell 'kernel' to do stuff

_terminate:
    movi 2, cc // set the system call code register to the code for exiting(0)
    movi 0, a0 // set the exit code argument to 0(for "everything's ok")
    ecall // tell 'kernel' to do stuff

hello: .ascin "Hello, Catdog!" // the `ascin` directive automatically adds a newline to the end of our string