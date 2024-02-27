#pragma once
#include "stdafx.h"
#include <vector>
#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L)
#include <optional>
#endif
#include <stdint.h>
#include <cstring>
#include <tuple>
using namespace std;

#define dllg /* tag */

#if defined(WIN32)
#define dllx extern "C" __declspec(dllexport)
#elif defined(GNUC)
#define dllx extern "C" __attribute__ ((visibility("default"))) 
#else
#define dllx extern "C"
#endif

#ifdef _WINDEF_
typedef HWND GAME_HWND;
#endif

struct gml_buffer {
private:
	uint8_t* _data;
	int32_t _size;
	int32_t _tell;
public:
	gml_buffer() : _data(nullptr), _tell(0), _size(0) {}
	gml_buffer(uint8_t* data, int32_t size, int32_t tell) : _data(data), _size(size), _tell(tell) {}

	inline uint8_t* data() { return _data; }
	inline int32_t tell() { return _tell; }
	inline int32_t size() { return _size; }
};

class gml_istream {
	uint8_t* pos;
	uint8_t* start;
public:
	gml_istream(void* origin) : pos((uint8_t*)origin), start((uint8_t*)origin) {}

	template<class T> T read() {
		static_assert(std::is_trivially_copyable_v<T>, "T must be trivially copyable to be read");
		T result{};
		std::memcpy(&result, pos, sizeof(T));
		pos += sizeof(T);
		return result;
	}

	char* read_string() {
		char* r = (char*)pos;
		while (*pos != 0) pos++;
		pos++;
		return r;
	}

	template<class T> std::vector<T> read_vector() {
		static_assert(std::is_trivially_copyable_v<T>, "T must be trivially copyable to be read");
		auto n = read<uint32_t>();
		std::vector<T> vec(n);
		std::memcpy(vec.data(), pos, sizeof(T) * n);
		pos += sizeof(T) * n;
		return vec;
	}

	gml_buffer read_gml_buffer() {
		auto _data = (uint8_t*)read<int64_t>();
		auto _size = read<int32_t>();
		auto _tell = read<int32_t>();
		return gml_buffer(_data, _size, _tell);
	}

	#pragma region Tuples
	#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L)
	template<typename... Args>
	std::tuple<Args...> read_tuple() {
		std::tuple<Args...> tup;
		std::apply([this](auto&&... arg) {
			((
				arg = this->read<std::remove_reference_t<decltype(arg)>>()
				), ...);
			}, tup);
		return tup;
	}

	template<class T> optional<T> read_optional() {
		if (read<bool>()) {
			return read<T>;
		} else return {};
	}
	#else
	template<class A, class B> std::tuple<A, B> read_tuple() {
		A a = read<A>();
		B b = read<B>();
		return std::tuple<A, B>(a, b);
	}

	template<class A, class B, class C> std::tuple<A, B, C> read_tuple() {
		A a = read<A>();
		B b = read<B>();
		C c = read<C>();
		return std::tuple<A, B, C>(a, b, c);
	}

	template<class A, class B, class C, class D> std::tuple<A, B, C, D> read_tuple() {
		A a = read<A>();
		B b = read<B>();
		C c = read<C>();
		D d = read<d>();
		return std::tuple<A, B, C, D>(a, b, c, d);
	}
	#endif
};

class gml_ostream {
	uint8_t* pos;
	uint8_t* start;
public:
	gml_ostream(void* origin) : pos((uint8_t*)origin), start((uint8_t*)origin) {}

	template<class T> void write(T val) {
		static_assert(std::is_trivially_copyable_v<T>, "T must be trivially copyable to be write");
		memcpy(pos, &val, sizeof(T));
		pos += sizeof(T);
	}

	void write_string(const char* s) {
		for (int i = 0; s[i] != 0; i++) write<char>(s[i]);
		write<char>(0);
	}

	template<class T> void write_vector(std::vector<T>& vec) {
		static_assert(std::is_trivially_copyable_v<T>, "T must be trivially copyable to be write");
		auto n = vec.size();
		write<uint32_t>(n);
		memcpy(pos, vec.data(), n * sizeof(T));
		pos += n * sizeof(T);
	}

	#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L)
	template<typename... Args>
	void write_tuple(std::tuple<Args...> tup) {
		std::apply([this](auto&&... arg) {
			(this->write(arg), ...);
			}, tup);
	}

	template<class T> void write_optional(optional<T>& val) {
		auto hasValue = val.has_value();
		write<bool>(hasValue);
		if (hasValue) write<T>(val.value());
	}
	#else
	template<class A, class B> void write_tuple(std::tuple<A, B>& tup) {
		write<A>(std::get<0>(tup));
		write<B>(std::get<1>(tup));
	}
	template<class A, class B, class C> void write_tuple(std::tuple<A, B, C>& tup) {
		write<A>(std::get<0>(tup));
		write<B>(std::get<1>(tup));
		write<C>(std::get<2>(tup));
	}
	template<class A, class B, class C, class D> void write_tuple(std::tuple<A, B, C, D>& tup) {
		write<A>(std::get<0>(tup));
		write<B>(std::get<1>(tup));
		write<C>(std::get<2>(tup));
		write<D>(std::get<3>(tup));
	}
	#endif
};
//{{NO_DEPENDENCIES}}
// Microsoft Visual C++ generated include file.
// Used by Arduino.rc

