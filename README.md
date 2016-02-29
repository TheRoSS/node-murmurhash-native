# node-murmurhash-native

Uses native C++ code from https://github.com/aappleby/smhasher repository to bring MurmurHashes (versions 2 and 3) with correct big numbers to node

Version 2
===
32 bits
---
int **murmurHash2**(string|Buffer _data_, [int _seed_]) - the simple implementation

int **murmurHash2A**(string|Buffer _data_, [int _seed_]) - the simple implementation w/ Merkle-Damgard-esque construction

int **murmurHashAligned2**(string|Buffer _data_, [int _seed_]) - the little-endian aligned-read-only implementation

int **murmurHashNeutral2**(string|Buffer _data_, [int _seed_]) - the (slower) endian-neutral implementation

64 bits
---
string **murmurHash64A**(string|Buffer _data_, [int _seed_]) - 64-bit hash for 64-bit platforms, returns hex string

string **murmurHash64B**(string|Buffer _data_, [int _seed_]) - 64-bit hash for 32-bit platforms, returns hex string

Version 3
===
32 bits
---
int **murmurHash3_x86_32**(string|Buffer _data_, [int _seed_])

128 bits
---
string **murmurHash3_x86_128**(string|Buffer _data_, [int _seed_]) - 128-bit hash for 32-bit platforms, returns hex string

string **murmurHash3_x64_128**(string|Buffer _data_, [int _seed_]) - 128-bit hash for 64-bit platforms, returns hex string

Usage example
===
```js
> var hasher = require("murmurhash-native")
> hasher.murmurHash3_x64_128("ws2yy")
'9410cb6cee7e741319a92e1b06482e33'
> hasher.murmurHash2("ws2yy")
2490241110
```

Installation from Git
===
```
git clone --recursive 'https://github.com/TheRoSS/node-murmurhash-native.git'
cd node-murmurhash-native
npm install
```

Note the *--recursive* option. It loads native MurmurHash repository with C++ modules
