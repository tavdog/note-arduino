/*!
 * @file n_cjson_helpers.c
 *
 * Written by Ray Ozzie and Blues Inc. team.
 *
 * Copyright (c) 2019 Blues Inc. MIT License. Use of this source code is
 * governed by licenses granted by the copyright holder including that found in
 * the
 * <a href="https://github.com/blues/note-c/blob/master/LICENSE">LICENSE</a>
 * file.
 *
 */

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "n_lib.h"

//**************************************************************************/
/*!
    @brief  Determine if a field is present in a JSON response object.
    @param   rsp The JSON response object.
    @param   field The field to find.
    @returns boolean. `true` if the field is present.
*/
/**************************************************************************/
bool JIsPresent(J *rsp, const char *field)
{
    if (rsp == NULL) {
        return false;
    }
    return (JGetObjectItem(rsp, field) != NULL);
}

//**************************************************************************/
/*!
    @brief  Return a string from the specified JSON object.
    @param   rsp The JSON response object.
    @param   field The field to return.
    @returns The string response, or an empty string, if not present.
*/
/**************************************************************************/
char *JGetString(J *rsp, const char *field)
{
    if (rsp == NULL) {
        return (char *) c_nullstring;
    }
    J *item = JGetObjectItem(rsp, field);
    if (item == NULL) {
        return (char *) c_nullstring;
    }
    if (!JIsString(item)) {
        return (char *) c_nullstring;
    }
    if (item->valuestring == NULL) {
        return (char *) c_nullstring;
    }
    return item->valuestring;
}

//**************************************************************************/
/*!
    @brief  Return an object from the specified JSON object.
    @param   rsp The JSON response object.
    @param   field The field to return.
    @returns The object found, or NULL, if not present.
*/
/**************************************************************************/
J *JGetObject(J *rsp, const char *field)
{
    if (rsp == NULL) {
        return NULL;
    }
    J *item = JGetObjectItem(rsp, field);
    if (item == NULL) {
        return NULL;
    }
    if (!JIsObject(item)) {
        return NULL;
    }
    return item;
}

//**************************************************************************/
/*!
    @brief  Return the boolean repsentation of an item.
    @param   item The JSON item.
    @returns The boolean value.
*/
/**************************************************************************/
bool JBoolValue(J *item)
{
    if (item == NULL) {
        return false;
    }
    return ((item->type & 0xff) == JTrue);
}

//**************************************************************************/
/*!
    @brief  Return the string repsentation of an item.
    @param   item The JSON item.
    @returns The string value, or empty string, if NULL.
*/
/**************************************************************************/
char *JStringValue(J *item)
{
    if (item == NULL) {
        return "";
    }
    return item->valuestring;
}

//**************************************************************************/
/*!
    @brief  Return the number repsentation of an item.
    @param   item The JSON item.
    @returns The number, or 0.0, if NULL.
*/
/**************************************************************************/
JNUMBER JNumberValue(J *item)
{
    if (item == NULL) {
        return 0.0;
    }
    return item->valuenumber;
}

//**************************************************************************/
/*!
    @brief  Return a number from the specified JSON object.
    @param   rsp The JSON response object.
    @param   field The field to return.
    @returns The number found, or 0.0, if not present.
*/
/**************************************************************************/
JNUMBER JGetNumber(J *rsp, const char *field)
{
    if (rsp == NULL) {
        return 0.0;
    }
    J *item = JGetObjectItem(rsp, field);
    if (item == NULL) {
        return 0.0;
    }
    if (!JIsNumber(item)) {
        return 0.0;
    }
    return JNumberValue(item);
}

//**************************************************************************/
/*!
    @brief  Return the integer repsentation of an item.
    @param   item The JSON item.
    @returns The number, or 0, if NULL.
*/
/**************************************************************************/
long int JIntValue(J *item)
{
    if (item == NULL) {
        return 0;
    }
    return item->valueint;
}