// Next default values for new objects
// 
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NEXT_RESOURCE_VALUE        101
#define _APS_NEXT_COMMAND_VALUE         40001
#define _APS_NEXT_CONTROL_VALUE         1001
#define _APS_NEXT_SYMED_VALUE           101
#endif
#endif
//Serial Class from http://playground.arduino.cc/Interfacing/CPPWindows

#ifndef SERIALCLASS_H_INCLUDED
#define SERIALCLASS_H_INCLUDED

#define ARDUINO_WAIT_TIME 2000

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

class Serial
{
private:
    //Serial comm handler
    HANDLE hSerial;
    //Connection status
    bool connected;
    //Get various information about the connection
    COMSTAT status;
    //Keep track of last error
    DWORD errors;

public:
    Serial() {};
    //Initialize Serial communication with the given COM port
    void Init(char* portName, unsigned long baud);
    //Close the connection
    ~Serial();
    //Read data in a buffer, if nbChar is greater than the
    //maximum number of bytes available, it will return only the
    //bytes available. The function return -1 when nothing could
    //be read, the number of bytes actually read.
    int ReadData(char* buffer, unsigned int nbChar);
    //Writes data from a buffer through the Serial connection
    //return true on success.
    bool WriteData(char* buffer, unsigned int nbChar);
    //Check if we are actually connected
    bool IsConnected();


};

#endif // SERIALCLASS_H_INCLUDED
// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#ifdef _WINDOWS
	#include "targetver.h"
	
	#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
	#include <windows.h>
#endif

#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L)
#define tiny_cpp17
#endif

#if defined(WIN32)
#define dllx extern "C" __declspec(dllexport)
#elif defined(GNUC)
#define dllx extern "C" __attribute__ ((visibility("default"))) 
#else
#define dllx extern "C"
#endif

#define _trace // requires user32.lib;Kernel32.lib

#ifdef TINY // common things to implement
#define tiny_memset
#define tiny_memcpy
#define tiny_malloc
//#define tiny_dtoui3
#endif

#ifdef _trace
static constexpr char trace_prefix[] = "[Arduino] ";
#ifdef _WINDOWS
void trace(const char* format, ...);
#else
#define trace(...) { printf("%s", trace_prefix); printf(__VA_ARGS__); printf("\n"); fflush(stdout); }
#endif
#endif

#pragma region typed memory helpers
template<typename T> T* malloc_arr(size_t count) {
	return (T*)malloc(sizeof(T) * count);
}
template<typename T> T* realloc_arr(T* arr, size_t count) {
	return (T*)realloc(arr, sizeof(T) * count);
}
template<typename T> T* memcpy_arr(T* dst, const T* src, size_t count) {
	return (T*)memcpy(dst, src, sizeof(T) * count);
}
#pragma endregion

#include "tiny_string.h"
#include "tiny_optional.h"
#include "gml_ext.h"

// TODO: reference additional headers your program requires here
#pragma once

// Including SDKDDKVer.h defines the highest available Windows platform.

// If you wish to build your application for a previous Windows platform, include WinSDKVer.h and
// set the _WIN32_WINNT macro to the platform you wish to support before including SDKDDKVer.h.

#include <SDKDDKVer.h>
#pragma once
#include "stdafx.h"

template<typename T> class tiny_array {
	T* _data;
	size_t _size;
	size_t _capacity;

	bool add_impl(T value) {
		if (_size >= _capacity) {
			auto new_capacity = _capacity * 2;
			auto new_data = realloc_arr(_data, _capacity);
			if (new_data == nullptr) {
				trace("Failed to reallocate %u bytes in tiny_array::add", sizeof(T) * new_capacity);
				return false;
			}
			for (size_t i = _capacity; i < new_capacity; i++) new_data[i] = {};
			_data = new_data;
			_capacity = new_capacity;
		}
		_data[_size++] = value;
		return true;
	}
public:
	tiny_array() { }
	tiny_array(size_t capacity) { init(capacity); }
	inline void init(size_t capacity = 4) {
		if (capacity < 1) capacity = 1;
		_size = 0;
		_capacity = capacity;
		_data = malloc_arr<T>(capacity);
	}
	inline void free() {
		if (_data) {
			::free(_data);
			_data = nullptr;
		}
	}

	size_t size() { return _size; }
	size_t capacity() { return _capacity; }
	T* data() { return _data; }

	bool resize(size_t newsize, T value = {}) {
		if (newsize > _capacity) {
			auto new_data = realloc_arr(_data, newsize);
			if (new_data == nullptr) {
				trace("Failed to reallocate %u bytes in tiny_array::resize", sizeof(T) * newsize);
				return false;
			}
			_data = new_data;
			_capacity = newsize;
		}
		for (size_t i = _size; i < newsize; i++) _data[i] = value;
		for (size_t i = _size; --i >= newsize;) _data[i] = value;
		_size = newsize;
		return true;
	}

	#ifdef tiny_cpp17
	template<class... Args>
	inline bool add(Args... values) {
		return (add_impl(values) && ...);
	}
	#else
	inline void add(T value) {
		add_impl(value);
	}
	#endif

	bool remove(size_t index, size_t count = 1) {
		size_t end = index + count;
		if (end < _size) memcpy_arr(_data + start, _data + end, _size - end);
		_size -= end - index;
		return true;
	}

	bool set(T* values, size_t count) {
		if (!resize(count)) return false;
		memcpy_arr(_data, values, count);
		return true;
	}
	template<size_t count> inline bool set(T(&values)[count]) {
		return set(values, count);
	}

	T operator[] (size_t index) const { return _data[index]; }
	T& operator[] (size_t index) { return _data[index]; }
};#pragma once
#define tiny_optional_h

