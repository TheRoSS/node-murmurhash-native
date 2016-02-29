#include <v8.h>
#include <node.h>
#include <node_buffer.h>
#include <string>
#include <sstream>
#include <MurmurHash2.h>
#include <MurmurHash3.h>

namespace murmurhash {

using v8::Exception;
using v8::HandleScope;
using v8::FunctionCallbackInfo;
using v8::Function;
using v8::Isolate;
using v8::Handle;
using v8::Local;
using v8::Integer;
using v8::Object;
using v8::String;
using v8::Number;
using v8::Value;

std::string empty("");

std::string getDataFromArgs(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  
  if (args.Length() < 1 || args.Length() > 2) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
    return empty;
  }
  
  if (args.Length() == 2 && !args[1]->IsUint32()) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong argument type, integer seed expected")));
    return empty;
  }
  
  if (args[0]->IsString()) {
    String::Utf8Value str(args[0]->ToString());
    return std::string(*str);
  }

  if (node::Buffer::HasInstance(args[0])) {
    Local<Object> bufferObj = args[0]->ToObject();
    char*         bufferData   = node::Buffer::Data(bufferObj);
    size_t        bufferLength = node::Buffer::Length(bufferObj);
    return std::string(bufferData, bufferLength);
  }
  
  isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong data type, string or buffer expected")));
  return empty;
}

// MurmurHash2
// ============================================================================
void wrapMurmurHash2(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  HandleScope scope(isolate);
  std::string s = getDataFromArgs(args);
  if (!s.size()) {
    return;
  }
  
  uint32_t seed = args[1]->Uint32Value();
  uint32_t hash = MurmurHash2(s.data(), s.size(), seed);
  
  Local<Number> num = Number::New(isolate, hash);
  
  args.GetReturnValue().Set(num);
}

// MurmurHash2A
// ============================================================================
void wrapMurmurHash2A(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  HandleScope scope(isolate);
  std::string s = getDataFromArgs(args);
  if (!s.size()) {
    return;
  }
  
  uint32_t seed = args[1]->Uint32Value();
  uint32_t hash = MurmurHash2A(s.data(), s.size(), seed);
  
  Local<Number> num = Number::New(isolate, hash);
  
  args.GetReturnValue().Set(num);
}

// MurmurHashNeutral2
// ============================================================================
void wrapMurmurHashNeutral2(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  HandleScope scope(isolate);
  std::string s = getDataFromArgs(args);
  if (!s.size()) {
    return;
  }
  
  uint32_t seed = args[1]->Uint32Value();
  uint32_t hash = MurmurHashNeutral2(s.data(), s.size(), seed);
  
  Local<Number> num = Number::New(isolate, hash);
  
  args.GetReturnValue().Set(num);
}

// MurmurHashAligned2
// ============================================================================
void wrapMurmurHashAligned2(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  HandleScope scope(isolate);
  std::string s = getDataFromArgs(args);
  if (!s.size()) {
    return;
  }
  
  uint32_t seed = args[1]->Uint32Value();
  uint32_t hash = MurmurHashAligned2(s.data(), s.size(), seed);
  
  Local<Number> num = Number::New(isolate, hash);
  
  args.GetReturnValue().Set(num);
}

// MurmurHash64A
// ============================================================================
void wrapMurmurHash64A(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  HandleScope scope(isolate);
  std::string s = getDataFromArgs(args);
  if (!s.size()) {
    return;
  }
  
  uint32_t seed = args[1]->NumberValue();
  uint64_t hash = MurmurHash64A(s.data(), s.size(), seed);
  
  std::stringstream sstream;
  sstream << std::hex << hash;
  
  Local<String> result = String::NewFromUtf8(isolate, sstream.str().c_str());
  args.GetReturnValue().Set(result);
}

// MurmurHash64B
// ============================================================================
void wrapMurmurHash64B(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  HandleScope scope(isolate);
  std::string s = getDataFromArgs(args);
  if (!s.size()) {
    return;
  }
  
  uint32_t seed = args[1]->NumberValue();
  uint64_t hash = MurmurHash64B(s.data(), s.size(), seed);
  
  std::stringstream sstream;
  sstream << std::hex << hash;
  
  Local<String> result = String::NewFromUtf8(isolate, sstream.str().c_str());
  args.GetReturnValue().Set(result);
}

// MurmurHash3_x86_32
// ============================================================================
void wrapMurmurHash3_x86_32(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  HandleScope scope(isolate);
  std::string s = getDataFromArgs(args);
  if (!s.size()) {
    return;
  }
  
  uint32_t seed = args[1]->Uint32Value();
  uint32_t hash;
  MurmurHash3_x86_32(s.data(), s.size(), seed, &hash);
  
  Local<Number> num = Number::New(isolate, hash);
  
  args.GetReturnValue().Set(num);
}

// MurmurHash3_x86_128
// ============================================================================
void wrapMurmurHash3_x86_128(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  HandleScope scope(isolate);
  std::string s = getDataFromArgs(args);
  if (!s.size()) {
    return;
  }
  
  uint32_t seed = args[1]->Uint32Value();
  uint32_t hash[4];
  MurmurHash3_x86_128(s.data(), s.size(), seed, hash);
  
  std::stringstream sstream;
  sstream << std::hex << hash[3] << hash[2] << hash[1] << hash[0];
  
  Local<String> result = String::NewFromUtf8(isolate, sstream.str().c_str());
  args.GetReturnValue().Set(result);
}

// MurmurHash3_x64_128
// ============================================================================
void wrapMurmurHash3_x64_128(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  HandleScope scope(isolate);
  std::string s = getDataFromArgs(args);
  if (!s.size()) {
    return;
  }
  
  uint32_t seed = args[1]->Uint32Value();
  uint64_t hash[2];
  MurmurHash3_x64_128(s.data(), s.size(), seed, hash);
  
  std::stringstream sstream;
  sstream << std::hex << hash[1] << hash[0];
  
  Local<String> result = String::NewFromUtf8(isolate, sstream.str().c_str());
  args.GetReturnValue().Set(result);
}

// init
// ============================================================================
void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "murmurHash2", wrapMurmurHash2);
  NODE_SET_METHOD(exports, "murmurHash2A", wrapMurmurHash2A);
  NODE_SET_METHOD(exports, "murmurHashNeutral2", wrapMurmurHashNeutral2);
  NODE_SET_METHOD(exports, "murmurHashAligned2", wrapMurmurHashAligned2);
  NODE_SET_METHOD(exports, "murmurHash64A", wrapMurmurHash64A);
  NODE_SET_METHOD(exports, "murmurHash64B", wrapMurmurHash64B);
  
  NODE_SET_METHOD(exports, "murmurHash3_x86_32", wrapMurmurHash3_x86_32);
  NODE_SET_METHOD(exports, "murmurHash3_x86_128", wrapMurmurHash3_x86_128);
  NODE_SET_METHOD(exports, "murmurHash3_x64_128", wrapMurmurHash3_x64_128);
}

NODE_MODULE(murmurhash, init)

}   // namespace murmurhash

