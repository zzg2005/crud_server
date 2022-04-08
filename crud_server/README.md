# crud_server.cc: a simple CRUD REST API server
a simple CRUD REST API server based on Pistache  and  nlohmann JSON library.
* Pistache: https://github.com/oktal/pistache
* nlohmann JSON: https://github.com/nlohmann/json

## How to Build and Test:

### Requirement 1 : Download, build and install Pistache:
```
  git clone https://github.com/oktal/pistache.git
  cd pistache
  git submodule update --init
  mkdir build
  cd build
  cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ..
  make
  sudo make install
```  
###  Requirement 2: nlohmann JSON library
* A simple way, just copy 'nlohmann/json.hpp' (from nlohmann JSON library /single_include/)  to C language header file directory of the system such as '/usr/local/include'

OR
* Download, build and install Nlohmann JSON library:

```
  git clone https://github.com/nlohmann/json.git
  cd json
  mkdir build
  cd build
  cmake ..
  make
  sudo make install
```
  
### Build use 'g++' or 'c++'
```
g++ -std=c++14 crud_server.cc -o crud_server -lpistache -lpthread
```

### Test
```
curl -X POST http://127.0.0.1:9080/demo
curl -X GET http://127.0.0.1:9080/demo
curl -X POST http://127.0.0.1:9080/demo
curl -X DELETE http://127.0.0.1:9080/demo
curl -X GET http://127.0.0.1:9080/demo
curl -X PUT  -d '{"name" : "aaa", "age" : 30 }' http://127.0.0.1:9080/demo
```