template<typename T> class tiny_optional {
	T _value;
	bool _has_value;
public:
	tiny_optional() : _has_value(false) {
		_value = {};
	};
	tiny_optional(T value) : _value(value), _has_value(true) {}

	void reset() {
		_value = {};
		_has_value = false;
	}

	T value() { return _value; }
	bool has_value() { return _has_value; }

	constexpr void operator = (T value) {
		_value = value;
		_has_value = true;
	}
	constexpr const T* operator->() { return &_value; }
	constexpr const T* operator*() { return &_value; }
};
#pragma once
#include "stdafx.h"
#include <stdint.h>

template<typename C> class tiny_string_t {
	C* _data = nullptr;
	size_t _size = 0;
	size_t _capacity = 0;
public:
	tiny_string_t() {}
	inline void init(size_t capacity = 32) {
		_data = malloc_arr<C>(capacity);
		_size = 0;
		_capacity = capacity;
	}
	inline void init(const C* val) {
		init(4);
		set(val);
	}

	/// Returns current size, in characters (not including final NUL)
	inline size_t size() { return _size; }
	inline void setSize(size_t size) { _size = size; }

	inline bool empty() {
		return _size == 0;
	}
	inline C* c_str() {
		return _data;
	}
	inline C* prepare(size_t capacity) {
		if (_capacity < capacity) {
			auto new_data = realloc_arr(_data, capacity);
			if (new_data == nullptr) {
				trace("Failed to reallocate %u bytes in tiny_string::prepare", sizeof(C) * capacity);
				return nullptr;
			}
			_data = new_data;
			_capacity = capacity;
		}
		return _data;
	}
	inline const C* set(const C* value, size_t len = SIZE_MAX) {
		if (len == SIZE_MAX) {
			const C* iter = value;
			len = 1;
			while (*iter) { iter++; len++; }
		}
		C* result = prepare(len);
		memcpy_arr(result, value, len);
		_size = len - 1;
		return result;
	}
	//
	inline void operator=(const C* value) { set(value); }
	template<size_t size> inline void operator =(const C(&value)[size]) { set(value, size); }
};
struct tiny_string : public tiny_string_t<char> {
public:
	inline char* conv(const wchar_t* wstr) {
		auto size = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
		auto str = prepare(size);
		WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, size, NULL, NULL);
		setSize(size - 1);
		return str;
	}

	inline void operator=(const char* value) { set(value); }
	template<size_t size> inline void operator =(const char(&value)[size]) { set(value, size); }
};
struct tiny_wstring : public tiny_string_t<wchar_t> {
public:
	inline wchar_t* conv(const char* str) {
		auto size = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
		auto wstr = prepare(size);
		MultiByteToWideChar(CP_UTF8, 0, str, -1, wstr, size);
		setSize(size - 1);
		return wstr;
	}

	inline void operator=(const wchar_t* value) { set(value); }
	template<size_t size> inline void operator =(const wchar_t(&value)[size]) { set(value, size); }
};/// @author YellowAfterlife

#include "stdafx.h"

#include "SerialClass.h"
#include "tiny_array.h"
#include <vector>

static tiny_array<Serial*> arduinos;
static tiny_string result;
static tiny_array<char> result_acc;

#define clamp(val, vMin, vMax) (val < vMin ? vMin : (val > vMax ? vMax : val))

///Creates a new serial connection and returns the index in the vector or -1 if the connection failed.
dllx double arduino_create(char* com, double baud)
{
    Serial* SP = malloc_arr<Serial>(1);
    SP->Init(com, baud);
    if (SP->IsConnected()) {
        arduinos.add(SP);
        return arduinos.size() - 1;
    } else {
        free(SP);
    }
    return -1;
}

///Checks if the arduino is connected, returns 1 for true, 0 for false, and -1 if the arduino does not exist.
dllx double arduino_connected(double index)
{
    if (index < arduinos.size() && index >= 0) {
        Serial* SP = arduinos[index];
        if (SP->IsConnected())
            return 1;
        else
            return 0;
    }
    return -1;
}

#pragma region read
///Reads data from the arduino, returns the data on success or an empty string on failure.
dllx char* arduino_read(double index, double length)
{
    if (index < arduinos.size() && index >= 0) {
        Serial* SP = arduinos[index];
        if (SP->IsConnected()) {
            char* data = result.prepare(length + 1);
            data[(size_t)length] = 0;
            int bytes = SP->ReadData(data, length);
            if (bytes < 0) {
                return ""; //No data returned
            }
            return data; //Success
        }
        return ""; //Not connected
    }
    return ""; //Arduino does not exist
}

///Reads data until a delimiter, returns the data on success or an empty string on failure.
dllx char* arduino_read_to(double index, char* delim_str)
{
    if (index < arduinos.size() && index >= 0) {
        Serial* SP = arduinos[index];
        if (SP->IsConnected()) {
            char data[1]{};
            int bytes = SP->ReadData(data, 1);
            result_acc.resize(0);
            auto delim = (uint8_t)delim_str[0];
            while (data[0] != delim) {
                if (bytes < 0) {
                    return ""; //No data returned
                } else {
                    result_acc.add(data[0]);
                }
                bytes = SP->ReadData(data, 1);
            }
            result_acc.add(0);
            return result_acc.data(); //Success
        }
        return ""; //Not connected
    }
    return ""; //Arduino does not exist
}

///Reads data until a new line, returns the data on success or an empty string on failure.
dllx char* arduino_read_line(double index)
{
    char delim[] = "\n";
    return arduino_read_to(index, delim);
}