//**************************************************************************/
/*!
    @brief  Return an integer from the specified JSON object.
    @param   rsp The JSON response object.
    @param   field The field to return.
    @returns The int found, or 0, if not present.
*/
/**************************************************************************/
long int JGetInt(J *rsp, const char *field)
{
    if (rsp == NULL) {
        return 0;
    }
    J *item = JGetObjectItem(rsp, field);
    if (item == NULL) {
        return 0;
    }
    if (!JIsNumber(item)) {
        return 0;
    }
    return JIntValue(item);
}

//**************************************************************************/
/*!
    @brief  Return a boolean from the specified JSON object.
    @param   rsp The JSON response object.
    @param   field The field to return.
    @returns The boolean value, or false if not present.
*/
/**************************************************************************/
bool JGetBool(J *rsp, const char *field)
{
    if (rsp == NULL) {
        return false;
    }
    J *item = JGetObjectItem(rsp, field);
    if (item == NULL) {
        return false;
    }
    if (!JIsBool(item)) {
        return false;
    }
    return JIsTrue(item);
}

//**************************************************************************/
/*!
    @brief  Determine if a JSON object is valid and if a field is not present,
            or null.
    @param   rsp The JSON response object.
    @param   field The field to return.
    @returns bool. False if the field is not present, or NULL.
*/
/**************************************************************************/
bool JIsNullString(J *rsp, const char *field)
{
    if (rsp == NULL) {
        return false;
    }
    J *item = JGetObjectItem(rsp, field);
    if (item == NULL) {
        return true;
    }
    if (!JIsString(item)) {
        return false;
    }
    if (item->valuestring == NULL) {
        return true;
    }
    if (item->valuestring[0] == '\0') {
        return true;
    }
    return false;
}

//**************************************************************************/
/*!
    @brief  Determine if a field exists, is a string and matches a
            provided value.
    @param   rsp The JSON response object.
    @param   field The field to check.
    @param   teststr The string to test against the returned value.
    @returns bol. Whether the fields match exactly.
*/
/**************************************************************************/
bool JIsExactString(J *rsp, const char *field, const char *teststr)
{
    if (rsp == NULL) {
        return false;
    }
    J *item = JGetObjectItem(rsp, field);
    if (item == NULL) {
        return false;
    }
    if (!JIsString(item)) {
        return false;
    }
    if (item->valuestring == NULL) {
        return false;
    }
    if (strlen(teststr) == 0) {
        return false;
    }
    return (strcmp(item->valuestring, teststr) == 0);
}

//**************************************************************************/
/*!
    @brief  Determine if a field exists, is a string and contains a provided
            value.
    @param   rsp The JSON response object.
    @param   field The field to check.
    @param   substr The string to test against the returned value.
    @returns bol. Whether the provided string is found within the field.
*/
/**************************************************************************/
bool JContainsString(J *rsp, const char *field, const char *substr)
{
    if (rsp == NULL) {
        return false;
    }
    J *item = JGetObjectItem(rsp, field);
    if (item == NULL) {
        return false;
    }
    if (!JIsString(item)) {
        return false;
    }
    if (item->valuestring == NULL) {
        return false;
    }
    if (strlen(substr) == 0) {
        return false;
    }
    return (strstr(item->valuestring, substr) != NULL);
}

//**************************************************************************/
/*!
    @brief  Add a binary to a Note as a Base64-encoded string.
    @param   req The JSON object to which the field should be added
    @param   fieldName The field to set.
    @param   binaryData The binary data to set.
    @param   binaryDataLen The length of the binary string.
    @returns bool. Whether the binary field was set.
*/
/**************************************************************************/
bool JAddBinaryToObject(J *req, const char *fieldName, const void *binaryData, uint32_t binaryDataLen)
{
    unsigned stringDataLen = JB64EncodeLen(binaryDataLen);
    char *stringData = (char *) _Malloc(stringDataLen);
    if (stringData == NULL) {
        return false;
    }
    JB64Encode(stringData, binaryData, binaryDataLen);
    J *stringItem = JCreateStringReference(stringData);
    if (stringItem == NULL) {
        _Free(stringData);
        return false;
    }
    JAddItemToObject(req, fieldName, stringItem);
    return true;
}

