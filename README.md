# Opus Septum — exact `R = 7` verifier

Computational supplement for **Opus Septum: Secondary Orders of Discrete Logarithms at Equal-Order Primes** by C. Brice Turner (ORCID: [0009-0008-1836-153X](https://orcid.org/0009-0008-1836-153X)).

## Target definition

For a prime `p` with

```text
ord_p(2) = ord_p(3) = d,
```

let `k mod d` be the unique exponent satisfying

```text
2^k = 3 (mod p).
```

The secondary order is

```text
R_p(2,3) = ord_d(k).
```

This repository verifies the first exact secondary-order-seven example reported in the manuscript.

## First exact `R = 7` example

```text
p = 551,194,727
d = 275,597,363 = 43 * 71 * 90,271
k = 217,192,027
CRT local orders = (7, 7, 1)
ord_p(3/2) = 3,053 = 43 * 71
```

The direct arithmetic checker verifies:

- `p` is prime;
- `ord_p(2) = ord_p(3) = d`;
- `2^k = 3 (mod p)`;
- `ord_d(k) = 7`;
- the local CRT orders are `(7,7,1)`;
- the active displacement order is `3,053`.

## Exhaustive minimality search

The C++ verifier does **not** solve a general discrete logarithm. For every equal-order prime, it constructs the nonidentity seventh roots modulo the common order `d` using prime-power roots plus CRT, then tests each candidate directly against `2^k = 3 (mod p)`.

Retained exhaustive ranges:

```text
p < 200,000,000                         no hit
200,000,000 <= p < 400,000,000          no hit
400,000,000 <= p < 551,194,728          one hit: p = 551,194,727
```

Combined counts through the first hit:

```text
primes checked                 28,904,954
equal-order primes              8,178,941
7-eligible equal-order primes   2,386,472
exact seventh-root candidates  27,534,678
hits                                    1
```

Random-unit expected count through the first hit:

```text
E_7 = 2.27066800220848
```

## Files

- `verify_r7.cpp` — original verifier from `0` to an upper bound.
- `verify_r7_range.cpp` — range-aware exhaustive verifier used to extend the search.
- `verify_r7_expected.cpp` — range verifier that also sums the random-unit expectation.
- `verify_r7_pari.gp` — independent PARI/GP route; source retained, not claimed as executed in the manuscript's verification record.
- `check_first_hit.py` — independent direct arithmetic check using SymPy.
- `*.log` — retained outputs for the reported search/calibration ranges.
- `SHA256SUMS.txt` — SHA-256 hashes of the original verifier bundle.

## Reproduction

### C++ verifier

A C++17 compiler is sufficient.

```bash
g++ -O3 -std=c++17 verify_r7.cpp -o verify_r7
./verify_r7 551194728
```

For reproducible segmented ranges:

```bash
g++ -O3 -std=c++17 verify_r7_range.cpp -o verify_r7_range
./verify_r7_range 200000000 400000000
./verify_r7_range 400000000 551194728
```

To reproduce the random-unit calibration:

```bash
g++ -O3 -std=c++17 verify_r7_expected.cpp -o verify_r7_expected
./verify_r7_expected 5 200000000
./verify_r7_expected 200000000 400000000
./verify_r7_expected 400000000 551194728
```

### Independent arithmetic check

Requires Python 3 and SymPy.

```bash
python3 check_first_hit.py
```

Expected final line:

```text
verified first-hit arithmetic: 551194727 275597363 217192027 (7,7,1) m=3053
```

## Integrity

The principal verifier source has SHA-256

```text
54fe2cc13e188ca4821fa1daeb42af4c0d7eb0a69e7f084d0c4edb92c0e501cb
```

and the original `p < 200,000,000` result log has SHA-256

```text
8dbe6a50a5448d88d31b81d6539d524819c26916f48d4a708773ccbadbf52421
```

See `SHA256SUMS.txt` for all retained bundle hashes.

## Provenance

The mathematical investigation and computational verification were developed interactively by C. Brice Turner with AI assistance. The repository contains explicit source programs and retained outputs so the reported computational claims can be reproduced independently.

## Paper

Hexagon deposit: **pending**. This README can be updated with the permanent paper identifier after publication.