dllg tiny_optional<const char*> arduino_read_to_new(double index, double delim_u8) {
    if (index < arduinos.size() && index >= 0) {
        Serial* SP = arduinos[index];
        if (SP->IsConnected()) {
            uint8_t data[1]{};
            int bytes = SP->ReadData((char*)data, 1);
            result_acc.resize(0);
            auto delim = (uint8_t)delim_u8;
            while (data[0] != delim) {
                if (bytes < 0) return {}; //No data returned
                result_acc.add(data[0]);
                bytes = SP->ReadData((char*)data, 1);
            }
            result_acc.add(0);
            return result_acc.data(); //Success
        }
        return {}; //Not connected
    }
    return {}; //Arduino does not exist
}

/// Reads until an `\n`
dllg tiny_optional<const char*> arduino_read_line_new(double index) {
    return arduino_read_to_new(index, '\n');
}

/// Reads bytes to a buffer, returns number of bytes read (-1, -2 special)
dllg int arduino_read_buffer(double index, gml_buffer buf, int pos, int len) {
    if (index < arduinos.size() && index >= 0) {
        Serial* SP = arduinos[index];
        if (SP->IsConnected()) {
            int buf_size = buf.size();
            int start = clamp(pos, 0, buf_size);
            int till = pos + len;
            till = clamp(till, 0, buf_size);
            int bytes = SP->ReadData((char*)(buf.data() + start), till - start);
            return bytes;
        }
        return -2; //Not connected
    }
    return -1; //Arduino does not exist
}

dllg int arduino_read_buffer_to(double index, gml_buffer buf, int pos, int len, int delim_u8) {
    if (index < arduinos.size() && index >= 0) {
        Serial* SP = arduinos[index];
        if (SP->IsConnected()) {
            int buf_size = buf.size();
            int start = clamp(pos, 0, buf_size);
            int till = pos + len;
            till = clamp(till, 0, buf_size);
            if (start >= till) return 0;
            int curr = start;
            auto out = buf.data();

            uint8_t data[1]{};
            int bytes = SP->ReadData((char*)data, 1);
            while (data[0] != delim_u8) {
                if (bytes < 0) break;
                out[curr++] = data[0];
                if (curr >= till) break;
                bytes = SP->ReadData((char*)data, 1);
            }
            return curr - start;
        }
        return -2; //Not connected
    }
    return -1; //Arduino does not exist
}

/// Reads a NUL-terminated string
dllg tiny_optional<const char*> arduino_read_string(double index) {
    return arduino_read_to_new(index, 0);
}

dllg tiny_optional<const char*> arduino_read_text(double index, double length) {
    if (index < arduinos.size() && index >= 0) {
        Serial* SP = arduinos[index];
        if (SP->IsConnected()) {
            char* data = result.prepare(length + 1);
            int bytes = SP->ReadData(data, length);
            if (bytes < 0) return {}; //No data returned
            data[bytes] = 0;
            return data; //Success
        }
        return {}; //Not connected
    }
    return {}; //Arduino does not exist
}

static bool arduino_read_impl(double index, void* out, uint32_t len) {
    if (index < arduinos.size() && index >= 0) {
        Serial* SP = arduinos[index];
        if (SP->IsConnected()) {
            int bytes = SP->ReadData((char*)out, len);
            return bytes >= 0;
        }
        return false; //Not connected
    }
    return false; //Arduino does not exist
}
template<typename T> static inline bool arduino_read_auto(double index, T& out) {
    return arduino_read_impl(index, &out, sizeof(out));
}

///
dllg tiny_optional<int8_t> arduino_read_s8(double index) {
    int8_t val = {};
    if (arduino_read_auto(index, val)) return val;
    return {};
}
///
dllg tiny_optional<uint8_t> arduino_read_u8(double index) {
    uint8_t val = {};
    if (arduino_read_auto(index, val)) return val;
    return {};
}

///
dllg tiny_optional<int16_t> arduino_read_s16(double index) {
    int16_t val = {};
    if (arduino_read_auto(index, val)) return val;
    return {};
}
///
dllg tiny_optional<uint16_t> arduino_read_u16(double index) {
    uint16_t val = {};
    if (arduino_read_auto(index, val)) return val;
    return {};
}

///
dllg tiny_optional<int32_t> arduino_read_s32(double index) {
    int32_t val = {};
    if (arduino_read_auto(index, val)) return val;
    return {};
}
///
dllg tiny_optional<uint32_t> arduino_read_u32(double index) {
    uint32_t val = {};
    if (arduino_read_auto(index, val)) return val;
    return {};
}

///
dllg tiny_optional<int64_t> arduino_read_s64(double index) {
    int64_t val = {};
    if (arduino_read_auto(index, val)) return val;
    return {};
}

///
dllg tiny_optional<float> arduino_read_f32(double index) {
    float val = {};
    if (arduino_read_auto(index, val)) return val;
    return {};
}

///
dllg tiny_optional<float> arduino_read_f64(double index) {
    double val = {};
    if (arduino_read_auto(index, val)) return val;
    return {};
}

#pragma endregion

#pragma region write

static int arduino_write_impl(double index, const void* data, uint32_t len) {
    if (index < arduinos.size() && index >= 0) {
        Serial* SP = arduinos[index];
        if (SP->IsConnected()) {
            if (SP->WriteData((char*)data, len))
                return 1; //Success
            else
                return 0; //Failure
        }
        return -2; //Not connected
    }
    return -1; //Arduino does not exist
}
template<typename T> static inline int arduino_write_auto(double index, T& value) {
    return arduino_write_impl(index, &value, sizeof(value));
}