//**************************************************************************/
/*!
    @brief  Get binary from an object that is expected to be a Base64-encoded string.
    @param   rsp The JSON object containing the  field.
    @param   fieldName The field to get data from.
    @param   retBinaryData The binary data object allocated.  (Use standard "free" method to free it.)
    @param   retBinaryDataLen The length of the binary data.
    @returns bool. Whether the binary data was allocated and returned.
*/
/**************************************************************************/
bool JGetBinaryFromObject(J *rsp, const char *fieldName, uint8_t **retBinaryData, uint32_t *retBinaryDataLen)
{

    char *payload = JGetString(rsp, fieldName);
    if (payload[0] == '\0') {
        return false;
    }

    // Allocate a buffer for the payload
    char *p = (char *) _Malloc(JB64DecodeLen(payload));
    if (p == NULL) {
		return false;
	}
    uint32_t actualLen = JB64Decode(p, payload);

	// Return the binary to the caller
	*retBinaryData = (uint8_t *)p;
	*retBinaryDataLen = actualLen;
	return true;

}

//**************************************************************************/
/*!
    @brief  Get the object name.
    @param   item The JSON object.
    @returns The number, or and empty string, if NULL.
*/
/**************************************************************************/
const char *JGetItemName(const J * item)
{
    if (item->string == NULL) {
        return "";
    }
    return item->string;
}

//**************************************************************************/
/*!
    @brief  Convert an integer to text
    @param   an integer
    @returns The number converted to text, null-terminated.
    @note The buffer midt be large enough because no bounds checking is done.
*/
/**************************************************************************/
void JItoA(long int n, char *s)
{
    char c;
    long int i, j, sign;
    if ((sign = n) < 0) {
        n = -n;
    }
    i = 0;
    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
    if (sign < 0) {
        s[i++] = '-';
    }
    s[i] = '\0';
    for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

//**************************************************************************/
/*!
    @brief  Convert text to an integer
    @param   a null-terminated text buffer
    @returns An integer, or 0 if invalid
*/
/**************************************************************************/
long int JAtoI(const char *string)
{
    long int result = 0;
    unsigned int digit;
    int sign;
    while (*string == ' ') {
        string += 1;
    }
    if (*string == '-') {
        sign = 1;
        string += 1;
    } else {
        sign = 0;
        if (*string == '+') {
            string += 1;
        }
    }
    for ( ; ; string += 1) {
        digit = *string - '0';
        if (digit > 9) {
            break;
        }
        result = (10*result) + digit;
    }
    if (sign) {
        result = -result;
    }
    return result;
}

//**************************************************************************/
/*!
    @brief  Convert a buffer/len to a null-terminated c-string
    @param   a buffer containing text with a counted length
    @returns A c-string (NULL if invalid) that must be freed with JFree()
*/
/**************************************************************************/
char *JAllocString(uint8_t *buffer, uint32_t len)
{
    char *buf = _Malloc(len+1);
    if (buf == NULL) {
        return false;
    }
    if (len > 0) {
        memcpy(buf, buffer, len);
    }
    buf[len] = '\0';
    return buf;
}

//**************************************************************************/
/*!
    @brief  Return the type of an item, as a string
    @param   item The JSON item.
    @returns The type
*/
/**************************************************************************/
const char *JType(J *item)
{
    if (item == NULL) {
        return "";
    }
    switch (item->type & 0xff) {
    case JTrue:
    case JFalse:
        return "bool";
    case JNULL:
        return "null";
    case JNumber:
        return "number";
    case JRaw:
    case JString:
        return "string";
    case JObject:
        return "object";
    case JArray:
        return "array";
    }
    return "invalid";
}
