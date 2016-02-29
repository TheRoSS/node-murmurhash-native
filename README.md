# node-murmurhash-native

Uses native C++ code from https://github.com/aappleby/smhasher repository to bring MurmurHashes (versions 2 and 3) with correct big numbers to node

Version 2
===
32 bits
---
int murmurHash2(<string|Buffer> data, [int seed]) - the simple implementation

int murmurHash2A(<string|Buffer> data, [int seed]) - the simple implementation w/ Merkle-Damgard-esque construction

int murmurHashAligned2(<string|Buffer> data, [int seed]) - the little-endian aligned-read-only implementation

int murmurHashNeutral2(<string|Buffer> data, [int seed]) - the (slower) endian-neutral implementation

64 bits
---
string murmurHash64A(<string|Buffer> data, [int seed]) - 64-bit hash for 64-bit platforms, returns hex string

string murmurHash64B(<string|Buffer> data, [int seed]) - 64-bit hash for 32-bit platforms, returns hex string

Version 3
===
32 bits
---
int MurmurHash3_x86_32(<string|Buffer> data, [int seed])

128 bits
---
string MurmurHash3_x86_128(<string|Buffer> data, [int seed]) - 128-bit hash for 32-bit platforms, returns hex string

string MurmurHash3_x64_128(<string|Buffer> data, [int seed]) - 128-bit hash for 64-bit platforms, returns hex string

Usage example
===
```js
> var hasher = require("murmurhash-native")
> m.murmurHash3_x64_128("ws2yy")
'9410cb6cee7e741319a92e1b06482e33'
```