///Writes data to the arduino, returns 1 if successful, 0 if failure. and negative on error.
dllx double arduino_write(double index, char* buffer, double length) {
    return arduino_write_impl(index, buffer, length);
}

///
dllx double arduino_write_s8(double index, double value) {
    int8_t val = (int8_t)clamp(value, INT8_MIN, INT8_MAX);
    return arduino_write_auto(index, val);
}
///
dllx double arduino_write_u8(double index, double value) {
    byte val = (byte)clamp(value, 0, UINT8_MAX);
    return arduino_write_auto(index, val);
}

///
dllx double arduino_write_s16(double index, double value) {
    int16_t val = (int16_t)clamp(value, INT16_MIN, INT16_MAX);
    return arduino_write_auto(index, val);
}
///
dllx double arduino_write_u16(double index, double value) {
    uint16_t val = (uint16_t)clamp(value, 0, UINT16_MAX);
    return arduino_write_auto(index, val);
}

///
dllx double arduino_write_s32(double index, double value) {
    int32_t val = (int32_t)clamp(value, INT32_MIN, INT32_MAX);
    return arduino_write_auto(index, val);
}
///
dllx double arduino_write_u32(double index, double value) {
    uint32_t val = (uint32_t)clamp(value, 0, UINT32_MAX);
    return arduino_write_auto(index, val);
}

dllg int arduino_write_s64(double index, int64_t value) {
    int64_t val = clamp(value, INT64_MIN, INT64_MAX);
    return arduino_write_auto(index, val);
}

///
dllx double arduino_write_f32(double index, double value) {
    float val = (float)value;
    return arduino_write_auto(index, val);
}
///
dllx double arduino_write_f64(double index, double value) {
    double val = value;
    return arduino_write_auto(index, val);
}

/// writes a string (NUL-terminated)
dllx double arduino_write_string(double index, const char* string) {
    size_t len = 0;
    while (string[len]) len++;
    return arduino_write_impl(index, string, len + 1);
}

/// writes a string (unterminated)
dllx double arduino_write_text(double index, const char* string) {
    size_t len = 0;
    while (string[len]) len++;
    return arduino_write_impl(index, string, len);
}

dllg int arduino_write_buffer(int index, gml_buffer buf, int pos, int len) {
    int buf_size = buf.size();
    int start = clamp(pos, 0, buf_size);
    int till = pos + len;
    till = clamp(till, 0, buf_size);
    return arduino_write_impl(index, buf.data() + start, till - start);
}

#pragma endregion

///Deletes an arduino keeping all indices intact, returns 1 on success and 0 on failure.
dllx double arduino_delete(double index)
{
    if (index < arduinos.size() && index >= 0) {
        Serial* SP = arduinos[index];
        free(SP);
        arduinos[index] = nullptr;
        return 1;
    }
    return 0;
}

///Destroys all arduinos and frees memory.
dllx double arduino_destroy()
{
    for (int i = 0; i < arduinos.size(); i++) {
        if (arduinos[i] != nullptr) {
            Serial* SP = arduinos[i];
            free(SP);
            arduinos[i] = nullptr;
        }
    }
    arduinos.resize(0);
    return 1;
}

static void init() {
    arduinos.init();
    result.init();
    result_acc.init();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) init();
	return TRUE;
}
#include "gml_ext.h"
extern tiny_optional<const char*> arduino_read_to_new(double index, double delim_u8);
static tiny_optional<const char*> arduino_read_to_new_raw_vec;
dllx double arduino_read_to_new_raw(void* _in_ptr, double _in_ptr_size) {
	gml_istream _in(_in_ptr);
	double _arg_index;
	_arg_index = _in.read<double>();
	double _arg_delim_u8;
	_arg_delim_u8 = _in.read<double>();
	arduino_read_to_new_raw_vec = arduino_read_to_new(_arg_index, _arg_delim_u8);
	return (double)(arduino_read_to_new_raw_vec.has_value() ? 1 + (1 + strlen(arduino_read_to_new_raw_vec.value())) : 1);
}
dllx double arduino_read_to_new_raw_post(void* _out_ptr, double _out_ptr_size) {
	gml_ostream _out(_out_ptr);
	{
		auto& _opt = arduino_read_to_new_raw_vec;
		if (_opt.has_value()) {
			_out.write<bool>(true);
			_out.write_string(_opt.value());
			
		} else _out.write<bool>(false);
		
	}
	return 1;
}

extern tiny_optional<const char*> arduino_read_line_new(double index);
static tiny_optional<const char*> arduino_read_line_new_raw_vec;
dllx double arduino_read_line_new_raw(void* _in_ptr, double _in_ptr_size) {
	gml_istream _in(_in_ptr);
	double _arg_index;
	_arg_index = _in.read<double>();
	arduino_read_line_new_raw_vec = arduino_read_line_new(_arg_index);
	return (double)(arduino_read_line_new_raw_vec.has_value() ? 1 + (1 + strlen(arduino_read_line_new_raw_vec.value())) : 1);
}
dllx double arduino_read_line_new_raw_post(void* _out_ptr, double _out_ptr_size) {
	gml_ostream _out(_out_ptr);
	{
		auto& _opt = arduino_read_line_new_raw_vec;
		if (_opt.has_value()) {
			_out.write<bool>(true);
			_out.write_string(_opt.value());
			
		} else _out.write<bool>(false);
		
	}
	return 1;
}

