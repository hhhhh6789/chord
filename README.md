# chord

a simple [cord algorithm](https://en.wikipedia.org/wiki/Chord_(peer-to-peer)) simulator. work in progress. 

```bash
usage: chord <n>
```

n = size of network (log2(n) connections for each peer's routing table).

## build

We use SHA1 hash for the GUIDs, hence you should link with openssl libcrypto to build:

```
clang main.c -I/usr/local/opt/openssl/include -lcrypto
```