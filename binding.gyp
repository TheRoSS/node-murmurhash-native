{
    "targets": [
        {
            "target_name": "murmurhash",
            "sources": [
                "src/murmurhash.cc", 
                "deps/smhasher/src/MurmurHash2.cpp", 
                "deps/smhasher/src/MurmurHash3.cpp"
            ],
            "include_dirs": [
                "deps/smhasher/src"
            ]
        }
    ]
}