extern int arduino_read_buffer(double index, gml_buffer buf, int pos, int len);
dllx double arduino_read_buffer_raw(void* _in_ptr, double _in_ptr_size) {
	gml_istream _in(_in_ptr);
	double _arg_index;
	_arg_index = _in.read<double>();
	gml_buffer _arg_buf;
	_arg_buf = _in.read_gml_buffer();
	int _arg_pos;
	_arg_pos = _in.read<int>();
	int _arg_len;
	_arg_len = _in.read<int>();
	return arduino_read_buffer(_arg_index, _arg_buf, _arg_pos, _arg_len);
}

extern int arduino_read_buffer_to(double index, gml_buffer buf, int pos, int len, int delim_u8);
dllx double arduino_read_buffer_to_raw(void* _in_ptr, double _in_ptr_size) {
	gml_istream _in(_in_ptr);
	double _arg_index;
	_arg_index = _in.read<double>();
	gml_buffer _arg_buf;
	_arg_buf = _in.read_gml_buffer();
	int _arg_pos;
	_arg_pos = _in.read<int>();
	int _arg_len;
	_arg_len = _in.read<int>();
	int _arg_delim_u8;
	_arg_delim_u8 = _in.read<int>();
	return arduino_read_buffer_to(_arg_index, _arg_buf, _arg_pos, _arg_len, _arg_delim_u8);
}

extern tiny_optional<const char*> arduino_read_string(double index);
static tiny_optional<const char*> arduino_read_string_raw_vec;
dllx double arduino_read_string_raw(void* _in_ptr, double _in_ptr_size) {
	gml_istream _in(_in_ptr);
	double _arg_index;
	_arg_index = _in.read<double>();
	arduino_read_string_raw_vec = arduino_read_string(_arg_index);
	return (double)(arduino_read_string_raw_vec.has_value() ? 1 + (1 + strlen(arduino_read_string_raw_vec.value())) : 1);
}
dllx double arduino_read_string_raw_post(void* _out_ptr, double _out_ptr_size) {
	gml_ostream _out(_out_ptr);
	{
		auto& _opt = arduino_read_string_raw_vec;
		if (_opt.has_value()) {
			_out.write<bool>(true);
			_out.write_string(_opt.value());
			
		} else _out.write<bool>(false);
		
	}
	return 1;
}

extern tiny_optional<const char*> arduino_read_text(double index, double length);
static tiny_optional<const char*> arduino_read_text_raw_vec;
dllx double arduino_read_text_raw(void* _in_ptr, double _in_ptr_size) {
	gml_istream _in(_in_ptr);
	double _arg_index;
	_arg_index = _in.read<double>();
	double _arg_length;
	_arg_length = _in.read<double>();
	arduino_read_text_raw_vec = arduino_read_text(_arg_index, _arg_length);
	return (double)(arduino_read_text_raw_vec.has_value() ? 1 + (1 + strlen(arduino_read_text_raw_vec.value())) : 1);
}
dllx double arduino_read_text_raw_post(void* _out_ptr, double _out_ptr_size) {
	gml_ostream _out(_out_ptr);
	{
		auto& _opt = arduino_read_text_raw_vec;
		if (_opt.has_value()) {
			_out.write<bool>(true);
			_out.write_string(_opt.value());
			
		} else _out.write<bool>(false);
		
	}
	return 1;
}

extern tiny_optional<int8_t> arduino_read_s8(double index);
dllx double arduino_read_s8_raw(void* _inout_ptr, double _inout_ptr_size) {
	gml_istream _in(_inout_ptr);
	double _arg_index;
	_arg_index = _in.read<double>();
	tiny_optional<int8_t> _ret = arduino_read_s8(_arg_index);
	gml_ostream _out(_inout_ptr);
	{
		auto& _opt = _ret;
		if (_opt.has_value()) {
			_out.write<bool>(true);
			_out.write<int8_t>(_opt.value());
			
		} else _out.write<bool>(false);
		
	}
	return 1;
}

extern tiny_optional<uint8_t> arduino_read_u8(double index);
dllx double arduino_read_u8_raw(void* _inout_ptr, double _inout_ptr_size) {
	gml_istream _in(_inout_ptr);
	double _arg_index;
	_arg_index = _in.read<double>();
	tiny_optional<uint8_t> _ret = arduino_read_u8(_arg_index);
	gml_ostream _out(_inout_ptr);
	{
		auto& _opt = _ret;
		if (_opt.has_value()) {
			_out.write<bool>(true);
			_out.write<uint8_t>(_opt.value());
			
		} else _out.write<bool>(false);
		
	}
	return 1;
}

extern tiny_optional<int16_t> arduino_read_s16(double index);
dllx double arduino_read_s16_raw(void* _inout_ptr, double _inout_ptr_size) {
	gml_istream _in(_inout_ptr);
	double _arg_index;
	_arg_index = _in.read<double>();
	tiny_optional<int16_t> _ret = arduino_read_s16(_arg_index);
	gml_ostream _out(_inout_ptr);
	{
		auto& _opt = _ret;
		if (_opt.has_value()) {
			_out.write<bool>(true);
			_out.write<int16_t>(_opt.value());
			
		} else _out.write<bool>(false);
		
	}
	return 1;
}

