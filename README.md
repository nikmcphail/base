## **Counter-Strike: Source x64 Base**

**Created by Nik McPhail**

This is meant to be a sort of fun, do whatever project. 
This code is not going to be good, and I don't really advise anyone to compile it themselves. 
But ,if you want to, the instructions are below to do as you wish.

**Create Build Folder**

```
cmake . -B build -DCMAKE_BUILD_TYPE=Debug/Release -G Ninja -DCMAKE_C_COMPILER=clang-cl -DCMAKE_CXX_COMPILER=clang-cl
```

### !!!Where it says **Debug/Release**, use either option!!!

**Build DLL**

```
ninja -C build
```