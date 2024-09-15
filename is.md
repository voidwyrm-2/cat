# CAT Instruction Set

Instructions follow the general structure of `[instruction] [src], [dest]`

Comments can be done with `//` or `;`

### Registers

CAT has 64 registers
- `zero`(real: 0): the zero register, always zero, assignments to it are ignored
- `sc`(real: 1): the system call register, what the 'kernel' reads from to know what you want
- `cpr`(real: 2): the register that the `cmp` instruction sets
- `a0-8`(real: 3-10): the argument registers, what the 'kernel' and functions read from as arguments
- `r0-52`(real: 11-63): 

Instructions are 8 bytes long(except `load`, `store` and `adr`, which each are 10 bytes long) and are split into 2 byte segments
example:
`"mov r0, r1" -> 00 01 02 00`

> **Note:** the opcode for each instruction is just it's position in the list, starting from 0(`nop`)

Instruction | Parameters | Description
----------- | ---------- | -----------
`nop` | None | None
`ecall` | None | Makes the 'kernel' do things
`call` | `immediate/label` | `call_stack.push(pc); pc = immediate/label`
`ret` | None | `len(call_stack) == 0 ? exit(1) : pc = call_stack.pop()`
| Memory manipulation instructions |
`load` | `dest, src_address` | `dest = memory[src_address]`
`store` | `dest_address, src` | `memory[dest_address] = src`
`adr` | `dest, address` | `dest = address`
| Stack instructions |
`push` | `src` | `stack.push(src)`
`pop` | `dest` | `len(stack) == 0 ? exit(1) : dest = stack.pop()`
| Branch and comparison instructions |
`cmpeq` | `reg1, reg2` | `cmp = reg1 == reg2 ? 1 : 0`
`cmpne` | `reg1, reg2` | `cmp = reg1 != reg2 ? 1 : 0`
`cmpgt` | `reg1, reg2` | `cmp = reg1 > reg2 ? 1 : 0`
`cmplt` | `reg1, reg2` | `cmp = reg1 < reg2 ? 1 : 0`
`j` | `immediate/label` | `pc = immediate/label`
`jt` | `immediate/label` | `if (cpr) pc = immediate/label`
`jf` | `immediate/label` | `if (!cpr) pc = immediate/label`
| Arithmetic instructions |
`mov` | `src, dest` | `dest = src`
`movi` | `immediate, dest` | `dest = immediate`
`add` | `dest, src1, src2` | `dest = src1 + src2`
`sub` | `dest, src1, src2` | `dest = src1 - src2`
`mul` | `dest, src1, src2` | `dest = src1 * src2`
`div` | `dest, src1, src2` | `dest = int(src1 / src2)`
`and` | `dest, src1, src2` | `dest = src1 & src2`
`or` | `dest, src1, src2` | `dest = src1 | src2`
`xor` | `dest, src1, src2` | `dest = src1 ^ src2`

<!--`` | `` | ``-->

### Directives

- `.aswarn <string>`: normally things like trying to assign the comparision register would error during assembly time, so this directive makes what would normally be an error into a warning that doesn't stop assembly; see the [assemblers readme](./assemblers/readme.md/#errors) for the error IDs
- `.noflag <string>`: like `aswarn`, but neither an error nor a warning is shown
- `.space <bytes>`: creates the given number of 0 bytes in the file compiled file
- `.byte <number>`: creates a single byte with the given value
- `.ascii <string>`: includes the bytes of the given string in the output binary
- `.asciz <string>`: like `ascii`, but zero-terminated
- `.ascin <string>`: like `ascii`, but newline- and zero- terminated

### System Call Codes

> **Note:** the call representation functions are written in Go

```go
0 Exit(code int)
1 Read(input_buffer_address int, input_length int)
2 Write(string_memory_address int, string_length int)
```