extern tiny_optional<uint16_t> arduino_read_u16(double index);
dllx double arduino_read_u16_raw(void* _inout_ptr, double _inout_ptr_size) {
	gml_istream _in(_inout_ptr);
	double _arg_index;
	_arg_index = _in.read<double>();
	tiny_optional<uint16_t> _ret = arduino_read_u16(_arg_index);
	gml_ostream _out(_inout_ptr);
	{
		auto& _opt = _ret;
		if (_opt.has_value()) {
			_out.write<bool>(true);
			_out.write<uint16_t>(_opt.value());
			
		} else _out.write<bool>(false);
		
	}
	return 1;
}

extern tiny_optional<int32_t> arduino_read_s32(double index);
dllx double arduino_read_s32_raw(void* _inout_ptr, double _inout_ptr_size) {
	gml_istream _in(_inout_ptr);
	double _arg_index;
	_arg_index = _in.read<double>();
	tiny_optional<int32_t> _ret = arduino_read_s32(_arg_index);
	gml_ostream _out(_inout_ptr);
	{
		auto& _opt = _ret;
		if (_opt.has_value()) {
			_out.write<bool>(true);
			_out.write<int32_t>(_opt.value());
			
		} else _out.write<bool>(false);
		
	}
	return 1;
}

extern tiny_optional<uint32_t> arduino_read_u32(double index);
dllx double arduino_read_u32_raw(void* _inout_ptr, double _inout_ptr_size) {
	gml_istream _in(_inout_ptr);
	double _arg_index;
	_arg_index = _in.read<double>();
	tiny_optional<uint32_t> _ret = arduino_read_u32(_arg_index);
	gml_ostream _out(_inout_ptr);
	{
		auto& _opt = _ret;
		if (_opt.has_value()) {
			_out.write<bool>(true);
			_out.write<uint32_t>(_opt.value());
			
		} else _out.write<bool>(false);
		
	}
	return 1;
}

extern tiny_optional<int64_t> arduino_read_s64(double index);
dllx double arduino_read_s64_raw(void* _inout_ptr, double _inout_ptr_size) {
	gml_istream _in(_inout_ptr);
	double _arg_index;
	_arg_index = _in.read<double>();
	tiny_optional<int64_t> _ret = arduino_read_s64(_arg_index);
	gml_ostream _out(_inout_ptr);
	{
		auto& _opt = _ret;
		if (_opt.has_value()) {
			_out.write<bool>(true);
			_out.write<int64_t>(_opt.value());
			
		} else _out.write<bool>(false);
		
	}
	return 1;
}

extern tiny_optional<float> arduino_read_f32(double index);
dllx double arduino_read_f32_raw(void* _inout_ptr, double _inout_ptr_size) {
	gml_istream _in(_inout_ptr);
	double _arg_index;
	_arg_index = _in.read<double>();
	tiny_optional<float> _ret = arduino_read_f32(_arg_index);
	gml_ostream _out(_inout_ptr);
	{
		auto& _opt = _ret;
		if (_opt.has_value()) {
			_out.write<bool>(true);
			_out.write<float>(_opt.value());
			
		} else _out.write<bool>(false);
		
	}
	return 1;
}

extern tiny_optional<float> arduino_read_f64(double index);
dllx double arduino_read_f64_raw(void* _inout_ptr, double _inout_ptr_size) {
	gml_istream _in(_inout_ptr);
	double _arg_index;
	_arg_index = _in.read<double>();
	tiny_optional<float> _ret = arduino_read_f64(_arg_index);
	gml_ostream _out(_inout_ptr);
	{
		auto& _opt = _ret;
		if (_opt.has_value()) {
			_out.write<bool>(true);
			_out.write<float>(_opt.value());
			
		} else _out.write<bool>(false);
		
	}
	return 1;
}

extern int arduino_write_s64(double index, int64_t value);
dllx double arduino_write_s64_raw(void* _in_ptr, double _in_ptr_size) {
	gml_istream _in(_in_ptr);
	double _arg_index;
	_arg_index = _in.read<double>();
	int64_t _arg_value;
	_arg_value = _in.read<int64_t>();
	return arduino_write_s64(_arg_index, _arg_value);
}

extern int arduino_write_buffer(int index, gml_buffer buf, int pos, int len);
dllx double arduino_write_buffer_raw(void* _in_ptr, double _in_ptr_size) {
	gml_istream _in(_in_ptr);
	int _arg_index;
	_arg_index = _in.read<int>();
	gml_buffer _arg_buf;
	_arg_buf = _in.read_gml_buffer();
	int _arg_pos;
	_arg_pos = _in.read<int>();
	int _arg_len;
	_arg_len = _in.read<int>();
	return arduino_write_buffer(_arg_index, _arg_buf, _arg_pos, _arg_len);
}

//Serial Class from http://playground.arduino.cc/Interfacing/CPPWindows
#include "stdafx.h"
#include "SerialClass.h"

