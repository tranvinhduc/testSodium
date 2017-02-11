# Copy from 'Cryptography in NaCl'

P = 2 ** 255 - 19
A = 486662

def expmod (b, e, m):
    if e == 0: return 1
    t = expmod (b, e // 2, m) ** 2 % m
    if e & 1: t = (t * b) % m
    return t

def inv (x):
    return expmod (x, P - 2, P)

# Addition and doubling formulas taken
# from Appendix D of "Curve25519:
# New Diffie-Hellman speed records"

def add (xzn, xzm, xzd):       #???
    xn,zn = xzn
    xm,zm = xzm
    xd,zd = xzd
    x = 4 * (xm * xn - zm * zn) ** 2 * zd
    z = 4 * (xm * zn - zm * xn) ** 2 * xd
    return (x % P, z % P)

def double (xzn):              #???
    xn, zn = xzn
    x = (xn ** 2 - zn ** 2) ** 2
    z = 4 * xn * zn * (xn ** 2 + A * xn * zn + zn ** 2)
    return (x % P, z % P)

def curve25519 (n, base):
    one = (base, 1)
    two = double (one)
    # f(m) evaluates to a tuple
    # containing the mth multiple and the
    # (m+1)th multiple of base.
    def f(m):
        if m == 1: return (one, two)
        (pm, pm1) = f(m // 2)
        if (m & 1):
            return (add (pm, pm1, one), double (pm1))
        return (double(pm), add(pm, pm1, one))
    ((x,z), _) = f(n)
    return (x * inv(z)) % P

def unpack(s):
    if len(s) != 32:
        raise ValueError ('Invalid Curve25519 argument')
    return sum(ord(s[i]) << (8*i) for i in range(32))

def pack(n):
    return ''.join ([chr((n >> (8 * i)) & 255) for i in range(32)])

def clamp (n):
    n &= ~7
    n &= ~(128 << 8 * 31)
    n |= 64 << 8 * 31
    return n

def crypto_scalarmult_curve25519 (n, p):
    n = clamp(unpack(n))
    p = unpack(p)
    return pack (curve25519(n,p))

def crypto_scalarmult_curve25519_base (n):
    n = clamp (unpack(n))
    return pack (curve25519(n,9))

## Test 

sk = [ 0x77,0x07,0x6d,0x0a,0x73,0x18,0xa5,0x7d
       ,0x3c,0x16,0xc1,0x72,0x51,0xb2,0x66,0x45
       ,0xdf,0x4c,0x2f,0x87,0xeb,0xc0,0x99,0x2a
       ,0xb1,0x77,0xfb,0xa5,0x1d,0xb9,0x2c,0x2a ]

n=''.join([chr(sk[i]) for i in range(32)])

pk=[ 0x85,0x20,0xf0,0x09,0x89,0x30,0xa7,0x54
    ,0x74,0x8b,0x7d,0xdc,0xb4,0x3e,0xf7,0x5a
    ,0x0d,0xbf,0x3a,0x0d,0x26,0x38,0x1a,0xf4
     ,0xeb,0xa4,0xa9,0x8e,0xaa,0x9b,0x4e,0x6a ]

s=''.join([chr(pk[i]) for i in range(32)])


print (s == crypto_scalarmult_curve25519_base(n))


