#pragma once

template <bool B, typename T>
struct enable_if {};

template <typename T>
struct enable_if <true, T> { typedef T type; };
