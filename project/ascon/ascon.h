#pragma once

#include <memory.h>

#include "common.h"
#include "byte_arr.h"

extern State state;

/**
 * @note
 * Array inside the returned byte has been calloc'ed. Remember
 * to clean it!
 * 
 * @param tag
 * Tag is a key array. Create it before hand and pass it to args.
 * The function will store the tag in it.
 */
ByteArr asconEncrypt(Key key, Key nonce, ByteArr data,
                     ByteArr plain, Key tag);

/**
 * @note
 * Array inside the returned byte has been calloc'ed. Remember
 * to clean it!
 * 
 * @param tag
 * Tag is a key array. Pass a tag, if it does not match, then
 * null bytes object will be returned.
 */
ByteArr asconDecrypt(Key key, Key nonce, ByteArr data,
                     ByteArr cipher, Key tag);