void Serial::Init(char* portName, unsigned long baud)
{
    //We're not yet connected
    this->connected = false;

    //Try to connect to the given port throuh CreateFile
    this->hSerial = CreateFileA(portName,
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    //Check if the connection was successfull
    if (this->hSerial == INVALID_HANDLE_VALUE)
    {
        //If not success full display an Error
        if (GetLastError() == ERROR_FILE_NOT_FOUND) {

            //Print Error if neccessary
            trace("ERROR: Handle was not attached. Reason: %s not available.\n", portName);

        } else
        {
            trace("ERROR!!!");
        }
    } else
    {
        //If connected we try to set the comm parameters
        DCB dcbSerialParams = { 0 };

        //Try to get the current
        if (!GetCommState(this->hSerial, &dcbSerialParams))
        {
            //If impossible, show an error
            trace("failed to get current serial parameters!");
        } else
        {
            //Define serial connection parameters for the arduino board
            dcbSerialParams.BaudRate = baud;
            dcbSerialParams.ByteSize = 8;
            dcbSerialParams.StopBits = ONESTOPBIT;
            dcbSerialParams.Parity = NOPARITY;
            //Setting the DTR to Control_Enable ensures that the Arduino is properly
            //reset upon establishing a connection
            dcbSerialParams.fDtrControl = DTR_CONTROL_ENABLE;

            //Set the parameters and check for their proper application
            if (!SetCommState(hSerial, &dcbSerialParams))
            {
                trace("ALERT: Could not set Serial Port parameters");
            } else
            {
                //If everything went fine we're connected
                this->connected = true;
                //Flush any remaining characters in the buffers
                PurgeComm(this->hSerial, PURGE_RXCLEAR | PURGE_TXCLEAR);
                //We wait 2s as the arduino board will be reseting
                Sleep(ARDUINO_WAIT_TIME);
            }
        }
    }

}

Serial::~Serial()
{
    //Check if we are connected before trying to disconnect
    if (this->connected)
    {
        //We're no longer connected
        this->connected = false;
        //Close the serial handler
        CloseHandle(this->hSerial);
    }
}

int Serial::ReadData(char* buffer, unsigned int nbChar)
{
    //Number of bytes we'll have read
    DWORD bytesRead;
    //Number of bytes we'll really ask to read
    unsigned int toRead;

    //Use the ClearCommError function to get status info on the Serial port
    ClearCommError(this->hSerial, &this->errors, &this->status);

    //Check if there is something to read
    if (this->status.cbInQue > 0)
    {
        //If there is we check if there is enough data to read the required number
        //of characters, if not we'll read only the available characters to prevent
        //locking of the application.
        if (this->status.cbInQue > nbChar)
        {
            toRead = nbChar;
        } else
        {
            toRead = this->status.cbInQue;
        }

        //Try to read the require number of chars, and return the number of read bytes on success
        if (ReadFile(this->hSerial, buffer, toRead, &bytesRead, NULL) && bytesRead != 0)
        {
            return bytesRead;
        }

    }

    //If nothing has been read, or that an error was detected return -1
    return -1;

}


bool Serial::WriteData(char* buffer, unsigned int nbChar)
{
    DWORD bytesSend;

    //Try to write the buffer on the Serial port
    if (!WriteFile(this->hSerial, (void*)buffer, nbChar, &bytesSend, 0))
    {
        //In case it don't work get comm error and return false
        ClearCommError(this->hSerial, &this->errors, &this->status);

        return false;
    } else
        return true;
}

bool Serial::IsConnected()
{
    //Simply return the connection status
    return this->connected;
}
// stdafx.cpp : source file that includes just the standard includes
// Arduino.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
#include <strsafe.h>
#ifdef tiny_dtoui3
#include <intrin.h>
#endif

#if _WINDOWS
// http://computer-programming-forum.com/7-vc.net/07649664cea3e3d7.htm
extern "C" int _fltused = 0;
#endif

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file
#ifdef _trace
#ifdef _WINDOWS
// https://yal.cc/printf-without-standard-library/
void trace(const char* pszFormat, ...) {
	char buf[1024 + sizeof(trace_prefix)];
	wsprintfA(buf, "%s", trace_prefix);
	va_list argList;
	va_start(argList, pszFormat);
	wvsprintfA(buf + sizeof(trace_prefix) - 1, pszFormat, argList);
	va_end(argList);
	DWORD done;
	auto len = strlen(buf);
	buf[len] = '\n';
	buf[++len] = 0;
	WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), buf, (DWORD)len, &done, NULL);
}
#endif
#endif

#pragma warning(disable: 28251 28252)

#ifdef tiny_memset
#pragma function(memset)
void* __cdecl memset(void* _Dst, _In_ int _Val,_In_ size_t _Size) {
	auto ptr = static_cast<uint8_t*>(_Dst);
	while (_Size) {
		*ptr++ = _Val;
		_Size--;
	}
	return _Dst;
}
#endif

#ifdef tiny_memcpy
#pragma function(memcpy)
void* memcpy(void* _Dst, const void* _Src, size_t _Size) {
	auto src8 = static_cast<const uint64_t*>(_Src);
	auto dst8 = static_cast<uint64_t*>(_Dst);
	for (; _Size > 32; _Size -= 32) {
		*dst8++ = *src8++;
		*dst8++ = *src8++;
		*dst8++ = *src8++;
		*dst8++ = *src8++;
	}
	for (; _Size > 8; _Size -= 8) *dst8++ = *src8++;
	//
	auto src1 = (const uint8_t*)(src8);
	auto dst1 = (uint8_t*)(dst8);
	for (; _Size != 0; _Size--) *dst1++ = *src1++;
	return _Dst;
}
#endif

#ifdef tiny_malloc
void* __cdecl malloc(size_t _Size) {
	return HeapAlloc(GetProcessHeap(), 0, _Size);
}
void* __cdecl realloc(void* _Block, size_t _Size) {
	return HeapReAlloc(GetProcessHeap(), 0, _Block, _Size);
}
void __cdecl free(void* _Block) {
	HeapFree(GetProcessHeap(), 0, _Block);
}
#endif

#ifdef tiny_dtoui3
// https:/stackoverflow.com/a/55011686/5578773
extern "C" unsigned int _dtoui3(const double x) {
	return (unsigned int)_mm_cvttsd_si32(_mm_set_sd(x));
}
#endif

#pragma warning(default: 28251 28252)
