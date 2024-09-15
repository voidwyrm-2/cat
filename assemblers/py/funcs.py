def number_to_bytes(num: int, amount: int) -> bytearray:
    out: bytearray = bytearray()

    for _ in range(amount):
        if num == 0:
            break;
        elif num <= 0xff:
            out.append(num)
        else:
            out.append(num & 0xff)
        num >>= 8

    out.reverse()
    return out